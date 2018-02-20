/*
 * File:   chrono.h
 * Author: Sajeeb
 *
 * Created on Febryary 11, 2018, 6:36 PM
 */


#ifndef MISC_FUNCTIONS_H
#define MISC_FUNCTIONS_H

#include "typedefs.h"

inline void _replace(BYTE* string, BYTE character, const BYTE* replacement=NULL);

inline INT bitvector_s_i(UBYTE *bitvec, INT i);
inline INT ij2k(INT i, INT j, INT n);

inline bool** delinearize_adj_matrix(UBYTE* bitvector_adjacency, INT nb_points);

template <typename array_type>
inline void print_1_D_array(array_type* array,INT size);

#endif
