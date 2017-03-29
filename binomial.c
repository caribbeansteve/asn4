#include "binomial.h"

struct BinomialNode{
	void *value;
	DArray *children;
	struct BinomialNode *parent;
	void (*display)(FILE *,void *);
};

BinomialNode *newBinomialNode(void (*disp)(FILE *,void *),void *value){
	BinomialNode *node = malloc(sizeof(BinomialNode));
	node->children = newDArray(disp);
	node->parent = node;
	node->display = disp;
	node->value = value;

	return node;
}
void displayBinomialNode(FILE *fp, void *n){
	BinomialNode *new = (BinomialNode *) n;
	new->display(fp, new->value);
	fprintf(fp, "-%d", sizeDArray(new->children));
	if(new->parent != new){
		fprintf(fp, "(");
		new->display(fp, new->parent->value);
		fprintf(fp, "-%d", sizeDArray(new->parent->children));
		fprintf(fp, ")");
	}
}

struct Binomial{
	int (*compare)(void *,void *);
	void (*update)(void *,BinomialNode *);
	void (*display)(FILE *,void *);

	BinomialNode *extreme;
	DArray *rootlist;
	int size;
};

Binomial *newBinomial(
    void (*d)(FILE *,void *),        //display
    int (*c)(void *,void *),         //comparator
    void (*u)(void *,BinomialNode *) //updater
){
	Binomial *newB = malloc(sizeof(Binomial));
	newB->compare = c;
	newB->display = d;
	newB->update = u;
	newB->rootlist = newDArray(displayBinomialNode);
	newB->extreme = 0;
	newB->size = 0;

	return newB;
}

BinomialNode *insertBinomial(Binomial *b,void *value){
	BinomialNode *n = newBinomialNode(b->display, value);
	consolidate(b, n);
	b->size++;
	if(!b->extreme || b->compare(n->value, b->extreme->value) > 0){
		b->extreme = n;
	}
	return n;
}

void consolidate(Binomial *b, BinomialNode *n){
	int degree = sizeDArray(n->children);

	while(getDArray(b->rootlist, degree)){
		n = combine(b, getDArray(b->rootlist, degree), n);
		setDArray(b->rootlist, degree, 0);
		++degree;
	}
	setDArray(b->rootlist, degree, n);
}

BinomialNode *combine(Binomial *b, BinomialNode *x, BinomialNode *y){
	if(b->compare(x->value, y->value) > 0){
		int i = sizeDArray(y->children);
		setDArray(x->children, i, (void *) y);
		y->parent = x;
		return x;
	} else {
		int i = sizeDArray(x->children);
		setDArray(y->children, i, (void*) x);
		x->parent = y;
		return y;
	}
}


int sizeBinomial(Binomial *b){
	return b->size;
}

void deleteBinomial(Binomial *b, BinomialNode *n){
	decreaseKeyBinomial(b, n, 0);
	extractBinomial(b);
}

void decreaseKeyBinomial(Binomial *b, BinomialNode *n, void *value){
	n->value = value;
	bubbleUp(b, n);
	if(b->compare(b->extreme->value, n->value) > 0){
		b->extreme = n;
	}
}

BinomialNode *bubbleUp(Binomial *b, BinomialNode *n){
	if(n->parent == n){
		return n;
	} else if(b->compare(n->parent->value, n->value) > 0){
		return n;
	} else {
		void *temp = n->parent->value;
		if(b->update){
			
			b->update(n->value, n->parent);
			b->update(temp, n);
		}
		n->parent->value = n->value;
		n->value = temp;
		return bubbleUp(b, n->parent);
	}
}

void *extractBinomial(Binomial *b){
	BinomialNode *ex = b->extreme;
	void *val; 
	int index;

	for(int i = 0; i < sizeDArray(b->rootlist); i++){
		if(ex == getDArray(b->rootlist ,i)){
			index = i;
			break;
		}
	}
	setDArray(b->rootlist, index, 0);
	merge(b, ex->children);
	b->size--;
	val = ex->value;
	free(ex);
	BinomialNode *newEx = 0;
	BinomialNode *temp;
	double ma = log((double)b->size) / log(2.0);
	for(int i = 0; i <= (int) ma; i++){
		temp = getDArray(b->rootlist, i);
		if((temp && !newEx) ){
			newEx = temp;
		} else if(temp && newEx && b->compare(temp->value, newEx->value) > 0)
		{
			newEx = temp;
		}
	}
	b->extreme = newEx;
	return val;
}

void merge(Binomial *b, DArray *d){
	BinomialNode *temp;
	while(sizeDArray(d)){
		temp = removeDArray(d);
		temp->parent = temp;
		consolidate(b, temp);
	}
	free(d);
}

void displayBinomial(FILE *fp,Binomial *b){
	int level = 0;
	void *x;
	BinomialNode *binTemp;
	int size = sizeDArray(b->rootlist);
	queue *q = newQueue(b->display);

	for(int i = 0; i < size; i++){
		if(getDArray(b->rootlist, i) != 0){
			enqueue(q, getDArray(b->rootlist, i));
			enqueue(q, 0);
			x = dequeue(q);
			fprintf(fp, "%d:", level++);
			while(sizeQueue(q)){
				if(!x){
					if(peekQueue(q) == 0){
						break;
					}
					fprintf(fp, "\n%d:", level++);
					enqueue(q, 0);
				} else {
					binTemp = ((BinomialNode *) x);
					fprintf(fp, " ");
					displayBinomialNode(fp, x);
					for(int j = 0; j < sizeDArray(binTemp->children); j++){
						if(getDArray(binTemp->children, j)){
							enqueue(q, getDArray(binTemp->children, j));
						}
					}
				}
				x = dequeue(q);
			}
			fprintf(fp, "\n----\n");
			level = 0;
			while(sizeQueue(q)){
				dequeue(q);
			}
		}
	}

}

