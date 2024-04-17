// expression.c
#include "expression.h"
#include <stdio.h>


// Função para preencher a representação binária e contar os '1's
void fill_binary_representation(Term *term) {
    term->count_one = 0;
    for (int i = 0; i < 8; i++) {
        if ((term->num >> i) & 1) {
            term->count_one++;
        }
    }
}

// Function to print the simplified expression
void print_binary(unsigned int num) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i % 4 == 0) printf(" "); // Facilita a leitura, agrupando os bits
    }
}

// Função para imprimir a representação binária como expressão lógica
void print_expression(int num, int mask) {
    for (int i = 7; i >= 0; i--) {
        char var = 'H' - (7 - i);
        if (mask & (1 << i)) {
            printf("-");
        } else {
            printf("%c", (num & (1 << i)) ? var : ('~' + var));
        }
    }
    printf("\n");
}