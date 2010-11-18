#include <stdio.h>
#include "Grammar.h"
#include "LRM.h"

void dumpProductionList(ProductionList *list, SymbolTable *stable)
{
	int i;

	list = list->start;

	while(list)
	{
		printf("LHS : %s, RHS : ", stable->symbols[list->prod->left]);

		for(i=0; i < list->prod->rightcount; ++i)
		{
			printf("%s,", stable->symbols[list->prod->right[i]]);
		}

		printf("\n");

		list = list->next;
	}
}

void dumpLRM(LRM *lrm, SymbolTable *stable)
{
	int i,k;

	printf("Leftmost set:\n");

	// Header
	printf("%10s ", "symbol:");

	for(i = 0; i < stable->count; ++i)
	{
		printf("%10s", stable->symbols[i]);
	}

	printf("\n");

	// Body
	for(i = 0; i < stable->count; ++i)
	{
		printf("%10s ", stable->symbols[i]);
		for(k = 0; k < stable->count; ++k)
		{
			if(LRM_LValue(lrm, i, k) == LRM_INCLUDED)
				printf("%10c", '+');
			else
				printf("%10c", ' ');
		}
		printf("\n");
	}

	printf("Rightmost set:\n");

	// Header
	printf("%10s ", "symbol:");

	for(i = 0; i < stable->count; ++i)
	{
		printf("%10s", stable->symbols[i]);
	}

	printf("\n");

	// Body
	for(i = 0; i < stable->count; ++i)
	{
		printf("%10s ", stable->symbols[i]);
		for(k = 0; k < stable->count; ++k)
		{
			if(LRM_RValue(lrm, i, k) == LRM_INCLUDED)
				printf("%10c", '+');
			else
				printf("%10c", ' ');
		}
		printf("\n");
	}
}

int main(int argc, char* argv[])
{

	if(argc != 2)
	{
		printf("Invalid number of arguments, must be one\n");
		return -1;
	}

	FILE *i_file = fopen(argv[1], "r");

	char buffer[MAX_STRING_LENGTH];
	ProductionList *list = NULL;
	Production *prod = NULL;
	SymbolTable stable = {0};

	while(fgets(buffer, MAX_STRING_LENGTH, i_file) != NULL)
	{
		trim(buffer);

		prod = parseProductionRule(buffer, &stable);

		if(!prod)
			continue;

		if(list)
		{
			list = addProductionToList(prod, list);
		}
		else
		{
			list = createProductionList(prod);
		}
	}

	dumpProductionList(list, &stable);
	
	list = list->start;

	LRM *lrm = createLRM(&stable, list);

	dumpLRM(lrm, &stable);
}
