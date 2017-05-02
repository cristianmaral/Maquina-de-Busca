#ifndef LISTAENCADEADA_H_INCLUDED
#define LISTAENCADEADA_H_INCLUDED

typedef struct {
    int qtde;
    int idDoc;
    float peso;
} TItem;

typedef struct Celula {
    TItem item;
    struct Celula *prox;
} TCelula;

typedef struct {
    TCelula *primeiro;
    TCelula *ultimo;
    int tamanho;
} TLista;

void inicializaLista (TLista *Lista);
void insereLista (TLista *Lista, TItem *item);
void imprimeLista(TLista *Lista);

#endif // LISTAENCADEADA_H_INCLUDED
