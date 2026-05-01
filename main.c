#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "CppVector.h"
#include "SortFunctions.h"
#include "TestFunctions.h"

void testes(int qtdTestes, int tamanhoLista, DataType dataType ){
    int  rnd, i;
    teste **testes = (teste**)malloc(sizeof(teste*)* qtdTestes);
    srand(time(NULL));

    //criando multiplo casos de teste
    for(i=0; i<qtdTestes; i++){
        testes[i] = criarTeste(tamanhoLista, dataType);
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

    printf("\n-------------------------------------------------\n");
    printf("\n----- EXECUTANDO C++ SORT COM STRUCT VECTOR -----\n");
    printf("\n-------------------------------------------------\n");

    ExecutaTeste(testes,qtdTestes, tamanhoLista, 4);
    imprimeTestes(testes, qtdTestes, 3);
    printf("\nResetando resultados...\n");
    resetaResultado(testes, qtdTestes, tamanhoLista);

    printf("\n-------------------------------------------------\n");
    printf("\n----- EXECUTANDO C++ SORT COM VETOR SIMPLES -----\n");
    printf("\n-------------------------------------------------\n");

    ExecutaTeste(testes,qtdTestes, tamanhoLista, 5);
    imprimeTestes(testes, qtdTestes, 3);
    printf("\nResetando resultados...\n");
    resetaResultado(testes, qtdTestes, tamanhoLista);

    destruirTestes(testes, qtdTestes);

    return;
}

void TestCppVector(DataType dataType, int list_size){

    if(dataType == TYPE_CHAR){
        int rnd;
        char val;
        srand(time(NULL));

        lista *l = crialista(TYPE_CHAR);
        for(int i=0; i<10; i++){
            rnd = (char) (65 + (rand() % 26));
            push_back(l, &rnd); //envia dado como ponteiro
        }

        val = 'A';
        push_back(l, &val);
        val = 'B';
        push_back(l, &val);
        val = 'C';
        push_back(l, &val);
        val = 'D';
        push_back(l, &val);
        val = 'E';
        push_back(l, &val);
        
        pop_back(l);
        val = 'F';
        insert(2, l, &val);
        
        erase(2, l);
        print(l);
        
        printf("Tamanho: %d\n", size(l));
        printf("Elemento no indice 2: %c\n", (char)at(l, 2));
        
        clear(l);
        free(l);
    }else if(dataType == TYPE_INT){
        int rnd, val;
        srand(time(NULL));

        lista *l = crialista(TYPE_INT);
        
        for(int i=0; i<10; i++){
            rnd = rand() % 10;
            push_back(l, &rnd); //envia dado como ponteiro
        }

        val = 1;
        push_back(l, &val);
        val = 2;
        push_back(l, &val);
        val = 3;
        push_back(l, &val);
        val = 4;
        push_back(l, &val);
        val = 5;
        push_back(l, &val);
        
        pop_back(l);
        val = 10;
        insert(2, l, &val);
        
        erase(2, l);
        print(l);
        
        printf("Tamanho: %d\n", size(l));
        printf("Elemento no indice 2: %d\n", at(l, 2));
        
        clear(l);
        free(l);
        return;
    }

    return;

}
int main() {
    
    TestCppVector(TYPE_INT, 10);
    TestCppVector(TYPE_CHAR, 10);

    testes(5,30,TYPE_INT);
    testes(5,30,TYPE_CHAR);

    return 0;
}