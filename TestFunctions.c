#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "TestFunctions.h"
#include "SortFunctions.h"

teste* criarTeste(int tamanho){
    int i, rnd;
    teste *novoTeste = malloc(sizeof(teste));
    lista *entrada = crialista();
    lista *saida = crialista();

    for(int i = 0; i < tamanho; i++) {
        rnd = rand() % 1000;
        push_back(entrada, rnd);
        push_back(saida, rnd);
    }
    novoTeste->entrada = entrada;
    novoTeste->saida = saida;
    novoTeste->valida = false;

    return novoTeste;
}

bool ordenada(lista *l, int tamanho) {
    if(tamanho<=1) return true;
    
    for (int i = 0; i < tamanho - 1; i++) {
        if (at(l, i) > at(l, i + 1)) {
            return false;
        }
    }
    return true;
}

void destruirTestes(teste** testes, int tamanho){
    
    for(int i=0; i<tamanho;i++){
        clear(testes[i]->entrada);
        clear(testes[i]->saida);
        free(testes[i]->entrada);
        free(testes[i]->saida);
        free(testes[i]);
    }
    free(testes);

}

void imprimeTeste(teste **testes, int i, int modo){

    if(modo<1 || modo>3) return;

    printf("\n----------------CASO %i----------------\n",i+1);
    
    if(testes[i]->valida){
        printf("Validação: [OK]\n");
    }else{
        printf("Validação: [NOK]\n");
    }

    switch (modo){
    case 1: //somente saida
        printf("Saida:   ");
        print(testes[i]->saida);
        break;
    case 2: //somente entrada
        printf("Entrada: ");
        print(testes[i]->entrada);
        break;
    case 3: //entrada e saída
        printf("Entrada: ");
        print(testes[i]->entrada);
        printf("Saida:   ");
        print(testes[i]->saida);
        break;
    default:
        break;
    }
    printf("--------------------------------\n");
    return;
}
void imprimeTestes(teste **testes,int qtdTestes,int modo){

    for(int i=0; i<qtdTestes;i++){
        imprimeTeste(testes, i, modo);
    }

    return;
}

void resetaResultado(teste **testes, int qtdTestes, int tamanhoLista){
    for(int i=0; i<qtdTestes; i++){
        clear(testes[i]->saida);
        
        for(int j=0; j<tamanhoLista;j++){
            push_back(testes[i]->saida, at(testes[i]->entrada, j));
        }

        testes[i]->valida = false;
    }
}

void ExecutaTeste(teste **testes,int qtdTestes, int tamanhoLista, int algoritmo){

    for(int i=0; i<qtdTestes; i++){
        switch (algoritmo){
        case 1:
            insertionSort(testes[i]->saida, 0, tamanhoLista-1);
            break;
        case 2:
            quicksort(testes[i]->saida, 0, tamanhoLista-1);
            break;
        case 3:
            heapsort(testes[i]->saida, 0, tamanhoLista-1);
            break;
        case 4:
            sort(testes[i]->saida);
            break;
        default:
            break;
        }
        testes[i]->valida = ordenada(testes[i]->saida, tamanhoLista);
    }
    return;
}
