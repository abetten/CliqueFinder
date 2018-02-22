/* 
 * File:   Rainbow_Clique_Finding.cpp
 * Author: sajeeb
 * 
 * Created on February 16, 2018, 5:52 PM
 */

// change

#include "Rainbow_Clique_Finding.h"
#include <algorithm>
#include <cstdint>
#include <limits>
#include "chrono.h"

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
		for (INT i=0; i<graph->nb_points; ++i)
			live_points[i] = new INT [graph->nb_points+1];
		this->color_satisfied = new INT [this->graph->nb_colors]();
		this->current_clique = new INT [this->graph->nb_colors]();
		this->color_frequency = new INT[this->graph->nb_colors]();
		this->nb_live_points_at_depth = new INT [graph->nb_colors]();
		
		//graph->print_adj_matrix();
		//graph->delete_verticies_with_degree(graph->nb_colors-1);
		
		cout<< "-------------------------------------------------------" <<endl;
		
		chrono C1;
		
		find_rainbow_cliques(0);
		
		cout << "Rainbow clique finding took " << C1.calculateDuration() << " milliseconds" << endl;
		
		cout << "===================================================================================" <<endl;
		cout<<"SOLUTIONS"<<endl;;
		cout << "===================================================================================" <<endl;
		for (INT i=0; i<solutions.size(); ++i) {
			cout<<"Solution "<<i<<": [" ;
			for (INT j=0; j<graph->nb_colors; ++j) {
				cout<<solutions[i][j];
				if (j+1 != graph->nb_colors) cout<<", ";
			}
			cout<<"]"<<endl;;
		}
		cout << "===================================================================================" <<endl;
		
	}
	if (size !=0) cout<< "passed graphs array" <<endl;
}

inline void Rainbow_Clique_Finding::create_color_freq_of_live_points(INT depth) {
	// any point in the graph that is dead will have a negative value in the
	// live_point array
	// reset color_frequency stats
	fill(this->color_frequency, this->color_frequency+graph->nb_colors, 0);
	
	for (INT i=0,p=1; i<live_points[depth][0]; ++i,++p) {
		INT point_color = graph->point_color[live_points[depth][p]];
		this->color_frequency[point_color] += 1;
	}
}

inline INT Rainbow_Clique_Finding::min_element_index(INT* array, INT size) {
	// returns index of the lowest value in t he array
	INT max = std::numeric_limits<INT>::max();
	INT min_element = max;
	INT return_value = -1;
	for (INT i=0; i<size; ++i) {
		if (array[i] < min_element && !color_satisfied[i]) {
			min_element = array[i];
			return_value = i;
		}
	}
	
		
	return return_value;
}

void Rainbow_Clique_Finding::find_rainbow_cliques(INT depth) {
	
	INT pt, pt1;
	if (depth == graph->nb_colors) {
		cout<<"Current Clique at depth "<<depth<<": ";
		print_1_D_array(current_clique,graph->nb_colors);
		vector<INT> solution;
		for (INT i=0; i<graph->nb_points; ++i) {
			solution.push_back(current_clique[i]);
		}
		solutions.push_back(solution);
		return;
	}
	//cout << "===================================================================================" <<endl;
	if (depth > 0) {
		pt1 = current_clique[depth-1];
		// find number of adjacent verticies to the vertex selected at
		// previous depth
		INT num_live_points_at_depth = 0;
		// i -> live points in prev depth
		// j -> i shifted right by 1
		// p ->
		for (INT i=0,j=1,p=1; i<live_points[depth-1][0]; ++i,++j) {
			if (graph->is_adjacenct(pt1,live_points[depth-1][j])) {
				live_points[depth][p++] = live_points[depth-1][j];
				num_live_points_at_depth++;
			}
		}
		live_points[depth][0] = num_live_points_at_depth;
		//cout<< "nb_live_points_at_depth_["<< depth <<"]: " << num_live_points_at_depth <<endl;
		//cout<<"points adj to "<< pt1 <<": ";
		//print_1_D_array(live_points[depth],live_points[depth][0]+1);
	}else{
		for (INT i=0,p=1; i<graph->nb_points;i++) {
			live_points[depth][p++] = i;
		}
		live_points[depth][0] = graph->nb_points;
		//cout<<"nb_live_points_at_depth_["<< depth <<"]: "<<live_points[depth][0]<<endl;
		//cout<<"live_points array: ";
		//print_1_D_array(live_points[depth], live_points[depth][0]+1);
	}
	
	
	
	create_color_freq_of_live_points(depth);
	
	
	
#if 0
	cout<< "color_satisfied table: ";
	print_1_D_array(color_satisfied, graph->nb_colors);
	cout<< "Color Frequency Table: ";
	print_1_D_array(color_frequency, graph->nb_colors);
#endif
	
	
	// find color value with the lowest frequency
	INT lowest_color = min_element_index(this->color_frequency,graph->nb_colors);
	//cout<< "Color with lowest frequency: " << lowest_color << " [This is the actual color]" <<endl;
	
	
	/*
	 [ 0, 1, 2, 3, 4, 5, 6 ]
	 [ 8, 1, 7, 9, 13, 15, 16 ]
	 */
	
	this->color_satisfied[lowest_color] = TRUE;
	// find how many points are there with the lowest value at current depth
	for (INT i=0,p=1; i<live_points[depth][0]; ++i,++p) {
		//cout<<"color("<<live_points[depth][p]<<"): "<<graph->point_color[live_points[depth][p]]<<endl;
		if (graph->point_color[live_points[depth][p]] == lowest_color) {
			if (!color_satisfied[lowest_color] && color_frequency[lowest_color]==0) {
				cout<<"FOUND AN UNSATISFIED COLOR WITH A FREQUENCY OF ZERO"<<endl;
				
			}
			//cout<< "Picking Vertex " << live_points[depth][p] <<endl;
			this->current_clique[depth] = live_points[depth][p];
			//cout<< "Calling find_rainbow_cliques("<<depth+1<<")"<<endl;
			
			find_rainbow_cliques(depth+1);
			
			
#if 0
			cout<< "["<<depth<<"]: " <<"Control returned from depth: " << depth+1 <<endl;
			cout<<"lowest color: "<<lowest_color<<endl;
			cout<< "color_satisfied table: ";
			print_1_D_array(color_satisfied, graph->nb_colors);
			cout<< "Color Frequency Table: ";
			print_1_D_array(color_frequency, graph->nb_colors);
			
			cout<<"current_clique: ";
			print_1_D_array(current_clique, graph->nb_colors);
#endif
		}
	}
	this->color_satisfied[lowest_color] = FALSE;
}

bool Rainbow_Clique_Finding::all_color_satisfied(){
	for (INT i=0; i<graph->nb_colors; ++i)
		if (!color_satisfied[i]) return false;
	return true;
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
	
	/*---------------------------------------------------------------------------------------------*/
	// Actual k-clique finding algorithm
	/*---------------------------------------------------------------------------------------------*/
	
	/*---------------------------------------------------------------------------------------------*/
	
	
	
	cout<<"Done Rainbow_Clique_Finding::find_cliques_of_size_"<<k<<endl;
}
