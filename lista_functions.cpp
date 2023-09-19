#include <iostream>
#include <string.h>
#include <fstream>
#include <time.h>
#include <stdbool.h>
using namespace std;

typedef struct {
  int comp = 0;
  int mov = 0;
  double tempoGasto = 0.0;
}contRegistro;

typedef struct Node {
  // RG
  int rg;
  // Nome
  char nome[10];
  // Ponteiro que irá apontar para o próximo valor
  struct Node *proximo = NULL;

}Node;

// Criando a lista
typedef struct{
  // Início da lista
  Node *inicio;
  // Final da lista
  Node *final;
}ListaEnc;

void lendoDados(char nome[], int *rg) {
  // Lendo os dados
  cout << "\nDigite um nome: "; // Nome
  cin >> nome;
  cout << "Digite um RG: "; // RG
  cin >> *rg;
}

Node* getByIndex(ListaEnc *lista, int index) {
  Node* aux = lista->inicio;
  for (int pos = 0; pos <= index; pos ++) {
    if (pos == index) {
      break;
    }
    aux = aux->proximo;
  }
  return aux;
}

void primeiroElementoEnc(ListaEnc *lista, char nome[], int rg) {
  // Alocando memória para o novo elemento
  Node *novo = (Node*)malloc(sizeof(Node));
  // Preenchendo o valor
  strcpy(novo->nome, nome);
  novo->rg = rg;
  // Próximo valor
  novo->proximo = NULL;
  // Inserindo valor no início
  lista->inicio = novo;
  // Como é o único valor da lista, tbm será o valor final
  lista->final = novo;
}

void inserirInicioEnc(ListaEnc *lista, char nome[], int rg, contRegistro* registro) {
  // Zerando os contadores
  registro->mov = 0;
  registro->comp = 0;
  // Começando a contar o tempo de execução do código
  clock_t begin = clock();
  // Alocando memória para o novo elemento
  Node *novo = (Node*)malloc(sizeof(Node));
  // Preenchendo o valor
  strcpy(novo->nome, nome);
  novo->rg = rg;
  // Próximo valor
  novo->proximo = lista->inicio;
  // Inserindo valor no início
  lista->inicio = novo;
  // Parando de contar o tempo
  clock_t end = clock();
  // Tempo gasto no total
  registro->tempoGasto = (double)(end - begin) / CLOCKS_PER_SEC;
  // Número de movimentações
  registro->mov += 4;
  // Número de comparações
  registro->comp = 0;
}

// Inserir item na lista
void inserirFinalEnc(ListaEnc *lista, char nome[], int rg, contRegistro* registro) {
  // Zerando os contadores
  registro->mov = 0;
  registro->comp = 0;
  // Começando a contar o tempo de execução do código
  clock_t begin = clock();
  // Alocando memória para o valor
  Node *novo = (Node*)malloc(sizeof(Node));
  // Preenchendo valor
  novo->rg = rg; // RG
  strcpy(novo->nome, nome); // Nome

  // Próximo valor
  novo->proximo = NULL;
  lista->final->proximo = novo;
  lista->final = novo;
  // Parando de contar o tempo
  clock_t end = clock();
  // Tempo gasto no total
  registro->tempoGasto = (double)(end - begin) / CLOCKS_PER_SEC;
  // Número de movimentações
  registro->mov += 5;
  // Número de comparações
  registro->comp = 0;
}

void inserirPosNEnc(ListaEnc *lista, char nome[], int rg, int posN, contRegistro* registro) {
  // Zerando os contadores
  registro->mov = 0;
  registro->comp = 0;
  // Começando a contar o tempo de execução do código
  clock_t begin = clock();
  // Posição atual da lista
  int posAt = 0;
  // Alocando memória para o valor
  Node *node, *novo = (Node*)malloc(sizeof(Node));
  // Preenchendo o novo nó
  novo->rg = rg; // RG
  strcpy(novo->nome, nome); // Nome
  // Nó cópia, para percorrer os itens
  node = lista->inicio;
  registro->mov += 5;
  // Passando pelos itens da lista até encontra a posição desejada
  while (posAt + 1 != posN) {
    node = node->proximo;
    registro->mov += 2;
    // Caso chegue no último item da lista
    registro->comp += 2;
    if (node->proximo == NULL && posAt != posN) {
      cout << "A posicao desejada nao foi encontrada!" << endl;
      return;
    }
    // Incrementando a posição
    posAt ++;
    registro->comp ++;
  }
  // Após encontrar a posição desejada
  // Próximo valor
  novo->proximo = node->proximo->proximo;
  node->proximo = novo;
  // Caso seja o primeiro item da lista
  if (posN == 0) {
    lista->inicio = novo;
  }
  registro->comp ++;
  // Parando de contar o tempo
  clock_t end = clock();
  // Tempo gasto no total
  registro->tempoGasto = (double)(end - begin) / CLOCKS_PER_SEC;
  // Número de movimentações
  registro->mov += 2;
}

void removeInicioEnc(ListaEnc *lista, contRegistro* registro) {
  // Zerando os contadores
  registro->mov = 0;
  registro->comp = 0;
  // Começando a contar o tempo de execução do código
  clock_t begin = clock();
  // Cópia do antigo início
  Node *node;
  node = lista->inicio;
  // Novo início
  lista->inicio = lista->inicio->proximo;
  free(node);
  // Parando de contar o tempo
  clock_t end = clock();
  registro->mov = 3;
  // Tempo gasto no total
  registro->tempoGasto = (double)(end - begin) / CLOCKS_PER_SEC;
}

void removeFinalEnc(ListaEnc *lista, contRegistro *registro) {
  // Zerando os contadores
  registro->mov = 0;
  registro->comp = 0;
  // Começando a contar o tempo de execução do código
  clock_t begin = clock();
  // Cópia da lista
  Node *node;
  node = lista->inicio;
  registro->mov ++;
  while(true) {
    registro->comp += 2;
    if (node->proximo->proximo == NULL) {
      lista->final = node;
      free(node->proximo);
      node->proximo = NULL;
      registro->mov += 2;
      break;
    }
    else {
      node = node->proximo;
      registro->mov ++;
    }
  }
  // Parando de contar o tempo
  clock_t end = clock();
  // Tempo gasto no total
  registro->tempoGasto = (double)(end - begin) / CLOCKS_PER_SEC;
}

// Imprimir lista
void imprimirListaEncadeada(ListaEnc *lista) {
  // Início da lista
  Node *inicio = lista->inicio;

  // Tamanho da lista
  cout << "Valores da lista: " << endl;
  // Percorrendo lista até chegar no último elemento
  while(inicio != NULL) {
    // Imprimindo valor
    cout << inicio->nome << ", " << inicio->rg << endl;
    // Passando para o próximo valor da lista
    inicio = inicio->proximo;
  }
}

void removePosNEnc(ListaEnc *lista, int posN, contRegistro *registro) {
  // Zerando os contadores
  registro->mov = 0;
  registro->comp = 0;
  // Posição atual da lista
  int posAt = 0;
  // Começando a contar o tempo de execução do código
  clock_t begin = clock();
  // Alocando memória para o valor
  Node *node, *nodeAnt;
  // Nó cópia, para percorrer os itens
  node = lista->inicio;
  nodeAnt = node;
  registro->mov += 3;
  // Passando pelos itens da lista até encontra a posição desejada
  while (posAt != posN) {
    nodeAnt = node;
    node = node->proximo;
    registro->mov++;
    // Caso chegue no último item da lista
    registro->comp += 2;
    if (node->proximo == NULL && posAt != posN) {
      cout << "A posicao desejada nao foi encontrada!" << endl;
      return;
    }
    // Incrementando a posição
    posAt++;
    registro->comp++;
  }
  // Após encontrar a posição desejada
  // Caso seja o primeiro item da lista
  if (posAt == 0) {
    lista->inicio = lista->inicio->proximo;
  } else {
    // Removendo item da lista
    nodeAnt->proximo = node->proximo;
  }
  free(node);
  registro->comp++;
  // Parando de contar o tempo
  clock_t end = clock();
  // Tempo gasto no total
  registro->tempoGasto = (double)(end - begin) / CLOCKS_PER_SEC;
  // Número de movimentações
  registro->mov += 4;
}

Node procurarRGEnc(ListaEnc *lista, int *tam, int rg,contRegistro* registro) {
  // Zerando os contadores
  registro->mov = 0;
  registro->comp = 0;
  // Começando a contar o tempo de execução do código
  clock_t begin = clock();
  // Nó para percorrer pelos itens da lista
  Node *node;
  node = lista->inicio;
  // Nó que será retornado caso o RG não seja encontrado
  Node lista2;
  strcpy(lista2.nome, "SemNome");
  lista2.rg = 0;
  // Registro
  registro->mov += 3;

  // Passando pelos itens da lista
  while (node->proximo != NULL) {
    registro->comp ++;
    // Caso encontre o RG pesquisado
    if (node->rg == rg) {
      // Parando de contar o tempo
      clock_t end = clock();
      // Tempo gasto no total
      registro->tempoGasto = (double)(end - begin) / CLOCKS_PER_SEC;
      return *node;
    }
    node = node->proximo;
  }
  // Parando de contar o tempo
  clock_t end = clock();
  // Tempo gasto no total
  registro->tempoGasto = (double)(end - begin) / CLOCKS_PER_SEC;
  // Caso não encontre o RG
  return lista2;
}

typedef struct
{
  // Nome
  char nome[10];
  int rg;
}ListaSeq;

void imprimirListaSeq(ListaSeq *lista, int *tam) {
  int i = 0;

  // Imprimindo
  for (i; i < *tam; i ++) {
    cout << lista[i].nome << ", " << lista[i].rg << endl;
  }
}

ListaSeq buscaBinariaSeq(ListaSeq **lista, int *tam, int item, contRegistro *registro, int *posicao) {
  // Zerando os contadores
  registro->mov = 0;
  registro->comp = 0;
  // Começando a contar o tempo de execução do código
  clock_t begin = clock();

  int inicio = 0;
  int final = *tam - 1;
  ListaSeq itemDesejado;
  itemDesejado.rg = -1;
  registro->mov += 4;

  while (inicio <= final) {  /* Condição de parada */

    int i = (inicio + final) / 2;  /* Calcula o meio do sub-vetor */

    if ((*lista)[i].rg == item) {  /* Item encontrado */
      strcpy(itemDesejado.nome, (*lista)[i].nome);
      itemDesejado.rg = (*lista)[i].rg;
      registro->mov += 2;
      // Parando de contar o tempo
      clock_t end = clock();
      // Tempo gasto no total
      registro->tempoGasto = (double)(end - begin) / CLOCKS_PER_SEC;
      *posicao = i;
      
      return itemDesejado;
    }

    if ((*lista)[i].rg < item) {  /* Item está no sub-vetor à direita */
      inicio = i + 1;
    } else {  /* vector[i] > item. Item está no sub-vetor à esquerda */
      final = i;
    }
    registro->mov ++;
    registro->comp += 2;
  }
  
  // Parando de contar o tempo
  clock_t end = clock();
  // Tempo gasto no total
  registro->tempoGasto = (double)(end - begin) / CLOCKS_PER_SEC;
  return itemDesejado;
}

Node* buscaBinariaEnc(ListaEnc *lista, int *tam, int item, contRegistro *registro) {
  // Zerando os contadores
  registro->mov = 0;
  registro->comp = 0;
  // Começando a contar o tempo de execução do código
  clock_t begin = clock();

  int inicio = 0;
  int final = *tam - 1;
  Node *itemDesejado = (Node*)malloc(sizeof(Node));
  itemDesejado->rg = -1;
  registro->mov += 4;

  while (inicio <= final) {  /* Condição de parada */

    int i = (inicio + final) / 2;  /* Calcula o meio do sub-vetor */

    if (getByIndex(lista, i)->rg == item) {  /* Item encontrado */
      strcpy(itemDesejado->nome, getByIndex(lista, i)->nome);
      itemDesejado->rg = getByIndex(lista, i)->rg;
      registro->mov += 2;
      // Parando de contar o tempo
      clock_t end = clock();
      // Tempo gasto no total
      registro->tempoGasto = (double)(end - begin) / CLOCKS_PER_SEC;
      return itemDesejado;
    }

    if (getByIndex(lista, i)->rg < item) {  /* Item está no sub-vetor à direita */
      inicio = i + 1;
    } else {  /* vector[i] > item. Item está no sub-vetor à esquerda */
      final = i;
    }
    registro->mov ++;
    registro->comp += 2;
  }
  
  // Parando de contar o tempo
  clock_t end = clock();
  // Tempo gasto no total
  registro->tempoGasto = (double)(end - begin) / CLOCKS_PER_SEC;
  return itemDesejado;
}

// Adicionar item na lista
void adcItemListaSeq(ListaSeq **lista, int *tam, char nome[], int rg, contRegistro* registro) {
  // Zerando os contadores
  registro->mov = 0;
  registro->comp = 0;
  // Começando a contar o tempo de execução do código
  clock_t begin = clock();
  // Realocando memória para receber novo item da lista
  (*lista) = (ListaSeq *)realloc((*lista), (*tam+1)*sizeof(ListaSeq));
  // Adicionando os novos dados na lista
  (*lista)[*tam].rg = rg;
  strcpy((*lista)[*tam].nome, nome);
  (*tam) ++;
  // Parando de contar o tempo
  clock_t end = clock();
  // Tempo gasto no total
  registro->tempoGasto = (double)(end - begin) / CLOCKS_PER_SEC;
  // Número de movimentações
  registro->mov += 4;
  // Número de comparações
  registro->comp = 0;
}

// Adicionar item na lista
void inserirPosSeq(ListaSeq **lista, int posN, int *tam, char nome[], int rg, contRegistro* registro) {
  // Zerando os contadores
  registro->mov = 0;
  registro->comp = 0;
  // Index lista cópia
  int j = 0;
  // Começando a contar o tempo de execução do código
  clock_t begin = clock();
  ListaSeq *listaCopia;
  listaCopia = (ListaSeq *)malloc((*tam+1)*sizeof(ListaSeq));
  registro->mov += 1;

  // Passando os valores da lista original para a lista cópia
  for (int i = 0; i < *tam + 1; i++) {
    if (posN == i) {
      listaCopia[i].rg = rg;
      strcpy(listaCopia[i].nome, nome);
      j ++;
      continue;
    }
    else {
      // Movendo os itens para frente
      listaCopia[i].rg = (*lista)[i - j].rg;
      strcpy(listaCopia[i].nome, (*lista)[i - j].nome);
      registro->mov += 2;
      registro->comp ++;
    }
  }
  (*tam) ++;
  // Realocando memória para o novo tamanho da lista
  (*lista) = (ListaSeq *)realloc((*lista), (*tam)*sizeof(ListaSeq));

  // Passando os itens da lista cópia para a original
  for (int i = 0; i < *tam; i ++) {
    registro->comp ++;
    (*lista)[i].rg = listaCopia[i].rg;
    strcpy((*lista)[i].nome, listaCopia[i].nome);
    registro->comp ++;
  }

  // Parando de contar o tempo
  clock_t end = clock();
  // Tempo gasto no total
  registro->tempoGasto = (double)(end - begin) / CLOCKS_PER_SEC;
}

// Adicionar item no final da lista
void adcItemInicioListaSeq(ListaSeq **lista, int *tam, char nome[], int rg, contRegistro* registro) {
  // Zerando os contadores
  registro->mov = 0;
  registro->comp = 0;
  // Começando a contar o tempo de execução do código
  clock_t begin = clock();
  // Cópia da lista original
  ListaSeq *listaCopia;
  // Alocando memória para a lista cópia
  listaCopia = (ListaSeq *)malloc((*tam)*sizeof(ListaSeq));
  // Realocando memória para receber novo item da lista
  (*lista) = (ListaSeq *)realloc((*lista), (*tam+1)*sizeof(ListaSeq));
  registro->mov += 2;

  // Passando os valores da lista original para a lista cópia
  for (int i = 0; i < *tam; i++) {
      // Movendo os itens para frente
      listaCopia[i].rg = (*lista)[i].rg;
      strcpy(listaCopia[i].nome, (*lista)[i].nome);
      registro->mov += 2;
      registro->comp ++;
  }

  // Passando os itens da lista uma posição para frente
  for (int i = 1; i < *tam + 1; i++) {
      // Movendo os itens para frente
      (*lista)[i].rg = listaCopia[i - 1].rg;
      strcpy((*lista)[i].nome, listaCopia[i - 1].nome);
      registro->mov += 2;
      registro->comp ++;
  }

  // Adicionando o novo item no início da lista
  (*lista)[0].rg = rg;
  strcpy((*lista)[0].nome, nome);
  // Incrementando a variável de tamanho da lista
  (*tam) ++;
  // Número de movimentações
  registro->mov += 3;
  // Parando de contar o tempo
  clock_t end = clock();
  // Tempo gasto no total
  registro->tempoGasto = (double)(end - begin) / CLOCKS_PER_SEC;
  // Número de comparações
  registro->comp = 0;
}

// Remover primeiro item da lista
void remvoeInicioSeq(ListaSeq **lista, int *tam, contRegistro* registro) {
  // Zerando os contadores
  registro->mov = 0;
  registro->comp = 0;
  // Começando a contar o tempo de execução do código
  clock_t begin = clock();
  // Cópia da lista originala
  ListaSeq *listaCopia;
  // Alocando memória para a lista cópia
  listaCopia = (ListaSeq *)malloc((*tam-1)*sizeof(ListaSeq));
  registro->mov += 1;

  // Passando os valores da lista original para a lista cópia
  for (int i = 1; i < *tam; i++) {
      // Movendo os itens para frente
      listaCopia[i-1].rg = (*lista)[i].rg;
      strcpy(listaCopia[i-1].nome, (*lista)[i].nome);
      registro->mov += 2;
      registro->comp ++;
  }

  // Passando os itens da lista uma posição para trás
  for (int i = 0; i < *tam - 1; i++) {
      // Movendo os itens para frente
      (*lista)[i].rg = listaCopia[i].rg;
      strcpy((*lista)[i].nome, listaCopia[i].nome);
      registro->mov += 2;
      registro->comp ++;
  }

  // Realocando memória para o novo tamanho da lista
  (*lista) = (ListaSeq *)realloc((*lista), (*tam-1)*sizeof(ListaSeq));
  // Incrementando a variável de tamanho da lista
  (*tam) --;
  // Número de movimentações
  registro->mov += 2;
  // Parando de contar o tempo
  clock_t end = clock();
  // Tempo gasto no total
  registro->tempoGasto = (double)(end - begin) / CLOCKS_PER_SEC;
}

void removeFinalSeq(ListaSeq **lista, int *tam, contRegistro* registro) {

  // Zerando os contadores
  registro->mov = 0;
  registro->comp = 0;
  // Começando a contar o tempo de execução do código
  clock_t begin = clock();
  (*lista) = (ListaSeq *)realloc((*lista), (*tam-1)*sizeof(ListaSeq));
  // Incrementando a variável de tamanho da lista
  (*tam) --;
  // Número de movimentações
  registro->mov += 2;
  // Parando de contar o tempo
  clock_t end = clock();
  // Tempo gasto no total
  registro->tempoGasto = (double)(end - begin) / CLOCKS_PER_SEC;
}

// Remover primeiro item da lista
void remvoePosNSeq(ListaSeq **lista, int *tam, int posN,contRegistro* registro) {
  // Zerando os contadores
  registro->mov = 0;
  registro->comp = 0;
  // Index da lista original
  int j = 0;
  // Começando a contar o tempo de execução do código
  clock_t begin = clock();
  // Cópia da lista originala
  ListaSeq *listaCopia;
  // Alocando memória para a lista cópia
  listaCopia = (ListaSeq *)malloc((*tam-1)*sizeof(ListaSeq));
  registro->mov += 2;

  // Passando os valores da lista original para a lista cópia
  for (int i = 0; i < *tam - 1; i++) {
      registro->comp ++;
      registro->mov ++;
      if (i != posN) {
        // Movendo os itens para frente
        listaCopia[i].rg = (*lista)[j].rg;
        strcpy(listaCopia[i].nome, (*lista)[j].nome);
        registro->mov += 2;
      }
      else {
        j ++;
        listaCopia[i].rg = (*lista)[j].rg;
        strcpy(listaCopia[i].nome, (*lista)[j].nome);
        registro->mov += 3;
      }
      j ++;
  }

  // Passando os itens da lista cópia para a original
  for (int i = 0; i < *tam - 1; i++) {
      // Movendo os itens para frente
      (*lista)[i].rg = listaCopia[i].rg;
      strcpy((*lista)[i].nome, listaCopia[i].nome);
      registro->mov += 2;
  }

  // Realocando memória para o novo tamanho da lista
  (*lista) = (ListaSeq *)realloc((*lista), (*tam-1)*sizeof(ListaSeq));
  // Incrementando a variável de tamanho da lista
  (*tam) --;
  // Número de movimentações
  registro->mov += 2;
  // Parando de contar o tempo
  clock_t end = clock();
  // Tempo gasto no total
  registro->tempoGasto = (double)(end - begin) / CLOCKS_PER_SEC;
}

ListaSeq procurarRGSeq(ListaSeq **lista, int *tam, int rg,contRegistro* registro) {
  // Zerando os contadores
  registro->mov = 0;
  registro->comp = 0;
  // Começando a contar o tempo de execução do código
  clock_t begin = clock();
  // Nó que será retornado caso o RG não seja encontrado
  ListaSeq lista2;
  // Registro
  registro->mov += 3;

  // Passando pelos itens da lista
  for (int i = 0; i < *tam; i ++) {
    registro->comp ++;
    lista2.rg = (*lista)[i].rg;
    strcpy(lista2.nome, (*lista)[i].nome);
    // Caso encontre o RG pesquisado
    if (lista2.rg == rg) {
      // Parando de contar o tempo
      clock_t end = clock();
      // Tempo gasto no total
      registro->tempoGasto = (double)(end - begin) / CLOCKS_PER_SEC;
      return lista2;
    }
  }
  // Caso não encontre o RG pesquisado
  strcpy(lista2.nome, "SemNome");
  lista2.rg = 0;
  // Parando de contar o tempo
  clock_t end = clock();
  // Tempo gasto no total
  registro->tempoGasto = (double)(end - begin) / CLOCKS_PER_SEC;
  // Caso não encontre o RG
  return lista2;
}
