#include "../headers/analiseFrequencia.h"
#include "../headers/criptografado.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void frequencia(Frequencia *freq, char * nomeArquivo){
    int *chave = (int*)malloc(sizeof(int) * 26);
    char alfabeto[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int cont = 0;
    int contletras = 0;
    int valor,i;
    
    FILE *arquivo;
    for( i = 0; i < 26; i++){
        chave[i] = 0;
    }
    int tamArquivo = contaCaracters(nomeArquivo);
    char *texto = (char*)malloc(sizeof(char) * tamArquivo);
    arquivo = fopen(nomeArquivo,"r");
    if(arquivo == NULL){
        printf("Falha no arquivo de alfabeto!!\n");
    }else{
        while (!feof(arquivo)){
            fgets(texto, tamArquivo , arquivo);
        }
        int i = 0;
        while(texto[i] != '\0'){
            valor = (int)texto[i];
            if(valor > 64 && valor < 91){
                 chave[valor-65]++;
                 contletras++;
            }
            i++;
        }
    //calculando a frequencia das letras
     for( i = 0; i < 26; i++){
         freq[i].cont = chave[i];
         freq[i].letra = alfabeto[i];
         freq[i].freq = (100) * (freq[i].cont / (double)contletras);
      }
    }
    Shellsort(freq);
    fclose(arquivo);  
}

void Shellsort(Frequencia *freq){
   int n = 26; 
   int i, j;
   int h = 1;
   Frequencia aux;
   do
      h = h * 3 + 1;
   while (h < n);
   do
   {
      h = h / 3;
      for (i = h; i < n; i++)
      {
         aux = freq[i];
         j = i;
         while (freq[j - h].freq < aux.freq)
         {

            freq[j] = freq[j - h];
            j -= h;
            if (j < h)
               break;
         }
         freq[j] = aux;
      }
   } while (h != 1);
}


void imprimeTabelaFrequencia(Frequencia *freq){
    FILE *arquivo;
    int i;
    char palavra[20];
    arquivo = fopen("entradas/portugues.txt","r");
      if(arquivo == NULL){
        printf("Falha no arquivo de alfabeto!!\n");return;
      }
    printf("\nLetra, Cont,  Freq.            Letra	     Frequencia\n");
    for( i = 0; i < 26; i++){
      fgets(palavra,20, arquivo);
      printf("%c      %d         %.2f%%       %s", freq[i].letra, freq[i].cont, freq[i].freq, palavra);
      
    }
    fclose(arquivo);
}