#include "ListaEncadeada.h"
#include <stdlib.h>

/* Inicializa uma lista - já alocando a célula cabeça */
void inicializaLista (TLista *Lista) {
    Lista->primeiro = Lista->ultimo = (TCelula *)malloc(sizeof(TCelula));
    Lista->primeiro->prox = NULL;
    Lista->tamanho = 0;
}

/* Função para reinicializar a lista */
void reinicializaLista (TLista *Lista) {
	TCelula *iterator;
	if(Lista != NULL){
		iterator = Lista->primeiro->prox;
		while (iterator != NULL) {
			free(Lista->primeiro);
			Lista->primeiro = iterator;
			iterator = iterator->prox;
		}
		free(Lista->ultimo);
	}
	inicializaLista(Lista);
}

/* Insere uma celula na lista */
void insereCelulaEmLista (TLista *Lista, TCelula *celula) {
    Lista->ultimo->prox = celula;
    Lista->ultimo = celula;
    Lista->tamanho++;
    celula->prox = NULL;
}

/* Insere um item na lista */
void insereLista (TLista *Lista, TItem *item) {
    TCelula *aux;
    aux = (TCelula *)malloc(sizeof(TCelula));
    aux->item = *item;
    Lista->ultimo->prox = aux;
    Lista->ultimo = aux;
    Lista->tamanho++;
    aux->prox = NULL;
}

/* Imprime o par ordenado (qtde,idDoc) */
void imprimeLista (TLista *Lista, char* saida) {
    TCelula *aux;
    aux = Lista->primeiro->prox;

    while (aux != NULL) {
        if(aux->prox == NULL)
            sprintf(saida,"%s<%d,%d>\n", saida, aux->item.termo.qtde, aux->item.termo.idDoc);
        /* Imprime "->" no final do par ordenado */
        else
            sprintf(saida,"%s<%d,%d> -> ", saida, aux->item.termo.qtde, aux->item.termo.idDoc);

        aux = aux->prox;
    }
}

/* Ordena a Lista de Arquivos de acordo com a relevância - decrescentemente */
void OrdenaListaArquivos (TLista *ListaArquivos) {
    TCelula *aux, *aux2;
    TItem item;

    aux = ListaArquivos->primeiro->prox;
    if(aux == NULL || aux->prox == NULL)
        return;

    while(aux != NULL) {
        aux2 = aux->prox;
        while(aux2 != NULL) {
            if(aux2->item.arq.relevancia > aux->item.arq.relevancia) {
                item = aux->item;
                aux->item = aux2->item;
                aux2->item = item;
            }
            aux2 = aux2->prox;
        }
        aux = aux->prox;
    }
}
