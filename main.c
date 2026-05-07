#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "CppVector.h"
#include "SortFunctions.h"

void run_csv_benchmark(int n, DataType type, const char* filename, const char* type_label) {
    clock_t start, end;
    lista *l = crialista(type);
    FILE *file = fopen(filename, "r");
    if (!file) return;

    if (type == TYPE_INT) {
        int *buf = malloc(sizeof(int) * n);
        for(int i=0; i<n; i++) fscanf(file, "%d", &buf[i]);
        start = clock();
        for(int i=0; i<n; i++) push_back(l, &buf[i]);
        end = clock();
        free(buf);
    } else {
        char *buf = malloc(sizeof(char) * n);
        for(int i=0; i<n; i++) fscanf(file, " %c", &buf[i]);
        start = clock();
        for(int i=0; i<n; i++) push_back(l, &buf[i]);
        end = clock();
        free(buf);
    }
    fclose(file);
    double t_ins = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

    int target = (l->ini) ? l->ini->valor : 0;
    start = clock();
    no *aux = l->ini;
    while (aux != NULL) { if (aux->valor == (int)target) break; aux = aux->prox; }
    end = clock();
    double t_sea = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

    start = clock();
    sortVectorStruct(l); // sortVectorStruct(1) para testar diretamente na lista encadeada
    end = clock();
    double t_sor = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

    int mid = size(l) / 2;
    start = clock();
    if (mid > 0) erase(mid, l);
    end = clock();
    double t_rem = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

    size_t mem = (n * sizeof(no) + sizeof(lista)) / 1024;

    printf("C,%s,%d,%.6f,%.6f,%.6f,%.6f,%lu\n", type_label, n, t_ins, t_sea, t_sor, t_rem, mem);

    clear(l);
    free(l);
}

int main() {
    int sizes[] = {100, 1000, 10000, 100000, 1000000};
    const char* fInt[] = {"int_100.txt", "int_1000.txt", "int_10000.txt", "int_100000.txt", "int_1000000.txt"};
    const char* fChar[] = {"char_100.txt", "char_1000.txt", "char_10000.txt", "char_100000.txt", "char_1000000.txt"};

    for (int i = 0; i < 5; i++) {
        run_csv_benchmark(sizes[i], TYPE_INT, fInt[i], "INT");
        run_csv_benchmark(sizes[i], TYPE_CHAR, fChar[i], "CHAR");
    }
}
