typedef struct no {
    int valor;
    struct no *prox;
    struct no *ant;
} no;

typedef struct lista {
    struct no *ini;
    struct no *fim;
} lista;


void push_back(lista *l, int valor);
void pop_back(lista *l);
void insert(int n, lista *l, int valor);
void erase(int n, lista *l);
int size(lista *l);
bool empty(lista *l);
void clear(lista *l);
void swap(lista *l1, lista *l2);
int get_element(lista *l, int n);
int at(lista *l, int n);
void print(lista *l);