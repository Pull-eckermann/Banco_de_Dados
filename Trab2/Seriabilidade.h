#ifndef SERIABILIDADE_H
#define SERIABILIDADE_H

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

/*------------------------------------------------------------*/
void criaAresta(nodoT* i, nodoT* j);
void addNodoGrafo(listaNodoT **grafo, nodoT *nodo);
nodoT *buscaNodoGrafo(listaNodoT *grafo, unsigned int n);
nodoT *initNodo(unsigned int n_transaction);
void criaGrafo(listaNodoT **grafo, operacao *listOp);
int buscaCicloGrafo(listaNodoT *grafo);
int DFSNodo(nodoT *t);
int tamGrafo(listaNodoT *grafo);
void freeGrafo(listaNodoT **grafo);

#endif // SERIABILIDADE_H
