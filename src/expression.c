// expression.c
#include "expression.h"
#include <stdio.h>

/**
 * Imprime a representação binária de um termo, usando 'X' para indicar bits mascarados.
 *
 * Parâmetros:
 *   term: Term - O termo a ser impresso em formato binário.
 *
 * Retorna:
 *   void - Não há valor de retorno.
 *
 * Processo:
 *   1. **Iteração sobre os bits:**
 *      - A função itera sobre os bits do termo, começando do bit mais significativo (bit 7) até o bit menos significativo (bit 0).
 *   2. **Verificação da máscara:**
 *      - Para cada bit, a função verifica se o bit correspondente na máscara do termo é 1. Isso é feito deslocando a máscara para a direita
 *        pelo índice do bit atual e aplicando a operação AND bit a bit com 1 (`(term.mask >> i) & 1`).
 *      - Se o resultado for 1, significa que o bit está mascarado e deve ser impresso como 'X'.
 *   3. **Impressão do bit:**
 *      - Se o bit não estiver mascarado, o valor do bit no número do termo é impresso.
 *      - Isso é feito deslocando o número do termo para a direita pelo índice do bit atual e aplicando a operação AND bit a bit com 1
 *        (`(term.num >> i) & 1`). O resultado será 0 ou 1, representando o valor do bit.
 *   4. **Formatação da saída:**
 *      - Após imprimir cada grupo de 4 bits, a função imprime um espaço em branco para facilitar a leitura da saída binária.
 *
 * Exceções:
 *   Não aplicável.
 */
void print_binary(Term term)
{
    for (int i = 7; i >= 0; i--)
    {
        if ((term.mask >> i) & 1)
        {
            printf("X");
        }
        else
        {
            printf("%d", (term.num >> i) & 1);
        }
        if (i % 4 == 0)
            printf(" ");
    }
}

/**
 * Imprime a representação da expressão lógica correspondente a um termo.
 *
 * Parâmetros:
 *   num: int - O número do termo, representando os valores dos bits não mascarados.
 *   mask: int - A máscara do termo, indicando quais bits são 'não importa' (X).
 *
 * Retorna:
 *   void - Não há valor de retorno.
 *
 * Processo:
 *   1. **Iteração sobre as variáveis:**
 *      - A função itera sobre as variáveis da expressão, assumindo que elas são nomeadas como A, B, C, etc., em ordem inversa aos bits (A
 *        sendo a variável correspondente ao bit menos significativo).
 *   2. **Verificação da máscara:**
 *      - Para cada variável, a função verifica se o bit correspondente na máscara é 1. Isso é feito deslocando 1 para a esquerda pelo índice
 *        da variável e aplicando a operação AND bit a bit com a máscara (`mask & (1 << i)`).
 *      - Se o resultado for 1, significa que o bit está mascarado e a variável não deve ser incluída na expressão.
 *   3. **Impressão da variável:**
 *      - Se o bit não estiver mascarado, a função imprime o nome da variável.
 *      - Em seguida, a função verifica o valor do bit correspondente no número do termo. Se o valor for 1, a função imprime um espaço em
 *        branco após o nome da variável. Se o valor for 0, a função imprime um apóstrofo (') após o nome da variável, representando a
 *        operação NOT.
 *   4. **Formatação da saída:**
 *      - Após imprimir cada termo da expressão, a função imprime " + " para separá-lo dos próximos termos.
 *
 * Exceções:
 *   Não aplicável.
 */
void print_expression(int num, int mask)
{
    for (int i = 0; i <= 7; i++)
    {
        char var = 'A' + (7 - i);
        if (mask & (1 << i))
        {
            continue;
        }

        printf("%c%c", var, (num & (1 << i)) ? ' ' : '\'');
    }
}