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
        //Adiciona todas as operaçẽos que forem da transação de número i
        if(op->n_transaction == arr[i]){
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
    //Se for equivalente seta result como 1
    if(testaEquivalencia(listOp, listAux)) 
      *result = 1;
    freeOpList(&listAux);
  }
  //Comparação para poupar processamento caso já tenha encontrado visão equivalente
  else if(*result != 1){ 
    for (int i = l; i <= r; i++){
      //Faz a troca para o escalonamento do vetor de transações
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
  //Testa a segunda regra do algoritmo de equivalência
  //Faz toda a parte de criar a lista de pares
  for(operacao *opr = listOp; opr != NULL; opr = opr->prox){
    if(opr->operation == 'R'){ //Se for um read
      int lastW = 0;
      int wExists = 0;
      //Se baseia no timestamp para criar os pares write read
      for(operacao *opw = listOp; ((opw != NULL) && (opw->timestamp < opr->timestamp)); opw = opw->prox){
        //Se for um W com o mesmo atributo e esteve antes de R
        if((opw->operation == 'W') && (opw->atributo == opr->atributo)){
          if(opw->n_transaction != opr->n_transaction){ //Se estão em transaçẽos distintas
	          lastW = opw->timestamp; //Garante que esta escolhendo o último w
	          wExists = 1; //Dis que existe o par
	        }
        }
      }
      if(wExists){ //Cria o par e adiciona na lista de pares se existir
        par_wr *par = malloc(sizeof(par_wr));
	      par->tw = lastW;
	      par->tr = opr->timestamp;
	      if(parList != NULL){
	        par->prox = parList;
	        parList = par;
	      }else{
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
          if(opw->timestamp == par->tw){
            freePar(parList);
            return 0; //Encontrou W(X) depois do R(X) do par, não equivalente
          }
  }
  freePar(parList);
  //A partir deste ponto testa a terceira regra do algoritmo de equivalência
  int lastW1;
  int lastW2;
  for(operacao *op1 = listOp; op1 != NULL; op1 = op1->prox){
    char atr = op1->atributo;
    for(operacao *op2 = listOp; op2 != NULL; op2 = op2->prox)
      if((op2->atributo == atr) && (op2->operation == 'W'))
        lastW1 = op2->n_transaction; //Ultima escrita de atr em listOp

    for(operacao *op2 = listAux; op2 != NULL; op2 = op2->prox)
      if((op2->atributo == atr) && (op2->operation == 'W'))
        lastW2 = op2->n_transaction; //Ultima escrita de atr em listAux

    if(lastW1 != lastW2) //Se as ultimas escritas forem diferentes
      return 0; //Não é equivalente
  }
  return 1;
}

//Libera a estrutura de pares do algoritmo de visão
void freePar(par_wr *parList){
  while(parList != NULL){
    par_wr *aux = parList;
    parList = parList->prox;
    free(aux);
  }
}



