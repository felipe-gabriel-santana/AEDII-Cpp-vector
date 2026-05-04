#ifndef SORTS_H
#define SORTS_H

void troca_elementos(int *a, int *b){
    int aux = *a;
    *a = *b;
    *b = aux;
}

void insertion_sort(Vector *v){
    if(v == NULL || v->size <= 1) return;

    int n = (int)v->size;
    for(int i = 1; i < n; i++){
        int key = v->data[i];
        int j = i - 1;

        while(j >= 0 && v->data[j] > key){
            v->data[j + 1] = v->data[j];
            j--;
        }
        v->data[j + 1] = key;
    }
}

void heapify(Vector *v, int n, int i){
    int maior = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if(esquerda < n && v->data[esquerda] > v->data[maior]){
        maior = esquerda;
    }

    if(direita < n && v->data[direita] > v->data[maior]){
        maior = direita;
    }

    if(maior != i){
        troca_elementos(&v->data[i], &v->data[maior]);
        heapify(v, n, maior);
    }
}

void heap_sort(Vector *v){
    if(v == NULL || v->size <= 1) return;

    int n = (int)v->size;

    for(int i = n / 2 - 1; i >= 0; i--){
        heapify(v, n, i);
    }

    for(int i = n - 1; i > 0; i--){
        troca_elementos(&v->data[0], &v->data[i]);
        heapify(v, i, 0);
    }
}

int partition(Vector *v, int low, int high){
    int pivo = v->data[high];
    int i = low - 1;

    for(int j = low; j < high; j++){
        if(v->data[j] < pivo){
            i++;
            troca_elementos(&v->data[i], &v->data[j]);
        }
    }
    troca_elementos(&v->data[i + 1], &v->data[high]);
    return i + 1;
}

void quick_sort(Vector *v, int low, int high){
    if(low < high){
        int pi = partition(v, low, high);
        quick_sort(v, low, pi - 1);
        quick_sort(v, pi + 1, high);
    }
}

void chama_quicksort(Vector *v){
    if(v == NULL || v->size <= 1) return;
    
    quick_sort(v, 0, (int)v->size - 1);
}

void insertion_sort_range(Vector *v, int low, int high){
    for(int i = low + 1; i <= high; i++){
        int key = v->data[i];
        int j = i - 1;

        while(j >= low && v->data[j] > key){
            v->data[j + 1] = v->data[j];
            j--;
        }
        v->data[j + 1] = key;
    }
}

void heapify_range(Vector *v, int low, int n, int i){
    int maior = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if(esquerda < n && v->data[low + esquerda] > v->data[low + maior]){
        maior = esquerda;
    }

    if(direita < n && v->data[low + direita] > v->data[low + maior]){
        maior = direita;
    }

    if(maior != i){
        troca_elementos(&v->data[low + i], &v->data[low + maior]);
        heapify_range(v, low, n, maior);
    }
}

void heap_sort_range(Vector *v, int low, int high){
    int n = high - low + 1;

    for(int i = n / 2 - 1; i >= 0; i--){
        heapify_range(v, low, n, i);
    }

    for(int i = n - 1; i > 0; i--){
        troca_elementos(&v->data[low], &v->data[low + i]);
        heapify_range(v, low, i, 0);
    }
}

int calcular_max_depth(int n){
    int depth = 0;
    while(n > 1){
        depth++;
        n /= 2;
    }
    return 2 * depth;
}

void intro_sort_recursive(Vector *v, int low, int high, int max_depth){
    int size = high - low + 1;

    if(size < 16){
        insertion_sort_range(v, low, high);
        return;
    }

    if(max_depth == 0){
        heap_sort_range(v, low, high);
        return;
    }

    int pi = partition(v, low, high);
    intro_sort_recursive(v, low, pi - 1, max_depth - 1);
    intro_sort_recursive(v, pi + 1, high, max_depth - 1);
}

void chama_introsort(Vector *v){
    if(v == NULL || v->size <= 1) return;
    
    int max_depth = calcular_max_depth((int)v->size);
    intro_sort_recursive(v, 0, (int)v->size - 1, max_depth);
}

#endif