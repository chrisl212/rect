#include <stdio.h>
#include <stdlib.h>
#include "packing.h"

//size of buffer to read from file
#define BUF_SZ 64

Node *_create_nonleaf(int type) {
	//creates a nonleaf node with type 'H' or 'V'
	Node *nonleaf = calloc(1, sizeof(*nonleaf));
	nonleaf->id = type;
	return nonleaf;
}

Node *_create_leaf(int label, double width, double height) {
	//creates a leaf node with the given information
	Node *leaf = calloc(1, sizeof(*leaf));
	leaf->leaf = 1; //indicates a leaf node
	leaf->id = label;
	leaf->width = width;
	leaf->height = height;
	return leaf;
}

Node *_build_tree(FILE *f) {
	char buf[BUF_SZ] = {0}; //a buffer to be used for reading
	if (!fgets(buf, BUF_SZ, f)) {
		//if the file cannot be read from, fail
		return NULL;
	}
	Node *node = NULL;
	if (buf[0] == 'H' || buf[0] == 'V' ) {
		//if the first character is an 'H' or 'V', it is a nonleaf node
		node = _create_nonleaf((int)buf[0]);
	} else {
		//if the first character is a number, it is a leaf node
		int id = -1;
		double width, height = width = 0.0;
		//parses the data from the buffer
		sscanf(buf, "%d(%le,%le)", &id, &width, &height);
		node = _create_leaf(id, width, height); //creates a leaf node and returns it
		return node;
	}
	//finds the left and right nodes if it is a nonleaf
	node->left = _build_tree(f);
	node->right = _build_tree(f);
	return node;
}

Node *read_tree(FILE *f) {
	Node *root = _build_tree(f); //builds the tree from the file
	return root;
}

void print_tree(Node *tree, FILE *f) {
	if (!tree) {
		//cuts off when a null pointer is reached
		return;
	}
	//prints the left and right nodes before the node -> postorder
	print_tree(tree->left, f);
	print_tree(tree->right, f);
	if (tree->leaf) {
		//prints the leaf node
		fprintf(f, "%d(%le,%le)\n", tree->id, tree->width, tree->height);
	} else {
		//prints the nonleaf node
		fprintf(f, "%c\n", tree->id);
	}
}

double _max(double a, double b) {
	//returns the max of two numbers
	return (a > b) ? a : b;
}

void _find_dim(Node *tree) {
	if (!tree) {
		//cuts off when a null pointer is reached
		return;
	}
	//performs a postorder traversal
	_find_dim(tree->left);
	_find_dim(tree->right);
	if (tree->id == 'H') {
		//calculates the width of the horizontal cut
		//using the maximum width of either its 
		//left or right node
		tree->width = _max(tree->left->width, tree->right->width);
		//calculates the height of the horizontal cuts
		//using the sum of the heights of its nodes
		tree->height = tree->left->height + tree->right->height;
	} else if (tree->id == 'V') {
		//calculates the height of the vertical cut
		//using the max of the heights of its left and 
		//right nodes
		tree->height = _max(tree->left->height, tree->right->height);
		//calculates the width of the cut using the sum of
		//the widths of its left and right nodes
		tree->width = tree->left->width + tree->right->width;
	}
}

void _find_coord(Node *tree, double x, double y) {
	if (tree->id == 'H') {
		//goes through the left node of the horizontal 
		//cut using the passed in x as the base x 
		//value and the passed in y + the height of the 
		//right node as the y value
		_find_coord(tree->left, x, y+tree->right->height);
	       	//goes through the right node using the passed
		//in x and y values	
		_find_coord(tree->right, x, y);
	} else if (tree->id == 'V') {
		//goes through the left node of the vertical cuts
		//using the passed in x and y values
		_find_coord(tree->left, x, y);
		//goes through the right node of the vertical cut
		//using the passed in x value + the width of the 
		//left node and the passed in y value
		_find_coord(tree->right, x+tree->left->width, y);
	} else {
		//the x,y of a leaf node will be the value passed in
		tree->x = x;
		tree->y = y;
	}
}

void pack_tree(Node *tree) {
	_find_dim(tree); //finds the dimensions of nonleaf nodes
	_find_coord(tree, 0.0, 0.0); //finds the coordinates of leaf nodes
}

void save_dim(Node *tree, FILE *f) {
	if (!tree) {
		//cuts off once a null pointer is reached 
		return;
	}
	if (tree->leaf) {
		//prints a leaf node using integral representation
		fprintf(f, "%d(%le,%le)\n", tree->id, tree->width, tree->height);
	} else {
		//prints a nonleaf node using character representation
		fprintf(f, "%c(%le,%le)\n", tree->id, tree->width, tree->height);
	}
	//performs a preorder traversal
	save_dim(tree->left, f);
	save_dim(tree->right, f);
}

void save_coord(Node *tree, FILE *f) {
	if (!tree) {
		//cuts off once a null pointer is reached
		return;
	}
	if (tree->leaf) {
		//if it is a leaf node, prints the coordinates
		fprintf(f, "%d(%le,%le)\n", tree->id, tree->x, tree->y);
	}
	//performs a preorder traversal
	save_coord(tree->left, f);
	save_coord(tree->right, f);
}

void free_tree(Node *tree) {
	if (!tree) {
		//cuts off once a null pointer is reached 
		return;
	}
	//performs a postorder traversal
	free_tree(tree->left);
	free_tree(tree->right);
	free(tree); //frees the node
}
