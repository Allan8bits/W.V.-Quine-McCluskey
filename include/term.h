#include <stdbool.h>
#ifndef TERM_H
#define TERM_H

typedef struct {
    unsigned int num; // Valor do termo
    unsigned int mask; // Máscara de bits de "don't care"
    int countOne; // Contagem de bits '1'
    bool used; // Indica se o termo foi usado
} Term;

extern int MAX_VARIABLES;

void fillBinaryRepresentation(Term *nb);
void print_expression(int num, int mask);

#endif // TERM_H
