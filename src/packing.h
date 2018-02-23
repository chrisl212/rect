#ifndef PACKING_H
#define PACKING_H

typedef struct _Node {
	int leaf;
	int id;
	double width;
	double height;
	double x;
	double y;	
	struct _Node *left;
	struct _Node *right;
} Node;

Node *read_tree(FILE *f);
void print_tree(Node *tree, FILE *f);
void pack_tree(Node *tree);
void save_dim(Node *tree, FILE *f);
void save_coord(Node *tree, FILE *f);
void free_tree(Node *tree);

#endif

