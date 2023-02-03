#ifndef SERIABILIDADE_H
#define SERIABILIDADE_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_T 1000

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
void criaGrafo(listaNodoT **grafo, operacao *listOp);
int buscaCicloGrafo(listaNodoT *grafo);
int DFSNodo(nodoT *t);
int isCommited(operacao *op, int commits[MAX_T]);
void freeOpList(operacao **listOp);
void freeGrafo(listaNodoT **grafo);

#endif // SERIABILIDADE_H
