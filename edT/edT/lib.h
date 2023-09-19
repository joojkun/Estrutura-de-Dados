#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFERTEXT 8000
#define BUFFER 20

typedef struct Texto{
    char text[BUFFERTEXT];
    int numchar;
}Texto;
typedef struct Palavras{
    char palavra[BUFFER];
    int *p;
    int np;
}Palavras;

typedef struct Dcnr{
    struct Palavras **vet;
    int tam;
}Dcnr;

void readTexto(Texto* texto);
void createInv(Texto* texto, Dcnr* arqinvr);
void printInv2(Dcnr* arqinv);
void freeInv(Dcnr* arqinvr);
void InvSort(Dcnr* arqinvr, int inicio, int fim);
int binSearch(Dcnr* arqInvr, char inicial, int i, int f);
void printWord (Dcnr* arqInvr, Texto* texto, int p, int ocorrencia);
void searchWord (Dcnr* arqInvr, Texto* texto);