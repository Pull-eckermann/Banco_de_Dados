#include "VisaoEquivalente.h"

int visaoEquivalente(unsigned int *trans, int tam, operacao *listOp){
  int result = 0;
  permute(trans, 0, tam - 1, listOp, &result);
  return result;
}

//Função recursiva e gera todas as permutações possíveis do vetor arr.
void permute(unsigned int *arr, int l, int r, operacao *listOp, int *result){
  if (l == r){
    operacao *listAux = NULL;
    //Cria uma lista de op de acordo com a ordem de transações no vetor
    for(int i = 0; i <= r; i++){
      for(operacao *op = listOp; op != NULL; op = op->prox){
        if(op->n_transaction == arr[i]){ //Adiciona todas as operaçẽos que forem da transação t
          operacao *opAux = malloc(sizeof(operacao));
          opAux->timestamp = op->timestamp;
          opAux->n_transaction = op->n_transaction;
          opAux->operation = op->operation;
          opAux->atributo = op->atributo;
          opAux->prox = NULL;
          addOp(&listAux, opAux);
        }
      }
    }
    if(testaEquivalencia(listOp, listAux))
      *result = 1;
    freeOpList(&listAux);
  }
  else{
    for (int i = l; i <= r; i++){
      swap(&arr[l], &arr[i]);
      permute(arr, l + 1, r, listOp, result);
      swap(&arr[l], &arr[i]);
    }
  }
}

// usada para trocar dois elementos em um vetor
void swap(unsigned int *a, unsigned int *b){
  int temp = *a;
  *a = *b;
  *b = temp;
}

//Testa a equivalência entre duas lista de operações
int testaEquivalencia(operacao *listOp, operacao *listAux){
  return 0;
}


