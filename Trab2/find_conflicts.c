#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Seriabilidade.h"
#include "VisaoEquivalente.h"
#include "utils.h"

int main(int argc, char *argv[]){
  operacao *listOp = NULL;
  listaNodoT *grafo = NULL;
  int commits[MAX_T]; //Vetor que confere comitações
  for(int i = 0; i < MAX_T; i++) commits[i] = -1; //Iniciliza com -1
  char line[100];
  int escalonamento = 0; //Identificador do escalonamento

  // Faz a leitura dos arquivos de entrada, linha por linha
  //armazenando numa lista de operações ordenada pelo timestamp
  while(scanf("%99[^\n]%*c", line) == 1){
    unsigned int timestamp = (unsigned int) atoi(strtok(line, " "));
    unsigned int n_transaction = (unsigned int) atoi(strtok(NULL, " "));
    char *operation = strtok(NULL, " ");
    char *atributo = strtok(NULL, " ");
    if(*operation != 'C'){ //Não é um commit então adiciona na lista de op
      operacao *op = malloc(sizeof(operacao));
      op->timestamp = timestamp;
      op->n_transaction = n_transaction;
      op->operation = *operation;
      op->atributo = *atributo;
      op->prox = NULL;
      addOp(&listOp, op); //Esse procedimento insere ordenado na lista de op
    }else{
      commits[(int) n_transaction] = 1;
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
        //temCiclo será 1 se existir ciclo no grafo
        int temCiclo = buscaCicloGrafo(grafo);
        /*===========================Algoritmo de visão equivalente===========================*/
        int tam = tamGrafo(grafo);
        unsigned int *trans = malloc(sizeof(unsigned int) * tam);
        int index = tam - 1;
        for(listaNodoT *g = grafo; g != NULL; g = g->prox){
          trans[index] = g->transaction->n_transacao;
          index--;
        }
        //equivalente será 1 se existe visão equivalente em listOp
        int equivalente = visaoEquivalente(trans, tam, listOp);

        //Imprime o resultado do escalonamento
        printf("%d ", escalonamento);
        for(int i = 0; i < tam; i++)
          printf("%d,", trans[i]);
        if(temCiclo == 1)
          printf(" NS ");
        else
          printf(" SS ");
        if(equivalente == 1)
          printf("SV\n");
        else
          printf("NV\n");

        //Libera tudo para novo escalonamento
        for(int i = 0; i < MAX_T; i++) commits[i] = -1; //Reseta os commits para novo escalonamento
        freeOpList(&listOp);
        freeGrafo(&grafo);
      }
    }
  }
  
  return 0;
}
