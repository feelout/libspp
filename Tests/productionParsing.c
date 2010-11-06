#include "Grammar.h"
#include <stdio.h>
#include <string.h>

#define RULES_COUNT 3

void dumpProduction(Production *prod, SymbolTable *table)
{
	printf("LHS : %s, RHS : ", table->symbols[prod->left]);
	int i;
	for(i=0; i < prod->rightcount; ++i)
	{
		printf("%s,", table->symbols[prod->right[i]]);
	}
	printf("\n");
}

int main(int argc, char* argv[])
{
	SymbolTable stable;
	stable.count = 0;

	char* rules[RULES_COUNT] = {
		"A`->`B",
		"B`->`1`B`0",
		"B`->`1`0"};

	int i;
	char buffer[15];
	for(i = 0; i < RULES_COUNT; ++i)
	{
		strcpy(buffer, rules[i]);
		printf("Parsing rule %s\n", buffer);
		Production *p = parseProductionRule(buffer, &stable);
		dumpProduction(p, &stable);
	}


}
