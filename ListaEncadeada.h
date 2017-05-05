#ifndef LISTAENCADEADA_H_INCLUDED
#define LISTAENCADEADA_H_INCLUDED

typedef struct {
	int qtde;
	int idDoc;
	float peso;
} TItem;

typedef struct Celula {
	union{
		char* palavra;
		TItem item;
	};
	struct Celula *prox;
} TCelula;

typedef struct {
	TCelula *primeiro;
	TCelula *ultimo;
	int tamanho;
} TLista;

void inicializaLista (TLista *Lista);
void insereLista (TLista *Lista, TItem *item);
void insereCelulaEmLista (TLista *Lista, TCelula *celula);
void imprimeLista(TLista *Lista);
void imprimeListaDePalavras (TLista *Lista);
#endif // LISTAENCADEADA_H_INCLUDED
