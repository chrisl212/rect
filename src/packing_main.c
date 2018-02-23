#include <stdio.h>
#include <stdlib.h>
#include "packing.h"

int main(int argc, char **argv) {
	if (argc != 5) {
		return EXIT_FAILURE;
	}
	FILE *in_f = fopen(argv[1], "r");
	if (!in_f) {
		return EXIT_FAILURE;
	}
	Node *tree = read_tree(in_f);
	fclose (in_f);

	FILE *out1_f = fopen(argv[2], "w");
	if (!out1_f) {
		return EXIT_FAILURE;
	}
	print_tree(tree, out1_f);
	fclose(out1_f);

	pack_tree(tree);

	FILE *out2_f = fopen(argv[3], "w");
	if (!out2_f) {
		return EXIT_FAILURE;
	}
	save_dim(tree, out2_f);
	fclose(out2_f);

	FILE *out3_f = fopen(argv[4], "w");
	if (!out3_f) {
		return EXIT_FAILURE;
	}
	save_coord(tree, out3_f);
	fclose(out3_f);

	free_tree(tree);

	return EXIT_SUCCESS;
}

