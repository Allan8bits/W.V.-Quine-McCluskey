#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "term.h"        // Assegure que o arquivo de cabeçalho contém as definições corretas
#include "expression.h"  // Assegure que o arquivo de cabeçalho contém as funções de impressão corretas

// Função para combinar dois termos se eles diferirem por exatamente um bit, considerando máscaras
Term combine_terms(Term a, Term b) {
    Term result;
    result.num = a.num & b.num;
    result.mask = (a.num ^ b.num) | a.mask | b.mask;
    result.used = false;
    return result;
}

// Verifica se dois termos podem ser combinados
bool can_combine(Term a, Term b) {
    unsigned int diff = (a.num ^ b.num);
    unsigned int relevant_diff = diff | a.mask | b.mask;  // Considera bits originalmente mascarados como diferentes

    return relevant_diff != 0 && (relevant_diff & (relevant_diff - 1)) == 0;
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
        fill_binary_representation(&terms[i]);
    }

    for (int i = 0; i < num_terms; i++) {
        printf("Termo %d: ", i+1);
        print_binary(terms[i]);
        printf("\n");
    }

    bool progress;
    do {
        progress = false;
        for (int i = 0; i < num_terms - 1; i++) {
            for (int j = i + 1; j < num_terms; j++) {
                if (!terms[i].used && !terms[j].used && can_combine(terms[i], terms[j])) {
                    Term newTerm = combine_terms(terms[i], terms[j]);
                    terms[i] = newTerm; // Substitui o termo i pelo novo termo combinado
                    terms[j].used = true; // Marca o termo j como usado
                    progress = true;
                }
            }
        }
        // Remove termos usados
        int offset = 0;
        for (int i = 0; i < num_terms; i++) {
            if (!terms[i].used) {
                terms[offset++] = terms[i];
            }
        }
        num_terms = offset;
    } while (progress);

    // Remover duplicatas
    remove_duplicates(terms, &num_terms);

    printf("\n");
    // Imprimir termos resultantes
    for (int i = 0; i < num_terms; i++) {
        printf("Termo Final: ");
        print_binary(terms[i]);
        printf("\n");
    }
    free(terms); // Liberar memória alocada
}