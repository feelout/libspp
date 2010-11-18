#ifndef PRECEDENCE_MATRIX_H
#define PRECEDENCE_MATRIX_H

#include "Grammar.h"

#define PR_EMPTY	0
#define PR_NEWPIVOT	1
#define PR_INPIVOT	2
#define PR_ENDPIVOT	4

typedef struct 
{
	int dimension;
	int **matrix;
} PrecedenceMatrix;

PrecedenceMatrix* createPrecedenceMatrix(SymbolTable *stable, ProductionList *plist);

#endif//PRECEDENCE_MATRIX_H
