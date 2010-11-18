#ifndef MAP_H
#define MAP_H

#include "rbtree.h"

typedef struct
{
	TreeNode *root;
} Map;

Map* createMap(void* key, void* value, Comparator cmp);
void addToMap(Map *map, void* key, void* value);
void* getValueFromMap(Map *map, void* key);

#endif //MAP_H
