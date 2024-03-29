#ifndef UTILS_H
#define UTILS_H

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

typedef struct par_wr{
  unsigned int tw; // Timestamp write
  unsigned int tr; // Timestamp read
  struct par_wr *prox;
}par_wr;

/*------------------------------------------------------------*/
int isCommited(operacao *op, int commits[MAX_T]);
void freeOpList(operacao **listOp);
int tamOp(operacao *listOp);
void addOp(operacao **listOp, operacao *op);
void ordenaVetor(unsigned int **trans, int tam);


#endif // UTILS_H
