#include <stdio.h>
#include <string.h>

//escopo de funcoes
void limparScanf();
void cadastrarTelefone();
void consultarTelefone();

int main()
{
    //MENU
    FILE *telefonesTXT = fopen("Telefones.txt", "a");//Cria o arquivo telefones caso não exista.
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
                cadastrarTelefone();
                break;
            case 2:
                consultarTelefone();
                break;
            case 3:
                break;
            case 4:
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

void cadastrarTelefone(){
    FILE *telefonesTXT = fopen("Telefones.txt", "a");
    char NOME[50], TELEFONE[13];
    char vazio=0;
    printf("\nCadastrando dados\n\n");
    do{
        if(vazio==1) printf("“\nNome ou telefone em branco, digite novamente\n"); //depois de rodar novamente o loop, sinaliza o que o nome ou o telefone estavam vazios
        printf("Nome: ");
        scanf(" %49[^\n]",NOME);
        printf("Telefone: ");
        scanf(" %12[^\n],",TELEFONE);
        vazio=1; 
    }while(NOME[0] == 0 || TELEFONE[0] == 0); //se o primeiro valor de nome ou telefone forem vazios, roda o loop de novo.
    fprintf(telefonesTXT,"%s,%s\n",NOME,TELEFONE);
    fclose(telefonesTXT);
    printf("\nDados cadastrados!\n%s %s\n\n\n",NOME,TELEFONE);
}

void consultarTelefone(){
    FILE *telefonesTXT = fopen("Telefones.txt", "r");
    char ENTRADA[50], NOME[50], TELEFONE[13], ch = 0;
    int tamanho;
    printf("\n\nConsultando dados\n");
    printf("\nNome: ");
    scanf(" %49[^\n]",ENTRADA);
    NOME[0] = 0;
    while (1){
        ch = getc(telefonesTXT);
        tamanho = strlen(NOME);
        if(ch==10){ //se ch for new line, então recomeça o vetor nome, 
            tamanho = 0;
            ch = getc(telefonesTXT); //vai para o proximo ch, para tirar o nw de ch.
        }
        NOME[tamanho] = ch;
        NOME[tamanho+1] = 0;
        if(strcmp(NOME, ENTRADA) == 0)break;//se o nome de entrada bater com algum nome do arquivo quebra o loop
        if(ch==EOF){
            printf("\nTelefone de %s nao cadastrado\n\n\n",ENTRADA);
            return;
        };
        tamanho = (tamanho==49) ? 0: tamanho;
    }
    ch = getc(telefonesTXT); //pega a ,
    tamanho=0;
    TELEFONE[0] = 0;
    while (tamanho<11){
        ch =getc(telefonesTXT);
        tamanho = strlen(TELEFONE);
        TELEFONE[tamanho] = ch;
        TELEFONE[tamanho+1] = 0; //pega o numero
    }
    printf("\nTelefone encontrado com sucesso, %s %s.\n\n\n",NOME,TELEFONE);
    fclose(telefonesTXT);
}