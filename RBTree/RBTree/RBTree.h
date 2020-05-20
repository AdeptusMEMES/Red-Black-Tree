#pragma once

#include "pch.h"
#include <iostream>

using namespace std;

typedef int T;

typedef enum
{
	BLACK,
	RED
} nodeColor;

typedef struct Node_
{
	struct Node_ *left;
	struct Node_ *right;
	struct Node_ *parent;
	nodeColor color;
	T data;
} Node;

#define NIL &sentinel
Node sentinel = { NULL, NULL, 0, BLACK, 0 };
Node *root = NIL;

void rotateLeft(Node *x)
{
	Node *y = x->right;

	x->right = y->left;

	if (y->left != NIL)
		y->left->parent = x;

	if (y != NIL)
		y->parent = x->parent;

	if (x->parent)
	{
		if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	}
	else
		root = y;

	y->left = x;
	if (x != NIL)
		x->parent = y;
}

void rotateRight(Node *x)
{
	Node *y = x->left;

	x->left = y->right;

	if (y->right != NIL)
		y->right->parent = x;

	if (y != NIL)
		y->parent = x->parent;

	if (x->parent)
	{
		if (x == x->parent->right)
			x->parent->right = y;
		else
			x->parent->left = y;
	}
	else
		root = y;

	y->right = x;
	if (x != NIL)
		x->parent = y;
}

void insertFixup(Node *x)
{
	while (x != root && x->parent->color == RED)
	{
		Node *uncle;
		if (x->parent == x->parent->parent->left)
		{
			uncle = x->parent->parent->right;
			if (uncle->color == RED)	// red uncle
			{
				x->parent->color = BLACK;	//recoloring only
				uncle->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			}
			else    //recoloring and rotate
			{
				if (x == x->parent->right)
				{
					x = x->parent;
					rotateLeft(x);
				}
				x->parent->color = BLACK;
				x->parent->parent->color = RED;
				rotateRight(x->parent->parent);
			}
		}
		else
		{
			uncle = x->parent->parent->left;
			if (uncle->color == RED)	//uncle is RED
			{
				x->parent->color = BLACK;
				uncle->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			}
			else    //uncle is BLACK
			{
				if (x == x->parent->left)
				{
					x = x->parent;
					rotateRight(x);
				}
				x->parent->color = BLACK;
				x->parent->parent->color = RED;
				rotateLeft(x->parent->parent);
			}
		}
	}
	root->color = BLACK;
}

void insertNode(T data)
{
	Node *current, *parent, *x;

	current = root;
	parent = 0;
	while (current != NIL)
	{
		if (data == current->data)
			return;
		parent = current;
		if (data < current->data)
			current = current->left;
		else
			current = current->right;
	}

	x = new Node;
	x->data = data;
	x->parent = parent;
	x->left = NIL;
	x->right = NIL;
	x->color = RED;

	if (parent)
	{
		if (data < parent->data)
			parent->left = x;
		else
			parent->right = x;
	}

	else
		root = x;

	insertFixup(x);
}

void deleteFixup(Node *x)
{
	while (x != root && x->color == BLACK)
	{
		Node *w;
		if (x == x->parent->left)	//x is left child
		{
			w = x->parent->right;
			if (w->color == RED)	//red brother	
			{
				w->color = BLACK;
				x->parent->color = RED;
				rotateLeft(x->parent);
				w = x->parent->right;
			}
			if (w->left->color == BLACK && w->right->color == BLACK)	//red brother with black children
			{
				w->color = RED;
				x = x->parent;
			}
			else
			{
				if (w->right->color == BLACK)	//red brother with black right child
				{
					w->left->color = BLACK;
					w->color = RED;
					rotateRight(w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				rotateLeft(x->parent);
				x = root;
			}
		}
		else
		{
			w = x->parent->left;
			if (w->color == RED)
			{
				w->color = BLACK;
				x->parent->color = RED;
				rotateRight(x->parent);
				w = x->parent->left;
			}
			if (w->right->color == BLACK && w->left->color == BLACK)
			{
				w->color = RED;
				x = x->parent;
			}
			else
			{
				if (w->left->color == BLACK)
				{
					w->right->color = BLACK;
					w->color = RED;
					rotateLeft(w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				rotateRight(x->parent);
				x = root;
			}
		}
	}
	x->color = BLACK;
}

void deleteNode(Node *z)
{
	Node *x, *y;
	if (!z || z == NIL)
		return;
	if (z->left == NIL || z->right == NIL)	// y has a NIL node as a child
		y = z;
	else
	{
		y = z->right;
		while (y->left != NIL) y = y->left;
	}

	if (y->left != NIL)	//x is y's only child
		x = y->left;
	else
		x = y->right;

	x->parent = y->parent;	//remove y from the parent chain
	if (y->parent)
	{
		if (y == y->parent->left)
			y->parent->left = x;
		else
			y->parent->right = x;
	}
	else
		root = x;

	if (y != z)
		z->data = y->data;

	if (y->color == BLACK)
		deleteFixup(x);

	free(y);
}

Node *findNode(T data)
{
	Node *current = root;
	while (current != NIL)
	{
		if (data == current->data)
			return (current);
		else
		{
			if (data < current->data)
				current = current->left;
			else
				current = current->right;
		}
	}
	return(NULL);
}

void inOrder(Node *current)
{
	if (current->left != NIL)
		inOrder(current->left);
	cout << current->data << " ";
	if (current->right != NIL)
		inOrder(current->right);
}

void clearTree(Node *current)
{
	if (current->left != NIL)
		clearTree(current->left);
	if (current->right != NIL)
		clearTree(current->right);
	if (current == root)
		root = NIL;
	else
		free(current);
}
