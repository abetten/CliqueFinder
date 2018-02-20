/*
 * File:   graph.cpp
 * Author: Sajeeb
 *
 * Created on Febryary 11, 2018, 6:56 PM
 */


#include "graph.h"
#include "typedefs.h"
#include <iostream>

using std::cout;
using std::endl;

void GRAPH::print_adj_matrix() {
	bool** matrix = this->adj_matrix;
	INT matrix_order = this->nb_points;
	for (INT i = 0; i < matrix_order; ++i) {
		for (INT j = 0; j < matrix_order; ++j) {
			cout << matrix[i][j] << "  ";
		}
		cout << endl;
	}
}

INT GRAPH::num_adj_verticies(INT i) {
	INT num_adj_verticies = 0;
	for (INT j = 0; j < nb_points; ++j) {
		if (is_adjacenct(i, j)) {
			num_adj_verticies = num_adj_verticies + 1;
		}
	}
	if (num_adj_verticies == 0) return -1;
	if (num_adj_verticies != 0) return num_adj_verticies;
}

/*
 * The purpose of this function is to turn the particular graph object that this
 * is a part of into the complement of that graph object, in particular, by 
 * flipping all the zeros(0's) in the adj. matrix to a one(1) and all the ones(1's)
 * to zeros(0's). Executing this function is guaranteed to mutate the current
 * graph object.
 */
void GRAPH::complement() {
	for (INT i=0; i<nb_points; ++i) {
		for (INT j=0; j<nb_points; ++j) {
			if (adj_matrix[i][j] == 0) adj_matrix[i][j] = 1;
			else if (adj_matrix[i][j] == 1) adj_matrix[i][j] = 0;
		}
	}
}