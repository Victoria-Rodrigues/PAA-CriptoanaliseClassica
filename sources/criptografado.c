#include "../headers/analiseFrequencia.h"
#include "../headers/criptografado.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contaCaracters(char *nomeArquivo){//passar o arquivo depois
    char c;
	FILE *fp;
	int count = 0;
    fp = fopen(nomeArquivo, "r");
    while(!feof(fp)){
		c = getc(fp);
        count++;
	}
	fclose(fp);
    return count;
}

void initCriptografia(ChaveCriptografada *chave, char* nomeArquivo){
    int i;
    chave->chave = (char*)malloc(sizeof(char) * 26);
    chave->criptografia = (char*)malloc(sizeof(char) * 26);
    chave->textoMundanca = (char*)malloc(sizeof(char) * 26);
     chave->textoAntigo = (char*)malloc(sizeof(char) * 26);
    for( i = 0; i < 26; i++){
        chave->criptografia[i] = ' ';
    }
    strcpy(chave->chave,"ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    chave->textoCriptografado = (char*)malloc(sizeof(char) * contaCaracters(nomeArquivo));
    chave->textoDecifrado = (char*)malloc(sizeof(char) * contaCaracters(nomeArquivo));
    chave->tam = contaCaracters(nomeArquivo);
    preencherTexto(chave, nomeArquivo);
}



void preencherTexto(ChaveCriptografada *chave, char *nomeArquivo){
    FILE *arquivo;
    char var[30];
    arquivo = fopen(nomeArquivo,"r");
    if(arquivo == NULL){
        printf("Falha no arquivo de alfabeto!!\n");
    }else{
        while (!feof(arquivo)){
            fgets(chave->textoCriptografado, chave->tam, arquivo);
            strcpy(chave->textoDecifrado, chave->textoCriptografado);
        }   
    }
}

int casamentoPadrao(ChaveCriptografada *chave, char *padrao){
    int i = 0;
    int cont = 0;
    while (i < chave->tam){
        if(chave->textoCriptografado[i] == padrao[0]){
            casaPalavra(chave,  padrao, i, &cont);
        }
        i++;
    }
    return cont;
}

int casaPalavra(ChaveCriptografada *chave, char *padrao, int i, int *cont){
    int antI = i;
    int j;
    for( j = 0; j < strlen(padrao); j++){
        if(chave->textoCriptografado[i] == padrao[j]){
            i++;
        }else{
            return antI;
            break;
        }
    }
    *cont = *cont + 1;
    return i;
}

void modificaCaracter(ChaveCriptografada *chave, char c1, char c2){
    int value = (int)c1; //coloque uma verificação para não entrar caracteres errados
    chave->criptografia[value - 65] = c2;
    chave->textoMundanca[value - 65] = '*';
    chave->textoAntigo[value - 65] = c1;
    //printf("%c\n",chave->textoMundanca[value - 65]);
   
}

void estadoAtualCriptografia(Frequencia *freq,ChaveCriptografada *chave){
    
    char aux[chave->tam];
    
    int j,i,k,x;    
    for(i = 0; i< chave->tam; i++){
        aux[i] = '-';
    } 
    for(i = 0; i< 26; i++){
        for( j=0;j < chave->tam;j++){
            if(chave->textoMundanca[i] == '*'){
                char t1 = chave->textoAntigo[i]; 
                char t2 = chave->textoCriptografado[j];
                if(t1==t2){
                    chave->textoDecifrado[j] = chave->criptografia[i];
                    aux[j] = '^';
                }else{
                    if(aux[j]!='^')
                        aux[j] = '-';   
                }
            }
            
        }    
    }
    
    //IMPRIMINDO O TEXTO CRIPTOGRAFADO
    printf("\n=== Texto criptografado ===\n");
    printf("%s", chave->textoCriptografado);
    //IMPRIMINDO O ALFABETO
    printf("\n\n=== Chave ===\n");
    printf("%s\n",chave->chave);
    
    for( i = 0; i <26;i++){
        if(chave->textoMundanca[i] == '*'){
            printf("%c",chave->criptografia[i]);   
        }else{
            printf(" ");
        }
    }   
    
    printf("\n\n==== Texto parcialmento decifrado ===\n");
    
    int tamLinha = 90;//quantidade de caracteres por linha
    int repete = chave->tam/tamLinha;
    int resto = chave->tam%tamLinha;
    int inicio = 0,fim = tamLinha; 
    int acabou = 0;
    int contador = 1;
    for(j= 0; j<chave->tam;j++){
         
        printf("%c", chave->textoDecifrado[j]);
        if(contador%90==0){
            printf("\n");
            for( k = inicio; k<j+1;k++){
                if(aux[k]=='-')
                    printf(" ");
                else
                    printf("%c", aux[k]);
            }
            inicio = j+1;
            printf("\n");
        }contador++;
        if(j==chave->tam-1){
            printf("\n");
            for( k = inicio; k<j;k++){
                if(aux[k]=='-')
                    printf(" ");
                else
                    printf("%c", aux[k]);
            }
        } 
    }
    
}

void shiftAndAproximado(ChaveCriptografada* chaveCriptografada,char* padrao, int tolerancia){
    // printf("%s",chaveCriptografada->textoDecifrado);
    int tamPadrao=strlen(padrao);
    char* letrasMascaras;
    int casou=0;
    int i=0, j=0, k =0;
    int mascara0[tamPadrao];
    int ocorrencias=0;

    for(i=0;i<tamPadrao;i++){
        mascara0[i]=0;
    }
    letrasMascaras=calcMascaras(padrao);

    int qtdMascaras=strlen(letrasMascaras);
    int** binMascaras=  (int**)malloc(qtdMascaras*sizeof(int*));
    for(i=0;i<qtdMascaras;i++){
         binMascaras[i] = (int*)malloc(tamPadrao*sizeof(int));
    }
    inicializarBinMascaras(binMascaras,letrasMascaras,padrao);
    
    int** rs = (int**)malloc((tolerancia+1)*sizeof(int*));
    int** rsLinha = (int**)malloc((tolerancia+1)*sizeof(int*));
    
    for(i=0;i<tolerancia+1;i++){
         rs[i] = (int*) malloc(tamPadrao*sizeof(int));
         rsLinha[i] = (int*) malloc(tamPadrao*sizeof(int));
    }
    inicializarRs(rs,tolerancia+1,tamPadrao);
    i=0;
    while (chaveCriptografada->textoDecifrado[i]!='\0')
    {
        
        int* binCaracter=(int*)malloc(tamPadrao*sizeof(int));
        char c= chaveCriptografada->textoDecifrado[i];
        for(j=0;j<qtdMascaras;j++){
            if(c==letrasMascaras[j]){
                     binCaracter=binMascaras[j];
                break;
            }else{
                     binCaracter=mascara0;
            }
        }

       
        
        for(j=0;j<tolerancia+1;j++){
            if(j==0){
                rsLinha[j]=calcularR0Linha(rs[0],binCaracter,tamPadrao);
            }else{
                rsLinha[j]=calcularRjLinha(rs[j],rs[j-1],binCaracter,tamPadrao);
            }
            }
           

            for(j=0;j<tolerancia+1;j++){
             for(k=0;k<tamPadrao;k++){
                    rs[j][k]=rsLinha[j][k];
            }
            }
            for(j=0;j<tolerancia+1;j++){
                if(rsLinha[j][tamPadrao-1]==1 && i>=tamPadrao){
                    casou=1;
                    break;
                }
            }
         

         if(casou){
             ocorrencias++;
               printf("@[%d,%d): ",i-tamPadrao+1,i+1);
             for(j=i-tamPadrao+1;j<=i;j++){
            printf("%c",chaveCriptografada->textoDecifrado[j]);
        }
            printf("\n");
            casou=0;
         }
        i++;
    }
     printf("Quantidade de ocorrencias: %d",ocorrencias);

}
int* calcularRjLinha(int* binRj,int* binRjAnterior, int* binCaracter,int tamColuna){
    int i=0;
      int* shiftRj=shift(binRj,tamColuna);
    int* shiftRjAnterior=shift(binRjAnterior,tamColuna);
  
    int* rjLinha=(int*)(malloc(tamColuna*sizeof(int)));
    for(i=0;i<tamColuna;i++){
         if(i==0){
         rjLinha[i]= 1;
        }else{
         rjLinha[i]= (shiftRj[i] && binCaracter[i]) ||(shiftRjAnterior[i]);
        }
    }

    return rjLinha;
}
//Testado-> OK
int* calcularR0Linha(int* r0Anterior, int* binCaracter, int tamVetor){
    int i=0;
    int* shiftLiga1=shift(r0Anterior,tamVetor);
                shiftLiga1[i]=1;

  
    
    for (i=0;i<tamVetor;i++){
       
        shiftLiga1[i]=shiftLiga1[i] && binCaracter[i];

    }

    return shiftLiga1;
}
//Testado-> OK

void inicializarRs(int** rs,int tamLinha,int tamColuna){
    int i=0,j=0,cont=0;
    for(i=0;i<tamLinha;i++){
        cont=i;
        for(j=0;j<tamColuna;j++){
            if(cont>0){
                rs[i][j]=1;
                cont--;
            }else{
                rs[i][j]=0;
            }
            
        }
    }

}
//Testado-> OK

void inicializarBinMascaras(int** binMascaras,char* letrasMascara,char* padrao){
    int i=0,j=0;
    for (i=0;i<strlen(letrasMascara);i++){
        for(j=0;j<strlen(padrao);j++){
            if(letrasMascara[i]==padrao[j]){
                binMascaras[i][j]=1;
            }else{
                    binMascaras[i][j]=0;
            }
        }
    }
}
//Testado-> OK

int* shift(int* vetor,int tamVetor){
    int i,j;
    int* aux= (int*)malloc(tamVetor*sizeof(int));
  
   for(i=0;i<tamVetor-1;i++){
        aux[i+1]=vetor[i];
        }
        aux[0]=0;
    return aux;
    
}
//Testado-> OK

void printMatriz(int** matriz,int tamLinha,int tamColuna){
    int i=0,j=0;
    for (i=0;i<(tamLinha);i++){
        for(j=0;j<(tamColuna);j++){
            printf("[%d]",matriz[i][j]);
        }
    printf("\n");
    }

}
//Testado-> OK

char* calcMascaras(char* padrao){
    int tamTextoPadrao=strlen(padrao); 
    int i=0,j=0,cont=0;
    char* padraoOrdenado= (char*)(malloc(tamTextoPadrao*sizeof(char)));
    for(i=0;i<tamTextoPadrao;i++){
        padraoOrdenado[i]=padrao[i];
    } 
   
    for(i=0;i<tamTextoPadrao;i++){
        for(j=0;j<tamTextoPadrao-1;j++){
            if(((int)padraoOrdenado[j+1])<((int)padraoOrdenado[j])){
                char temp= padraoOrdenado[j];
                padraoOrdenado[j]=padraoOrdenado[j+1];
                padraoOrdenado[j+1]=temp;
            }
        }
    } 
    for(i=0;i<tamTextoPadrao-1;i++){
        if(padraoOrdenado[i+1]!=padraoOrdenado[i]){
            cont++;
        }
    } 
    cont+=1;
    int tamLetrasmascara=cont;
    char* letrasMascaras=(char*)malloc((cont)*sizeof(char));
    cont=0;
    for(i=0;i<tamTextoPadrao-1;i++){
        if(padraoOrdenado[i+1]!=padraoOrdenado[i]){
           letrasMascaras[cont]=padraoOrdenado[i];
           cont++;
        }
    } 
    letrasMascaras[tamLetrasmascara-1]=padraoOrdenado[tamTextoPadrao-1];

     return letrasMascaras;
}

void escreverArquivo(char* nomeArquivoChave,char* nomeArquivoTextoDecifrado , char* textoChave,char* textoDecifrado){
    FILE* arquivoChave;
    FILE* arquivoTextoDecifrado;
    arquivoChave = fopen(nomeArquivoChave, "w");
    arquivoTextoDecifrado= fopen(nomeArquivoTextoDecifrado, "w");
    fputs("ABCDEFGHIJKLMNOPQRSTUVWYZ\n",arquivoChave);
    fputs(textoChave,arquivoChave);
    fputs(textoDecifrado,arquivoTextoDecifrado);
    fclose(arquivoChave);
    fclose(arquivoTextoDecifrado);

}