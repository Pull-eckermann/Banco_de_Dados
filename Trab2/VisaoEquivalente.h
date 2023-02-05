#ifndef VISAOEQUIVALENTE_H
#define VISAOEQUIVALENTE_H

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

/*------------------------------------------------------------*/
int visaoEquivalente(unsigned int *trans, int tam, operacao *listOp);
int testaEquivalencia(operacao *listOp, operacao *listAux);
void swap(unsigned int *a, unsigned int *b);
void permute(unsigned int *arr, int l, int r, operacao *listOp, int *result);


#endif // VISAOEQUIVALENTE_H
