#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct node_t {
	int value;
	struct node_t *left, *right;
	unsigned char level;
} node_t;

node_t *add(node_t *root, int value) {
	if (root == NULL) {
		node_t *newNode = (node_t *)malloc(sizeof(node_t));
		newNode->left = NULL;
		newNode->right = NULL;
		newNode->value = value;
		return newNode;
	}

	if (value < root->value) 
		root->left = add(root->left, value);
	
	else if (value > root->value) 
		root->right = add(root->right, value);
	
	return root;
}

void destroy(node_t *root) {
	if (root == NULL)
		return;

	destroy(root->left);
	destroy(root->right);

	free(root);
}

unsigned char _height(node_t *node, unsigned char level) {
	if (node == NULL)
		return level;

	unsigned char right =  _height(node->right, level + 1);
	unsigned char left = _height(node->left, level + 1);
	
	return right > left ? right : left;
}

unsigned char height(node_t *root) {
	
	return _height(root, 0);
}

int isIdentical(node_t *firstRoot, node_t *secondRoot) {
	if (secondRoot == NULL && firstRoot == NULL)
		return 1;

	if (secondRoot == NULL || firstRoot == NULL)
		return 0;

	return firstRoot->value == secondRoot->value && 
		isIdentical(firstRoot->left, secondRoot->left) &&
		isIdentical(firstRoot->right, secondRoot->right); 
}

int *fetchValues(node_t *root, int *values) {
	if (root->left == NULL && root->right == NULL) {
		(*values) = root->value;
		return values + 1;
	}

	
	if (root->left)
		values = fetchValues(root->left, values);
	
	(*values) = root->value;
	values++;
	
	if (root->right)
		values = fetchValues(root->right, values);

	return values;
}

size_t sizeTree(node_t *root) {
	if (root == NULL)
		return 0;

	return sizeTree(root->left) + sizeTree(root->right) + 1;
}

node_t *_helperBalancer(node_t *root, int *arr, size_t size) {
	if (size == 0)
		return NULL;
	int element = arr[size / 2];
	root = add(root, element);
	_helperBalancer(root, arr, size / 2);

	_helperBalancer(root, arr + size / 2 + 1, size - (size / 2 + 1));

	return root;
}
node_t *balanceTree(node_t *root) {
	size_t size = sizeTree(root);
	int *arr = (int *)malloc(sizeof(int) * size);

	fetchValues(root, arr);

	node_t *newRoot =  _helperBalancer(NULL, arr, size);	

	free(arr);
	return newRoot;
}

void print2DUtil(node_t *root, int space) {
    size_t size = sizeTree(root);
	
	if (root == NULL)
		return;

	space += size;

	print2DUtil(root->right, space);

	printf("\n");
	for (int i = size; i < space; i++)
		printf(" ");
	printf("%d\n", root->value);

	print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
void printTree(node_t *root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

int isBalanced(node_t *root) {
	if (root == NULL)
		return 1;

	size_t elementCnt = sizeTree(root);
	int ifIsBalanced = (int)log2(elementCnt) + 1;

	return ifIsBalanced == height(root);
}

node_t *rightRotate(node_t *y) {
	node_t *x = y->left; 
	node_t *T2 = x->right;

	x->right = y;
	y->left = T2;

	return x;
}
node_t *leftRotate(node_t *y) {
	node_t *x = y->right; 
	node_t *T2 = x->left;

	x->left = y;
	y->right = T2;

	return x;
}

node_t *parent(node_t *root, node_t *child) {
	if (root == NULL)
		return NULL;
	if (root->left == child || root->right == child)
		return root;

	if (root->value < child->value)
		return parent(root->right, child);
	
	return parent(root->left, child);
}

char BF(node_t *root) {
	return height(root->left) - height(root->right);
}

node_t *minNode(node_t *root) {
	if (!root)
		return NULL;
	while(root->left)
		root = root->left;
	return root;
}

node_t *delete(node_t *root, int value) {
	if (root == NULL)
		return NULL;

	if (root->value > value)
		root->left = delete(root->left, value);
	else if (root->value < value)
		root->right = delete(root->right, value);
	else {
		if (root->left == NULL && root->right == NULL) {
			free(root);
			return NULL; // NULL == (void *)0
		}
		if (root->left == NULL || root->right == NULL) {
			node_t *temp = (root->left ? root->left : root->right);
			free(root);
			return temp;
		}
		else {
			node_t *minRight = minNode(root->right);
			root->value = minRight->value;
			
			root->right = delete(root->right, root->value);

			return root;
		}

	}
	return root;
}

int main() {
	// node_t *AVLroot = add(NULL, 30);
	// AVLroot = AVLInsert(AVLroot, 10);
	// AVLroot = AVLInsert(AVLroot, 20);
	// AVLroot = AVLInsert(AVLroot, 40);
	// AVLroot = AVLInsert(AVLroot, 16);
	// AVLroot = AVLInsert(AVLroot, 51);
	// AVLroot = AVLInsert(AVLroot, -14);
	// AVLroot = AVLInsert(AVLroot, 69);
	// AVLroot = AVLInsert(AVLroot, 420);

	// printTree(AVLroot);
	// printf("/////////////////////\n");

	// node_t *root = add(NULL, 15); 
	// root = add(root, 11);
	// root = add(root, 8);
	// root = add(root, -2);
	// root = add(root, 20);

	
	// node_t *root1 = add(NULL, 15); 
	// root1 = add(root1, 11);
	// root1 = add(root1, 8);
	// root1 = add(root1, -2);
	// root1 = add(root1, 20);

	// printf("%d\n", isIdentical(root, root1));
	
	// root1 = add(root1, 54);
	
	// printf("%d\n", isIdentical(root, root1));

	// int *arr = (int *)malloc(sizeof(int) * 6);
	// fetchValues(root1, arr);

	// for (int i = 0; i < 6; ++i) {
	// 	printf("%d ", arr[i]);
	// }
	// printf("\n");

	// printf("Height: %hhu\n", height(root));
	// printf("Is balanced: %d\n", isBalanced(root1));
	// root1 = balanceTree(root1);

	// printf("Is balanced: %d\n", isBalanced(root1));
	// fetchValues(root1, arr);

	// for (int i = 0; i < 6; ++i) {
	// 	printf("%d ", arr[i]);
	// }
	// printf("\n");
	// printTree(root1);
	// root1->left = leftRotate(root1->left);
	// printf("/////////////////////\n");
	// printTree(root1);
	// root1 = rightRotate(root1);
	// printf("/////////////////////\n");
	// printTree(root1);
	// root1 = delete(root1, 8);
	// printf("/////////////////////\n");
	// printTree(root1);
	// free(arr);
	// destroy(root);
	// destroy(root1);

	return 0;
}