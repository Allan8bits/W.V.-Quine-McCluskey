//include/logic_minimizer.h
#include "term.h"
#ifndef LOGIC_MINIMIZER_H
#define LOGIC_MINIMIZER_H

// Function prototypes
static bool can_combine(Term a, Term b);
static Term combine_terms(Term a, Term b);
void remove_duplicates(Term *terms, int *num_terms);
void generate_min_circuit(int v[], int size);
//static bool is_covered(Term term, int minterm);

#endif