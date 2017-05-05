#ifndef MAQUINADEBUSCA_H_INCLUDED
#define MAQUINADEBUSCA_H_INCLUDED

#include "Patricia.h"
#include "TST.h"

char *strlwr (char *str);
void AdicionaArquivo (TLista *ListaArquivos);
void FechaArquivos (TLista *ListaArquivos);
void CalculaPesos (TipoPatNo *t, int N);
void CalculaTermosDistintos (TipoPatNo *no, TCelula *arq, int idDoc);
void CalculaRelevancia (TipoPatNo *no, TLista *ListaArquivos, char **palavras, int n_termos);
void MontaIndiceInvertido (TLista *ListaArquivos, char *aux);
void BuscaTermos (TipoPatNo *no, TLista *ListaArquivos, char *string);



#endif // MAQUINADEBUSCA_H_INCLUDED
