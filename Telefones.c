#include <stdio.h>
#include <string.h>

//estruct de pessoa cadastrada

typedef struct dados{
    char NOME[50];
    char TELEFONE[13];
    unsigned int deslocamento;
    unsigned int linha;
};



//escopo de funcoes
void limparScanf();
struct dados cadastrarTelefone();
struct dados consultarTelefone();
void alterarTelefone(unsigned int deslocamento);
void excluirTelefone(char NOME[], char TELEFONE[]);

int main()
{
    //MENU
    FILE *telefonesTXT = fopen("Telefones.txt", "a");//Cria o arquivo telefones caso não exista.
    struct dados dados;
    fclose(telefonesTXT);
    int o=0;
    while(o!=5){
        printf("Menu de Opcoes\n"
                "\n1 - Cadastrar Telefone"
                "\n2 - Consultar Telefone"
                "\n3 - Alterar Telefone"
                "\n4 - Excluir Telefone"
                "\n5 - Encerrar Programa");

        printf("\n\nEscolha uma opcao: ");
        o = 6;
        scanf("%i",&o);

        switch(o){
            case 1:
                printf("\nCadastrando dados\n\n");
                dados = cadastrarTelefone();
                printf("\nDados cadastrados!\n%s %s\n\n\n",dados.NOME,dados.TELEFONE);
                break;
            case 2:
                printf("\n\nConsultando dados\n");
                dados = consultarTelefone();
                if(dados.deslocamento!=0) printf("\nTelefone encontrado com sucesso, %s %s.\n\n\n",dados.NOME,dados.TELEFONE);
                break;
            case 3:
                printf("\n\nAlterando dados\n");
                dados = consultarTelefone();
                if (dados.deslocamento!=0) alterarTelefone(dados.deslocamento);
                break;
            case 4:
                printf("\n\nExcluindo dados\n");
                dados = consultarTelefone();
                if (dados.deslocamento!=0) excluirTelefone(dados.NOME,dados.TELEFONE);
                break;
            case 5:
                break;
            default:
                printf("\nOpcao invalida\n");
                limparScanf();//Limpa o scanf para consumir um possivel char, caso a entrada seja um char.
                break;
        }
    }
    return 0;
}

void limparScanf(){
    char ch = 0;
    do{
        ch = getchar();
    }while(ch != EOF && ch != '\n');
}

struct dados cadastrarTelefone(){
    FILE *telefonesTXT = fopen("Telefones.txt", "a");
    struct dados dados;
    char vazio=0;
    do{
        if(vazio==1) printf("“\nNome ou telefone em branco, digite novamente\n"); //depois de rodar novamente o loop, sinaliza o que o nome ou o telefone estavam vazios
        printf("Nome: ");
        scanf(" %49[^\n]",dados.NOME);
        printf("Telefone: ");
        scanf(" %12[^\n],",dados.TELEFONE);
        vazio=1; 
    }while(dados.NOME[0] == 0 || dados.TELEFONE[0] == 0); //se o primeiro valor de nome ou telefone forem vazios, roda o loop de novo.
    fprintf(telefonesTXT,"%s,%s\n",dados.NOME,dados.TELEFONE);
    fclose(telefonesTXT);
    return dados;
}

struct dados consultarTelefone(){
    FILE *telefonesTXT = fopen("Telefones.txt", "r");
    struct dados dados;
    dados.deslocamento = 0, dados.linha = 0;
    char ENTRADA[50], ch = 0;
    int tamanho;
    printf("\nNome: ");
    scanf(" %49[^\n]",ENTRADA);
    dados.NOME[0] = 0;
    while (1){//pega o nome todo e vai comparando com o nome de entrada
        ch = getc(telefonesTXT);
        tamanho = strlen(dados.NOME);
        if(ch==10){ //se ch for new line, então recomeça o vetor nome, 
            tamanho = 0;
            ch = getc(telefonesTXT); //vai para o proximo ch, para tirar o nw de ch.
            dados.deslocamento+=2;//adiciona 1 para o char newline e um para o cr
            dados.linha++;
        }
        dados.NOME[tamanho] = ch;
        dados.NOME[tamanho+1] = 0;
        dados.deslocamento++;
        if(strcmp(dados.NOME, ENTRADA) == 0)break;//se o nome de entrada bater com algum nome do arquivo quebra o loop
        if(ch==EOF){
            printf("\nTelefone de %s nao cadastrado\n\n\n",ENTRADA);
            dados.deslocamento = 0;
            fclose(telefonesTXT);
            return dados;
        };
        tamanho = (tamanho==49) ? 0: tamanho;
    }
    dados.deslocamento++;
    ch = getc(telefonesTXT); //pega a ,
    tamanho=0;
    dados.TELEFONE[0] = 0;
    while (tamanho<11){
        ch =getc(telefonesTXT);
        tamanho = strlen(dados.TELEFONE);
        dados.TELEFONE[tamanho] = ch;
        dados.TELEFONE[tamanho+1] = 0; //pega o numero
    }
    fclose(telefonesTXT);
    return dados;
}

void alterarTelefone(unsigned int deslocamento){
    FILE *telefonesTXT = fopen("Telefones.txt", "r+");
    char TELEFONE[13];
    printf("\nNovo telefone: ");
    scanf(" %12[^\n]",TELEFONE);
    fseek(telefonesTXT, deslocamento, SEEK_SET);
    fputs(("%s/n",TELEFONE),telefonesTXT);
    fclose(telefonesTXT);
}

void excluirTelefone(char NOME[], char TELEFONE[]){
    FILE *telefonesTXT = fopen("Telefones.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    char excluir[65], linha[65];
    excluir [0] = 0;
    strcat(excluir,NOME);
    strcat(excluir,",");
    strcat(excluir,TELEFONE);
    while(fgets(linha, sizeof(linha), telefonesTXT)!=NULL){
        if(strstr(linha,excluir)==NULL) fputs(linha,temp);
    }
    fclose(telefonesTXT);
    fclose(temp);
    remove("Telefones.txt");
    rename("temp.txt", "Telefones.txt");
    printf("\nContato %s excluido com sucesso!\n",NOME);
}
