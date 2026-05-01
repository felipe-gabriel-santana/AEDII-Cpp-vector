#include <math.h>
#include "SortFunctions.h"

void insertAt(lista*l, int n, void* valor){
    erase(n, l);
    insert(n,l,valor);
    return;
}

void swapValues(lista *l, int i, int j){
    if(i == j){
        return;
    }

    if (l->dataType == TYPE_INT) {
        int aux1 = at(l,i);
        int aux2 = at(l,j);
        insertAt(l,i,&aux2);
        insertAt(l,j,&aux1);
    } else {
        char aux1 = (char) at(l,i);
        char aux2 = (char) at(l,j);
        insertAt(l,i,&aux2);
        insertAt(l,j,&aux1);
    }

    return;
}

void insertionSort(lista *l, int first, int last){

    if(last - first <= 0){
        return;
    }
    int i, j, x;
    if(l->dataType == TYPE_INT){
        int val;
        for(i= first+1; i<=last; i++){
            x = at(l,i);
            j=i-1;
            while (j>= first && at(l,j)>x){
                val = at(l,j);
                insertAt(l,j+1,&val);
                j--;
            }
            insertAt(l,j+1,&x);
        }
    }else{
        char val;
        for(i= first+1; i<=last; i++){
            x = at(l,i);
            j=i-1;
            while (j>= first && at(l,j)>x){
                val = (char) at(l,j);
                insertAt(l,j+1,&val);
                j--;
            }
            val = (char) x;
            insertAt(l,j+1,&val);
        }
    }
}

 int medianOfThreePivot(lista *A, int p, int r){
    int m = ((r-p)+1)/2;

    int v1 = at(A,p), v2 = at(A,m), v3 = at(A,r);

    if((v1>=v2 && v1<=v3) || (v1>=v3 && v1<=v2)){
        swapValues(A,p,r);
        return v1;
    }

    if((v2>=v1 && v2<=v3) || (v2>=v3 && v2<=v1)){
        swapValues(A,m,r);
        return v2;
    }

    return v3;
}

int partition(lista *A, int p, int r){
    int pivo = medianOfThreePivot(A, p, r);
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


void sortVectorStruct(lista *l) {
    int tamanho = size(l);
    
    if (tamanho<=1){
        return;
    }

    int depthLimit = 2 * (int)floor(log2(tamanho));

    IntroSort(l, 0, tamanho-1, depthLimit);
    return;
}