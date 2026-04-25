#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "CppVector.h"

int main() {
    int vetor[1000], rnd;
    srand(time(NULL));
    for(int i = 0; i < 1000; i++) {
        rnd = rand() % 1000;
        vetor[i] = rnd;
    }


    lista *l = crialista();
    
    for(int i=0; i<1000; i++){
        rnd = rand() % 1000;
        push_back(l, rnd);
    }
    

    push_back(l, 1);
    push_back(l, 2);
    push_back(l, 3);
    push_back(l, 4);
    push_back(l, 5);
    
    
    
    pop_back(l);
    
    
    insert(2, l, 10);
    
    erase(2, l);
    print(l);
    
    printf("Tamanho: %d\n", size(l));
    printf("Elemento no indice 2: %d\n", at(l, 2));
    
    clear(l);
    free(l);
    
    return 0;
}