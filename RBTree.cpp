#define _CRT_SECURE_NO_WARNINGS
#include <iostream> 
#include <stdio.h> 
#include <cstdlib>
using namespace std;
int level = 0;
#define COLOR_RED 0
#define COLOR_BLACK 1
struct rbtree {
	int key;
	int color;
	struct rbtree *parent;
	struct rbtree *left;
	struct rbtree *right;
};

struct rbtree EmptyNode = { 0, /*0,*/ COLOR_BLACK,NULL, NULL ,NULL };

struct rbtree *NullNode = &EmptyNode;

struct rbtree *rbtree_left_rotate(struct rbtree *root, struct rbtree *node)
{
	struct rbtree *right = node->right;
	/* Create node->right link */
	node->right = right->left;
	if (right->left != NullNode)
		right->left->parent = node;
	/* Create right->parent link */
	if (right != NullNode)
		right->parent = node->parent;

	if (node->parent != NullNode) {
		if (node == node->parent->left)
			node->parent->left = right;
		else
			node->parent->right = right;
	}
	else {
		root = right;
	}
	right->left = node;
	if (node != NullNode)
		node->parent = right;
	return root;
}

struct rbtree *rbtree_right_rotate(struct rbtree *root, struct rbtree *node)
{
	struct rbtree *left = node->left;
	/* Create node->left link */
	node->left = left->right;
	if (left->right != NullNode)
		left->right->parent = node;
	/* Create left->parent link */
	if (left != NullNode)
		left->parent = node->parent;

	if (node->parent != NullNode) {
		if (node == node->parent->right)
			node->parent->right = left;
		else
			node->parent->left = left;
	}
	else {
		root = left;
	}
	left->right = node;
	if (node != NullNode)
		node->parent = left;
	return root;
}

struct rbtree *rbtree_fixup_add(struct rbtree *root,struct rbtree *node)
{
	struct rbtree *uncle;
	/* Current node is RED */
	while (node != root &&
		node->parent->color == COLOR_RED)
	{
		if (node->parent ==	node->parent->parent->left)
		{
			/* node in left tree of grandfather */
			uncle = node->parent->parent->right;

			if (uncle->color == COLOR_RED) {
				/* Case 1 - uncle is RED */
				node->parent->color = COLOR_BLACK;
				uncle->color = COLOR_BLACK;
				node->parent->parent->color = COLOR_RED;
				node = node->parent->parent;
			}
			else {
				/* Cases 2 & 3 - uncle is BLACK */
				if (node == node->parent->right) {
					/* Reduce case 2 to case 3 */
					node = node->parent;
					root = rbtree_left_rotate(root,node);
				}

				/* Case 3 */
				node->parent->color = COLOR_BLACK;
				node->parent->parent->color = COLOR_RED;
				root = rbtree_right_rotate(root,node->parent->parent);
			}

		}
		else {
			/* Node in right tree of grandfather */
			uncle = node->parent->parent->left;
			if (uncle->color == COLOR_RED) {
				/* Uncle is RED */
				node->parent->color = COLOR_BLACK;
				uncle->color = COLOR_BLACK;
				node->parent->parent->color = COLOR_RED;
				node = node->parent->parent;
			}
			else {
				/* Uncle is BLACK */
				if (node == node->parent->left) {
					node = node->parent;
					root = rbtree_right_rotate(root,node);
				}
				node->parent->color = COLOR_BLACK;
				node->parent->parent->color = COLOR_RED;
				root = rbtree_left_rotate(root,node->parent->parent);
			}
		}
	}
	root->color = COLOR_BLACK;
	return root;
}

struct rbtree *rbtree_add(struct rbtree *root,int key)
{
	struct rbtree *node, *parent = NullNode;
	/* Search leaf for new element */
	for (node = root; node != NullNode && node != NULL; )
	{
		parent = node;
		if (key < node->key)
			node = node->left;
		else if (key > node->key)
			node = node->right;
		else
			return root;
	}
//	struct rbtree* node = (struct rbtree*) malloc(sizeof(struct rbtree));
	node = new rbtree;
	if (node == NULL)
		return NULL;
	node->key = key;
	//node->value = value;
	node->color = COLOR_RED;
	node->parent = parent;
	node->left = NullNode;
	node->right = NullNode;
	if (parent != NullNode) {
		if (key < parent->key)
			parent->left = node;
		else
			parent->right = node;
	}
	else {
		root = node;
	}
	return rbtree_fixup_add(root, node);
}

//функция для нахождения количества потомков дерева
int Node_Child(rbtree* Tree) {
	int l, r, h = 0;
	if (Tree != NULL) {
		l = Node_Child(Tree->left);//рекрсивная функция для нахождения количества потомков дерева
		r = Node_Child(Tree->right);
		h = r + l + 1;
	}
	return h;
}

void equ(rbtree* Tree)
{
	if (Tree == NULL)
		return;
	equ(Tree->left); //функция обхода поддеревьев
	equ(Tree->right);
	if ((Node_Child(Tree->left)== Node_Child(Tree->right))&&(Node_Child(Tree->left)!=1)&&( Node_Child(Tree->left)!=1))	// проверка 
	{
		if ((Tree->key != 0)) {
			cout << Tree->key << " " << endl;
			cout << "Left: " << Node_Child(Tree->left) << endl;
			cout << "Right: " << Node_Child(Tree->right) << endl;
		}
	}

}

void show(rbtree *&Tree) //Функция вывода дерева на экран
{
	if (Tree != NULL) //Пока не встретится пустое звено 
	{
		level++;
		show(Tree->left); //Рекурсивная функция для вывода левого поддерева 

		for (int i = 0; i<level; i++)
			cout << " ";
		cout << " " << Tree->key << endl; //Отображаем корень дерева 

		show(Tree->right); //Рекурсивная функци для вывода правого поддерева 
		level--;
	}

}

int main(int argc, char **argv)
{
	setlocale(LC_ALL, "Russian");
	struct rbtree *tree = NULL;
	int i;
	cout << "Введите числа: (0 - для завершения )" << endl;
	do
	{
		scanf("%d", &i);
		if (i != 0)
			tree = rbtree_add(tree, i);
	} while (i != 0);

	show(tree);
	equ(tree);

	system("pause");
	return 0;

}
