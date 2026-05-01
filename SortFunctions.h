#ifndef SORTFUNCTIONS_H
#define SORTFUNCTIONS_H

#include "CppVector.h"

void insertionSort(lista *l, int first, int last);
void quicksort(lista *A, int first, int last);
void heapsort(lista *A, int first, int last);
void sortVectorStruct(lista *l);
void sortCpp(lista *l);

#endif