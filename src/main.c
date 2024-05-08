/*********************************************************************
* Nome do Projeto: Algoritmo Quine-McCluskey
* Descrição: Este projeto é uma implementação em C do algoritmo
* Quine-McCluskey, usado para minimizar funções booleanas.
*
* Autor: Allan Rodrigo Remedi Amantino e João Vitor Silva Gomes
* Data: 08/05/2024
*
* Funções Principais:
* - void generate_min_circuit(): Gera a função boleana minimizada.
* - Term combine_terms(): Combina dois termos se eles diferirem por exatamente um bit, considerando suas máscaras.
* - bool can_combine():  Verifica se dois termos podem ser combinados, considerando máscaras.
*
* Observações:
* - Este código é apenas para fins educativos e pode não ser
*   totalmente otimizado para uso em produção.
*
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <logic_minimizer.h>

/**
 * Ponto de entrada principal do programa.
 *
 * Parâmetros:
 *   Não aplicável - main não recebe argumentos de linha de comando neste contexto.
 *
 * Retorna:
 *   int - Retorna 0 para indicar a execução bem-sucedida do programa.
 *
 * Processo:
 *   1. **Declaração e Inicialização de Variáveis:**
 *      - Declara um array `v` de inteiros que representa o conjunto de números para os quais o circuito lógico será minimizado.
 *   2. **Chamada da Função `generate_min_circuit`:**
 *      - Chama a função `generate_min_circuit`, passando o array `v` e seu tamanho como argumentos. 
 *      - O tamanho é calculado pela divisão do tamanho total do array pelo tamanho de um de seus elementos.
 *   3. **Retorno de Execução:**
 *      - Retorna 0 após a conclusão bem-sucedida da função `generate_min_circuit`, indicando que o programa terminou sem erros.
 *
 * Exceções:
 *   Não aplicável.
 */
int main()
{
    int v[] = {4, 8, 9, 10, 11, 12, 14, 15};
    generate_min_circuit(v, sizeof(v) / sizeof(v[0]));
    return 0;
}
