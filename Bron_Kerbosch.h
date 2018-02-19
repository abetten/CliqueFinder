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

class Bron_Kerbosch {
public:
	Bron_Kerbosch(GRAPH& graph);
	Bron_Kerbosch(GRAPH* graph_array, INT size=0);
	~Bron_Kerbosch();
private:
	GRAPH* graph = NULL;
	INT graph_array_size = 0;
};

#endif /* BRON_KERBOSCH_H */

