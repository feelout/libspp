#include "Set.h"
#include <stdlib.h>

Set* createSet(void *key, Comparator cmp)
{
	Set *set = (Set*)malloc(sizeof(Set));

	set->root = createRBTree(key, NULL, cmp);

	return set;
}

void addToSet(Set *set, void *key)
{
	addNode(set->root, key, NULL);
}

int contains(Set *set, void *key)
{
	return getNode(set->root, key) != NULL;
}
