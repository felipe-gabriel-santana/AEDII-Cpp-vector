#include <math.h>
#include <stdlib.h>

#include "SortFunctions.h"


void swapValuesCpp(int* vec, int i, int j){
    if(i == j){
        return;
    }

    int aux = vec[i];
    vec[i] = vec[j];
    vec[j] = aux;

    return;
}

void insertionSortCpp(int* vec, int first, int last){
    if(last - first <=0){
        return;
    }

    int i, j, x;

    for(i= first+1; i<=last; i++){
        x = vec[i];
        j=i-1;
        while (j>= first && vec[j]>x){
            vec[j+1] = vec[j];
            j--;
        }
        vec[j+1] = x;
    }
}

int medianOfThreePivotCpp(int *vec, int p, int r){
    int m = ((r-p)+1)/2;

    int v1 = vec[p], v2 = vec[m], v3 = vec[r];

    if((v1>=v2 && v1<=v3) || (v1>=v3 && v1<=v2)){
        swapValuesCpp(vec,p,r);
        return v1;
    }

    if((v2>=v1 && v2<=v3) || (v2>=v3 && v2<=v1)){
        swapValuesCpp(vec,m,r);
        return v2;
    }

    return v3;
}

int partitionCpp(int* vec, int p, int r){
    int pivo = medianOfThreePivotCpp(vec, p, r);
    int i= p-1;

    for(int j = p; j <= r - 1; j++) {
        if(vec[j] <= pivo) {
            i = i + 1;
            swapValuesCpp(vec,i,j);
        }
    }

    swapValuesCpp(vec,i+1,r);

    return i+1;
}


void quicksortCpp(int* vec, int first, int last){
    if(first < last) {
        int pivo = partitionCpp(vec, first, last);
        quicksortCpp(vec, first, pivo - 1);
        quicksortCpp(vec, pivo + 1, last);
    }
    return;
}

void maxHeapifyCpp(int* vec, int first, int i, int tamanho){
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;
    int maior = i;

    if(esq<tamanho && vec[first+esq] > vec[first+maior]){
        maior = esq;
    }
    if(dir<tamanho && vec[first+dir] > vec[first+maior]){
        maior = dir;
    }

    if(maior != i){
        swapValuesCpp(vec, first+i, first+maior);
        maxHeapifyCpp(vec, first, maior, tamanho);
    }
    return;
}

void buildMaxHeapCpp(int *vec, int first, int last, int tamanho){
    for (int i = (tamanho/2)-1; i >= 0; i--){
        maxHeapifyCpp(vec,first, i, tamanho);
    }
    return;
}

void heapsortCpp(int *vec, int first, int last){
    int tamanho = (last-first)+1;

    buildMaxHeapCpp(vec,first,last,tamanho);
    
    for (int i = tamanho - 1; i > 0; i--){
        swapValuesCpp(vec, first, first+i);
        maxHeapifyCpp(vec, first, 0, i);
    }

    return;
}


void IntroSortCpp(int *vec, int first, int last, int depthLimit) {
    if (first>=last){
        return;
    }

    int n = (last - first) + 1;

    if (n <= 16) {
        insertionSortCpp(vec, first, last);
        return;
    }

    if (depthLimit == 0) {
        heapsortCpp(vec, first, last);
        return;
    }

    int pivo = partitionCpp(vec, first, last);

    IntroSortCpp(vec, first, pivo - 1, depthLimit - 1);
    IntroSortCpp(vec, pivo + 1, last, depthLimit - 1);
    return;
}

int* ListToIntVec(lista *l, int tamanho){
    int *vec = malloc(sizeof(int)*tamanho);
    int i=0;
    no *aux = l->ini;

    while (aux != NULL) {
        vec[i] = aux->valor;
        aux = aux->prox;
        i++;
    }

    return vec;
}

void IntVecToList(int* vec, lista *l, int tamanho){
    int i=0;
    no *aux = l->ini;

    for(int i=0; i<tamanho; i++){
        aux->valor = vec[i];
        aux = aux->prox;
    }

    return;
}

void sortCpp(lista *l) {
    int tamanho = size(l);
    
    if (tamanho<=1){
        return;
    }

    //converte lista desordenada para vetor de acesso rápido
    int* vec = ListToIntVec(l,tamanho);

    //limite de profundidade para aplicar heap
    int depthLimit = 2 * (int)floor(log2(tamanho));

    IntroSortCpp(vec, 0, tamanho-1, depthLimit);

    //convete vetor ordenado de volta para lista
    IntVecToList(vec, l, tamanho);

    free(vec);
    return;
}