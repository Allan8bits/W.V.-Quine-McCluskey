// src/main.c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <logic_minimizer.h>

int main() {
    int v[] = {4, 8, 9, 10, 11, 12, 14, 15};
    generate_min_circuit(v, sizeof(v)/sizeof(v[0]));
    return 0;
}
