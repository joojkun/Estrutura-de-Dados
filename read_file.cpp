#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "lista_functions.cpp"
using namespace std;

// Lê arquivo e cria lista encadiada
void setListaEnc(char arquivoNome[], ListaEnc *lista, contRegistro *registroEnc, int *tam) {
  // Linha do arquivo
  char line[20];
  char nome[10]; // Nome
  int rg; // RG
  char *token;
  // Arquivo
  FILE *arquivo = fopen(arquivoNome, "r");
  (*tam) = 0;

  // Caso não consiga abrir o arquivo
  if (arquivo == NULL) {
      perror("Unable to read the file");
      cout << "Erro encadeada" << endl;
      exit(1);
  }

  fgets(line, sizeof(line), arquivo);
  // Inserindo primeiro item da lista
  token = strtok(line, ",");
  // Coletando o nome
  strcpy(nome, token);
  token = strtok(NULL, ",");
  // Coletando o RG
  rg = atoi(token);
  primeiroElementoEnc(lista, nome, rg);
  (*tam) ++;

  // Inserindo o restante da lista
  while(fgets(line, sizeof(line), arquivo)) {
      // Separando a linha pelas virgulas
      token = strtok(line, ",");
      // Coletando o nome
      strcpy(nome, token);
      token = strtok(NULL, ",");
      // Coletando o RG
      rg = atoi(token);

      // Adicionando item na lista
      Node *node, *novo = (Node*)malloc(sizeof(Node));
      // Preenchendo valor
      novo->rg = rg; // RG
      strcpy(novo->nome, nome); // Nome

      // Próximo valor
      novo->proximo = NULL;
      lista->final->proximo = novo;
      lista->final = novo;
      (*tam) ++;
  }
  // Fechando o arquivo
  fclose(arquivo);
}

// Lê arquivo e cria lista sequêncial
void setListaSeq(ListaSeq **lista, char arquivoNome[], int *tam) {
  // Index da lista
  int index = 0;
  // Linha do arquivo
  char line[20];
  char nome[10]; // Nome
  int rg; // RG
  char *token;

  // Alocando memóeria da lista
  (*lista) = (ListaSeq *)malloc((*tam)*sizeof(ListaSeq));
  // Arquivo
  FILE *arquivo = fopen(arquivoNome, "r");

  // Caso não consiga abrir o arquivo
  if (arquivo == NULL) {
      perror("Unable to read the file");
      cout << "Erro sequencial" << endl;
      exit(1);
  }

  // Inserindo itens da lista
  while(fgets(line, sizeof(line), arquivo)) {
      // Separando a linha pelas virgulas
      token = strtok(line, ",");
      // Coletando o nome
      strcpy(nome, token);
      token = strtok(NULL, ",");
      // Coletando o RG
      rg = atoi(token);
      // cout << nome << ", " << rg << endl;
      strcpy((*lista)[index].nome, nome);
      (*lista)[index].rg = rg;
      index ++; // Incremente da index
  }

  // Fechando o arquivo
  fclose(arquivo);
}

void escreverLista(ListaSeq **lista, char arquivoNome[], int *tam) {
    ListaSeq listaCopia;
    ofstream myfile (arquivoNome);
    if (myfile.is_open())
    {
      for (int i = 0; i < (*tam); i ++) {
        listaCopia.rg = (*lista)[i].rg;
        strcpy(listaCopia.nome, (*lista)[i].nome);
        myfile << listaCopia.nome << "," << listaCopia.rg << endl;
      }
      myfile.close();
      cout << "Lista passada para o arquivo com sucesso!" << endl;
    }
    else cout << "Unable to open file";
}
