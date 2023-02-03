#include <stdio.h>
#include <stdlib.h>
#include "Seriabilidade.h"

int main(int argc, char *argv[]){
  operacao *listOp = NULL;
  listaNodoT *grafo = NULL;
  int commits[MAX_T]; //Vetor que confere comitações
  for(int i = 0; i < MAX_T; i++) commits[i] = -1; //Iniciliza com -1
  char line[100];
  unsigned int escalonamento = 0; //Identificador do escalonamento

  // Faz a leitura dos arquivos de entrada, linha por linha
  //armazenando numa lista de operações ordenada pelo timestamp
  while(scanf("%99[^\n]%*c", line) == 1){
    if(line[4] != 'C'){ //Não é um commit então adiciona na lista de op
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
    }else{
      commits[(int) line[2]] = 1;
      if(isCommited(listOp, commits)){
        escalonamento++;
        /*===============Algoritmo de Teste de seriabilidade quanto ao conflito===============*/
        //Cria o grafo de acordo com a lista de operações
        criaGrafo(&grafo, listOp);

        //Adiciona as arestas de acordo com o algoritmo do teste de seriabilidade
        for(operacao *opi = listOp; opi != NULL; opi = opi->prox){
          for(operacao *opj = opi; opj != NULL; opj = opj->prox){
            if(opj->n_transaction != opi->n_transaction){ //Confere se não é a mesma transação
              if(opi->operation == 'W'){
                if(((opj->operation == 'W') || (opj->operation == 'R')) && (opi->atributo == opj->atributo)){
                  nodoT *i = buscaNodoGrafo(grafo, opi->n_transaction);
                  nodoT *j = buscaNodoGrafo(grafo, opj->n_transaction);
                  criaAresta(i,j);
                }
              }
              if(opi->operation == 'R'){
                if((opj->operation == 'W') && (opj->atributo == opi->atributo)){
                  nodoT *i = buscaNodoGrafo(grafo, opi->n_transaction);
                  nodoT *j = buscaNodoGrafo(grafo, opj->n_transaction);
                  criaAresta(i,j);
                }
              }
            }
          }
        }

        int temCiclo = buscaCicloGrafo(grafo);
        /*===========================Algoritmo de visão equivalente===========================*/




        //Libera tudo para novo escalonamento
        for(int i = 0; i < MAX_T; i++) commits[i] = -1; //Reseta os commits para novo escalonamento
        freeOpList(&listOp);
        freeGrafo(&grafo);
      }
    }
  }

/*  int temCiclo = buscaCicloGrafo(grafo);
  
  printf("temCiclo = %d\n", temCiclo);
  for(listaNodoT *x = grafo; x!=NULL; x=x->prox){
    printf("Transacao: %c\n", x->transaction->n_transacao);
    printf("Arestas\n");
    for(listaNodoT *y = x->transaction->arestas; y!=NULL; y=y->prox){
      printf("%c\n", y->transaction->n_transacao);
    }
  }*/

  return 0;
}
