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

#include <vector>

using std::vector;

class Bron_Kerbosch {
public:
	Bron_Kerbosch(GRAPH& graph);
	Bron_Kerbosch(GRAPH* graph_array, INT size=0);
	
	// adapted from: https://en.wikipedia.org/wiki/Bron%E2%80%93Kerbosch_algorithm under the
	// without pivoting section
	// P -> vertex set of the graph
	void find_max_clique_without_pivoting(vector<INT>& R, vector<INT>& P, vector<INT>& X);
	
	~Bron_Kerbosch();
	
private:
	GRAPH* graph = NULL;
	INT graph_array_size = 0;
};

#endif /* BRON_KERBOSCH_H */

