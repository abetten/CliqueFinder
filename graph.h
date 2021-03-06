/*
 * The purpose of this class is to only contain information pertaining to the 
 * graph. This class should not contain any member functions that implement 
 * any graph algorithms. The only member functions that this class is allowed to
 * contain are the functions that read in data from an external source that the
 * graph should contain. These member functions include, but are not limited to 
 * delinearizing the adjacency vector to an adjacency matrix that si stored in 
 * an instance of this class. Although this class can be used as a tree by not 
 * having edges between nodes at the same level, it is highly not recommended.
 */

/*
 * File:   graph.h
 * Author: Sajeeb
 *
 * Created on Febryary 11, 2018, 6:11 PM
 */


#ifndef GRAPH_H
#define GRAPH_H

#include "typedefs.h"
#include <iostream>
#include <string.h>
#include <fstream>
#include <math.h>
#include <vector>
#include "misc_functions.cpp"

using std::vector;
using std::cout;
using std::endl;

class GRAPH {
public:

	GRAPH(INT graph_id, const BYTE* fname_template) {
		BYTE fname[1000]; // input file name for where the graph is stored on disk
		BYTE fname_base[1000]; // base filename for the graph, i.e. filename without the file extension
		FILE* fp;

		sprintf(fname, fname_template, graph_id); // replace %ld in fname_template with graph_id
		// and assign the result to fname
		strcpy(fname_base, fname); // fname = fname_base
		_replace(fname_base, '.'); // replace everything after '.' with nothing


		fp = fopen(fname, "rb"); // open the graphs binary file

		// Populate Variables
		fread(&nb_points, 1, 4, fp); // read the number of points in the graph
		fread(&nb_colors, 1, 4, fp); // read the number of colors in the graph

		fread(&user_data_size, 1, 4, fp);
		user_data = new INT[user_data_size];
		for (INT i = 0; i < user_data_size; ++i) fread(&user_data[i], 1, 4, fp);

		points = new INT[nb_points](); // allocate memory for each point in the graph
		point_color = new INT[nb_points](); // allocate memory for the color of each point in the graph
		for (INT i = 0; i < nb_points; ++i) {
			fread(&points[i], 1, 4, fp);
			fread(&point_color[i], 1, 4, fp);
			if (point_color[i] >= nb_colors) {
				cout << "point_color[i] >= nb_colors" << endl;
				cout << "point_color[i]=" << point_color[i] << endl;
				cout << "i=" << i << endl;
				cout << "nb_colors=" << nb_colors << endl;
				exit(-1);
			}
		}

		L = (nb_points * (nb_points - 1)) >> 1; //number of entries in the linearized adj. matrix
		bitvector_length = (L + 7) >> 3; // number of chars used to store the linearized adj. matrix
		bitvector_adjacency = new UBYTE [bitvector_length]();
		fread(bitvector_adjacency, 1, bitvector_length, fp);

		adj_matrix = delinearize_adj_matrix(bitvector_adjacency, nb_points);

		fclose(fp);
	}

	~GRAPH() {
		if (user_data) delete [] user_data;
		if (points) delete [] points;
		if (point_color) delete [] point_color;
		if (bitvector_adjacency) delete [] bitvector_adjacency;
		if (adj_matrix) for (INT i = 0; i < nb_points; ++i) delete [] adj_matrix[i];
		if (adj_matrix) delete [] adj_matrix;
	}

	// Class member functions
	void print_adj_matrix();

	inline bool is_adjacenct(INT i, INT j) {
		if (i < 0 || j < 0 || i >= nb_points || j >= nb_points) return 0;
		return GRAPH::adj_matrix[i][j];
	}

	// Class member variables
	INT nb_points = 0; // number of points in the graph
	INT nb_colors = 0; // number of colors in the graph
	INT L = 0;
	INT bitvector_length = 0; // length of the bit-vector
	INT user_data_size = 0;
	INT* user_data = NULL;
	INT* points = NULL; // array of points in the graph
	INT* point_color = NULL; // the color of the respective point
	UBYTE* bitvector_adjacency = NULL; // liearized adjacency matrix
	bool** adj_matrix = NULL; // adjacency matrix
	
	// Class member functions
	INT num_adj_verticies(INT i);
	void complement();
	void delete_verticies_with_degree(INT K);

private:

};


#endif
