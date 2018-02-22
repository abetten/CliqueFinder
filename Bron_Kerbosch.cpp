/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bron_Kerbosch.cpp
 * Author: sajeeb
 * 
 * Created on February 18, 2018, 10:29 PM
 */

#include "Bron_Kerbosch.h"
#include "chrono.h"

Bron_Kerbosch::Bron_Kerbosch(GRAPH& graph) {
	this->graph = &graph;
	Bron_Kerbosch(this->graph, 0);
}

Bron_Kerbosch::Bron_Kerbosch(GRAPH* graph_array, INT size) {
	chrono C1;
	
	this->graph = graph_array;
	this->graph_array_size = size;
	if (size != 0) cout << "passed graphs array" << endl;
	if (size == 0) {
		cout << "passed graphs pointer" << endl;

	}
	// set vector<INT> P to be the vertex set of the graph
	cout<<graph->nb_points<<endl;
	P.reserve(graph->nb_points);
	for (INT i = 0; i < graph->nb_points; ++i) P.push_back(i);
	
	
	C1.reset();
	// delete vertices with less than graph->nb_color-1 adj. verticies
	graph->delete_verticies_with_degree(graph->nb_colors-1);
	cout<<"graph->delete_verticies_with_degree(graph->nb_colors-1): "<<
		C1.calculateDuration()<<" milliseconds"<<endl;
	
	C1.reset();
	find_max_clique_without_pivoting(R, P, X);
	cout<<"find_max_clique_without_pivoting(R, P, X): "<<
		C1.calculateDuration()<<" milliseconds"<<endl;
	
	
	
	for (INT i=0; i<cliques.size(); ++i) print_vector(cliques[i]);
}

void Bron_Kerbosch::find_max_clique_without_pivoting(vector<INT> R, vector<INT>& P, vector<INT> X) {
	if (P.size() == 0 && X.size() == 0) {
		if (R.size() == graph->nb_colors) cliques.push_back(R);
		return;
	}
	for (INT v : P) {
		vector<INT> N = find_neighbor_(v),
			    P_i_N = set_intersection_(P,N),
			    X_i_N = set_intersection_(X,N);
		find_max_clique_without_pivoting(set_union_(R,v),P_i_N,X_i_N);
		delete_element(P,v);
		X.push_back(v);
	}
}

vector<INT> Bron_Kerbosch::find_neighbor_(INT v) {
	vector<INT> N;
	for (UINT i = 0; i < graph->nb_points; ++i) {
		if (graph->is_adjacenct(v,i)) N.push_back(i);
	}
	return N;
}

vector<INT> Bron_Kerbosch::set_intersection_(const vector<INT>& P, const vector<INT>& Q) {
	vector<INT> result;
	for (UINT i = 0; i < Q.size(); ++i) {
		for (UINT j = 0; j < P.size(); ++j) {
			if (P[j] == Q[i]) {
				result.push_back(P[j]);
			}
		}
	}
	return result;
}

vector<INT> Bron_Kerbosch::set_union_(vector<INT>& P, INT v) {
	bool v_exists = false;
	vector<INT> result = P;
	for (UINT i=0; i<P.size(); ++i)
		if (P[i] == v) v_exists = true;
	if (!v_exists) result.push_back(v);
	return result;
}

void Bron_Kerbosch::delete_element(vector<INT>& P, INT key) {
	for (UINT i=0; i<P.size(); ++i) {
		if (P[i] == key) P.erase(P.begin()+i);
	}
}

Bron_Kerbosch::~Bron_Kerbosch() {
}

