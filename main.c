#include <stdio.h>
#include <stdlib.h>
#include "headers/criptografado.h"
#include "headers/analiseFrequencia.h"

// gcc main.c -o run sources/analiseFrequencia.c sources/criptografado.c

int main(){
    
    ChaveCriptografada chave;
    Frequencia freq[26];
    char padrao[40];
    int opcao, cont=0;
    char nomeArquivo[50];
    char c1, c2;
    printf("Digite o nome do arquivo de entradas:\n");
    scanf("%s", nomeArquivo);
    initCriptografia(&chave, nomeArquivo);
    modificaCaracter(&chave, 'I','A');
    modificaCaracter(&chave, 'M', 'E');
    modificaCaracter(&chave, 'K', 'O');
    modificaCaracter(&chave, 'L', 'S');
    modificaCaracter(&chave, 'U', 'R');
    modificaCaracter(&chave, 'P', 'T');
    modificaCaracter(&chave, 'N', 'D');
    modificaCaracter(&chave, 'X', 'I');
    modificaCaracter(&chave, 'B', 'U');
    modificaCaracter(&chave, 'T', 'N');
    modificaCaracter(&chave, 'D', 'M');
    modificaCaracter(&chave, 'J', 'C');
    modificaCaracter(&chave, 'Z', 'P');
    modificaCaracter(&chave, 'W', 'L');
    modificaCaracter(&chave, 'Q', 'V');
    modificaCaracter(&chave, 'C', 'G');
    modificaCaracter(&chave, 'R', 'Q');
    modificaCaracter(&chave, 'S', 'H');
    modificaCaracter(&chave, 'G', 'Z');
    modificaCaracter(&chave, 'H', 'F');
    modificaCaracter(&chave, 'Y', 'B');
    modificaCaracter(&chave, 'A', 'J');
    modificaCaracter(&chave, 'O', 'X');
    modificaCaracter(&chave, 'E', 'Y');
    modificaCaracter(&chave, 'F', 'K');
    modificaCaracter(&chave, 'V', 'W');
    while (1){
        printf("\n\n=================================================\n");
        printf("========================MENU=====================\n");
        printf("=================================================\n");
        printf("[1] - Apresentar o estado atual da criptoanalise\n");
        printf("[2] - Fazer analise de frequencia no texto criptografado\n");
        printf("[3] - Realizar casamento exato de caracteres no texto criptografado\n");
        printf("[4] - Realizar casamento aproximado de caracteres no texto parcialmente decifrado\n");
        printf("[5] - Alterar chave de criptografia\n");
        printf("[6] - Exportar resultado e encerrar o programa\n");
        printf("[0] - Sair\n");
        printf("Opcao: ");
        scanf("%d",&opcao);
        if(opcao==0)break;
        printf("\n");
        frequencia(freq, nomeArquivo);//NAO RETIRAR, PRECISA PARA OBTER A TABELA DE FREQUENCIA
        if(opcao == 1){
            estadoAtualCriptografia(freq,&chave);          
        }else if(opcao == 2){
            frequencia(freq, nomeArquivo);
            imprimeTabelaFrequencia(freq);
        }else if(opcao == 3){
            printf("Digite o padrao:");
            scanf("%s", padrao);
            printf("Qual o padrao utilizado?\n> %s\nOcorrencias:%d", padrao,casamentoPadrao(&chave,padrao));
        }else if(opcao == 4){
            int tolerancia;
            printf("Digite o padrao e tolerancia utilizados?\n");
            scanf("%s %d", padrao, &tolerancia);
            shiftAndAproximado(&chave,padrao,tolerancia);
        }else if(opcao == 5){
             printf("Informe a letra original, seguida da letra para a qual foi mapeada:\n");
             fflush(stdin);
             scanf("%c %c", &c1, &c2);
             printf("> %c %c", c1, c2);
             modificaCaracter(&chave, c1, c2);
             printf("\nRegistrado: %c -> %c\n", c1, c2);
        }else if(opcao == 6){
            char nomeArquivoChave[50],nomeArquivoTextoDecifrado[50];
             printf("Nome do arquivo da chave:");
            scanf("%s",nomeArquivoChave);
             printf("Nome do arquivo do texto decifrado:");
            scanf("%s",nomeArquivoTextoDecifrado);
            escreverArquivo(nomeArquivoChave,nomeArquivoTextoDecifrado,chave.criptografia,chave.textoDecifrado);
            break;
        }
    }
   
    return 0;
}