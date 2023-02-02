#ifndef SERIABILIDADE_H
#define SERIABILIDADE_H

#include <stdio.h>
#include <stdlib.h>

//Uma lista encadead simples de nodosT
typedef struct listaNodoT{
  struct nodoT *transaction;
  struct listaNodoT *prox;
}listaNodoT;

//Struct representando um nodo transação do grafo de transações
typedef struct nodoT{
  unsigned int n_transacao;
  struct listaNodoT *arestas;
}nodoT;

//Struct que representa uma operação lida da entrada padrão
typedef struct operacao{
  unsigned int timestamp;
  unsigned int n_transaction;
  char operation;
  char atributo;
  struct operacao *prox;
}operacao;
/*------------------------------------------------------------*/
void criaAresta(nodoT* i, nodoT* j);
void addNodoGrafo(listaNodoT **grafo, nodoT *nodo);
nodoT *buscaNodoGrafo(listaNodoT *grafo, unsigned int n);
nodoT *initNodo(unsigned int n_transaction);



#endif // SERIABILIDADE_H
