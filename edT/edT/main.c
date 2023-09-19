#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

int main()
{
    Texto texto;
    Dcnr arqinv;
    int op;
    do
    {
        printf("\n1-Carregar arquivo de texto\n2-Apresentar Arquivo Invertido\n3-Procurar Palavra no texto\n0-Sair\n:");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            readTexto(&texto);
            createInv2(&texto, &arqinv);
            InvSort(&arqinv,0,arqinv.tam-1);
            break;
        case 2:
            printInv(&arqinv);
            break;
        case 3:
            searchWord(&arqinv, &texto);
            break;
        default:
            break;
        }
    } while (op != 0);
}

void readTexto(Texto *texto)
{
    char nomearquivo[20] = "Historia.txt";
    int i = 0;
    FILE *arq;
    arq = fopen(nomearquivo, "rt");
    if (arq == NULL)
    {
        printf("NAO FOI POSSIVEL ABRIR O ARQUIVO\n");
        return;
    }
    while (!feof(arq)) //caractere por caractere
    {
        fscanf(arq, "%c", &(texto->text[i]));
        i++;
    }
    texto->numchar = i;
    fclose(arq);
    printf("ARQUIVO CARREGADO! \n");
}

void createInv2(Texto *texto, Dcnr *arqinv){
    int i = 0, j = 0, k, flag = 0, palavrainicial = -1;
    char palavra[BUFFER];
    arqinv->vet = (Palavras **)malloc(sizeof(Palavras *));
    arqinv->tam = 0;
    arqinv->vet[0] = (Palavras *)malloc(sizeof(Palavras));
    for (i = 0; i < texto->numchar; i++){
        if (texto->text[i] == ' ' || texto->text[i] == '\n' || texto->text[i] == '.' || texto->text[i] == ',' || texto->text[i] == '?' || texto->text[i] == '!' || texto->text[i] == '\0' || texto->text[i] == '(' || texto->text[i] == ')' || texto->text[i] == '[' || texto->text[i] == ']' || texto->text[i] == '{' || texto->text[i] == '}' || texto->text[i] == '-' || texto->text[i] == '_' || texto->text[i] == ';' || texto->text[i] == ':')
        {
            palavra[j+1] = '\0';
            flag = 0;
                for (k = 0; k < arqinv->tam && flag == 0; k++) //percorre o arquivo para ver se ja existe a palavra na listaInvertida
                {
                    if (strcmp(arqinv->vet[k]->palavra, palavra) == 0)
                    {
                        flag = 1;
                        arqinv->vet[k]->np++;
                        arqinv->vet[k]->p = (int *)realloc(arqinv->vet[k]->p, arqinv->vet[k]->np * sizeof(int));
                        arqinv->vet[k]->p[((arqinv->vet[k]->np - 1))] = palavrainicial-(j-1);
                    }
                }
                if (flag == 0) // cria novo nó na listaInvertida se ja não existir 
                {
                    arqinv->tam++;
                    arqinv->vet = (Palavras **)realloc(arqinv->vet, arqinv->tam * sizeof(Palavras *));
                    arqinv->vet[arqinv->tam - 1] = (Palavras *)malloc(sizeof(Palavras));
                    arqinv->vet[arqinv->tam - 1]->p = (int *)malloc(sizeof(int));
                    arqinv->vet[arqinv->tam - 1]->p[0] = palavrainicial-(j-1);
                    arqinv->vet[arqinv->tam - 1]->np = 1;
                    strcpy(arqinv->vet[arqinv->tam - 1]->palavra, palavra);
                }
            j = 0;
            palavrainicial = -1;
            memset(palavra, 0, sizeof(palavra));
        }
        else {
            if(palavrainicial = -1)
                palavrainicial = i;
            palavra[j] = texto->text[i];
            j++;
        }
    }
}

void printInv(Dcnr *arqinv)
{
    int i, j;
    for (i = 0; i < arqinv->tam; i++)
    {
        if (strcmp(arqinv->vet[i]->palavra, " ") == 0)
        {
            printf("' ' ");
        }
        else if (strcmp(arqinv->vet[i]->palavra, "\n") == 0)
        {
            printf("\'\\n\' ");
        }
        else
        {
            printf("\"%s\" ", arqinv->vet[i]->palavra);
        }
        printf("(%d)", arqinv->vet[i]->np);
        for (j = 0; j < arqinv->vet[i]->np; j++)
        {
            printf("%d ", arqinv->vet[i]->p[j]);
        }
        printf("\n");
    }
}

void freeInv(Dcnr *arqinv)
{
    int i;

    for (i = 0; i < arqinv->tam; i++)
    {
        free(arqinv->vet[i]->p);
    }
    free(arqinv->vet);
}

void InvSort(Dcnr *arqinv, int inicio, int fim)
{
    int i = inicio, j = fim;
    Palavras *aux;
    char pivo;
    pivo = arqinv->vet[(inicio + fim) / 2]->palavra[0];
    while (i <= j)
    {

        while (arqinv->vet[i]->palavra[0] < pivo)
        {
            i++;
        }

        while (arqinv->vet[j]->palavra[0] > pivo)
        {
            j--;
        }

        if (i <= j)
        {
            aux = arqinv->vet[j];
            arqinv->vet[j] = arqinv->vet[i];
            arqinv->vet[i] = aux;
            i++;
            j--;
        }
    }

    if (i < fim)
    {

        InvSort(arqinv, i, fim);
    }
    if (j > inicio)
    {

        InvSort(arqinv, inicio, j);
    }
}

int buscaSequencial(Dcnr *arqInvr, char palavra[], int p)
{
    int achou = 0;

    if (p != -1)
    {
        if ((strcmp(arqInvr->vet[p]->palavra, palavra) == 0))
        {
            return p;
        }
    }
    else
    {
        return -1;
    }

    while (arqInvr->vet[p]->palavra[0] == palavra[0] && p > 0)
    {
        p--;
    }
    p++;

    while (p < arqInvr->tam && achou == 0 && arqInvr->vet[p]->palavra[0] == palavra[0])
    {
        if (strcmp(arqInvr->vet[p]->palavra, palavra) == 0)
        {
            achou = 1;
        }
        else
        {
            p++;
        }
    }
    if (achou == 1)
    {
        return p;
    }
    else
    {
        return -1;
    }
}

int binSearch(Dcnr *arqInvr, char inicial, int i, int f)
{
    int m, p = -1;

    m = (i + f) / 2;

    if (i < f)
    {
        if (arqInvr->vet[m]->palavra[0] == inicial)
        {
            return m;
        }
        else
        {
            if (arqInvr->vet[m]->palavra[0] < inicial)
            {
                p = binSearch(arqInvr, inicial, m + 1, f);
            }
            else
            {
                p = binSearch(arqInvr, inicial, i, m - 1);
            }
        }
    }
    else if (arqInvr->vet[m]->palavra[0] == inicial)
    {
        return m;
    }

    return p;
}

void printWord(Dcnr *arqInvr, Texto *texto, int p, int ocorrencia)
{
    int i, ini = ocorrencia - 2, fim = ocorrencia, palavrafinal;

    palavrafinal = ocorrencia + (strlen(arqInvr->vet[p]->palavra));
    fim = palavrafinal;
    for (i = 0; i < 10; i++)
    {
        if (ini > 0)
        {
            ini--;
        }

        if (fim < strlen(texto->text))
        {
            fim++;
        }
    }
    for (i = ini; i < fim; i++)
    {
        if (i == ocorrencia || i == palavrafinal)
        {
            printf("__");
        }
        printf("%c", texto->text[i]);
    }
    printf("\n\n");
}

void searchWord(Dcnr *arqInvr, Texto *texto)
{
    char palavra[20];
    int p, op = 1, ocorrencia = 0;

    printf("Pesquisar por: ");
    scanf("%s", palavra);
    getchar();

    p = binSearch(arqInvr, palavra[0], 0, (arqInvr->tam) - 1);

    if (p == -1)
    {
        printf("Palavra nao encontrada!");

        system("pause");
    }
    else
    {

        p = buscaSequencial(arqInvr, palavra, p);
        if (p == -1)
        {
            printf("Palavra nao encontrada!");

            system("pause");
        }
        else
        {

            do
            {
                system("cls");

                printf("Ocorrencia %d de %d\n", ocorrencia + 1, arqInvr->vet[p]->np);
                printf("A palavra ocorre %d vezes\n", arqInvr->vet[p]->np);
                printf("Ocorrencia na posicao %d:\n\n", arqInvr->vet[p]->p[ocorrencia]);
                printWord(arqInvr, texto, p, arqInvr->vet[p]->p[ocorrencia]);
                if (arqInvr->vet[p]->np == 1)
                {
                    system("pause");
                    op = 0;
                }
                else if (ocorrencia < arqInvr->vet[p]->np - 1)
                {
                    printf("0-voltar\n1-proxima ocorrencia\n");
                    scanf("%d", &op);
                    if (op == 1)
                    {
                        ocorrencia++;
                    }
                    else
                    {
                        op = 0;
                    };
                }
                else if (ocorrencia == arqInvr->vet[p]->np - 1)
                {
                    system("pause");
                    op = 0;
                }

            } while (op != 0);
        }
    }
    system("cls");
}