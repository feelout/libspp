#include "Grammar.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Symbol* tokenizeString(char *string)
{
	Symbol symbols[MAX_STRING_LENGTH];
	int symbNum = 0;

	Symbol symb = strtok(string, SYMBOL_SEPARATORS);

	while(symb)
	{
		symbols[symbNum++] = symb;
		symb = strtok(NULL, SYMBOL_SEPARATORS);
	}

	Symbol* result = (Symbol*)malloc((symbNum+1) * sizeof(Symbol));

	int i;
	for(i = 0; i < symbNum; ++i)
	{
		result[i] = symbols[i];
	}
	result[symbNum] = NULL;

	return result;
}

int getSymbolTableID(Symbol *sym, SymbolTable *table)
{
	//printf("Searching for the symbol %s in table\n", *sym);
	//printf("Total symbols : %d\n", table->count);

	int i;
	for(i=0; i < table->count; ++i)
	{
		//printf("table->symbols[%d] = %s\n", i, table->symbols[i]);
		if(strcmp(*sym, table->symbols[i]) == 0)
			return i;
	}

	return -1;
}

int addSymbolToTable(Symbol *sym, SymbolTable *table)
{
	//printf("Adding symbol %s to the table\n", *sym);

	int id = getSymbolTableID(sym, table);

	//printf("Id of symbol : %d\n", id);

	if(id != -1)
		return id;

	/* TODO: Check for overflow */
	table->symbols[table->count] = *sym;
	return table->count++;
}

Production* parseProductionRule(char *string, SymbolTable *table)
{
	//printf("Parsing production %s\n", string);
	//printf("Already %d symbols in the table\n", table->count);

	char* buffer = (char*)malloc(strlen(string) * sizeof(char));

	strcpy(buffer, string);

	Symbol *currentToken = tokenizeString(buffer);
	int id;

	if(strcmp(currentToken[1], PRODUCTION_ARROW) != 0)
		fail("parseProductionRule : arrow not found");

	Production *prod = (Production*)malloc(sizeof(Production));
	prod->left = addSymbolToTable(currentToken, table);

	currentToken += 2; /* Skipping production arrow */

	prod->rightcount = 0;

	int k = 0;

	while(currentToken[k])
	{
		id = addSymbolToTable(&currentToken[k], table);
		/* TODO: Check for overflow */
		prod->right[prod->rightcount++] = id;
		k++;
	}

	return prod;
}

ProductionList* createProductionList(Production *prod)
{
	ProductionList* head = (ProductionList*)malloc(sizeof(ProductionList));
	head->start = head;
	head->next = 0;
	head->prev = NULL;
	head->prod = prod;

	return head;
}

ProductionList* addProductionToList(Production *prod, ProductionList *list)
{
	ProductionList *node = createProductionList(prod);

	node->start = list->start;
	node->prod = prod;

	while(list->next)
		list++;

	list->next = node;
	node->prev = list;

	return node;
}

ProductionList* concatenateProductionLists(ProductionList *first, ProductionList *second)
{
	second->start = first->start;

	while(first->next)
		first = first->next;

	first->next = second;
	second->prev = first;

	return first;
}

ProductionList* sortProductionList(ProductionList *prod, int (*cmp)(ProductionList *p1, ProductionList *p2))
{
	ProductionList *first = prod, *second = prod, *endofsecond = prod;	
	ProductionList *list = NULL;
	while(1)
	{
		/* [First, Second) is already sorted chunk */
		while(second && cmp(first, second) < 1) second = second->next;
		endofsecond = second;
		/* [Second, EndOfSecond) is another sorted chunk */
		while(endofsecond && cmp(second, endofsecond) < 1) endofsecond = endofsecond->next;

		/* Merging two chunks */
		while(first != second || second != endofsecond) 
		{
			if(cmp(first, second) == 1)
			{
				if(list)
				{
					list->next = second;
					second->prev = list;
					second->start = list->start;
				}
				else
				{
					list = second;
					list->prev = NULL;
					list->start = list;
				}
				second = second->next;
			}
			else
			{
				if(list)
				{
					list->next = first;
					first->prev = list;
					first->start = list->start;
				}
				else
				{
					list = first;
					list->prev = NULL;
					list->start = list;
				}
				first = first->next;
			}

			list = list->next;
		}
	}

	return list;
}
