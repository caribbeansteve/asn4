#include <stdio.h>
#include <stdlib.h>
#include "darray.h"

struct DArray {
    void (*display)(FILE *, void *);
    void **array;
    int capacity;
    int size;
};

DArray *newDArray(void (*disp)(FILE *,void *)){
	DArray *newArr = malloc(sizeof(DArray));
	newArr->display = disp;
	newArr->capacity = 1;
	newArr->size = 0;
	newArr->array = malloc(newArr->capacity * sizeof(void *));

	return newArr;
}

void insertDArray(DArray *a,void *v){
	a->size++;
	if(a->size > a->capacity){
		a = resize(a);
	}
	a->array[a->size - 1] = v;
}


void *removeDArray(DArray *a){
	if(!a->size){
		fprintf(stderr, "Nothing to remove");
	}
	void *temp = a->array[a->size - 1];
	a->array[a->size - 1] = 0;
	if(a->capacity > 0 && --a->size < a->capacity / 4){
		desize(a);
	}
	return temp;
}


void *getDArray(DArray *a,int index){
	return a->array[index];
}

void setDArray(DArray *a,int index,void *value){
	if(value == 0 && !a->array[index]){
		a->size--;
	}
	if(a->size == index){
		insertDArray(a, value);
	}
	else{
		a->array[index] = value;
	}
}


int sizeDArray(DArray *a){
	return a->size;
}


void displayDArray(FILE *fp,DArray *a){
	int flag = 0;
	if(!a->size){
		fprintf(fp, "[][%d]", a->capacity);
		return;
	}
	fprintf(fp, "[");
	if(a->array[0]){
			a->display(fp, a->array[0]);
			flag++;
		}
	for(int i = 1; i < a->size; i++){
		if(a->array[i]){
			if(flag){
				fprintf(fp, ",");
			}
			a->display(fp, a->array[i]);
		}
	}
	fprintf(fp, "][%d]", a->capacity - a->size);
}


void *resize(DArray *a){
	void **temp = malloc(a->capacity * 2 * sizeof(void *));

	for(int i = 0; i < a->size - 1; i++){
		temp[i] = a->array[i];
	}
	a->array = temp;
	a->capacity = a->capacity * 2;
	return a;
}

void *desize(DArray *a){
	int cap = a->capacity;
	void **temp = malloc(cap / 2 * sizeof(void *));
	for(int i = 0; i < a->size; i++){
		temp[i] = a->array[i];
	}
	a->array = temp;
	a->capacity = a->capacity / 2;
	return a;
}