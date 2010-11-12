#include "Set.h"
#include <stdlib.h>

Set* createSet(void *key, void *value, Comparator cmp)
{
	Set *set = (Set*)malloc(sizeof(Set));

	set->root = createRBTree(key, value, cmp);

	return set;
}

void addToSet(Set *set, void *key, void *value)
{
	addNode(set->root, key, value);
}

void* getValue(Set *set, void *key)
{
	TreeNode *node = getNode(set->root, key);

	if(!node)
		return NULL;

	return node->value;
}

int contains(Set *set, void *key)
{
	return getValue(set, key) != NULL;
}
