#include "read_file.cpp"
#include <string>
#include <math.h>

// Selection Sort Lista Sequencial
void SelSortSeq(ListaSeq **lista, int *tam, contRegistro* registro) {
  // Zerando os contadores
  registro->mov = 0;
  registro->comp = 0;
  // Começando a contar o tempo de execução do código
  clock_t begin = clock();
  int menorPos;
  ListaSeq aux;
  registro->mov += 2;

  // Passando pelos itens da lista
  for (int i = 0; i < *tam - 1; i ++) {
    menorPos = i;
    // Comparando com os demais itens da lista
    for (int j = i + 1; j < *tam; j ++) {
      // Caso encontre um valor menor do que o valor atual
      if ((*lista)[j].rg < (*lista)[menorPos].rg) {
        // Novo menor valor encontrado
        menorPos = j;
      }
    }
    if (i != menorPos) {
      aux = (*lista)[i];
      (*lista)[i] = (*lista)[menorPos];
      (*lista)[menorPos] = aux;
    }
    registro->mov += 8;
    registro->mov += 4;
  }
  // Parando de contar o tempo
  clock_t end = clock();
  // Tempo gasto no total
  registro->tempoGasto = (double)(end - begin) / CLOCKS_PER_SEC;
}

// Selection Sort Lista Encadeada
void SelSortEnc(ListaEnc *lista, contRegistro* registro) {
  // Zerando os contadores
  registro->mov = 0;
  registro->comp = 0;
  // Começando a contar o tempo de execução do código
  clock_t begin = clock();
  Node *nodeI, *nodeJ;
  Node *menorPos;
  char auxNome[30];
  int auxRg;
  
  // Início da lista 
  nodeI = lista->inicio;
  nodeJ = nodeI->proximo;
  registro->mov += 7;
  // Passando pelos itens da lista
  while (nodeI != NULL) {
    menorPos = nodeI;
    // Comparando com os demais itens da lista
    while (nodeJ != NULL) {
      // Caso encontre um valor menor do que o valor atual
      if (nodeJ->rg < menorPos->rg) {
        // Novo menor valor encontrado
        menorPos = nodeJ;
      }
      nodeJ = nodeJ->proximo;
    }

    if (nodeI->rg != menorPos->rg) {
      // Cópia dos dados da NodeI
      strcpy(auxNome, nodeI->nome);
      auxRg = nodeI->rg;

      strcpy(nodeI->nome, menorPos->nome);
      nodeI->rg = menorPos->rg;

      strcpy(menorPos->nome, auxNome);
      menorPos->rg = auxRg;
    }
    if (nodeI->proximo == NULL) {
      break;
    }
    nodeI = nodeI->proximo;
    nodeJ = nodeI->proximo;
    registro->mov += 11;
    registro->comp += 5;
  }
  // Parando de contar o tempo
  clock_t end = clock();
  // Tempo gasto no total
  registro->tempoGasto = (double)(end - begin) / CLOCKS_PER_SEC;
}

// Selection Sort Lista Sequencial
void InsecSortSeq(ListaSeq **lista, int *tam, contRegistro* registro) {
  // Zerando os contadores
  registro->mov = 0;
  registro->comp = 0;
  // Começando a contar o tempo de execução do código
  clock_t begin = clock();
  int indice;
  ListaSeq aux;

  registro->mov += 2;
  // Passando pelos itens da lista
  for (int i = 0; i < *tam; i ++) {
    aux = (*lista)[i];
    indice = i;

    // Comparando com os demais itens da lista
    while (indice > 0 && (*lista)[indice - 1].rg > aux.rg) {
      (*lista)[indice] = (*lista)[indice - 1];
      indice --;
    }
    (*lista)[indice] = aux;
    registro->mov += 5;
    registro->comp += 2;
  }
  // Parando de contar o tempo
  clock_t end = clock();
  // Tempo gasto no total
  registro->tempoGasto = (double)(end - begin) / CLOCKS_PER_SEC;
}

// Selection Sort Lista Encadeada
void InsecSortEnc(ListaEnc *lista, int *tam, contRegistro* registro) {
  // Zerando os contadores
  registro->mov = 0;
  registro->comp = 0;
  // Começando a contar o tempo de execução do código
  clock_t begin = clock();
  int indice;
  Node *aux;
  char nome[30], nome2[30];
  int rg, rg2;

  registro->mov += 4;
  // Passando pelos itens da lista
  for (int i = 0; i < *tam; i ++) {
    strcpy(nome, getByIndex(lista, i)->nome);
    rg = getByIndex(lista, i)->rg;
    indice = i;

    // Comparando com os demais itens da lista
    while (indice > 0 && getByIndex(lista, indice - 1)->rg > rg) {
      strcpy(nome2, getByIndex(lista, indice - 1)->nome);
      rg2 = getByIndex(lista, indice - 1)->rg;
      
      strcpy(getByIndex(lista, indice)->nome, nome2);
      getByIndex(lista, indice)->rg = rg2;
      indice --;
    }
    strcpy(getByIndex(lista, indice)->nome, nome);
    getByIndex(lista, indice)->rg = rg;
    registro->mov += 10;
    registro->comp += 2;
  }
  // Parando de contar o tempo
  clock_t end = clock();
  // Tempo gasto no total
  registro->tempoGasto = (double)(end - begin) / CLOCKS_PER_SEC;
}

// Bubble sort lista encadeada
void bubbleSortEnc(ListaEnc *lista, int *tam, contRegistro* registro) {
  // Zerando os contadores
  registro->mov = 0;
  registro->comp = 0;
  // Começando a contar o tempo de execução do código
  clock_t begin = clock();
  // Variável auxiliar
  char nome[30];
  int rg;
  Node *nodeI, *nodeJ;
  nodeI = lista->inicio;
  nodeJ = lista->inicio;

  registro->mov += 5;
  for (int i = 0; i < *tam; i ++) {
    for (int j = 0; j < *tam - i - 1; j ++) {
      if (nodeJ->rg > nodeJ->proximo->rg) {
        strcpy(nome, nodeJ->nome);
        rg = nodeJ->rg;

        strcpy(nodeJ->nome, nodeJ->proximo->nome);
        nodeJ->rg = nodeJ->proximo->rg;
        
        strcpy(nodeJ->proximo->nome, nome);
        nodeJ->proximo->rg = rg;
      }
      nodeJ = nodeJ->proximo;
    }
    nodeJ = lista->inicio;
    registro->mov += 8;
    registro->comp += 3;
  }
  // Parando de contar o tempo
  clock_t end = clock();
  // Tempo gasto no total
  registro->tempoGasto = (double)(end - begin) / CLOCKS_PER_SEC;
}

// Bubble sort lista sequencial
void bubbleSortSeq(ListaSeq **lista, int *tam, contRegistro* registro) {
  // Zerando os contadores
  registro->mov = 1;
  registro->comp = 0;
  // Começando a contar o tempo de execução do código
  clock_t begin = clock();
  // Variável auxiliar
  ListaSeq aux;

  for (int i = 0; i < *tam; i ++) {
    for (int j = 0; j < *tam - i - 1; j ++) {
      if ((*lista)[j].rg > (*lista)[j + 1].rg) {
        aux = (*lista)[j];
        (*lista)[j] = (*lista)[j + 1];
        (*lista)[j + 1] = aux;
      }
      registro->mov += 3;
      registro->comp += 2;
    }
    registro->comp ++;
  }
  // Parando de contar o tempo
  clock_t end = clock();
  // Tempo gasto no total
  registro->tempoGasto = (double)(end - begin) / CLOCKS_PER_SEC;
}

void shellSortEnc(ListaEnc *lista, int *tam, contRegistro* registro) {
  // Zerando os contadores
  registro->mov = 0;
  registro->comp = 0;
  // Começando a contar o tempo de execução do código
  clock_t begin = clock();
  int i, j, h = 1;
  Node *node = lista->inicio;
  // Cópia dos valores do nó
  char nome[10], nomeJ[30];
  int rg, rgJ;

  registro->mov += 8;
  // Calculando o "h" inicial
  while (h < *tam/3) {
    h = 3 * h + 1;
    registro->comp ++;
    registro->mov ++;
  }

  // Ordenando a lista
  while (h > 0) {
    for (i = h; i < *tam; i ++) {
      // Salvando os valores do nó em um nó auxiliar
      strcpy(nome, getByIndex(lista, i)->nome);
      rg = getByIndex(lista, i)->rg;

      // Cópia do Index atual que será utilizado para ordernar por intervalos
      j = i;
      registro->mov += 3;
      // Efetuando comparação entre elementos com distância "h" entre si
      while (j >= h && rg < getByIndex(lista, j - h)->rg) {
        // Trocando os valores dos nós
        strcpy(nomeJ, getByIndex(lista, j - h)->nome);
        rgJ = getByIndex(lista, j - h)->rg;

        strcpy(getByIndex(lista, j)->nome, nomeJ);
        getByIndex(lista, j)->rg = rgJ;
        j = j - h;
        registro->mov += 5;
        registro->comp ++;
      }
      strcpy(getByIndex(lista, j)->nome, nome);
      getByIndex(lista, j)->rg = rg;
      registro->mov += 2;
      registro->comp ++;
    }
    // Atualizando o valor de h
    h = (h - 1) / 3;
    registro->mov ++;
    registro->comp ++;
  }
  // Parando de contar o tempo
  clock_t end = clock();
  // Tempo gasto no total
  registro->tempoGasto = (double)(end - begin) / CLOCKS_PER_SEC;
}

void shellSortSeq(ListaSeq **lista, int *tam, contRegistro* registro) {
  // Zerando os contadores
  registro->mov = 0;
  registro->comp = 0;
  // Começando a contar o tempo de execução do código
  clock_t begin = clock();
  int i, j, h = 1;
  ListaSeq aux;

  registro->mov += 4;
  // Calculando o "h" inicial
  while (h < *tam/3) {
    h = 3 * h + 1;
    registro->comp ++;
    registro->mov ++;
  }

  // Ordenandop a lista
  while (h > 0) {
    for (i = h; i < *tam; i ++) {
      aux = (*lista)[i];
      j = i;
      // Efetuando comparação entre elementos com distância "h" entre si
      while (j >= h && aux.rg < (*lista)[j - h].rg) {
        (*lista)[j] = (*lista)[j - h];
        j = j - h;
        registro->mov += 2;
        registro->comp ++;
      }
      (*lista)[j] = aux;
      registro->mov += 3;
      registro->comp ++;
    }
    // Atualizando o valor de h
    h = (h - 1) / 3;
    registro->comp ++;
    registro->mov ++;
  }
  // Parando de contar o tempo
  clock_t end = clock();
  // Tempo gasto no total
  registro->tempoGasto = (double)(end - begin) / CLOCKS_PER_SEC;
}

int divideLista(ListaSeq **lista, int inicio, int final, contRegistro* registro){
    int esq, dir;
    ListaSeq pivo, aux;
    // Index do início da lista
    esq = inicio;
    // Index do final da lista
    dir = final;
    pivo = (*lista)[inicio];
    registro->mov += 7;
    while(esq < dir){
        while(esq <= final && (*lista)[esq].rg <= pivo.rg)
            esq++;
            registro->comp ++;
            registro->mov ++;

        while(dir >= 0 && (*lista)[dir].rg > pivo.rg)
            dir --;
            registro->comp ++;
            registro->mov ++;

        if(esq < dir){
            aux = (*lista)[esq];
            (*lista)[esq] = (*lista)[dir];
            (*lista)[dir] = aux;
            registro->comp ++;
            registro->mov += 3;
        }
      registro->comp ++;
    }
    (*lista)[inicio] = (*lista)[dir];
    (*lista)[dir] = pivo;
    registro->mov += 2;
    return dir;
}

void quickSortSeq(ListaSeq **lista, int inicio, int fim, contRegistro* registro) {
  // Pivô que será utilizado para dividir a função
  int pivo;
  registro->mov ++;
  registro->comp ++;
  if(fim > inicio){
      // Gerando o pivô e dividindo a lista
      pivo = divideLista(lista, inicio, fim, registro);
      // Ordenando a lista antes do pivô
      quickSortSeq(lista, inicio, pivo - 1, registro);
      // Ordenando a lista depois do pivô
      quickSortSeq(lista, pivo + 1, fim, registro); 
      registro->mov += 3;
  }
}

int divideListaEnc(ListaEnc *lista, int inicio, int final, contRegistro* registro){
    int esq, dir;
    char pivoNome[10], auxNome[10];
    int pivoRG, auxRG;
    // Index do início da lista
    esq = inicio;
    // Index do final da lista
    dir = final;

    // Valor do pivô
    strcpy(pivoNome, getByIndex(lista, inicio)->nome);
    pivoRG = getByIndex(lista, inicio)->rg;

    registro->mov += 10;
    while(esq < dir){
      while(esq <= final && getByIndex(lista, esq)->rg <= pivoRG)
          esq++;
          registro->comp ++;
          registro->mov ++;

      while(dir >= 0 && getByIndex(lista, dir)->rg > pivoRG)
          dir --;
          registro->comp ++;
          registro->mov ++;

      if(esq < dir){
        strcpy(auxNome, getByIndex(lista, esq)->nome);
        auxRG = getByIndex(lista, esq)->rg;

        strcpy(getByIndex(lista, esq)->nome, getByIndex(lista, dir)->nome);
        getByIndex(lista, esq)->rg = getByIndex(lista, dir)->rg;

        strcpy(getByIndex(lista, dir)->nome, auxNome);
        getByIndex(lista, dir)->rg = auxRG;
        registro->comp ++;
        registro->mov += 6;
      }
      registro->comp ++;
    }
    strcpy(auxNome, getByIndex(lista, dir)->nome);
    auxRG = getByIndex(lista, dir)->rg;

    strcpy(getByIndex(lista, inicio)->nome, auxNome);
    getByIndex(lista, inicio)->rg = auxRG;

    strcpy(getByIndex(lista, dir)->nome, pivoNome);
    getByIndex(lista, dir)->rg = pivoRG;
    registro->mov += 6;
    return dir;
}

void quickSortEnc(ListaEnc *lista, int inicio, int fim, contRegistro* registro) {
    // Pivô que será utilizado para dividir a função
    int pivo;
    registro->mov ++;
    if(fim > inicio){
        // Gerando o pivô e dividindo a lista
        pivo = divideListaEnc(lista, inicio, fim, registro);
        // Ordenando a lista antes do pivô
        quickSortEnc(lista, inicio, pivo - 1, registro);
        // Ordenando a lista depois do pivô
        quickSortEnc(lista, pivo + 1, fim, registro);
        registro->comp ++;
        registro->mov ++;
    }
}

void mergeSeq(ListaSeq **lista, int inicio, int meio, int fim, contRegistro *registro){
  ListaSeq *listaTemp;
  // Índices da lista
  int indexP1, indexP2;
  int tam, i, j, k;
  int fim1 = 0, fim2 = 0;
  tam = fim - inicio + 1;
  indexP1 = inicio;
  indexP2 = meio+1;
  // Alocando memória para a lista temporária
  listaTemp = (ListaSeq *)malloc(tam*sizeof(ListaSeq));
  registro->mov += 13;
  // Ordenando as duas divisões da lista no ponteiro temporário
  if(listaTemp != NULL){
    for(i = 0; i < tam; i++){
      if(!fim1 && !fim2){
          if((*lista)[indexP1].rg < (*lista)[indexP2].rg) {
              listaTemp[i] = (*lista)[indexP1 ++];
          }
          else
              listaTemp[i] = (*lista)[indexP2 ++];

          if (indexP1 > meio) fim1 = 1;
          if (indexP2 > fim) fim2 = 1;
          registro->mov += 2;
          registro->comp += 3;
      }
      else{
        if(!fim1)
            listaTemp[i] = (*lista)[indexP1 ++];
        else
            listaTemp[i] = (*lista)[indexP2 ++];
        registro->mov ++;
        registro->comp ++;
      }
      registro->comp ++;
    }
    for(j = 0,  k = inicio; j < tam; j++, k++) {
        (*lista)[k] = listaTemp[j];
        registro->comp ++;
        registro->mov ++;
    }
    registro->comp ++;
  }
  free(listaTemp);
}

void mergeSortSeq(ListaSeq **lista, int inicio, int fim, contRegistro *registro) {
    // Posição do Meio da lista
    int meio;
    registro->mov ++;
    if(inicio < fim){
        // Index onde a lista será dividiva no meio
        meio = floor((inicio + fim) / 2);
        // Ordenando a primeira metade da lista
        mergeSortSeq(lista, inicio, meio, registro);
        // Ordenando a segunda metade da lista
        mergeSortSeq(lista, meio + 1, fim, registro);
        // Juntando as duas metades ordenadas
        mergeSeq(lista, inicio, meio, fim, registro);
        registro->mov ++;
        registro->comp ++;
    }
}

/*
    Algoritmo Merge Sort parte 1 e parte 2
*/

void merge_sort(ListaEnc *lista, int inicio, int fim) { // 6 ,4 ,8  ,2,7
  int meio, i, j;
  Node *posTemp;
  // Vetor Temporário
  ListaEnc listaTemp;
  listaTemp.inicio = NULL;
  listaTemp.final = NULL;
  // Variáveis auxiliares de valor
  char auxNome[10];
  int auxRG;

  // tamanho do vetor é maior que 1?
  if (inicio < fim) {
    meio = (inicio + fim) / 2; // calcula o meio do vetor
    merge_sort(lista, inicio, meio); // metade à esquerda
    merge_sort(lista, meio + 1, fim); // metade a direita

    // fazer o merge, ordenando os elementos (Segunda Etapa)
    i = inicio; // início da primeira parte do vetor, que termina em meio
    j = meio + 1; // início da segunda parte do vetor, que termina em fim

    // Percorrendo ambas as metades simultaneamente
    while (i <= meio && j <= fim) {
      if (getByIndex(lista, i)->rg < getByIndex(lista, j)->rg) {
          // Novo valor da lista auxiliar
          Node *novo = (Node*)malloc(sizeof(Node));
          // Nome
          strcpy(auxNome, getByIndex(lista, i)->nome);
          strcpy(novo->nome, auxNome);
          // RG
          auxRG = getByIndex(lista, i)->rg;
          novo->rg = auxRG;
          cout << novo->nome << ", " << novo->rg << endl;
          novo->proximo = NULL;
          lista->final->proximo = novo;
          // Caso seja o primeiro item da lista
          if (listaTemp.inicio == NULL) {
            listaTemp.inicio = novo;
          }
          lista->final = novo;
          i++;
      }
      else {
          // Novo valor da lista auxiliar
          Node *novo = (Node*)malloc(sizeof(Node));
          // Nome
          strcpy(auxNome, getByIndex(lista, j)->nome);
          strcpy(novo->nome, auxNome);
          // RG
          auxRG = getByIndex(lista, j)->rg;
          novo->rg = auxRG;
          cout << novo->nome << ", " << novo->rg << endl;
          novo->proximo = NULL;
          lista->final->proximo = novo;
          // Caso seja o primeiro item da lista
          if (listaTemp.inicio == NULL) {
            listaTemp.inicio = novo;
          }
          lista->final = novo;
          j++;
      }
    }

    // copia o resto da primeira parte se foi a segunda que finalizou
    while (i <= meio) {
      // Novo valor da lista auxiliar
      Node *novo = (Node*)malloc(sizeof(Node));
      // Nome
      strcpy(auxNome, getByIndex(lista, i)->nome);
      strcpy(novo->nome, auxNome);
      // RG
      auxRG = getByIndex(lista, i)->rg;
      novo->rg = auxRG;
      novo->proximo = NULL;
      lista->final->proximo = novo;
      // Caso seja o primeiro item da lista
      if (listaTemp.inicio == NULL) {
        listaTemp.inicio = novo;
      }
      lista->final = novo;
      i++;
    }
    // copia o resto da segunda parte se foi a primeira que finalizou
    while (j <= fim) {
      // Novo valor da lista auxiliar
      Node *novo = (Node*)malloc(sizeof(Node));
      // Nome
      strcpy(auxNome, getByIndex(lista, j)->nome);
      strcpy(novo->nome, auxNome);
      // RG
      auxRG = getByIndex(lista, j)->rg;
      novo->rg = auxRG;
      novo->proximo = NULL;
      lista->final->proximo = novo;
      // Caso seja o primeiro item da lista
      if (listaTemp.inicio == NULL) {
        listaTemp.inicio = novo;
      }
      lista->final = novo;
      j++;
    }

    // copia os elementos já ordenados do vetor auxiliar para o vetor original
    for (i = inicio; i <= fim; i++) {
      // Nome
      strcpy(auxNome, getByIndex(&listaTemp, i)->nome);
      strcpy(getByIndex(lista, i)->nome, auxNome);
      // RG
      auxRG = getByIndex(&listaTemp, i)->rg;
      getByIndex(lista, i)->rg = auxRG;
      cout << getByIndex(lista, i)->nome << ", " << getByIndex(lista, i)->rg << endl;
    }
  }
}
