/*
 * File:   chrono.h
 * Author: Sajeeb
 *
 * Created on Febryary 11, 2018, 6:39 PM
 */

#include <strings.h>
#include <iostream>
#include <cstring>

#include "typedefs.h"
#include "misc_functions.h"


using std::cout;
using std::endl;

inline void _replace(BYTE* string, BYTE character,  const BYTE* replacement/*=NULL*/) {
	// replace everything after a particular character
	char* pch = strrchr(string, character); // pointer to last occurrence of character
	string[pch-string] = '\0' ;  // add null terminator in place of the '.'
	if (replacement) strcat(string, replacement);
}

inline INT bitvector_s_i(UBYTE *bitvec, INT i) {
	// returns 0 or 1
	
	long int ii, bit;
	unsigned char mask;
	
	ii = i >> 3;
	bit = i & 7;
	mask = ((unsigned char) 1) << bit;
	unsigned char &x = bitvec[ii];
	if (x & mask) {
		return 1;
	} else {
		return 0;
	}
}

inline INT ij2k(INT i, INT j, INT n) {
	if (i == j) {
		cout << "ij2k() i == j" << endl;
		exit(1);
	}
	if (i > j) {
		return ij2k(j, i, n);
	} else {
		return ( (n - i) * i + ((i * (i - 1)) >> 1) + j - i - 1 );
	}
}

inline bool** delinearize_adj_matrix(UBYTE* bitvector_adjacency, INT nb_points) {
	// turn the linearized adjaency matrix back into a nxn matrix
	bool** adj_matrix = new bool* [nb_points]; // allocate memory for matrix rows
	for (INT i=0; i<nb_points; ++i) adj_matrix[i] = new bool [nb_points]; // allocate memory for cols
	for (INT i=0; i<nb_points; ++i) {	// row
		adj_matrix[i][i]=0; // set all the elements along the diagonal equal to zero
		for (INT j=i+1; j<nb_points; ++j) {	//column
			INT k = ij2k(i, j, nb_points);
			INT aij = bitvector_s_i(bitvector_adjacency, k);
			adj_matrix[i][j] = adj_matrix[j][i] = aij;
		}
	}
	return adj_matrix;
}

template <typename array_type>
inline void print_1_D_array(array_type* array,INT size) {
	cout<<"[ ";
	for (INT i=0; i<size; ++i) {
		cout << array[i];
		if (i+1 != size)
			cout<<", ";
	}
	cout<<" ]"<<endl;
}