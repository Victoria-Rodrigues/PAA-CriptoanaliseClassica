#ifndef ANALISEFREQUENCIA_H
#define ANALISEFREQUENCIA_H

typedef struct{
    char letra;
    int cont;
    float freq;
}Frequencia;


void frequencia(Frequencia *freq, char * nomeArquivo);
void Shellsort(Frequencia *freq);
void imprimeTabelaFrequencia(Frequencia *freq);


#endif