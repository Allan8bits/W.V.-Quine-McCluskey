// expression.c
#include "expression.h"
#include <stdio.h>

// Function to print the simplified expression
void print_binary(unsigned int num) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i % 4 == 0) printf(" "); // Facilita a leitura, agrupando os bits
    }
}
