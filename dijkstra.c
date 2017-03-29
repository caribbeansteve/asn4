#include <stdio.h>
#include <stdlib.h>
#include "darray.h"
#include "integer.h"
#include "binomial.h"


int main(){
	Binomial *b = newBinomial(displayInteger, compareInteger, 0);
	insertBinomial(b, (void *) newInteger(4));
	insertBinomial(b, (void *) newInteger(8));
	insertBinomial(b, (void *) newInteger(16));
	insertBinomial(b, (void *) newInteger(5));
	insertBinomial(b, (void *) newInteger(1));
	// insertBinomial(b, (void *) newInteger(505));
	// insertBinomial(b, (void *) newInteger(4122));
	// insertBinomial(b, (void *) newInteger(54));
	extractBinomial(b);
	displayBinomial(stdout, b);
	return 0;
}