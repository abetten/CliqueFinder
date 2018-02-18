/*
 * The purpose of this class is to be a dictionary of algorithms that can be
 * applied to graph object(s) to achieve a particular goal. For example, an
 * algorithm for doing topological sort on a graph(s) or an algorithm for finding
 * the maximal possible subgraph in a graph of n nodes and e edges. Such algorithms
 * can be called by specifying the algorithm name at construction and calling
 * the graph_algorithms.start_execution() to start the execution of the algorithm.
 * 
 */

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
#include "graph.h"
#include "typedefs.h"

#include "Rainbow_Clique_Finding.h"

using std::vector;

class graph_algorithms {
public:
	enum algorithm { // defines a list of implemented algorithms in this class
		Rainbow_Clique_Finding,
		Minimum_Spanning_Tree
	};
	
	graph_algorithms(GRAPH& graph, algorithm alg) {
		// Takes in reference to a single graph object
		this->graph = &graph;
		this->algo = alg;
	}
	
	graph_algorithms(vector<GRAPH*>& graph_vector,  algorithm alg) {
		// Takes in reference to a vector of graph pointers, where the
		// pointers point to graph objects in memory
		this->graph_vector = &graph_vector;
		this->algo = alg;
	}

	graph_algorithms(GRAPH* graph_array, algorithm alg, INT size=0):
	graph_array_size(size) {
		// Takes in pointer to an array of graph objects
		this->graph = graph_array;
		this->algo = alg;
	}
	
	void start_execution();
	
	// member public variables
	bool parallel_execution = false;
	// parallel_execution_type
private:
	GRAPH* graph = NULL; // can point to either an array of graphs or to a
			     // single graph object
	INT graph_array_size = 0;
	vector<GRAPH*>* graph_vector = NULL;
	algorithm algo;
	
	// list of all algorithms that can be applied to the graph
	
};


#endif
