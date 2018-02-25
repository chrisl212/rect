#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "packing.h"

int main(int argc, char **argv) {
	if (argc != 5) {
		return EXIT_FAILURE;
	}

	//Opens the file for reading
	FILE *in_f = fopen(argv[1], "r");
	if (!in_f) {
		//if the file cannot be opened, fails
		return EXIT_FAILURE;
	}
	Node *tree = read_tree(in_f); //parses the tree
	fclose(in_f); //closes the input file

	FILE *out1_f = fopen(argv[2], "w"); //opens the postorder file
	if (!out1_f) {
		//if the file cannot be opened, fails
		free_tree(tree);
		return EXIT_FAILURE;
	}
	print_tree(tree, out1_f); //prints the tree in postorder to the file 
	fclose(out1_f); //closes the postorder file

	pack_tree(tree); //performs packing on the tree

	FILE *out2_f = fopen(argv[3], "w"); //opens the dimensions file for writing
	if (!out2_f) {
		//if the file cannot be opened, fails
		free_tree(tree);
		return EXIT_FAILURE;
	}
	save_dim(tree, out2_f); //saves the dimensions to the file
	fclose(out2_f); //closes the dimensions file

	FILE *out3_f = fopen(argv[4], "w"); //opens the coord file for writing
	if (!out3_f) {
		//if the file cannot be opened, fails
		free_tree(tree);
		return EXIT_FAILURE;
	}
	save_coord(tree, out3_f); //saves the coords to the file
	fclose(out3_f); //closes the coordinate file

	free_tree(tree); //frees the tree

	return EXIT_SUCCESS;
}

