#include <stdio.h>
#include "vector.h"
#include "sorts.h"

int main(){
    Vector v;
    init_vector(&v);

    push_back(&v, 42);
    push_back(&v, 15);
    push_back(&v, 8);
    push_back(&v, 100);
    push_back(&v, 4);
    push_back(&v, 23);
    push_back(&v, 16);

    printf("Vetor original: \n");
    for(int i = 0; i < size(&v); i++){
        printf("%d ", at(&v, i));
    }
    printf("\n\n");

    chama_introsort(&v);

    printf("Vetor ordenado: \n");
    for(int i = 0; i < size(&v); i++){
        printf("%d ", at(&v, i));
    }
    printf("\n");

    clear(&v);

    return 0;
}