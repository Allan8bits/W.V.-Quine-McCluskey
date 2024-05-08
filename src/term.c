// src/term.c
#include "term.h"
#include <stdio.h>
#include <string.h>

/**
 * Remove termos duplicados.
 * 
 * Parâmetros:
 *   terms: Term* - Ponteiro para o array de termos.
 *   num_terms: int* - Ponteiro para o número de termos no array.
 *
 * Retorna:
 *   void - Não há valor de retorno.
 *
 * Processo:
 *   1. **Inicialização do Índice de Armazenamento:**
 *      - A função inicia uma variável `k` para armazenar a posição do próximo termo único no array.
 *   2. **Loop de Verificação de Duplicatas:**
 *      - Itera sobre todos os termos do array usando a variável `i`.
 *      - Para cada termo, verifica-se a existência de duplicatas comparando com todos os termos já identificados como únicos 
 *        (usando o índice `j` que vai de 0 a `k`).
 *   3. **Condição de Unicidade:**
 *      - Se um termo é único (não encontrado nos índices de 0 a `k`), ele é movido para a posição `k` do array. O índice `k` é então 
 *        incrementado.
 *   4. **Atualização do Contador de Termos:**
 *      - Após a conclusão do loop, o valor apontado por `num_terms` é atualizado para `k`, que representa o novo número de termos únicos.
 *
 * Exceções:
 *   Não aplicável.
 */
void remove_duplicates(Term *terms, int *num_terms)
{
    int k = 0;
    for (int i = 0; i < *num_terms; i++)
    {
        bool is_duplicate = false;
        for (int j = 0; j < k; j++)
        {
            if (terms[i].num == terms[j].num && terms[i].mask == terms[j].mask)
            {
                is_duplicate = true;
                break;
            }
        }
        if (!is_duplicate)
        {
            terms[k++] = terms[i];
        }
    }
    *num_terms = k;
}