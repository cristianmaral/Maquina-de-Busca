#include "ListaEncadeada.h"
#include <stdlib.h>

/* Inicializa uma lista - já alocando a célula cabeça */
void inicializaLista (TLista *Lista) {
    Lista->primeiro = Lista->ultimo = (TCelula *)malloc(sizeof(TCelula));
    Lista->primeiro->prox = NULL;
    Lista->tamanho = 0;
}

/* Insere um item na lista */
void insereLista (TLista *Lista, TItem *item) {
    TCelula *aux;
    aux = (TCelula *)malloc(sizeof(TCelula));
    aux->item = *item;
    Lista->ultimo->prox = aux;
    Lista->ultimo = aux;
    Lista->tamanho++;
}

/* Imprime o par ordenado (qtde,idDoc) */
void imprimeLista (TLista *Lista) {
    TCelula *aux;
    aux = Lista->primeiro->prox;

    while (aux != NULL) {
        if(aux->prox == NULL)
            printf("<%d,%d>\n", aux->item.it.termo.qtde, aux->item.it.termo.idDoc);
        /* Imprime "->" no final do par ordenado */
        else
            printf("<%d,%d> -> ", aux->item.it.termo.qtde, aux->item.it.termo.idDoc);

        aux = aux->prox;
    }
}
