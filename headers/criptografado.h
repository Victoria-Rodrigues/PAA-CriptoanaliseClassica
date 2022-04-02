#ifndef CRIPTOGRAFADO_H
#define CRIPTOGRAFADO_H
#define MAXCHAR 256   // quantidade de caracteres na tabela ASCII
#include "analiseFrequencia.h"
typedef struct{
    int tam;
    char *chave; // alfabeto    
    char *criptografia; //cada posição representa uma letra se a primeira posiçaõ tiver S então S será A
    char *textoDecifrado;
    char *textoCriptografado;
    char *textoMundanca;
    char *textoAntigo;
    
    
    
}ChaveCriptografada;

int contaCaracters(char *nomeArquivo);
void initCriptografia(ChaveCriptografada *chave, char* nomeArquivo);
void preencherTexto(ChaveCriptografada *chave, char *nomeArquivo);
int casamentoPadrao(ChaveCriptografada *chave, char *padrao);
int casaPalavra(ChaveCriptografada *chave, char *padrao, int i, int *cont);
void modificaCaracter(ChaveCriptografada *chave, char c1, char c2);
void estadoAtualCriptografia(Frequencia *freq,ChaveCriptografada *chave);
char* calcMascaras(char* padrao);
void printMatriz(int** matriz,int tamLinha,int tamColuna);
int* shift(int* vetor,int tamVetor);
void inicializarBinMascaras(int** binMascaras,char* letrasMascara,char* padrao);
void inicializarRs(int** rs,int tamLinha,int tamColuna);
int* calcularR0Linha(int* r0Anterior, int* binCaracter, int tamVetor);
int* calcularRjLinha(int* binRj,int* binRjAnterior, int* binCaracter,int tamColuna);
void shiftAndAproximado(ChaveCriptografada* chaveCriptografada,char* padrao, int tolerancia);
void escreverArquivo(char* nomeArquivoChave,char* nomeArquivoTextoDecifrado , char* textoChave,char* textoDecifrado);
#endif