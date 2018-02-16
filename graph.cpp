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

inline void GRAPH::print_adj_matrix(bool** matrix, INT matrix_order) {
	for (INT i=0; i<matrix_order; ++i) {
		for (INT j=0; j<matrix_order; ++j) {
			cout<< matrix[i][j] << "  ";
		}
		cout<<endl;
	}
}


inline bool GRAPH::is_adjacenct(INT i, INT j) {
	return GRAPH::adj_matrix[i][j];
}
