#include <stdbool.h>
#ifndef TERM_H
#define TERM_H

typedef struct
{
    unsigned int num;  // Valor do termo
    unsigned int mask; // Máscara de bits de "don't care"
    bool used;         // Indica se o termo foi usado
} Term;

void remove_duplicates(Term *terms, int *num_terms);

#endif // TERM_H
