#ifndef PACKING_H
#define PACKING_H

typedef struct _Node {
	int leaf; //indicates that a node is leaf node (rectangle)
	int id; //either a number or an 'H' or 'V'
	double width; //the width of the node
	double height; //the height of the node
	double x; //the x-coord of the node
	double y; //the y-coord of the node
	struct _Node *left;
	struct _Node *right;
} Node;

Node *read_tree(FILE *f); //reads the tree from an opened file
void print_tree(Node *tree, FILE *f); //prints the tree in postorder to a file
void pack_tree(Node *tree); //packs the tree
void save_dim(Node *tree, FILE *f); //saves the dimensions of the tree to an open file
void save_coord(Node *tree, FILE *f); //saves the coordinates of the tree to an open file
void free_tree(Node *tree); //frees the memory occupied by the tree

#endif

