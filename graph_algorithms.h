/*
 * File:   graph_algorithms.h
 * Author: Sajeeb
 *
 * Created on February 15, 2018, 8:27 PM
 */


#ifndef GRAPH_ALGORITHMS
#define GRAPH_ALGORITHMS

#include <iostream>
#include <vector>

using std::vector;

#include "graph.h"


class graph_algorithms {
public:
	enum algorithm { // defines a list of implemented algorithms in this class
		Rainbow_Clique_Finding
	};
	
	graph_algorithms(GRAPH& graph, algorithm alg) {
		// Takes in reference to a single graph object
		this->graph = &graph;
		this->algo = alg;
	}
	
	graph_algorithms(vector<GRAPH>& graph_vector,  algorithm alg) {
		this->graph_vector = &graph_vector;
		this->algo = alg;
	}

	graph_algorithms(GRAPH* graph_array, algorithm alg) {
		// pointer to an array of graph objects
		this->graph = graph_array;
		this->algo = alg;
	}
	
	inline void start_execution();
private:
	GRAPH* graph = NULL; // can point to either an array of graphs or to a
			     // single graph object
	vector<GRAPH>* graph_vector;
	algorithm algo;
	
	// list of all algorithms that cam be applied to the graph
	
};


#endif
