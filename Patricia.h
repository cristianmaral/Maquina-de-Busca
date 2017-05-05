#ifndef MAQUINADEBUSCA_H_INCLUDED
#define MAQUINADEBUSCA_H_INCLUDED

#include "Patricia.h"
#include "TST.h"
#include <stdio.h>

char *strlwr (char *str);
void AdicionaArquivo (TLista *ListaArquivos);
void FechaArquivos (TLista *ListaArquivos);
void CalculaPesos (TipoPatNo *t, int N);
void CalculaTermosDistintos (TipoPatNo *no, TCelula *arq, int idDoc);
void MontaIndiceInvertido (TLista *ListaArquivos);

#endif // MAQUINADEBUSCA_H_INCLUDED
