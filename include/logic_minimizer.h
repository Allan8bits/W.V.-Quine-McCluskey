//include/logic_minimizer.h
#include "term.h"
#ifndef LOGIC_MINIMIZER_H
#define LOGIC_MINIMIZER_H

// Function prototypes
static bool can_combine(Term a, Term b);
static Term combine_terms(Term a, Term b);
static bool is_covered(Term term, int minterm);
void generate_min_circuit(int v[], int size);

#endif