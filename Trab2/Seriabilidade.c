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

//Cria uma lista encadeada de transacoes de acordo com a lista de operacoes
void criaGrafo(listaNodoT **grafo, operacao *listOp){
  for(operacao *x = listOp; x != NULL; x=x->prox){
    if(buscaNodoGrafo(*grafo, x->n_transaction) == NULL){ //Retorna nulo se não encontra o nodo
      nodoT *novoNodo = initNodo(x->n_transaction); //Como não existe o nodo ainda, cria pela primeira vez
      addNodoGrafo(grafo, novoNodo); // Adiciona novo nodo no grafo
    }
  }
}

//Algoritmo para busca de ciclo em grafo baseado no seguinte endereço:
//https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/cycles-and-dags.html#sec:on-the-fly
static int cnt, pre[MAX_T];
static int cntt, post[MAX_T];

int buscaCicloGrafo(listaNodoT *grafo){
  cnt = cntt = 0;
  for(listaNodoT *g=grafo; g!=NULL; g=g->prox)
    pre[g->transaction->n_transacao] = post[g->transaction->n_transacao] = -1;
  for(listaNodoT *g=grafo; g!=NULL; g=g->prox)
    if(pre[g->transaction->n_transacao] == -1)
      if(DFSNodo(g->transaction))
        return 1; //True - Tem ciclo
  return 0; //False - Não tem ciclo
}

int DFSNodo(nodoT *t){
  pre[t->n_transacao] = cnt++;
  for(listaNodoT *a=t->arestas; a!=NULL; a=a->prox){
    nodoT *x = a->transaction;
    if(pre[x->n_transacao] == -1){
      if(DFSNodo(x))
        return 1;
    }else{
      if(post[x->n_transacao] == -1)
        return 1; //Base da recursão
    }
  }
  post[t->n_transacao] = cntt++;
  return 0; //Não encontrou ciclo
}

//Confere se o escalonamento está commitado
int isCommited(operacao *listOp, int commits[MAX_T]){
  if(listOp != NULL){
    for(operacao *op = listOp; op != NULL; op = op->prox){
      if(commits[op->n_transaction] == -1) //Se qualquer um deles estiver em -1 quer dizer que não commitou ainda
        return 0;
    }
    return 1; //Todas as transações estão marcadas como commit
  }
  return 0;
}

//Funções para liberação de espaço
void freeOpList(operacao **listOp){
  operacao *op = *listOp;
  *listOp = NULL;

  while(op != NULL){
    operacao *aux = op;
    op = op->prox;
    free(aux);
  }
}

void freeGrafo(listaNodoT **grafo){
  listaNodoT * g = *grafo;
  *grafo = NULL;

  while(g != NULL){
    listaNodoT *aux = g;
    g = g->prox;

    nodoT *t = aux->transaction;
    listaNodoT *aux2 = t->arestas;
    while(aux2 != NULL){
      listaNodoT *aux3 = aux2;
      aux2 = aux2->prox;
      free(aux3);
    }
    free(aux);
  }
}

