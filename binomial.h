#include <stdio.h>
#include "darray.h"
#include "queue.h"
#include <math.h>

#ifndef __BINHEAP_INCLUDED__
#define __BINHEAP_INCLUDED__

typedef struct BinomialNode BinomialNode;

BinomialNode *newBinomialNode(void (*display)(FILE *,void *),void *value);
void displayBinomialNode(FILE *fp,void *n);

typedef struct Binomial Binomial;

extern Binomial *newBinomial(
    void (*d)(FILE *,void *),        //display
    int (*c)(void *,void *),         //comparator
    void (*u)(void *,BinomialNode *) //updater
);
extern BinomialNode *insertBinomial(Binomial *b,void *value);
extern int sizeBinomial(Binomial *b);
extern void deleteBinomial(Binomial *b,BinomialNode *n);
extern void decreaseKeyBinomial(Binomial *b,BinomialNode *n,void *value);
extern void *extractBinomial(Binomial *b);
extern void displayBinomial(FILE *fp,Binomial *b);
extern void consolidate(Binomial *, BinomialNode *);
extern void merge(Binomial *b, DArray *d);
extern BinomialNode *bubbleUp(Binomial *b, BinomialNode *n);
BinomialNode *combine(Binomial *b, BinomialNode *x, BinomialNode *y);

#endif