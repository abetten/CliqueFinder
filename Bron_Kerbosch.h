/*
 * 
 */

/* 
 * File:   Bron_Kerbosch.h
 * Author: sajeeb
 *
 * Created on February 18, 2018, 10:29 PM
 */

#ifndef BRON_KERBOSCH_H
#define BRON_KERBOSCH_H

#include "graph.h"
#include "typedefs.h"
#include "misc_functions.cpp"

#include <vector>

using std::vector;
using std::cout;
using std::endl;

class Bron_Kerbosch {
public:
	Bron_Kerbosch(GRAPH& graph);
	Bron_Kerbosch(GRAPH* graph_array, INT size = 0);

	// adapted from: https://en.wikipedia.org/wiki/Bron%E2%80%93Kerbosch_algorithm under the
	// without pivoting section
	// P -> vertex set of the graph
	void find_max_clique_without_pivoting(vector<INT> R, vector<INT>& P, vector<INT> X);

	~Bron_Kerbosch();

private:
	GRAPH* graph = NULL;
	INT graph_array_size = 0;
	// P -> vertex set of the graph
	//
	vector<INT> R, P, X;
	vector<vector<INT>> cliques;
	// member functions
	inline vector<INT> find_neighbor_(INT v);
	inline vector<INT> set_intersection_(const vector<INT>& P, const vector<INT>& Q);
	inline void delete_element(vector<INT>& P, INT key);
	inline vector<INT> set_union_(vector<INT>& P, INT v);

	inline void print_vector(vector<INT>& R) {
		cout << "[ ";
		for (UINT i = 0; i < R.size(); ++i) {
			cout << R[i];
			if (i + 1 != R.size()) {
				cout << ", ";
			}
		}
		cout << " ]" << endl;
	}
};

#endif /* BRON_KERBOSCH_H */

