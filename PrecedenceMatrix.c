#include "PrecedenceMatrix.h"
#include <stdlib.h>

void createEmptyMatrix(PrecedenceMatrix *matrix)
{
	int i = 0;

	matrix->matrix = (int**)malloc(sizeof(int*)*matrix->dimension);

	for(i=0; i < matrix->dimension; ++i)
	{
		matrix->matrix[i] = (int*)malloc(sizeof(int)*matrix->dimension);
	}
}

PrecedenceMatrix* createPrecedenceMatrix(SymbolTable *stable, ProductionList *plist)
{
	PrecedenceMatrix* matrix = (PrecedenceMatrix*)malloc(sizeof(PrecedenceMatrix));

	matrix->dimension = stable->count;
	createEmptyMatrix(matrix);
}
