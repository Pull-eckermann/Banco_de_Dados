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
  else if(*result != 1){
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
  par_wr *parList = NULL;
  //Faz toda a parte de criar a lista de pares
  for(operacao *opr = listOp; opr != NULL; opr = opr->prox){
    if(opr->operation == 'R'){
      int lastW = 0;
      int wExists = 0;
      for(operacao *opw = listOp; ((opw != NULL) && (opw->timestamp < opr->timestamp)); opw = opw->prox){
        if((opw->operation == 'W') && (opw->atributo == opr->atributo)){
          if(opw->n_transaction != opr->n_transaction){
	    lastW = opw->timestamp;
	    wExists = 1;
	  }
        }
      }
      if(wExists){
        par_wr *par = malloc(sizeof(par_wr));
	par->tw = lastW;
	par->tr = opr->timestamp;
	if(parList != NULL){
	  par->prox = parList;
	  parList = par;
	}
	else{
	  parList = par;
	  par->prox = NULL;
        }
      }	
    } 
  }
  
  //Faz a parte de conferir se a lista de pares segue a mesma em listAux
  //Retorna 0 caso encontre disparidade
  for(par_wr *par = parList; par != NULL; par = par->prox){
    for(operacao *opr = listAux; opr != NULL; opr = opr->prox)   
      if(opr->timestamp == par->tr)
        for(operacao *opw = opr; opw != NULL; opw = opw->prox)
          if(opw->timestamp == par->tw)
            return 0; //Encontrou W(X) depois do R(X) do par, não equivalente
  }
  //A partir deste ponto testa a terceira regra
  return 1;
}

//Libera a estrutura de pares do algoritmo de visão
void freePar(par_wr *parList){

}



