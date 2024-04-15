//src/term.c
#include "term.h"
#include <stdio.h>
#include <string.h>

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