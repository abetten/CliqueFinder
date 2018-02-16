#include <iostream>
#include <string.h>
#include <fstream>
#include "chrono.h"

using namespace std;

/*------------------------------------------------------------------------------------------------------------*/
/// Header Section
/*------------------------------------------------------------------------------------------------------------*/

typedef long int INT;
typedef unsigned long UINT;
typedef char BYTE;
typedef unsigned char UBYTE;
typedef int INT4;

#define FALSE 0
#define TRUE 1

long int bitvector_s_i(unsigned char *bitvec, long int i);
long int ij2k(long int i, long int j, long int n);

inline INT bitvector_s_i(unsigned char *bitvec, long int i) {
	// returns 0 or 1
	
	long int ii, bit;
	unsigned char mask;
	
	ii = i >> 3;
	bit = i & 7;
	mask = ((unsigned char) 1) << bit;
	unsigned char &x = bitvec[ii];
	if (x & mask) {
		return 1;
	} else {
		return 0;
	}
}

inline INT ij2k(long int i, long int j, long int n) {
	if (i == j) {
		cout << "ij2k() i == j" << endl;
		exit(1);
	}
	if (i > j) {
		return ij2k(j, i, n);
	} else {
		return ( (n - i) * i + ((i * (i - 1)) >> 1) + j - i - 1 );
	}
}

inline bool** delinearize_adj_matrix(UBYTE* bitvector_adjacency, INT nb_points) {
	// turn the linearized adjaency matrix back into a nxn matrix
	bool** adj_matrix = new bool* [nb_points]; // allocate memory for matrix rows
	for (INT i=0; i<nb_points; ++i) adj_matrix[i] = new bool [nb_points]; // allocate memory for cols
	for (INT i=0; i<nb_points; ++i) {	// row
		adj_matrix[i][i]=0; // set all the elements along the diagonal equal to zero
		for (INT j=i+1; j<nb_points; ++j) {	//column
			INT k = ij2k(i, j, nb_points);
			INT aij = bitvector_s_i(bitvector_adjacency, k);
			adj_matrix[i][j] = adj_matrix[j][i] = aij;
		}
	}
	return adj_matrix;
}

inline void print_matrix(bool** matrix, INT matrix_order) {
	for (INT i=0; i<matrix_order; ++i) {
		for (INT j=0; j<matrix_order; ++j) {
			cout<< matrix[i][j] << "  ";
		}
		cout<<endl;
	}
}

/*------------------------------------------------------------------------------------------------------------*/

int main(int argc, char** argv) {

	INT verbose_level = 0;
	INT f_list_of_cases = FALSE;
	const BYTE *fname_list_of_cases = NULL;
	const BYTE *fname_template = NULL; // input filename template for the graphs that are on disk
	INT f_output_file = FALSE;
	const BYTE *output_file = NULL;

	// Parse Input arguments
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
	
	
	INT* graph_sets;
	INT graph_set_cardinality; // number of elements in the graph set, i.e. nb_cases
	BYTE solution_file[1000];
	BYTE stats_file[1000];
	
	if (f_output_file) {
		sprintf(solution_file, "%s", output_file); // solution_file = output_file
		sprintf(stats_file, "%s", output_file); // stats_file = output_file
		// replace extension
		char* pch = strrchr(stats_file,'.'); // pointer to last occurrence of '.'
		stats_file[pch-stats_file] = '\0' ;  // add null terminator in place of the '.'
		strcat(stats_file, "_stats.csv");    // concatinate string to the end
	}else{
		sprintf(solution_file, "solutions_%s", fname_list_of_cases);
		sprintf(stats_file, "statistics_%s", fname_list_of_cases);
		// replace extension
		char* pch = strrchr(stats_file,'.'); // pointer to last occurrence of '.'
		stats_file[pch-stats_file] = '\0' ;  // add null terminator in place of the '.'
		strcat(stats_file, ".csv");    // concatinate string to the end
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
		INT graph_id = graph_sets[i]; // get the ith element from the set of graphs
		BYTE fname[1000]; // input file name for where the graph is stored on disk
		BYTE fname_base[1000]; // base filename for the graph, i.e. filename without the file extension
		FILE* fp;
		
		/*-------------------------------------------------------------------------------------------*/
		// To be filled with data from graphs binary file					   (1)
		/*-------------------------------------------------------------------------------------------*/
		INT nb_points; // number of points in the graph
		INT nb_colors; // number of colors in the graph
		INT L;
		INT bitvector_length; // length of the bit-vector
		INT user_data_size;
		INT* user_data;
		INT* points; // array of points in the graph
		INT* point_color; // the color of the respective point
		UBYTE* bitvector_adjacency; // liearized adjacency matrix
		/*-------------------------------------------------------------------------------------------*/
		
		sprintf(fname, fname_template, graph_id); // replace %ld in fname_template with graph_id
							  // and assign the result to fname
		
		strcpy(fname_base, fname); // fname = fname_base
		// remove extension form fname_base to get base filename
		char* pch = strrchr(fname_base,'.'); // pointer to last occurrence of '.'
		fname_base[pch-fname_base] = '\0' ;  // add null terminator in place of the '.'
		
		fp = fopen(fname, "rb"); // open the graphs binary file
		
		/*--------------------------------------------------------------------------------------------*/
		// Populate Variables from (1)
		/*--------------------------------------------------------------------------------------------*/
		fread(&nb_points, 1, 4, fp); // read the number of points in the graph
		fread(&nb_colors, 1, 4, fp); // read the number of colors in the graph
		
		fread(&user_data_size, 1, 4, fp);
		user_data = new INT[user_data_size];
		for (INT i=0; i<user_data_size; ++i) fread(&user_data[i], 1, 4, fp);
		
		points = new INT[nb_points]; // allocate memory for each point in the graph
		point_color = new INT[nb_points]; // allocate memory for the color of each point in the graph
		for (INT i=0; i<nb_points; ++i) {
			fread(&points[i], 1, 4, fp);
			fread(&point_color[i], 1, 4, fp);
			if (point_color[i] >= nb_colors) {
				cout << "point_color[i] >= nb_colors" << endl;
				cout << "point_color[i]=" << point_color[i] << endl;
				cout << "i=" << i << endl;
				cout << "nb_colors=" << nb_colors << endl;
				exit(-1);
			}
		}
		
		L = (nb_points * (nb_points - 1)) >> 1; //number of entries in the linearized adj. matrix
		bitvector_length = (L + 7) >> 3; // number of chars used to store the linearized adj. matrix
		bitvector_adjacency = new UBYTE [bitvector_length];
		fread(bitvector_adjacency, 1, bitvector_length, fp);
		/*--------------------------------------------------------------------------------------------*/
		
		
		
		/*--------------------------------------------------------------------------------------------*/
		// Get Adj. Matrix
		/*--------------------------------------------------------------------------------------------*/
		bool** adj_matrix = delinearize_adj_matrix(bitvector_adjacency, nb_points);
		//print_matrix(adj_matrix, nb_points);
		/*--------------------------------------------------------------------------------------------*/
		
		
		
		/*--------------------------------------------------------------------------------------------*/
		//
		/*--------------------------------------------------------------------------------------------*/
		
		/*--------------------------------------------------------------------------------------------*/
		
		
		/*--------------------------------------------------------------------------------------------*/
		// Delete Dynamically allocated Memory
		/*--------------------------------------------------------------------------------------------*/
		delete [] points;
		delete [] point_color;
		delete [] user_data;
		for (INT i=0; i<nb_points; ++i) delete [] adj_matrix[i];
		delete [] adj_matrix;
		delete [] bitvector_adjacency;
		/*--------------------------------------------------------------------------------------------*/
	}
	/*---------------------------------------------------------------------------------------------------*/
    
    
	
	
	f.close();
	delete [] graph_sets;
}











