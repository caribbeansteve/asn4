#include "dijkstra.h"



int main(){
	//1. Read in the file and store the smallest and largest int nums to a val
	FILE *fp = fopen("testfile.txt", "r+");
	Binomial *b = newBinomial(printVertex, compareVertex, updateVertex);
	DArray *edges = newDArray(printEdge);
	graph *g = makeGraph(10);
	//This will return a stored adjacency matrix, ready to go for dijkstra
	//Need to add a param for the heap of vertexes
	int root = initialPass(fp, edges, b, &g);
	printGraph(stdout, g);
	printf("Root Value: %d\n", root);
	displayBinomial(stdout, b);

	return 0;
}


Binomial *dijkstra(int root, graph *g, DArray *edges, Binomial *b){
	vertex* currentVert;
	edge *currentEdge;
	int smaller; int larger;
	int to = g->size;
	int sum = 0;
	Binomial *span = newBinomial(printVertex, compareVertex, updateVertex);

	while(sizeBinomial(b)){
		currentVert = (vertex *) extractMin(b);
		for(int i = 0; i < g->gize; i++){
			currentEdge = g->adjMatrix[current][i]
			if(currentEdge){
				 
			}
		}
	}
}





int initialPass(FILE *fp, DArray *edges, Binomial *b, graph **g){
	int largest = -1; int size = 10;
	int smallest = PINFINITY;
	int larger = -1; int smaller = -1;
	int first = -1; int second = -1; int weight = -1; 

	vertex *f = 0; vertex *s = 0;
	BinomialNode *inserter = 0;
	char *current = readToken(fp);
	int *check = calloc(size + 1, sizeof(int));
	int *temp;

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
			if(larger > largest){
				//could cause issues
				if(larger > size){
					size = larger;
					temp = calloc(size + 1, sizeof(int));
					for(int i = 0; i < largest + 1; i++){
						temp[i] = check[i];
					}
					check = temp;
				}
				largest = larger;
			} 
			if(smaller < smallest && smaller != -1) smallest = smaller;

			f = makeVertex(smaller);
			s = makeVertex(larger);

			//check if the vertex is in the list and add it
			if(!check[smaller]){
				check[smaller] = 1;
				inserter = insertBinomial(b, (void *) f);
				f->this = inserter;
			} 
			if(!check[larger]){
				check[larger] = 1;
				inserter = insertBinomial(b, (void *) s);
				s->this = inserter;
			} 
			//insert the edge into the edge array
			insertDArray(edges, (void *) makeEdge(f, s, weight));
			//reset temp variables
			first = -1; second = -1; weight = -1; smaller = -1; larger = -1;
			f = 0; s = 0; inserter = 0;
		}
		current = readToken(fp);
	}
	*g = makeGraph(largest);
	craftGraph(*g, edges);
	return smallest;

}

graph *craftGraph(graph *g, DArray *edges){
	edge *temp;

	while(sizeDArray(edges)){
		temp = removeDArray(edges);
		addEdge(g, temp->start->val, temp->end->val, temp->weight);
	}
	return g;
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
	if(e){
		if(weight < e->weight){
			e->weight = weight;
		}
		return;
	}

	g->adjMatrix[smaller->val][larger->val] = makeEdge(smaller, larger, weight);
}

graph *makeGraph(int s){
	graph *newG = malloc(sizeof(graph));
	newG->adjMatrix = malloc(s * sizeof(edge));
	for(int i = 0; i <= s; i++){
		newG->adjMatrix[i] = malloc(s * sizeof(edge));
	}
	newG->size = s;
	return newG;
}

void printGraph(FILE *fp, graph *g){
	edge *temp;
	for(int i = 0; i <= g->size; i++){
		fprintf(fp, "%d:[", i);
		for(int j = 0; j <= g->size; j++){
			temp = g->adjMatrix[i][j];
			if(temp){
				fprintf(fp, "%d", temp->weight);
			} else {
				fprintf(fp, "0");
			}
			if(j != g->size){
				fprintf(fp, ", ");
			}
		}
		fprintf(fp, "]\n");
	}
}

edge *getEdge(graph *g, vertex *v, vertex *w){
	if(g->adjMatrix[v->val][w->val]){
		return (edge *) g->adjMatrix[v->val][w->val];
	}
	return 0;
}

vertex *makeVertex(int value){
	vertex *newV = malloc(sizeof(vertex));
	newV->distance = -1;
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
	//More to this
}
int compareVertex(void *v, void *w){
	vertex *a = (vertex *) v;
	vertex *b = (vertex *) w;
	if(a->distance == -1 && b->distance != -1){
		return -1;
	} if(b->distance == -1 && a->distance != -1){
		return 1;
	}

	return b->distance - a->distance;
}



