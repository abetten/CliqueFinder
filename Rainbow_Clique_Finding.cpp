/* 
 * File:   Rainbow_Clique_Finding.cpp
 * Author: sajeeb
 * 
 * Created on February 16, 2018, 5:52 PM
 */

#include "Rainbow_Clique_Finding.h"
#include <algorithm>
#include <cstdint>
#include <limits>

using std::fill;

Rainbow_Clique_Finding::Rainbow_Clique_Finding(GRAPH& graph) {
	this->graph = &graph;
	cout<< "Passed Graphs Reference." <<endl;
	Rainbow_Clique_Finding(this->graph,0);
}

Rainbow_Clique_Finding::Rainbow_Clique_Finding(vector<GRAPH*>& graph_vector) {
	this->graph_vector = &graph_vector;
	cout<< "Passed Graphs Vector" <<endl;
}

Rainbow_Clique_Finding::Rainbow_Clique_Finding(GRAPH* graph_array, INT size) {
	this->graph = graph_array;
	this->graph_array_size = size;
	if (size==0) {
		
		cout<< "passed graphs pointer" <<endl;
		
		this->live_points = new INT* [graph->nb_colors];
		this->color_satisfied = new INT [this->graph->nb_colors]();
		this->current_clique = new INT [this->graph->nb_colors]();
		this->color_frequency = new INT[this->graph->nb_colors]();
		this->nb_live_points_at_depth = new INT [graph->nb_colors]();
		
		cout<< "-------------------------------------------------------" <<endl;
		
		find_cliques_of_size_(graph->nb_colors);
	}
	if (size !=0) cout<< "passed graphs array" <<endl;
}

inline void Rainbow_Clique_Finding::create_color_freq_of_live_points(INT depth) {
	// any point in the graph that is dead will have a negative value in the
	// live_point array
	// reset color_frequency stats
	fill(this->color_frequency, this->color_frequency+graph->nb_colors, 0);
	
	for (INT i=0; i<nb_live_points_at_depth[depth]; ++i) {
		INT point_color = graph->point_color[live_points[depth][i]];
		this->color_frequency[point_color] += 1;
	}
}

inline INT Rainbow_Clique_Finding::min_element_index(INT* array, INT size) {
	// returns index of the lowest value in t he array
	INT min_element = std::numeric_limits<std::int32_t>::max();
	INT return_value = -1;
	for (INT i=0; i<size; ++i) {
		if (array[i] !=0 && array[i] < min_element) {
			min_element = array[i];
			return_value = i;
		}
	}
	
		
	return return_value;
}

void Rainbow_Clique_Finding::find_rainbow_cliques(INT depth) {
	
	INT pt, pt1;
	if (depth == graph->nb_colors) {
		return;
	}
	cout << "===================================================================================" <<endl;
	if (depth > 0) {
		pt1 = current_clique[depth-1];
		// clear number of points at current depth
		nb_live_points_at_depth[depth] = 0;
		// find number of adjacent verticies to the vertex selected at
		// previous depth
		for (INT i=0; i<nb_live_points_at_depth[depth-1]; ++i) {
			if (graph->is_adjacenct(pt1,live_points[depth-1][i])) {
				nb_live_points_at_depth[depth] += 1;
			//	cout<<"\tis_adj("<<pt1<<", "<<live_points[depth-1][i]<< "): 1"<<endl;
			}
		}
		cout<< "nb_live_points_at_depth_["<< depth <<"]: " << nb_live_points_at_depth[depth] <<endl;
		// allocate memory to store the live vertices at current depth
		live_points[depth] = new INT [ nb_live_points_at_depth[depth] ];
		// find the live verticies at current depth and put them in 
		// live_points[depth]
		for (INT i=0,p=0; i<nb_live_points_at_depth[depth-1]; ++i) {
			if (graph->is_adjacenct(pt1,live_points[depth-1][i])) {
				live_points[depth][p++] = live_points[depth-1][i];
			}
		}
		cout<<"points adj to "<< graph->points[pt1] <<": ";
		print_1_D_array(live_points[depth],nb_live_points_at_depth[depth]);
	}else{
		nb_live_points_at_depth[depth] = graph->nb_points;
		live_points[depth] = new INT [nb_live_points_at_depth[depth]];
		for (INT i=0; i<nb_live_points_at_depth[depth]; ++i) {
			live_points[depth][i] = i;
		}
		cout<<"nb_live_points_at_depth_["<< depth <<"]: "<<nb_live_points_at_depth[depth]<<endl;
		cout<<"live_points array: ";
		print_1_D_array(live_points[depth], nb_live_points_at_depth[depth]);
	}
	create_color_freq_of_live_points(depth);
	cout<< "Color Frequency Table: ";
	print_1_D_array(color_frequency, graph->nb_colors);
	// find color value with the lowest frequency
	INT lowest_color = min_element_index(this->color_frequency,graph->nb_colors);
	cout<< "Color with lowest frequency: " << lowest_color << " [This is the actual color]" <<endl;
	this->color_satisfied[lowest_color] = TRUE;
	// find how many points are there with the lowest value at current depth
	for (INT i=0; i<nb_live_points_at_depth[depth]; ++i) {
		if (graph->point_color[live_points[depth][i]] == lowest_color) {
			cout<< "Point that has the color with the lowest color frequency: ";
			cout<< graph->points[live_points[depth][i]] <<endl;
			cout<< "Index of the point with the lowest color frequency: " << live_points[depth][i] <<endl;
			pt = live_points[depth][i];
			this->current_clique[depth] = pt;
			cout<< "Calling find_rainbow_cliques("<<depth+1<<")"<<endl;
			find_rainbow_cliques(depth+1);
			cout<< "Control returned from depth: " << depth <<endl;
		}
	}
	this->color_satisfied[lowest_color] = FALSE;
}


void Rainbow_Clique_Finding::find_cliques_of_size_(INT k) {
	cout<<"Starting Rainbow_Clique_Finding::find_cliques_of_size_"<<k<<endl;
	vector<INT> P;
	
	//graph->complement();
	
	
	INT counter =0;
	
	// delete verticies with less than k-1 adj. verticies
	while (true) {
		// delete all elements in P
		P.clear();
		// Find verticies with less than k-1 adj. verticies
		for (INT i=0; i<graph->nb_points; ++i) {
			if (graph->num_adj_verticies(i) != -1)
				if (graph->num_adj_verticies(i) < k-1) P.push_back(i);
		}
		cout<<"verticies with less than "<<k-1<<" adj. verticies: ";
		print_vector(P);
		// delete verticies with less than k-1 adj. verticies
		for (INT i=0; i<P.size(); ++i) {
			for (INT j=0; j<graph->nb_points; ++j) {
				graph->adj_matrix[P[i]][j] = false ;
				graph->adj_matrix[j][P[i]] = false ;
			}
		}
		if (P.size() == 0) break;
	}
	
	graph->print_adj_matrix();
	/*---------------------------------------------------------------------------------------------*/
	// Actual k-clique finding algorithm
	/*---------------------------------------------------------------------------------------------*/
	
	/*---------------------------------------------------------------------------------------------*/
	
	
	
	cout<<"Done Rainbow_Clique_Finding::find_cliques_of_size_"<<k<<endl;
}
