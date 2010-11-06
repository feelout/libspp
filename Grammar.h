
#define MAX_SYMBOLS 256
#define MAX_RHS_SYMBOLS 4

#define SYMBOL_SEPARATORS "`"
#define PRODUCTION_ARROW "->"

#define MAX_STRING_LENGTH 255

typedef char* Symbol;

typedef struct SymbolTable 
{
	int count;
	Symbol symbols[MAX_SYMBOLS];
} SymbolTable;

typedef struct Production
{
	int left;
	int right[MAX_RHS_SYMBOLS];
	int rightcount;
} Production;

typedef struct ProductionList
{
	struct ProductionList *start;
	struct ProductionList *next;
	struct ProductionList *prev;
	Production* prod;
} ProductionList;

/* ProductionList manipulation functions */
ProductionList* createProductionList(Production *prod);
ProductionList* addProductionToList(Production *prod, ProductionList *list);
/* In-place merge sorting of the list
 * cmp function should work with NULL values (Va(a != NULL => cmp(a, NULL) = -1)) 
 * -1 - first value is less
 *  0 - values are equal
 *  1 - first value is greater
 *  */
ProductionList* sortProductionList(ProductionList *list, int (*cmp)(ProductionList *p1, ProductionList *p2));

/* Symbol manipulating functions */
int getSymbolTableID(Symbol *sym, SymbolTable *table);
int addSymbolToTable(Symbol *sym, SymbolTable *table);

/* Grammar loading */
/* Splits @param string into tokens */
Symbol* tokenizeString(char *string);
Production* parseProductionRule(char *string, SymbolTable *table);
