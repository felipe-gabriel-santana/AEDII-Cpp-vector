#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "CppVector.h"
#include "SortFunctions.h"
#include "TestFunctions.h"

void testes(int qtdTestes, int tamanhoLista){
    int  rnd, i;
    teste **testes = (teste**)malloc(sizeof(teste*)* qtdTestes);
    srand(time(NULL));

    //criando multiplo casos de teste
    for(i=0; i<qtdTestes; i++){
        testes[i] = criarTeste(tamanhoLista);
    }
    printf("\n-------------------------------------\n");
    printf("\n----- EXECUTANDO INSERTION SORT -----\n");
    printf("\n-------------------------------------\n");

    ExecutaTeste(testes,qtdTestes, tamanhoLista, 1);
    imprimeTestes(testes, qtdTestes, 3);
    printf("\nResetando resultados...\n");
    resetaResultado(testes, qtdTestes, tamanhoLista);

    printf("\n---------------------------------\n");
    printf("\n----- EXECUTANDO QUICK SORT -----\n");
    printf("\n---------------------------------\n");

    ExecutaTeste(testes,qtdTestes, tamanhoLista, 2);
    imprimeTestes(testes, qtdTestes, 3);
    printf("\nResetando resultados...\n");
    resetaResultado(testes, qtdTestes, tamanhoLista);

    printf("\n--------------------------------\n");
    printf("\n----- EXECUTANDO HEAP SORT -----\n");
    printf("\n--------------------------------\n");

    ExecutaTeste(testes,qtdTestes, tamanhoLista, 3);
    imprimeTestes(testes, qtdTestes, 3);
    printf("\nResetando resultados...\n");
    resetaResultado(testes, qtdTestes, tamanhoLista);

    printf("\n-------------------------------\n");
    printf("\n----- EXECUTANDO C++ SORT -----\n");
    printf("\n-------------------------------\n");

    ExecutaTeste(testes,qtdTestes, tamanhoLista, 4);
    imprimeTestes(testes, qtdTestes, 3);
    printf("\nResetando resultados...\n");
    resetaResultado(testes, qtdTestes, tamanhoLista);

    destruirTestes(testes, qtdTestes);

    return;
}


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
    
    testes(5,100);

    return 0;
}