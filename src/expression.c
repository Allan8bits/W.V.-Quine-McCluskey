// expression.c
#include "expression.h"
#include <stdio.h>

// Function to print the simplified expression
void print_binary(Term term)
{
    for (int i = 7; i >= 0; i--)
    {
        if ((term.mask >> i) & 1)
        {
            printf("X"); // Usa 'X' para indicar um bit mascarado
        }
        else
        {
            printf("%d", (term.num >> i) & 1); // Imprime o bit correspondente
        }
        if (i % 4 == 0)
            printf(" "); // Facilita a leitura, agrupando os bits
    }
}

// Função para imprimir a representação binária como expressão lógica
void print_expression(int num, int mask)
{
    for (int i = 7; i >= 0; i--)
    {
        char var = 'A' + (7 - i);
        if (mask & (1 << i))
        {
            continue;
        }

        printf("%c%c", var, (num & (1 << i)) ? ' ' : '\'');
    }
    printf(" + ");
}