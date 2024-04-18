#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "term.h"
#include "expression.h"

// Função para combinar dois termos se eles diferirem por exatamente um bit, considerando máscaras
Term combine_terms(Term a, Term b) {
    Term result;
    unsigned int combined_mask = a.mask | b.mask; // Máscaras combinadas
    unsigned int diff_bit = (a.num ^ b.num) & ~(a.mask | b.mask); // Diferença apenas em bits não mascarados

    result.num = (a.num & b.num) & ~diff_bit; // Mantém bits iguais que não são a diferença
    result.mask = combined_mask | diff_bit; // Atualiza a máscara com a diferença detectada
    result.used = false;
    return result;
}

// Verifica se dois termos podem ser combinados, considerando máscaras
bool can_combine(Term a, Term b) {
    // Obtenha todos os bits que diferem
    unsigned int diff = (a.num ^ b.num) | (a.mask ^ b.mask);

    // Certifique-se de que há exatamente um bit de diferença
    return diff != 0 && (diff & (diff - 1)) == 0;
}

// Função para gerar o circuito minimizado
void generate_min_circuit(int v[], int size) {
    Term *groups[size + 1];  // Armazenamento permanente
    Term *new_groups[size + 1];  // Armazenamento temporário
    Term * prime_implicants;
     int  prime_implicants_size = 0;
    int group_sizes[size + 1];
    memset(group_sizes, 0, sizeof(group_sizes));
    int new_group_sizes[size + 1];
    memset(new_group_sizes, 0, sizeof(new_group_sizes));
     prime_implicants = malloc(size * sizeof(Term));
    memset(new_group_sizes, 0, sizeof(new_group_sizes));

    // Inicializar os grupos e alocar memória
    for (int i = 0; i <= size; i++) {
        groups[i] = malloc(size * sizeof(Term));
        new_groups[i] = malloc(size * sizeof(Term));
    }

    // Agrupar termos conforme o número de '1's
    for (int i = 0; i < size; i++) {
        int bitCount = __builtin_popcount(v[i]);
        groups[bitCount][group_sizes[bitCount]++] = (Term){v[i], 0, false};
    }

    bool progress;
    do {
        progress = false;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < group_sizes[i]; j++) {
                bool combined = false;
                for (int k = 0; k < group_sizes[i + 1]; k++) {
                    if (can_combine(groups[i][j], groups[i + 1][k])) {
                        Term new_term = combine_terms(groups[i][j], groups[i + 1][k]);
                        groups[i][j].used = true;
                        groups[i+1][k].used = true;
                        new_groups[i][new_group_sizes[i]++] = new_term;
                        progress = true;
                        // Imprime os termos antes e depois da combinação
                        printf("\nCombining: ");
                        print_binary(groups[i][j]);
                        print_binary(groups[i + 1][k]);
                        printf("\nResult:    ");
                        print_binary(new_term);
                    }
                }              
                if (!groups[i][j].used) {
                     prime_implicants[ prime_implicants_size++] = groups[i][j];
                }
                printf("\n");
            }
        }
        // Atualizar os grupos com novos termos e preparar para a próxima iteração
        for (int i = 0; i <= size; i++) {
            memcpy(groups[i], new_groups[i], new_group_sizes[i] * sizeof(Term));
            group_sizes[i] = new_group_sizes[i];
            new_group_sizes[i] = 0;  // Resetar tamanhos de novos grupos para a próxima iteração
        }
    } while (progress);

    remove_duplicates(prime_implicants, & prime_implicants_size);

    // Imprime os termos finais
    printf("\n----------FINAL TERMS----------\n");
    for (int i = 0; i <  prime_implicants_size; i++) {
        printf("\nPrime Implicants: ");
        print_binary( prime_implicants[i]);
    }
    printf("\n\ny = ");    
    for (int i = 0; i <  prime_implicants_size; i++) {
        print_expression(prime_implicants[i].num, prime_implicants[i].mask);
    }

    // Limpeza e impressão dos resultados
    for (int i = 0; i <= size; i++) {
        free(groups[i]);
        free(new_groups[i]);
    }
}