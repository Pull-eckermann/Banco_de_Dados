#include "utils.h"

//Confere se o escalonamento está commitado
int isCommited(operacao *listOp, int commits[MAX_T]){
  if(listOp != NULL){
    for(operacao *op = listOp; op != NULL; op = op->prox){
      //Cada indice do vetor commits representa o número da transação
      if(commits[op->n_transaction] == -1) //Se qualquer um deles estiver em -1 quer dizer que não commitou ainda
        return 0;
    }
    return 1; //Todas as transações estão marcadas como commit
  }
  return 0;
}

//Funções para liberação de espaço
void freeOpList(operacao **listOp){
  if(*listOp != NULL){
    operacao *op = *listOp;
    *listOp = NULL;

    while(op != NULL){
      operacao *aux = op;
      op = op->prox;
      free(aux);
    }
  }
}

//Calcula o tamanho da lista de operações
int tamOp(operacao *listOp){
  if(listOp != NULL){
    int tam = 0;
    for (operacao *op = listOp; op != NULL; op = op->prox)
      tam++;  //Tamanho da lista de operações
    return tam;
  }
  return 0;
}

//Adiciona uma operaçao à lista de operações indicadas
void addOp(operacao **listOp, operacao *op){
  if(*listOp != NULL){
    operacao *aux;
    //Tramites para conseguir adicionar operação no final da lista
    for(operacao *x = *listOp; x != NULL; x = x->prox)
      if(x->prox == NULL)
        aux = x;
    aux->prox = op;
  }else
    *listOp = op;
}

void ordenaVetor(unsigned int **trans, int tam) {
  int i, j, minIndex;
  unsigned int temp;

  for (i = 0; i < tam - 1; i++) {
    minIndex = i;
    for (j = i + 1; j < tam; j++) {
      if (trans[0][j] < trans[0][minIndex]) {
        minIndex = j;
      }
    }
    if (minIndex != i) {
      temp = trans[0][i];
      trans[0][i] = trans[0][minIndex];
      trans[0][minIndex] = temp;
    }
  }
}
