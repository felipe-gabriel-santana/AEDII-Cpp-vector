#ifndef CPPVECTOR_H
#define CPPVECTOR_H

#include <stdbool.h>

typedef enum {
    TYPE_INT,
    TYPE_CHAR
} DataType;

typedef struct no {
    int valor;
    struct no *prox;
    struct no *ant;
} no;

typedef struct lista {
    DataType dataType;
    struct no *ini;
    struct no *fim;
} lista;

lista* crialista(DataType dataType);
void push_back(lista *l, void* valor);
void pop_back(lista *l);
void insert(int n, lista *l, void* valor);
void erase(int n, lista *l);
int size(lista *l);
bool empty(lista *l);
void clear(lista *l);
void swap(lista *l1, lista *l2);
int get_element(lista *l, int n);
int at(lista *l, int n);
void print(lista *l);

#endif