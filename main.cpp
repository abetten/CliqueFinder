#include <iostream>
#include <string.h>
#include <fstream>
#include "chrono.h"

#include "typedefs.h"
#include "misc_functions.h"

#include "graph.h"
#include "graph_algorithms.h"

using namespace std;


int main(int argc, char** argv) {

	INT verbose_level = 0;
	INT f_list_of_cases = FALSE;
	const BYTE *fname_list_of_cases = NULL;
	const BYTE *fname_template = NULL; // input filename template for the graphs that are on disk
	INT f_output_file = FALSE;
	const BYTE *output_file = NULL;

	/*--------------------------------------------------------------------------------------------------*/
	// Parse Input arguments
	/*--------------------------------------------------------------------------------------------------*/
	for (INT i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-v") == 0) {
			verbose_level = atoi(argv[++i]);
			cout << "-v " << verbose_level << endl;
		} else if (strcmp(argv[i], "-list_of_cases") == 0) {
			f_list_of_cases = TRUE;
			fname_list_of_cases = argv[++i];
			fname_template = argv[++i];
			cout << "-list_of_cases " << fname_list_of_cases << " " << fname_template << endl;
		} else if (strcmp(argv[i], "-output_file") == 0) {
			f_output_file = TRUE;
			output_file = argv[++i];
			cout << "-output_file " << output_file << endl;
		}
	}
	/*--------------------------------------------------------------------------------------------------*/
	
	INT* graph_sets;
	INT graph_set_cardinality; // number of elements in the graph set, i.e. nb_cases
	BYTE solution_file[1000];
	BYTE stats_file[1000];
	
	if (f_output_file) {
		sprintf(solution_file, "%s", output_file); // solution_file = output_file
		sprintf(stats_file, "%s", output_file); // stats_file = output_file
		// replace extension
		_replace(stats_file, '.', "_stats.csv");
	}else{
		sprintf(solution_file, "solutions_%s", fname_list_of_cases);
		sprintf(stats_file, "statistics_%s", fname_list_of_cases);
		// replace extension
		_replace(stats_file, '.', ".csv");
	}
	
	
	// Read number of cases and allocate memory
	ifstream f(fname_list_of_cases);
	f >> graph_set_cardinality;
	graph_sets = new INT[graph_set_cardinality];

	// Populate graph_sets
	for (INT i=0; i<graph_set_cardinality;) {
		INT a = -1;
		while (f >> a) {
			if (a >= 0) graph_sets[i++] = a;
		}
	}
	
	
	
	/*---------------------------------------------------------------------------------------------------*/
	for (INT i=0; i<graph_set_cardinality; ++i) {
		GRAPH G(graph_sets[i],fname_template);
		graph_algorithms g_algo(G,graph_algorithms::Rainbow_Clique_Finding);
		g_algo.start_execution();
	}
	/*---------------------------------------------------------------------------------------------------*/
    
    
	
	
	f.close();
	delete [] graph_sets;
}











