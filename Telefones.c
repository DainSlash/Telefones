#include <stdio.h>
#include <locale.h>


//escopo de funcoes
void limparScanf();
void cadastrarTelefone();


int main()
{
    //MENU
    int o=0;
    while(o!=5){
        printf("\n\nMenu de Opcoes\n"
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
    int contador=0;
    printf("\nCadastrando dados\n\n");
    do{
        if(contador>0) printf("“\nNome ou telefone em branco, digite novamente\n");
        printf("Nome: ");
        scanf(" %49[^\n]",NOME); //tamanho de 19, ja que eh necessario um espaco para /0
        printf("Telefone: ");
        scanf(" %12[^\n],",TELEFONE);
        contador++;
    }while(NOME[0] == NULL || TELEFONE[0] == NULL);
    fprintf(telefonesTXT,"%s,%s\n",NOME,TELEFONE);
    fclose(telefonesTXT);
    printf("\nDados cadastrados\n");
    
}