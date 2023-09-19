#include <iostream>
#include <stdio.h>
#include <iomanip>
#include "sort_functions.cpp"
#include <chrono>
#include <thread>
#include <stdbool.h>
#include <stdlib.h>
using namespace std;
// Função para limpar a tela

void menuLista(int *listaTam, char arquivo[], ListaEnc *listaEncadeada, ListaSeq **listaSequencial, int *tipoLista) {
  // Lista escolhida pelo usuário
  int listaEsc;
  contRegistro registroEncadeada;

  cout << "Selecione uma das listas para ser lida:" << endl;
  cout << "1 - NomeRG10.txt (10 registros)\n"
          "2 - NomeRG50.txt (50 registros)\n"
          "3 - NomeRG100.txt (100 registros)\n"
          "4 - NomeRG1K.txt (1K registros)\n"
          "5 - NomeRG10K.txt (10K registros)\n"
          "6 - NomeRG1M.txt (1Mi registros)\n"
          "7 - NomeRG100M.txt (100Mi registros)" << endl;
  cin >> listaEsc;
  cout << "Voce ira preferir:\n 1 - Lista Sequencial\n 2 - Lista Encadeada" << endl;
  cin >> *tipoLista;
  // Lendo a escolha do usuário
  switch(listaEsc) {
    case 1:
      cout << "Lista de 10 registros selecionada!" << endl;
      strcpy(arquivo, "Lista_Nomes/NomeRG10.txt"); // Setando o arquivo selecionado
      break;
    case 2:
      cout << "Lista de 50 registros selecionada!" << endl;
      strcpy(arquivo, "Lista_Nomes/NomeRG50.txt"); // Setando o arquivo selecionado
      break;
    case 3:
      cout << "Lista de 100 registros selecionada!" << endl;
      strcpy(arquivo, "Lista_Nomes/NomeRG100.txt"); // Setando o arquivo selecionado
      break;
    case 4:
      cout << "Lista de 1K registros selecionada!" << endl;
      strcpy(arquivo, "Lista_Nomes/NomeRG1K.txt"); // Setando o arquivo selecionado
      break;
    case 5:
      cout << "Lista de 10K registros selecionada!" << endl;
      strcpy(arquivo, "Lista_Nomes/NomeRG10K.txt"); // Setando o arquivo selecionado
      break;
    case 6:
      cout << "Lista de 1Mi de registros selecionada!" << endl;
      strcpy(arquivo, "Lista_Nomes/NomeRG1M.txt"); // Setando o arquivo selecionado
      break;
    case 7:
      cout << "Lista de 100Mi de registros selecionada!" << endl;
      strcpy(arquivo, "Lista_Nomes/NomeRG100M.txt"); // Setando o arquivo selecionado
      break;
  }
  cout << "Carregando as listas..." << endl;
  // Criando as listas
  setListaEnc(arquivo, listaEncadeada, &registroEncadeada, listaTam);
  cout << "Lista encadeada criada!" << endl;
  setListaSeq(listaSequencial , arquivo, listaTam);
  cout << "Lista sequencial criada!" << endl;
}

void imprimeInformacoes(contRegistro* registroEnc, contRegistro* registroSeq) {
  cout << fixed << setprecision(3);
  cout << "Numero de Comparacoes: (Encadeada: " << registroEnc->comp << "), (Sequencial: " << registroSeq->comp << ")"
  "| Numero de Movimentacoes: (Encadeada: " << registroEnc->mov << "), (Sequencial: " << registroSeq->mov << ")" 
  " | Tempo de Execucao: (Encadeada: " << registroEnc->tempoGasto << "), (Sequencial: " << registroSeq->tempoGasto << ")" << endl;
}

void InfoOrdEnc(contRegistro* registroEnc) {
  cout << fixed << setprecision(3);
  cout << "Numero de Comparacoes: " << registroEnc->comp << " | Numero de Movimentacoes: " << registroEnc->mov <<
  " | Tempo de Execucao: " << registroEnc->tempoGasto << endl;
}

void InfoOrdSeq(contRegistro* registroSeq) {
  cout << fixed << setprecision(3);
  cout << "Numero de Comparacoes: " << registroSeq->comp << " | Numero de Movimentacoes: " << registroSeq->mov <<
  " | Tempo de Execucao: " << registroSeq->tempoGasto << endl;
}

// Menu de opções das funções que o usuário irá poder executar
void menuOpcoes(ListaEnc *listaEncadeada, ListaSeq *listaSequencial, int *tam, int *tipoLista) {
  // Dados que serão adicionados na tabela
  char nome[15];
  int rg = 0;
  // Posição N que poderá ser lida
  int posN = 0;
  // Opção que será lida
  int opcaoEscolhida;
  char buffer; // Buffer teclado
  contRegistro registroEncadeada;
  contRegistro registroSequencial;
  // Nó que o usuário poderá pesquisar na lista
  ListaSeq searchSeq;
  Node searchEnc;
  // Arquivo que poderá ser lido
  char arquivo[30];


  while(true) {
    // Limpando a tela
    system("cls");
    // Título Menu
    cout << "\nMenu de opcoes: " << endl;
    cout << "1 - Insercao de um no no inicio da lista e apresentar Nome, RG, C(n), M(n), Tempo de execucao e sua posicao N na lista.\n" 
    "2 - Insercao de um no no fim da lista e apresentar Nome, RG, C(n), M(n), Tempo de execucao e sua posicao N na lista.\n" 
    "3 - Insercao de um no na posicao N e apresentar Nome, RG, C(n), M(n), Tempo de execucao e sua posicao N na lista.\n" 
    "4 - Retirar um no do inicio da lista e apresentar Nome, RG, C(n), M(n), Tempo de execucao e sua posicao N na lista.\n" 
    "5 - Retirar um no no fim da lista e apresentar Nome, RG, C(n), M(n), Tempo de execucao e sua posicao N na lista.\n"
    "6 - Retirar um no na posicao N e apresentar Nome, RG, C(n), M(n), Tempo de execucao e sua posicao N na lista.\n" 
    "7 - Procurar um no com o campo RG e apresentar Nome, RG, C(n), M(n), Tempo de execucao e sua posicao N na lista.\n"
    "  1 - Usando busca sequencial;\n"
    "  2 - Usando busca binaria.\n"
    "8 - Usar para ordenar a lista um dos algoritmos a seguir e apresentar C(n), M(n) e Tempo de execucao:\n"
    "  1 - Selection Sort;\n"
    "  2 - Insertion-Sort;\n"
    "  3 - Bubble-Sort;\n"
    "  4 - Shell-Sort;\n"
    "  5 - Quick-Sort;\n"
    "  6 - Merge Sort.\n"
    "9 - Mostrar a lista na tela.\n"
    "10 - Salvar a lista em um arquivo no formato nome, RG.\n"
    "11 - Ler a lista de um arquivo no formato nome, RG.\n"
    "12 - Sair do sistema." << endl;
    cin >> opcaoEscolhida;
    switch (opcaoEscolhida) {
      // Inserção de um nó no início da lista
      case 1:
        // Lendo os dados que serão adicionados
        lendoDados(nome, &rg);
        // Adicionando item no início da lista
        inserirInicioEnc(listaEncadeada, nome, rg, &registroEncadeada);
        adcItemInicioListaSeq(&listaSequencial, tam, nome, rg, &registroSequencial);
        // Imprimindo informações do procedimento (Num de comoparações, movimentações e tempo de execução)
        imprimeInformacoes(&registroEncadeada, &registroSequencial);
        cout << "Nome: " << nome << " | RG: " << rg << " adicionado na lista!" << endl;
        break;

      // Inserção de item no final da lista
      case 2:
        // Lendo os dados que serão adicionados
        lendoDados(nome, &rg);
        // Adicionando item no final da lista
        inserirFinalEnc(listaEncadeada, nome, rg, &registroEncadeada);
        adcItemListaSeq(&listaSequencial, tam, nome, rg, &registroSequencial);
        // Imprimindo informações do procedimento (Num de comoparações, movimentações e tempo de execução)
        imprimeInformacoes(&registroEncadeada, &registroSequencial);
        cout << "Nome: " << nome << " | RG: " << rg << " adicionado na lista!" << endl;
        break;

      // Insercao de um no na posicao N
      case 3:
        // Lendo os dados que serão adicionados
        lendoDados(nome, &rg);
        cout << "Digite a posicao na qual deseja inserir os novos dados: " << endl;
        cin >> posN;
        // Adicionando os dados nas listas
        inserirPosNEnc(listaEncadeada, nome, rg, posN, &registroEncadeada);
        inserirPosSeq(&listaSequencial, posN, tam, nome, rg, &registroSequencial);
        imprimeInformacoes(&registroEncadeada, &registroSequencial);
        cout << "Nome: " << nome << " | RG: " << rg << " adicionado na lista!" << endl;
        break;
      
      // Retirar um no do inicio da lista
      case 4:
        strcpy(nome, listaSequencial[0].nome);
        rg = listaSequencial[0].rg;
        // Removendo itens
        removeInicioEnc(listaEncadeada, &registroEncadeada);
        remvoeInicioSeq(&listaSequencial, tam, &registroSequencial);
        imprimeInformacoes(&registroEncadeada, &registroSequencial);
        cout << "Nome: " << nome << " | RG: " << rg << " removido da lista!" << endl;
        break;

      // Retirar um no do fim da lista
      case 5:
        strcpy(nome, listaSequencial[*tam - 1].nome);
        rg = listaSequencial[*tam - 1].rg;
        // Removendo itens
        removeFinalEnc(listaEncadeada, &registroEncadeada);
        removeFinalSeq(&listaSequencial, tam, &registroSequencial);
        imprimeInformacoes(&registroEncadeada, &registroSequencial);
        cout << "Nome: " << nome << " | RG: " << rg << " removido da lista!" << endl;
        break;

      // Retirar um no na posicao N
      case 6:
        cout << "Digite a posicao do no que sera retirado: " << endl;
        cin >> posN;
        strcpy(nome, listaSequencial[posN].nome);
        rg = listaSequencial[posN].rg;
        removePosNEnc(listaEncadeada, posN, &registroEncadeada);
        remvoePosNSeq(&listaSequencial, tam, posN, &registroSequencial);
        imprimeInformacoes(&registroEncadeada, &registroSequencial);
        cout << "Nome: " << nome << " | RG: " << rg << " removido da lista!" << endl;
        break;

      // Procurar um no com o campo RG
      case 7:
        // Tipo da busca que será realizada
        int tipoBusca;
        int posicao;

        // Lendo o tipo da busca
        cout << "Selecione um dos tipos de busca:\n  1 - Ordenada\n  2 - Binaria" << endl;
        cin >> tipoBusca;
        
        // Lendo o RG
        cout << "Digite o RG que deseja pesquisar: " << endl;
        cin >> rg;
        // Busca ordenada
        if (tipoBusca == 1) {
          // Procurando o RG nas listas
          searchSeq = procurarRGSeq(&listaSequencial, tam, rg, &registroSequencial);
          searchEnc = procurarRGEnc(listaEncadeada, tam, rg, &registroEncadeada);
          // Caso o RG tenha sido encontrado
          if (searchSeq.rg != 0 && searchEnc.rg != 0) {    
            imprimeInformacoes(&registroEncadeada, &registroSequencial);
            cout << "Nome: " << searchEnc.nome << " | RG: " << searchEnc.rg << " encontrado!" << endl;
          }
          else {
            cout << "Registro nao encontrado." << endl;
          }
        }
        // Busca Binária
        else {
          // Lista Sequencial
          if (*tipoLista == 1) {
            ListaSeq resultadoBusca;
            resultadoBusca = buscaBinariaSeq(&listaSequencial, tam, rg, &registroSequencial, &posicao);
            cout << "Posicao: " << posicao << endl;
            if (resultadoBusca.rg == - 1) {
              cout << "O valor nao foi encontrado!" << endl;
            }
            else {
              cout << resultadoBusca.nome << ", " << resultadoBusca.rg << endl;
            }
            InfoOrdSeq(&registroSequencial);
          }
          else {
            Node *resultadoBusca = (Node*)malloc(sizeof(Node));
            resultadoBusca = buscaBinariaEnc(listaEncadeada, tam, rg, &registroSequencial);
            if (resultadoBusca->rg == - 1) {
              cout << "O valor nao foi encontrado!" << endl;
            }
            else {
              cout << resultadoBusca->nome << ", " << resultadoBusca->rg << endl;
            }
            InfoOrdSeq(&registroEncadeada);
          }
        }
        break;

      // Selection sort
      case 8:
        int modoOrdenacao;
        cout << "Escolha um dos modos de ordenacao a seguir:\n"
        "  1 - Selection Sort;\n"
        "  2 - Insertion-Sort;\n"
        "  3 - Bubble-Sort;\n"
        "  4 - Shell-Sort;\n"
        "  5 - Quick-Sort;\n"
        "  6 - Merge Sort." << endl;
        cin >> modoOrdenacao;
        switch (modoOrdenacao) {
          case 1:
            if (*tipoLista == 1) {
              SelSortSeq(&listaSequencial, tam, &registroSequencial);
              InfoOrdSeq(&registroSequencial);
            }
            else {
              SelSortEnc(listaEncadeada, &registroEncadeada);
              InfoOrdEnc(&registroEncadeada);
            }
            break;
          case 2:
            if (*tipoLista == 1) {
              InsecSortSeq(&listaSequencial, tam, &registroSequencial);
              InfoOrdSeq(&registroSequencial);
            }
            else {
              InsecSortEnc(listaEncadeada, tam, &registroEncadeada);
              InfoOrdEnc(&registroEncadeada);
            }
            break;
          case 3:
            if (*tipoLista == 1) {
              bubbleSortSeq(&listaSequencial, tam, &registroSequencial);
              InfoOrdSeq(&registroSequencial);
            }
            else {
              bubbleSortEnc(listaEncadeada, tam, &registroEncadeada);
              InfoOrdEnc(&registroEncadeada);
            }
            break;
          case 4:
            if (*tipoLista == 1) {
              shellSortSeq(&listaSequencial, tam, &registroSequencial);
              InfoOrdSeq(&registroSequencial);
            }
            else {
              shellSortEnc(listaEncadeada, tam, &registroEncadeada);
              InfoOrdEnc(&registroEncadeada);
            }
            break;
          case 5:
            if (*tipoLista == 1) {   
              // Zerando os contadores
              registroSequencial.mov = 0;
              registroSequencial.comp = 0;
              // Começando a contar o tempo de execução do código
              clock_t begin = clock();
              quickSortSeq(&listaSequencial, 0, *tam - 1, &registroSequencial);
              // Parando de contar o tempo
              clock_t end = clock();
              // Tempo gasto no total
              registroSequencial.tempoGasto = (double)(end - begin) / CLOCKS_PER_SEC;
              InfoOrdSeq(&registroSequencial);
            }
            else {   
              // Zerando os contadores
              registroEncadeada.mov = 0;
              registroEncadeada.comp = 0;
              // Começando a contar o tempo de execução do código
              clock_t begin = clock();
              quickSortEnc(listaEncadeada, 0, *tam - 1, &registroEncadeada);
              // Parando de contar o tempo
              clock_t end = clock();
              // Tempo gasto no total
              registroEncadeada.tempoGasto = (double)(end - begin) / CLOCKS_PER_SEC;
              InfoOrdEnc(&registroEncadeada);
            }
            break;
          case 6:
            if (*tipoLista == 1) {   
              // Zerando os contadores
              registroSequencial.mov = 0;
              registroSequencial.comp = 0;
              // Começando a contar o tempo de execução do código
              clock_t begin = clock();
              mergeSortSeq(&listaSequencial, 0, *tam - 1, &registroSequencial);
              // Parando de contar o tempo
              clock_t end = clock();
              // Tempo gasto no total
              registroSequencial.tempoGasto = (double)(end - begin) / CLOCKS_PER_SEC;
              InfoOrdSeq(&registroSequencial);
            }
            else {   
              // Zerando os contadores
              registroEncadeada.mov = 0;
              registroEncadeada.comp = 0;
              // Começando a contar o tempo de execução do código
              clock_t begin = clock();
              quickSortEnc(listaEncadeada, 0, *tam - 1, &registroEncadeada);
              // Parando de contar o tempo
              clock_t end = clock();
              // Tempo gasto no total
              registroEncadeada.tempoGasto = (double)(end - begin) / CLOCKS_PER_SEC;
              InfoOrdEnc(&registroEncadeada);
            }
            break;
          default:
            break;
        }
        break;

      // Imprimindo a lista na tela
      case 9:
        // Imprimindo
        if (*tipoLista == 1) {
          imprimirListaSeq(listaSequencial, tam);
        }
        else {
          imprimirListaEncadeada(listaEncadeada);
        }
        break;

      // Salvar a lista em um arquivo no formato nome, RG
      case 10:
          // Lendo o nome do arquivo
          cout << "Digite o nome do arquivo no qual a lista sera escrita: " << endl;
          cin >> arquivo;
          // Escrevendo a lista
          escreverLista(&listaSequencial, arquivo, tam);
          break;

      // Ler a lista de um arquivo no formato nome, RG
      case 11:
          // Lendo o nome do arquivo
          cout << "Digite o nome do arquivo que sera lido: " << endl;
          cin >> arquivo;
          setListaEnc(arquivo, listaEncadeada, &registroEncadeada, tam);
          setListaSeq(&listaSequencial , arquivo, tam);
          cout << "Listas criadas!" << endl;
          break;
      // Encerrando o programa
      case 12:
        cout << "Encerrando..." << endl;
        exit(0);

      default:
        break;
    }
    cout << "Digite 'c' para continuar..." << endl;
    cin >> buffer;
  }
}
