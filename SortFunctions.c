#include <math.h>
#include "SortFunctions.h"

void insertAt(lista*l, int n, int valor){
    erase(n, l);
    insert(n,l,valor);
    return;
}

void swapValues(lista *l, int i, int j){
    if(i == j){
        return;
    }

    int aux = at(l,i);

    insertAt(l,i,at(l, j));
    insertAt(l,j,aux);
    return;
}

void insertionSort(lista *l, int first, int last){

    if(last - first <= 0){
        return;
    }
    int i, j, x;

    for(i= first+1; i<=last; i++){
        x = at(l,i);
        j=i-1;

        while (j>= first && at(l,j)>x){
            insertAt(l,j+1,at(l,j));
            j--;
        }
        insertAt(l,j+1,x);
    }
}


int partition(lista *A, int p, int r){
    int pivo = at(A, r);
    int i = p - 1;

    for(int j = p; j <= r - 1; j++) {
        if(at(A, j) <= pivo) {
            i = i + 1;
            swapValues(A,i,j);
        }
    }
    swapValues(A,i+1,r);
    return i+1;
}

void quicksort(lista *A, int first, int last){
    if(first < last) {
        int pivo = partition(A, first, last);
        quicksort(A, first, pivo - 1);
        quicksort(A, pivo + 1, last);
    }
    return;
}


void maxHeapify(lista *l, int first, int i, int tamanho){
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;
    int maior = i;

    if(esq<tamanho && at(l,first+esq) > at(l, first+maior)){
        maior = esq;
    }
    if(dir<tamanho && at(l,first+dir) > at(l,first+maior)){
        maior = dir;
    }

    if(maior != i){
        swapValues(l, first+i, first+maior);
        maxHeapify(l, first, maior, tamanho);
    }
    return;
}

void buildMaxHeap(lista *l, int first, int last, int tamanho){
    for (int i = (tamanho/2)-1; i >= 0; i--){
        maxHeapify(l,first, i, tamanho);
    }
    return;
}

void heapsort(lista *l, int first, int last){
    int tamanho = (last-first)+1;

    buildMaxHeap(l,first,last,tamanho);
    
    for (int i = tamanho - 1; i > 0; i--){
        swapValues(l, first, first+i);
        maxHeapify(l, first, 0, i);
    }

    return;
}


void IntroSort(lista *l, int first, int last, int depthLimit) {
    if (first>=last){
        return;
    }

    int n = (last - first) + 1;

    if (n <= 16) {
        insertionSort(l, first, last);
        return;
    }

    if (depthLimit == 0) {
        heapsort(l, first, last);
        return;
    }

    int pivo = partition(l, first, last);

    IntroSort(l, first, pivo - 1, depthLimit - 1);
    IntroSort(l, pivo + 1, last, depthLimit - 1);
    return;
}


void sort(lista *l) {
    int tamanho = size(l);
    
    if (tamanho<=1){
        return;
    }

    int depthLimit = 2 * (int)floor(log2(tamanho));

    IntroSort(l, 0, tamanho-1, depthLimit);
    return;
}