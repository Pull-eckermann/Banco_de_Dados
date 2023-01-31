#include "Seriabilidade.h"

//Cria arestas do grafo do teste de seriabilidade por conflito
void criaAresta(nodoT* i, nodoT* j){
  listaNodoT *novaAresta = malloc(sizeof(listaNodoT));
  novaAresta->transaction = j;
  novaAresta->prox = i->arestas; //As arestas são inseridas no começo da fila de arestas
  i->arestas = novaAresta;  //A nova inserida passa a ser a cabeça
}

//Adiciona um nodo à lista de nodos que representa um grafo
void addNodoGrafo(listaNodoT **grafo, nodoT *nodo){
  if(nodo != NULL){
    listaNodoT *novoNodo = malloc(sizeof(listaNodoT));
    novoNodo->transaction = nodo;
    novoNodo->prox = *grafo;
    *grafo = novoNodo;
  }
}

//Realiza uma busca do nodo que contem o número de transação indicado
//Retorna o nodo caso encontre, ou NULO se não encontrar
nodoT *buscaNodoGrafo(listaNodoT *grafo, unsigned int n){
  if(grafo != NULL)
    for(listaNodoT *x = grafo; x != NULL; x = x->prox)
      if(x->transaction->n_transacao == n)
        return x->transaction;

  return NULL;
}

//Inicializa um nodo
nodoT *initNodo(unsigned int n_transaction){
  nodoT *transaction = malloc(sizeof(nodoT));
  transaction->n_transacao = n_transaction;
  transaction->arestas = NULL;
  return transaction;
}
