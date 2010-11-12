/* Generic set */

#ifndef SET_H
#define SET_H

#include "rbtree.h"

typedef struct
{
	TreeNode *root;
} Set;

Set* createSet(void *key, void *value, Comparator cmp);
void addToSet(Set *set, void *key, void *value);
void* getValue(Set *set, void *key);
int contains(Set *set, void *key);

#endif //SET_H
