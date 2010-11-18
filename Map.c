#include "Map.h"
#include <stdlib.h>

Map* createMap(void* key, void* value, Comparator cmp)
{
	Map *map = (Map*)malloc(sizeof(Map));

	map->root = createRBTree(key, value, cmp);
}

void addToMap(Map* map, void* key, void* value)
{
	addNode(map->root, key, value);
}

void* getValueFromMap(Map* map, void* key)
{
	return getNode(map->root, key);
}
