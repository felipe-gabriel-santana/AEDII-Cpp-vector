#ifndef SORTFUNCTIONS_H
#define SORTFUNCTIONS_H

#include "CppVector.h"


void insertionSort(lista *l, int first, int last);
void quicksort(lista *A, int first, int last);
void heapsort(lista *A, int first, int last);
void sort(lista *l);

#endif