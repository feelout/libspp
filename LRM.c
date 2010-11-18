#include "LRM.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int integerComparator(void *a, void *b)
{
	int ia = *(int*)a;
	int ib = *(int*)b;

	if(ia == ib)
		return 0;
	else if(ia < ib)
		return -1;
	else
		return 1;
}

LRM *createLRM(SymbolTable *stable, ProductionList *plist)
{
	int symbolsCount = stable->count;

	LRM *lrm = (LRM*)malloc(sizeof(LRM));

	lrm->leftmost = (int**)malloc(sizeof(int*) * symbolsCount);
	lrm->rightmost = (int**)malloc(sizeof(int*) * symbolsCount);

	int i,j,k;
	for(i = 0; i < symbolsCount; ++i) 
	{
		lrm->leftmost[i] = (int*)malloc(sizeof(int) * symbolsCount);
		lrm->rightmost[i] = (int*)malloc(sizeof(int) * symbolsCount);

		memset(lrm->leftmost[i], 0, sizeof(int) * symbolsCount);
		memset(lrm->rightmost[i], 0, sizeof(int) * symbolsCount);
	}

	ProductionList *iter = plist;

	int addedCount = 0; // Count of symbols added to tables in current iteration
	Production *prod;

	// Initial populating of LRM
	for(iter = plist; iter; iter = iter->next)
	{
		prod = iter->prod;

		LRM_LValue(lrm, prod->left, prod->right[0]) = LRM_INCLUDED;
		LRM_RValue(lrm, prod->left, prod->right[prod->rightcount-1]) = LRM_INCLUDED;
	}

	do
	{
		addedCount = 0;

		for(i = 0; i < symbolsCount; ++i)
		{
			for(j = 0; j < symbolsCount; ++j)
			{
				if(LRM_LValue(lrm, i, j) == LRM_INCLUDED)
				{
					for(k = 0; k < symbolsCount; ++k)
					{
						if(LRM_LValue(lrm, j, k) == LRM_INCLUDED &&
								LRM_LValue(lrm, i, k) == LRM_NOTINCLUDED)
						{
							LRM_LValue(lrm, i, k) = LRM_INCLUDED;

							++addedCount;
						}
					}
				}

				if(LRM_RValue(lrm, i, j) == LRM_INCLUDED)
				{
					for(k = 0; k < symbolsCount; ++k)
					{
						if(LRM_RValue(lrm, j, k) == LRM_INCLUDED &&
								LRM_RValue(lrm, i, k) == LRM_NOTINCLUDED)
						{
							LRM_RValue(lrm, i, k) = LRM_INCLUDED;

							++addedCount;
						}
					}
				}
			}
		}
	} while(addedCount > 0);

	return lrm;
}

Set *getNonTerminalSet(ProductionList *plist)
{
	Set *terminals = NULL;

	while(plist)
	{
		if(terminals)	
			addToSet(terminals, &plist->prod->left);
		else
			terminals = createSet(&plist->prod->left, integerComparator);
		++plist;
	}

	return terminals;
}
