#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "CppVector.h"
#include "SortFunctions.h"

typedef struct {
    double insere, busca, ordena, remove;
    size_t memoria;
} Tempos;

int Busca_linear(lista *l, int target) {
    no *aux = l->ini;
    int pos = 0;
    while (aux != NULL) {
        if (aux->valor == target) return pos;
        aux = aux->prox;
        pos++;
    }
    return -1;
}

Tempos Executa_operacoes(int n, DataType type, const char* filename) {
    Tempos m = {0,0,0,0,0};
    clock_t start, end;
    lista *l = crialista(type);

    // --- GERAÇÃO ALEATÓRIA COMENTADA ---
    /*
    for (int i = 0; i < n; i++) { ... }
    */

    FILE *file = fopen(filename, "r");
    if (!file) { printf("Erro: %s não encontrado\n", filename); return m; }

    if (type == TYPE_INT) {
        int *buffer = malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++) fscanf(file, "%d", &buffer[i]);
        
        start = clock();
        for (int i = 0; i < n; i++) push_back(l, &buffer[i]);
        end = clock();
        free(buffer);
    } else {
        char *buffer = malloc(sizeof(char) * n);
        for (int i = 0; i < n; i++) fscanf(file, " %c", &buffer[i]);
        
        start = clock();
        for (int i = 0; i < n; i++) push_back(l, &buffer[i]);
        end = clock();
        free(buffer);
    }
    fclose(file);
    m.insere = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

    int target = at(l, n/2);
    start = clock();
    Busca_linear(l, target);
    end = clock();
    m.busca = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

    start = clock();
    sortCpp(l); //sortVectorStruct(1) para utilizar a lista encadeada
    end = clock();
    m.ordena = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

    int mid = size(l) / 2;
    start = clock();
    if (mid > 0) erase(mid, l);
    end = clock();
    m.remove = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

    m.memoria = (n * sizeof(no) + sizeof(lista)) / 1024;

    clear(l);
    free(l);
    return m;
}

int main() {
    const char* filesInt[] = {"int_100.txt", "int_1000.txt", "int_10000.txt", "int_100000.txt", "int_1000000.txt"};
    const char* filesChar[] = {"char_100.txt", "char_1000.txt", "char_10000.txt", "char_100000.txt", "char_1000000.txt"};
    int sizes[] = {100, 1000, 10000, 100000, 1000000};

    printf("%-10s %-10s | %-11s | %-10s | %-11s | %-11s | %-10s\n", // para que a saída fique alinhada
           "Tipo", "Tamanho", "Inserir(ms)", "Buscar(ms)", "Remover(ms)", "Ordenar(ms)", "Memoria");
    printf("-----------------------------------------------------------------------------------------\n");

    for (int i = 0; i < 5; i++) {
        Tempos mi = Executa_operacoes(sizes[i], TYPE_INT, filesInt[i]);
        printf("%-10s %-10d | %-11.4f | %-10.4f | %-11.4f | %-11.4f | %lu KB\n", "INT", sizes[i], mi.insere, mi.busca, mi.remove, mi.ordena , mi.memoria);

        Tempos mc = Executa_operacoes(sizes[i], TYPE_CHAR, filesChar[i]);
        printf("%-10s %-10d | %-11.4f | %-10.4f | %-11.4f | %-11.4f | %lu KB\n", "CHAR", sizes[i], mc.insere, mc.busca, mc.remove, mc.ordena, mc.memoria);
        printf(".........................................................................................\n");
    }

}