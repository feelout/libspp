#include <stdlib.h>
#include <stdio.h>
#include "rbtree.h"

void debugWrite(void *k, void *v)
{
	int key = *(int*)k;
	int value = *(int*)v;

	printf("(%i,%i)\n", key, value);
}

TreeNode* createRBTree(void *key, void *value, Comparator cmp)
{
	TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));

	root->key = key;
	root->value = value;
	root->parent = NULL;
	root->left = root->right = NULL;
	root->color = COLOR_BLACK;
	root->cmp = cmp;

	return root;
}

TreeNode* getNode(TreeNode *root, void *key)
{
	if(!root)
		return NULL;
	TreeNode *node = root;
	Comparator cmp = root->cmp;
	int cr;

	while(node)
	{
		cr = cmp(key, root->key);
		switch(cr)
		{
			case 0:
				return node;
			case 1:
				node = node->right;
				break;
			case -1:
				node = node->left;
				break;
		}
	}

	return NULL;
}

TreeNode* bstAddNode(TreeNode *root, void *key, void *value)
{
	TreeNode *parent = root;
	Comparator cmp = root->cmp;
	int cr;

	while(1)
	{
		cr = cmp(key, parent->key);

		if(cr == 0)
		{
			parent->value = value;
			return parent;
		} else if(cr == -1)
		{
			if(parent->left)
			{
				parent = parent->left;
			}
			else
			{
				TreeNode *node = createRBTree(key, value, cmp);	
				node->color = COLOR_RED;
				node->parent = parent;
				parent->left = node;

				return node;
			}
		} else 
		{

			if(parent->right)
			{
				parent = parent->right;
			}
			else
			{
				TreeNode *node = createRBTree(key, value, cmp);	
				node->color = COLOR_RED;
				node->parent = parent;
				parent->right = node;

				return node;
			}
		}
	}

	return NULL; /* Shouldn`t come here */
}

TreeNode* getGrandParent(TreeNode *node)
{
	if(node->parent)
		return node->parent->parent;
	else
		return NULL;
}

TreeNode* getUncle(TreeNode *node)
{
	TreeNode *gp = getGrandParent(node);

	if(!gp)
		return NULL;

	if(gp->left == node->parent)
		return gp->right;
	else
		return gp->left;
}

int isLeftChild(TreeNode *node)
{
	if(!node->parent)
		return 0;
	if(node->parent->left == node)
		return 1;
	return 0;
}

void rotateLeft(TreeNode *node)
{
	TreeNode *parent = node->parent;
	TreeNode *right = node->right;
	TreeNode *newRight = right->left;

	int isleft = isLeftChild(node);

	node->right = newRight;
	node->parent = right;
	right->parent = parent;
	right->left = node;

	if(!parent)
		return;
	if(isleft)
		parent->left = right;
	else
		parent->right = right;
}

void rotateRight(TreeNode *node)
{
	TreeNode *parent = node->parent;
	TreeNode *left = node->left;
	TreeNode *newLeft = left->right;

	int isleft = isLeftChild(node);

	node->left = newLeft;
	node->parent = left;
	left->parent = parent;
	left->right = node;

	if(!parent)
		return;

	if(isleft)
		parent->left = left;
	else
		parent->right = left;
}

void balanceTree(TreeNode *node)
{
	TreeNode *parent = node->parent;
	TreeNode *gp = getGrandParent(node);
	TreeNode *uncle = getUncle(node);

	printf("Balancing node ");
	debugWrite(node->key, node->value);

	/* Case 0 : Root node, painting black */
	if(!parent)
	{
		printf("Balance : case 0\n");
		node->color = COLOR_BLACK;
		return;
	}

	/* Case 1 : Parent is black, all invariants hold */
	if(parent->color == COLOR_BLACK)
	{
		printf("Balance : case 1\n");
		return;
	}

	/* Case 2 : Parent and uncle are red */
	if(parent && uncle && parent->color == COLOR_RED && uncle->color == COLOR_RED)
	{
		printf("Balance : case 2\n");
		parent->color = COLOR_BLACK;
		uncle->color = COLOR_BLACK;
		gp->color = COLOR_RED;
		
		balanceTree(gp);
		return;
	}

	int parentLeft = isLeftChild(parent);
	int nodeLeft = isLeftChild(node);

	/* Case 3 : Parent is red, uncle is black, node is a different child as parent */
	if(parent && parent->color == COLOR_RED && (!uncle || uncle->color == COLOR_BLACK) && parentLeft != nodeLeft)
	{
		printf("Balance : case 3\n");
		if(parentLeft)
		{
			rotateLeft(parent);
			node = node->left;
		} else
		{
			rotateRight(parent);
			node = node->right;
		}

		/* Not yet fixed - need case 4 */
		parent = node->parent;
		uncle = getUncle(node);
		gp = getGrandParent(node);
		parentLeft = isLeftChild(parent);
		nodeLeft = isLeftChild(node);
	}


	/* Case 4 : Parent is red, uncle is black, node is a same child as parent */
	if(parent && parent->color == COLOR_RED && (!uncle || uncle->color == COLOR_BLACK) && parentLeft == nodeLeft)
	{
		printf("Balance : case 4\n");
		if(parentLeft)
		{
			rotateRight(gp);
		} else
		{
			rotateLeft(gp);
		}

		parent->color = COLOR_BLACK;
		gp->color = COLOR_RED;
	}
}

TreeNode* addNode(TreeNode *root, void *key, void *value)
{
	printf("Adding node ");
	debugWrite(key, value);
	TreeNode *node = bstAddNode(root, key, value);
	balanceTree(node);
	return node;
}

int checkRBInvariants(TreeNode *branch, int blackCount)
{
	/* Invariant 1 : all leaves are black */
	if(!branch)
		return blackCount == 1;

	if(branch->color == COLOR_RED)
	{
		/* Invariant 2 : the red node has two black children */
		if(branch->left && branch->left->color == COLOR_RED)
			return 0;
		if(branch->right && branch->right->color == COLOR_RED)
			return 0;
		return checkRBInvariants(branch->left, blackCount) &&
			checkRBInvariants(branch->right, blackCount);
	}

	return checkRBInvariants(branch->left, blackCount-1) &&
		checkRBInvariants(branch->right, blackCount-1);
}

int getSimplePathBlackNodesCount(TreeNode *root)
{
	if(root == NULL)
		return 1;
	int count = root->color == COLOR_BLACK;
	return count + getSimplePathBlackNodesCount(root->left);
}

int isARBTree(TreeNode *root)
{
	/* Invariant 1 : the root is black */
	if(root->color != COLOR_BLACK)
		return 0;

	int black_count = getSimplePathBlackNodesCount(root) - 1;

	return checkRBInvariants(root->left, black_count) &&
		checkRBInvariants(root->right, black_count);
}

void dumpTree(TreeNode *tree, int indent, void(*writer)(void*,void*,int))
{
	int i = indent;
	while(i)
	{
		printf("\t");
		--i;
	}

	if(!tree)
	{
		printf("Leaf\n");
		return;
	}

	writer(tree->key, tree->value, tree->color);

	dumpTree(tree->left, indent+1, writer);
	dumpTree(tree->right, indent+1, writer);
}
