#include <stdio.h>
#include <stdlib.h>
#include "CppVector.h"

lista* crialista(DataType dataType) {
    lista *l = (lista*)malloc(sizeof(lista));
    l->ini = NULL;
    l->fim = NULL;
    l->dataType = dataType;
    return l;
}

void push_back(lista *l, void* valor) {
    no *novo = (no*)malloc(sizeof(no));
    novo->prox = NULL;
    novo->ant = NULL;

    //identifica tipo de dado e faz conversão para tipo int
    if (l->dataType == TYPE_INT) {
        novo->valor = *(int *)valor;
    } else {
        novo->valor = (int)(*(char *)valor);
    }

    if (l->ini == NULL) {
        l->ini = novo;
        l->fim = novo;
    } else {
        novo->ant = l->fim;
        l->fim->prox = novo;
        l->fim = novo;
    }
}

void pop_back(lista *l) {
    if (l->ini == NULL) {
        printf("lista vazia!\n");
        return;
    }
    
    no *aux = l->fim;
    l->fim = aux->ant;
    
    if (l->fim == NULL) {
        l->ini = NULL;
    } else {
        l->fim->prox = NULL;
    }
    free(aux);
}

void insert(int n, lista *l, void* valor) {
    no *aux = l->ini;
    
    for (int i = 0; i < n && aux != NULL; i++) {
        aux = aux->prox;
    }
    
    if (aux == NULL) {
        push_back(l, valor);
        return;
    }
    
    no *novo = (no*)malloc(sizeof(no));

    //identifica tipo de dado e faz conversão para tipo int
    if (l->dataType == TYPE_INT) {
        novo->valor = *(int *)valor;
    } else {
        novo->valor = (int)(*(char *)valor);
    }
    
    if (aux == l->ini) {
        novo->ant = NULL;
        novo->prox = l->ini;
        l->ini->ant = novo;
        l->ini = novo;
        return;
    }

    novo->prox = aux;
    novo->ant = aux->ant;
    aux->ant->prox = novo;
    aux->ant = novo;
}

void erase(int n, lista *l) {
    no *aux = l->ini;
    for (int i = 0; i < n && aux != NULL; i++) {
        aux = aux->prox;
    }
    
    if (aux == NULL) return;

    if (aux == l->ini && aux == l->fim) {
        l->ini = NULL;
        l->fim = NULL;
    } else if (aux == l->ini) {
        l->ini = aux->prox;
        l->ini->ant = NULL;
    } else if (aux == l->fim) {
        l->fim = aux->ant;
        l->fim->prox = NULL;
    } else {
        aux->ant->prox = aux->prox;
        aux->prox->ant = aux->ant;
    }
    free(aux);
}

int size(lista *l) {
    int s = 0;
    no *aux = l->ini;
    while (aux != NULL) {
        s++;
        aux = aux->prox;
    }
    return s;
}

bool empty(lista *l) {
    return l->ini == NULL;
}

void clear(lista *l) {
    while (!empty(l)) {
        pop_back(l);
    }
}

void swap(lista *l1, lista *l2) {
    no *aux_ini = l1->ini;
    no *aux_fim = l1->fim;
    l1->ini = l2->ini;
    l1->fim = l2->fim;
    l2->ini = aux_ini;
    l2->fim = aux_fim;
}

int get_element(lista *l, int n) {
    no *aux = l->ini;
    for (int i = 0; i < n && aux != NULL; i++) {
        aux = aux->prox;
    }
    if(aux != NULL) return aux->valor;
    return -1;
}

int at(lista *l, int n) {
    if (n >= size(l) || n < 0) {
        printf("erro: indice fora dos limites!\n");
        return -1;
    }    
    no *aux = l->ini;
    for (int i = 0; i < n; i++) {
        aux = aux->prox;
    }
    return aux->valor;
}

void print(lista *l) {
    no *aux = l->ini;
    if(l->dataType == TYPE_INT){
        printf("[ ");
        while(aux != NULL) {
            printf("%d ", aux->valor);
            aux = aux->prox;
        }
        printf("]\n");
    }else if(l->dataType == TYPE_CHAR){
        printf("[ ");
        while(aux != NULL) {
            printf("%c ", (char)aux->valor);
            aux = aux->prox;
        }
        printf("]\n");
    }
    return;
}

