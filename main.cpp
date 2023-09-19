#include "menu.cpp"

int main() {
  int listaTam = 0;
  char arquivo[30];
  int tipoLista;
  // Lista Encadeada
  ListaEnc listaEncadeada;
  // Lista Sequencial
  ListaSeq *listaSequencial;
  // Selecionando Tamanho da lista
  menuLista(&listaTam, arquivo, &listaEncadeada, &listaSequencial, &tipoLista);
  menuOpcoes(&listaEncadeada, listaSequencial, &listaTam, &tipoLista);

  return 0;
}
