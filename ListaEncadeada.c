#include "ListaEncadeada.h"
#include <stdio.h>
#include <stdlib.h>

/* Inicializa uma lista - já alocando a célula cabeça */
void inicializaLista (TLista *Lista) {
    Lista->primeiro = Lista->ultimo = (TCelula *)malloc(sizeof(TCelula));
    Lista->primeiro->prox = NULL;
}

/* Insere um item na lista */
void insereLista (TLista *Lista, TItem *item) {
    TCelula *aux;
    aux = (TCelula *)malloc(sizeof(TCelula));
    aux->item = *item;
    Lista->ultimo->prox = aux;
    Lista->ultimo = aux;
}

/* Imprime o par ordenado (qtde,idDoc) */
void imprimeLista (TLista *Lista) {
    TCelula *aux;
    aux = Lista->primeiro->prox;

    while (aux != NULL)
    {
        if(aux->prox == NULL)
            printf("(%d,%d)\n", aux->item.qtde, aux->item.idDoc);
        /* Imprime "->" no final do par ordenado */
        else
            printf("(%d,%d) -> ", aux->item.qtde, aux->item.idDoc);

        aux = aux->prox;
    }
}
