#ifndef TESTFUNCTIONS_H
#define TESTFUNCTIONS_H

#include <stdbool.h>
#include "CppVector.h"

typedef struct noTest {
    bool valida;
    struct lista *entrada;
    struct lista *saida;
} teste;

teste* criarTeste(int tamanho, DataType dataType);

bool ordenada(lista *l, int tamanho);

void destruirTestes(teste** testes, int tamanho);

void imprimeTeste(teste **testes, int i, int modo);

void imprimeTestes(teste **testes,int qtdTestes,int modo);

void resetaResultado(teste **testes, int qtdTestes, int tamanhoLista);

void ExecutaTeste(teste **testes,int qtdTestes, int tamanhoLista, int algoritmo);

#endif