/*
 * This class provides implementation for the Rainbow Clique Finding algorithm
 * only. This class is not allowed to contain any other member variables other
 * than the variables required for the execution of the algorithm. This same
 * philosophy goes for member functions within this class, i.e. the class
 * should only contain member functions that are required for the proper
 * functioning of the algorithm, these functions should be private instances
 * and should neither be public or protected.
 *
 */

/* 
 * File:   Rainbow_Clique_Finding.h
 * Author: sajeeb
 *
 * Created on February 16, 2018, 5:52 PM
 */

#ifndef RAINBOW_CLIQUE_FINDING_H
#define RAINBOW_CLIQUE_FINDING_H

#include "graph.h"
#include "typedefs.h"
#include <vector>

using std::vector;

class Rainbow_Clique_Finding {
public:
	
	Rainbow_Clique_Finding(GRAPH& graph);
	Rainbow_Clique_Finding(vector<GRAPH*>& graph_vector);
	Rainbow_Clique_Finding(GRAPH* graph_array, INT size=0);
	
	~Rainbow_Clique_Finding() {
		for (INT i=0; i<graph->nb_colors; ++i)
			if (live_points[i]) delete [] live_points[i];
		if (live_points) delete [] live_points;
		if (color_satisfied) delete[] color_satisfied;
		if (current_clique) delete [] current_clique;
		if (nb_live_points_at_depth) delete [] nb_live_points_at_depth;
	}
	
	
	
private:
	vector<vector<INT> > solutions;
	
	GRAPH* graph = NULL;
	vector<GRAPH*>* graph_vector = NULL;
	INT graph_array_size = -1;
	
	INT** live_points = NULL;
	INT* color_satisfied = NULL;
	INT* current_clique = NULL;
	INT* nb_live_points_at_depth = NULL;
	INT* color_frequency = NULL;
	
	// member functions required for this clique finding algorithm
	inline void create_color_freq_of_live_points(INT depth);
	inline INT min_element_index(INT* array, INT size);
	
	// main algorithm function
	void find_rainbow_cliques(INT depth);
	
	void find_cliques_of_size_(INT k);
	
	bool all_color_satisfied();
	
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

#endif /* RAINBOW_CLIQUE_FINDING_H */

