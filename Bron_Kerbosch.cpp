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
	Bron_Kerbosch(this->graph,0);
}

Bron_Kerbosch::Bron_Kerbosch(GRAPH* graph_array, INT size) {
	this->graph = graph_array;
	this->graph_array_size = size;
	if (size != 0) cout<< "passed graphs array" <<endl;
	if (size == 0) {
		cout<< "passed graphs pointer" <<endl;
		
	}
}

Bron_Kerbosch::~Bron_Kerbosch() {
}

