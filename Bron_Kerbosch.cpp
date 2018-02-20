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

Bron_Kerbosch::Bron_Kerbosch(GRAPH& graph) {
	this->graph = &graph;
	Bron_Kerbosch(this->graph, 0);
}

Bron_Kerbosch::Bron_Kerbosch(GRAPH* graph_array, INT size) {
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
	find_max_clique_without_pivoting(R, P, X);
	cout<<R.size()<<endl;
	print_vector(R);
}

void Bron_Kerbosch::find_max_clique_without_pivoting(vector<INT>& R, vector<INT>& P, vector<INT>& X) {
	cout<< "Entered Bron_Kerbosch::find_max_clique_without_pivoting" <<endl;
	if (P.size() == 0 && X.size() == 0) {
		cout<<"Clique["<<R.size()<<"]: ";
		print_vector(R);
		return;
	}
	INT lim=P.size();
	for (INT i=0; i<lim; ++i) {
		if (i>P.size()-1) {
			cout<<"i>P.size()-1"<<endl;
			exit (-1);
		}
		print_vector(P);
		INT v = P[i];
		cout<<"\tv: "<<v<<endl;
		vector<INT> N = find_neighbor_(v);
		cout<<"\t";
		print_vector(N);
		vector<INT> P_intersect_N = set_intersection_(P,N);
		print_vector(P_intersect_N);
		vector<INT> X_intersect_N = set_intersection_(X,N);
		print_vector(X_intersect_N);
		set_union_(R,v);
		print_vector(R);
		find_max_clique_without_pivoting(R,P_intersect_N,X_intersect_N);
		delete_element(P, v);
		lim = P.size();
		set_union_(X,v);
	}
}

vector<INT> Bron_Kerbosch::find_neighbor_(INT v) {
	cout<< "Starting Bron_Kerbosch::find_neighbor_("<<v<<")" <<endl;
	vector<INT> N;
	for (UINT i = 0; i < graph->nb_points; ++i) {
		if (graph->adj_matrix[v][i] == 1) N.push_back(i);
	}
	cout<< "Done Bron_Kerbosch::find_neighbor_" <<endl;
	return N;
}

vector<INT> Bron_Kerbosch::set_intersection_(const vector<INT>& P, const vector<INT>& Q) {
	cout<< "Starting Bron_Kerbosch::set_intersection_" <<endl;
	vector<INT> result;
	for (UINT i = 0; i < Q.size(); ++i) {
		for (UINT j = 0; j < P.size(); ++j) {
			if (P[j] == Q[i]) {
				result.push_back(P[j]);
			}
		}
	}
	cout<< "Done Bron_Kerbosch::set_intersection_" <<endl;
	return result;
}

void Bron_Kerbosch::set_union_(vector<INT>& P, INT v) {
	cout<< "Starting Bron_Kerbosch::set_union_" <<endl;
	bool v_exists = false;
	for (UINT i=0; i<P.size(); ++i)
		if (P[i] == v) v_exists = true;
	if (!v_exists) P.push_back(v);
	cout<< "Done Bron_Kerbosch::set_union_" <<endl;
}

void Bron_Kerbosch::delete_element(vector<INT>& P, INT key) {
	cout<< "Starting Bron_Kerbosch::delete_element" <<endl;
	for (UINT i=0; i<P.size(); ++i) {
		if (P[i] == key) P.erase(P.begin()+i);
	}
	cout<< "Done Bron_Kerbosch::delete_element" <<endl;
}

Bron_Kerbosch::~Bron_Kerbosch() {
	cout<< "Bron_Kerbosch::~Bron_Kerbosch" <<endl;
}

