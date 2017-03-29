#include "dijkstra.h"



int main(){
	//1. Read in the file and store the smallest and largest int nums to a val
	FILE *fp = fopen("testfile.txt", "r+");
	DArray *edges = newDArray(printEdge);
	initialPass(fp, edges);
	return 0;
}

graph *initialPass(FILE *fp, DArray *edges){
	graph *g;
	int largest = -1;
	int smallest = INFIN;
	int larger = -1; int smaller = -1;
	int first = -1; int second = -1; int weight = -1;
	char *current = readToken(fp);

	//pass over everything and grab the values, adding them to the edge array
	while(current){
		if(first == -1){
			first = atoi(current);
		} else if (second == -1){
			second = atoi(current);
		} else {
			if(current[0] == ';'){
				weight = 1;
			} else{
				weight = atoi(current);
				current = readToken(fp);
			}
			if(first > second){
				smaller = second; 
				larger = first;
			} else {
				larger = second;
				smaller = first;
			}
			//check if smallest or largest so that we know where to begin graph
			if(larger > largest) largest = larger;
			if(smaller > smallest) smallest = smaller;

			//insert the edge into the edge array
			insertDArray(edges, (void *) makeEdge(makeVertex(smaller), makeVertex(larger), weight));

			//reset temp variables
			first = -1; second = -1; weight = -1; smaller = -1; larger = -1;
		}
		current = readToken(fp);
	}
	displayDArray(stdout, edges);
	printf("\n");
	g = makeGraph(largest);
	return craftGraph(g, edges);
}

graph *craftGraph(graph *g, DArray *edges){
	
}

edge *makeEdge(vertex *v, vertex *u, int w){
	edge *newE = malloc(sizeof(edge));
	if(v->val > u->val){
		newE->start = u;
		newE->end = v;
	} else {
		newE->start = v;
		newE->end = u;
	}
	newE->weight = w;

	return newE;
}

void printEdge(FILE *fp, void *ed){
	edge *e = (edge *) ed;
	fprintf(fp, "(E: %d->%d, W: %d)", e->start->val, e->end->val, e->weight);
}

void addEdge(graph *g, int v, int w, int weight){
	if(v == w) return;
	vertex *smaller = v > w ? makeVertex(w) : makeVertex(v);
	vertex *larger = v > w ? makeVertex(v) : makeVertex(w);

	edge *e = getEdge(g, smaller, larger);
	if(!e){
		if(weight < e->weight){
			e->weight = weight;
		}
		return;
	}

	g->adjMatrix[smaller->val][larger->val] = makeEdge(smaller, larger, w);
}

graph *makeGraph(int size){
	graph *newG = malloc(sizeof(graph));
	newG->adjMatrix = malloc(size * size * sizeof(edge));
	return newG;
}

edge *getEdge(graph *g, vertex *v, vertex *w){
	return (edge *) g->adjMatrix[v->val][w->val];
}

vertex *makeVertex(int value){
	vertex *newV = malloc(sizeof(vertex));
	newV->distance = INFIN;
	newV->visited = 0;
	newV->val = value;
	newV->pred = newV;
	newV->neighbors = newDArray(printVertex);
	newV->this = 0;

	return newV;
}

void printVertex(FILE *fp, void *value){
	vertex *v = (vertex *) value;
	fprintf(fp, "%d", v->val);
	if(v->pred != v){
		fprintf(fp, "(%d)%d", v->pred->val, v->distance);
	}
}
void updateVertex(void *vert, BinomialNode *b){
	vertex *v = (vertex *) vert;
	v->this = b;
}
int compareVertex(void *v, void *w){
	return 0;
}



