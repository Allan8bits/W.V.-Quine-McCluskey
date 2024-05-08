#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "term.h"
#include "expression.h"

/**
 * Verifica se dois termos podem ser combinados, considerando máscaras.
 *
 * Parâmetros:
 *   a: Term - Primeiro termo para verificação.
 *   b: Term - Segundo termo para verificação.
 *
 * Retorna:
 *   bool - True se os termos podem ser combinados, False caso contrário.
 *
 * Processo:
 *   1. **Cálculo da diferença:**
 *      - A operação XOR bit a bit é aplicada aos números (`a.num ^ b.num`) e às máscaras (`a.mask ^ b.mask`) dos termos separadamente.
 *      - Os resultados do XOR são combinados usando a operação OR bit a bit para obter um valor que representa todos os bits que diferem entre os
 *        dois termos, considerando tanto os números quanto as máscaras.
 *   2. **Verificação de um único bit de diferença:**
 *      - Um truque bit a bit é usado para verificar se há exatamente um bit '1' no valor da diferença:
 *      - Se o valor da diferença for diferente de zero e o resultado do AND bit a bit entre o valor e o seu antecessor (`diff & (diff - 1)`) for
 *        zero, isso significa que há apenas um bit '1'.
 *
 * Exceções:
 *   Não aplicável.
 */
bool can_combine(Term a, Term b)
{
    unsigned int diff = (a.num ^ b.num) | (a.mask ^ b.mask);
    return diff != 0 && (diff & (diff - 1)) == 0;
}

/**
 * Combina dois termos se eles diferirem por exatamente um bit, considerando suas máscaras.
 *
 * Parâmetros:
 *   a: Term - Primeiro termo para combinação.
 *   b: Term - Segundo termo para combinação.
 *
 * Retorna:
 *   Term - Novo termo resultante da combinação dos dois termos de entrada.
 *
 * Processo:
 *   1. **Combinação de máscaras:**
 *      - A máscara do novo termo é criada combinando as máscaras dos termos de entrada usando a operação OR bit a bit (`a.mask | b.mask`).
 *      - Isso garante que qualquer bit 'X' (don't care) em qualquer um dos termos de entrada também seja 'X' no novo termo.
 *   2. **Identificação do bit de diferença:**
 *      - A operação XOR bit a bit (`a.num ^ b.num`) é aplicada aos números dos termos de entrada para identificar os bits que diferem.
 *      - Em seguida, o resultado do XOR é mascarado com o complemento da máscara combinada (`~(a.mask | b.mask)`) para manter apenas os bits de
 *        diferença que não são mascarados (ou seja, bits que são '0' ou '1' em ambos os termos).
 *      - Se os termos podem ser combinados, o resultado desta operação terá apenas um bit '1', que representa o único bit de diferença.
 *   3. **Criação do novo número:**
 *      - A operação AND bit a bit (`a.num & b.num`) é aplicada aos números dos termos de entrada para manter apenas os bits que são iguais em
 *        ambos os termos.
 *      - O resultado do AND é então mascarado com o complemento do bit de diferença (`~diff_bit`) para zerar o bit que difere entre os termos.
 *        Isso cria um novo número onde o bit de diferença é substituído por 'X' (don't care).
 *   4. **Configuração do novo termo:**
 *      - O novo termo (`result`) é criado com o número calculado na etapa 3 e a máscara calculada na etapa 1.
 *      - O atributo `used` do novo termo é definido como `false`, indicando que ele ainda não foi usado em combinações posteriores.
 *
 * Exceções:
 *   Não aplicável.
 */
Term combine_terms(Term a, Term b)
{
    Term result;
    unsigned int combined_mask = a.mask | b.mask;
    unsigned int diff_bit = (a.num ^ b.num) & ~(a.mask | b.mask);

    result.num = (a.num & b.num) & ~diff_bit;
    result.mask = combined_mask | diff_bit;
    result.used = false;
    return result;
}

void generate_min_circuit(int v[], int size)
{
    Term *groups[size + 1];                              // Array de ponteiros para armazenar grupos de termos por número de '1's
    Term *new_groups[size + 1];                          // Array temporário para armazenar novos grupos gerados na combinação
    Term *prime_implicants;                              // Array para armazenar os implicantes primos encontrados
    int prime_implicants_size = 0;                       // Contador para o número de implicantes primos
    int group_sizes[size + 1];                           // Array para armazenar o tamanho de cada grupo
    memset(group_sizes, 0, sizeof(group_sizes));         // Inicializa os tamanhos dos grupos com 0
    int new_group_sizes[size + 1];                       // Array para armazenar o tamanho dos novos grupos
    memset(new_group_sizes, 0, sizeof(new_group_sizes)); // Inicializa os tamanhos dos novos grupos com 0
    prime_implicants = malloc(size * sizeof(Term));      // Alocação dinâmica para os implicantes primos

    // Loop para inicializar os grupos e alocar memória para cada grupo
    for (int i = 0; i <= size; i++)
    {
        groups[i] = malloc(size * sizeof(Term));     // Aloca memória para armazenar termos no grupo i
        new_groups[i] = malloc(size * sizeof(Term)); // Aloca memória para armazenar novos termos no grupo i
    }

    // Loop para agrupar os termos baseados no número de '1's em sua representação binária
    for (int i = 0; i < size; i++)
    {
        int bit_count = __builtin_popcount(v[i]);                             // Conta o número de '1's no termo v[i]
        groups[bit_count][group_sizes[bit_count]++] = (Term){v[i], 0, false}; // Adiciona o termo ao grupo correspondente
    }

    bool progress; // Variável para verificar se houve progresso na combinação de termos
    do
    {
        progress = false;              // Inicializa progresso como falso
        for (int i = 0; i < size; i++) // Loop pelos grupos
        {
            for (int j = 0; j < group_sizes[i]; j++) // Loop pelos termos em um grupo
            {
                for (int k = 0; k < group_sizes[i + 1]; k++) // Loop pelos termos no grupo adjacente
                {
                    if (can_combine(groups[i][j], groups[i + 1][k])) // Verifica se dois termos podem ser combinados
                    {
                        Term new_term = combine_terms(groups[i][j], groups[i + 1][k]); // Combina os termos
                        groups[i][j].used = true;                                      // Marca o termo usado
                        groups[i + 1][k].used = true;                                  // Marca o termo usado
                        new_groups[i][new_group_sizes[i]++] = new_term;                // Adiciona o novo termo ao grupo temporário
                        progress = true;                                               // Atualiza o progresso para verdadeiro
                        // Imprime os termos antes e depois da combinação
                        printf("\nCombining: ");
                        print_binary(groups[i][j]);
                        print_binary(groups[i + 1][k]);
                        printf("\nResult:    ");
                        print_binary(new_term);
                    }
                }
                if (!groups[i][j].used) // Se o termo não foi combinado, adiciona aos implicantes primos
                {
                    prime_implicants[prime_implicants_size++] = groups[i][j];
                }
                printf("\n");
            }
        }
        // Atualiza os grupos com os novos termos e prepara para a próxima iteração
        for (int i = 0; i <= size; i++)
        {
            memcpy(groups[i], new_groups[i], new_group_sizes[i] * sizeof(Term));
            group_sizes[i] = new_group_sizes[i];
            new_group_sizes[i] = 0; // Resetar tamanhos dos novos grupos para a próxima iteração
        }
    } while (progress); // Continua enquanto houver progresso

    remove_duplicates(prime_implicants, &prime_implicants_size); // Remove duplicatas dos implicantes primos

    // Imprime os termos finais
    printf("\n\n----------FINAL TERMS----------\n");
    for (int i = 0; i < prime_implicants_size; i++)
    {
        printf("\nPrime Implicants: ");
        print_binary(prime_implicants[i]);
    }
    printf("\n\ny = ");
    for (int i = 0; i < prime_implicants_size; i++)
    {
        print_expression(prime_implicants[i].num, prime_implicants[i].mask);
    }

    // Limpeza e liberação de memória dos grupos
    for (int i = 0; i <= size; i++)
    {
        free(groups[i]);
        free(new_groups[i]);
    }
}