#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

typedef struct Vector{
    int *data;
    size_t size;
    size_t capacity;
}Vector;

void init_vector(Vector *v){
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

void push_back(Vector *v, int valor){
    if(v->size == v->capacity){
        v->capacity = v->capacity == 0 ? 1 : v->capacity * 2;
        v->data = (int *) realloc(v->data, v->capacity * sizeof(int));
    }
    v->data[v->size++] = valor;
}

void pop_back(Vector *v){
    if(v->size > 0){
        v->size--;
        if(v->size > 0 && v->size <= v->capacity / 4 && v->capacity > 4){
            v->capacity /= 2;
            v->data = (int *)realloc(v->data, v->capacity * sizeof(int));
        }
    }
}

void insert(Vector *v, size_t index, int valor){
    if(index > v->size){
        return;
    }
    if(v->size == v->capacity){
        v->capacity = v->capacity == 0 ? 1 : v->capacity * 2;
        v->data = (int *)realloc(v->data, v->capacity * sizeof(int));
    }
    
    memmove(&v->data[index + 1], &v->data[index], (v->size - index) * sizeof(int));
    
    v->data[index] = valor;
    v->size++;
}

void erase(Vector *v, size_t index){
    if(index >= v->size){
        return;
    }

    memmove(&v->data[index], &v->data[index + 1], (v->size - index - 1) * sizeof(int));
    
    v->size--;

    if(v->size > 0 && v->size <= v->capacity / 4 && v->capacity > 4){
        v->capacity /= 2;
        v->data = (int *)realloc(v->data, v->capacity * sizeof(int));
    }
}

void clear(Vector *v){
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

void swap(Vector *v1, Vector *v2){
    Vector aux = *v1;
    *v1 = *v2;
    *v2 = aux;
}

int operator(Vector *v, int i){
    return v->data[i];
}

int at(Vector *v, int i){
    if(i >= v->size || i < 0){
        return -1;
    }
    return v->data[i];
}

int front(Vector *v){
    if(v->size == 0) return -1;
    return v->data[0];
}

int back(Vector *v){
    if(v->size == 0) return -1;
    return v->data[v->size - 1];
}

size_t size(Vector *v){
    return v->size;
}

size_t capacity(Vector *v){
    return v->capacity;
}

bool empty(Vector *v){
    return (v->size == 0);
}

void reserve(Vector *v, size_t n){
    if(n > v->capacity){
        v->data = (int *) realloc(v->data, n * sizeof(int));
        v->capacity = n;
    }
}

void shrink_to_fit(Vector *v){
    if(v->size < v->capacity){
        v->capacity = v->size;
        v->data = (int *) realloc(v->data, v->size * sizeof(int));
    }
}

int *begin(Vector *v){
    return v->data;
}

int *end(Vector *v){
    return (v->data + v->size);
}

#endif