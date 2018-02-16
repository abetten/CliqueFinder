/*
 * This class provides implementation for the Rainbow Clique Finding algorithm
 * only. 
 */

/* 
 * File:   Rainbow_Clique_Finding.h
 * Author: sajeeb
 *
 * Created on February 16, 2018, 2:09 PM
 */

#ifndef RAINBOW_CLIQUE_FINDING_H
#define RAINBOW_CLIQUE_FINDING_H

#include "graph.h"
#include "typedefs.h"
#include <iostream>
#include <vector>

using std::vector;

class Rainbow_Clique_Finding {
public:
	Rainbow_Clique_Finding(GRAPH& graph) {
		this->graph = &graph;
	}
	Rainbow_Clique_Finding(vector<GRAPH*>& graph_vector) {
		this->graph_vector = &graph_vector;
	}
	Rainbow_Clique_Finding(GRAPH* graph_array, INT size=0) {
		this->graph = graph_array;
		this->graph_array_size = size;
	}
	Rainbow_Clique_Finding(const Rainbow_Clique_Finding& orig);
	virtual ~Rainbow_Clique_Finding();
private:
	GRAPH* graph;
	vector<GRAPH*>* graph_vector;
	INT graph_array_size = 0;
};

#endif /* RAINBOW_CLIQUE_FINDING_H */

