/* Red-black tree realisation */

#define COLOR_RED	1
#define COLOR_BLACK	2

typedef struct _TreeNode TreeNode;

/*
 * Comparator function for tree
 * a < b => Comparator(a,b) = -1
 * a = b => Comparator(a,b) = 0
 * a > b => Comparator(a,b) = 1
 */
typedef int(*Comparator)(void*, void*);

struct _TreeNode
{
	void *key;
	void *value;
	int color;
	TreeNode *parent;
	TreeNode *left;
	TreeNode *right;
	Comparator cmp;
};

TreeNode* createRBTree(void *key, void *value, Comparator cmp);
TreeNode* getNode(TreeNode *root, void *key);
TreeNode* addNode(TreeNode *root, void *key, void *value);
TreeNode* removeNode(TreeNode *root, void *key);
int isARBTree(TreeNode *root);

void dumpTree(TreeNode *tree, int indent, void(*writer)(void*,void*,int));
