#ifndef LRM_H
#define LRM_H

#include "Grammar.h"
#include "Set.h"

typedef struct
{
	int **leftmost;
	int **rightmost;
} LRM;

#define LRM_INCLUDED 1
#define LRM_NOTINCLUDED 0

#define LRM_LValue(LRM, s1, s2) (lrm->leftmost[s1][s2])
#define LRM_RValue(LRM, s1, s2) (lrm->rightmost[s1][s2])

LRM *createLRM(SymbolTable *stable, ProductionList *plist);

/* Set of nonterminal symbols : <int,int> */
Set *getNonTerminalSet(ProductionList *plist);

#endif //LRM_H
