#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "term.h"
#include "expression.h"

// Função para combinar dois termos se eles diferirem por exatamente um bit, considerando máscaras
Term combine_terms(Term a, Term b) {
    Term result;
    result.num = a.num & b.num;  // Mantém o número onde ambos os bits são 1
    result.mask = (a.num ^ b.num) | a.mask | b.mask;  // Marca diferenças e todas as máscaras existentes
    result.used = false;
    return result;
}

// Verifica se dois termos podem ser combinados, considerando máscaras
bool can_combine(Term a, Term b) {
    unsigned int diff = (a.num ^ b.num) & ~(a.mask | b.mask); // Diferenças onde não há máscaras
    unsigned int mask_diff = (a.mask ^ b.mask) & ~(a.num ^ b.num); // Diferenças nas máscaras que não estão no número

    return (diff | mask_diff) != 0 && ((diff | mask_diff) & ((diff | mask_diff) - 1)) == 0;
}

// Função para gerar o circuito minimizado
void generate_min_circuit(int v[], int size) {
    Term terms[size];
    int num_terms = size;

    // Inicializa os termos
    for (int i = 0; i < size; i++) {
        terms[i].num = v[i];
        terms[i].mask = 0;
        terms[i].used = false;
    }

    for (int i = 0; i < num_terms; i++) {
        printf("Termo %d: ", i+1);
        print_binary(terms[i]);
        printf("\n");
    }

    Term *groups[size + 1];
    int group_sizes[size + 1];
    memset(group_sizes, 0, sizeof(group_sizes));  // Inicializa todos os elementos a zero

    // Alocar memória para os grupos
    for (int i = 0; i <= size; i++) {
        groups[i] = malloc(num_terms * sizeof(Term));
    }

    // Preencher os grupos
    for (int i = 0; i < num_terms; i++) {
        int bit_count = count_bits(terms[i].num);
        groups[bit_count][group_sizes[bit_count]++] = terms[i];
    }

    // Combinar grupos
    bool progress;
    do {
        progress = false;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < group_sizes[i]; j++) {
                for (int k = 0; k < group_sizes[i + 1]; k++) {
                    if (!groups[i][j].used && !groups[i + 1][k].used && can_combine(groups[i][j], groups[i + 1][k])) {
                        Term newTerm = combine_terms(groups[i][j], groups[i + 1][k]);
                        groups[i][j] = newTerm;
                        groups[i + 1][k].used = true;
                        progress = true;
                    }
                }
            }
        }
    } while (progress);

    // Imprimir termos resultantes e liberar memória
    for (int i = 0; i <= size; i++) {
        for (int j = 0; j < group_sizes[i]; j++) {
            if (!groups[i][j].used) {
                printf("\nFinal Terms: ");
                print_binary(groups[i][j]);
            }
        }
        free(groups[i]);
    }
}