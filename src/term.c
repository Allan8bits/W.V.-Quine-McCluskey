//src/term.c
#include "term.h"
#include <stdio.h>
#include <string.h>

void remove_duplicates(Term *terms, int *num_terms) {
    int k = 0;  // Novo contador para o número de termos após remover duplicatas
    for (int i = 0; i < *num_terms; i++) {
        bool is_duplicate = false;
        for (int j = 0; j < k; j++) {
            if (terms[i].num == terms[j].num && terms[i].mask == terms[j].mask) {
                is_duplicate = true;
                break;
            }
        }
        if (!is_duplicate) {
            terms[k++] = terms[i];  // Adiciona este termo ao array se não for duplicado
        }
    }
    *num_terms = k;  // Atualiza o contador de termos para refletir o número de termos únicos
}