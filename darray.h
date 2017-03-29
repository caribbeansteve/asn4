#ifndef __DARRAY___
#define __DARRAY___

#include <stdio.h>
#include <stdlib.h>

typedef struct DArray DArray; //forward declaration of the DArray struct

DArray *newDArray(void (*display)(FILE *,void *));
void insertDArray(DArray *a,void *v);
void *removeDArray(DArray *a);
void *getDArray(DArray *a,int index);
void setDArray(DArray *a,int index,void *value);
int sizeDArray(DArray *a);
void displayDArray(FILE *,DArray *a);
void *resize(DArray *a);
void *desize(DArray *a);


#endif