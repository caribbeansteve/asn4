#ifndef djik
#define djik
#define INFIN -1

#include <stdio.h>
#include <stdlib.h>
#include "darray.h"
#include "integer.h"
#include "binomial.h"
#include "scanner.h"

typedef struct vertex {
	int distance; 
	int visited;
	int val;
	struct vertex *pred;
	DArray *neighbors;
	BinomialNode *this;

} vertex;

typedef struct edge {
	vertex *start;
	vertex *end;
	int weight;
} edge;

typedef struct graph{
	edge ***adjMatrix;
} graph;

extern edge *makeEdge(vertex *, vertex *, int);
extern graph *makeGraph(int);
extern void addEdge(graph *g, int , int , int );
extern edge *getEdge(graph *, vertex *, vertex *);
extern void printEdge(FILE *fp, void *ed);
extern graph *initialPass(FILE *fp, DArray *edges);
extern graph *craftGraph(graph *g, DArray *edges);

extern vertex *makeVertex(int );
extern void printVertex(FILE *, void *);
extern void updateVertex(void *, BinomialNode *);
extern int compareVertex(void *, void *);
#endif