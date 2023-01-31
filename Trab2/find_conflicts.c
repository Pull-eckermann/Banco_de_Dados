#include <stdio.h>
#include <stdlib.h>
#include "Seriabilidade.h"

int main(int argc, char *argv[]){
  operacao *listOp = NULL;  
  char line[10];

  // Faz a leitura dos arquivos de entrada, linha por linha
  //armazenando numa lista de operações
  while(scanf("%99[^\n]%*c", line) == 1){
    operacao *op = malloc(sizeof(operacao));
    op->timestamp = (unsigned int) line[0]; //Timestamp
    op->n_transaction = (unsigned int) line[2]; //Número da transação
    op->operation = (char) line[4]; //Operação
    op->atributo = (char) line[6]; //Atributo
    op->prox = NULL;

    if(listOp != NULL){
      operacao *aux;
      //Tramites para conseguir adicionar operação no final da lista
      for(operacao *x = listOp; x != NULL; x = x->prox)
        if(x->prox == NULL)
          aux = x;
      aux->prox = op;
    }else
      listOp = op;
  }

  //Cria o grafo de acordo com as operações
  listaNodoT *grafo = NULL;
  for(operacao *x = listOp; x != NULL; x=x->prox){
    if(buscaNodoGrafo(grafo, x->n_transaction) == NULL){ //Retorna nulo se não encontra o nodo
      nodoT *novoNodo = initNodo(x->n_transaction); //Como não existe o nodo ainda, cria pela primeira vez
      addNodoGrafo(&grafo, novoNodo); // Adiciona novo nodo no grafo
    }
  }

  return 0;
}
