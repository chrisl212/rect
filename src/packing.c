#include <stdio.h>
#include <stdlib.h>
#include "packing.h"

Node *_create_nonleaf(int type) {
	Node *nonleaf = calloc(1, sizeof(*nonleaf));
	nonleaf->id = type;
	return nonleaf;
}

Node *_create_leaf(int label, double width, double height) {
	Node *leaf = calloc(1, sizeof(*leaf));
	leaf->leaf = 1;
	leaf->id = label;
	leaf->width = width;
	leaf->height = height;
	return leaf;
}

Node *_build_tree(FILE *f) {
	char buf[256];
	if (!fgets(buf, 256, f)) {
		return NULL;
	}
	Node *node = NULL;
	if (buf[0] == 'H' || buf[0] == 'V' ) {
		node = _create_nonleaf((int)buf[0]);
	} else {
		int id = -1;
		double width, height = width = 0.0;
		sscanf(buf, "%d(%le,%le)", &id, &width, &height);
		node = _create_leaf(id, width, height);
		return node;
	}
	node->left = _build_tree(f);
	node->right = _build_tree(f);
	return node;
}

Node *read_tree(FILE *f) {
	Node *root = _build_tree(f);
	fclose(f);
	return root;
}

void print_tree(Node *tree, FILE *f) {
	if (!tree) {
		return;
	}
	print_tree(tree->left, f);
	print_tree(tree->right, f);
	if (tree->leaf) {
		fprintf(f, "%d(%le,%le)\n", tree->id, tree->width, tree->height);
	} else {
		fprintf(f, "%c\n", tree->id);
	}
}

void pack_tree(Node *tree) {

}

void save_dim(Node *tree, FILE *f) {
	if (!tree) {
		return;
	}
	if (tree->leaf) {
		fprintf(f, "%d(%le,%le)\n", tree->id, tree->width, tree->height);
	} else {
		fprintf(f, "%c(%le,%le)\n", tree->id, tree->width, tree->height);
	}
	save_dim(tree->left, f);
	save_dim(tree->right, f);
}

void save_coord(Node *tree, FILE *f) {
	if (!tree) {
		return;
	}
	if (tree->leaf) {
		fprintf(f, "%d(%le,%le)\n", tree->id, tree->x, tree->y);
	}
	save_coord(tree->left, f);
	save_coord(tree->right, f);
}

void free_tree(Node *tree) {
	if (!tree) {
		return;
	}
	free_tree(tree->left);
	free_tree(tree->right);
	free(tree);
}
