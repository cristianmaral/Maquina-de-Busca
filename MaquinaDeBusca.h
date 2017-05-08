#ifndef MAQUINADEBUSCA_H_INCLUDED
#define MAQUINADEBUSCA_H_INCLUDED

#include "Patricia.h"
#include "TST.h"
#include "ListaEncadeadaDeArquivos.h"
#include <gtk/gtk.h>

TLista ListaArquivos;
TipoPatNo *raizPat;
TipoTSTNo *raizTST;
gboolean cancela;

char* strlower (char *str);
void RetiraArquivo (char *nome_arq);
void AdicionaArquivo (char* nome_arq);
void FechaArquivos ();
void CalculaPesos (TipoPatNo *t, int N);
float RetornaPesoTermo (char *k, TipoPatNo *t, int idDoc);
void CalculaTermosDistintos (TipoPatNo *no, TCelula *arq, int idDoc);
void CalculaRelevancia (TipoPatNo *no, char **palavras, int n_termos);
void MontaIndiceInvertido();
void BuscaTermos (TipoPatNo *no, char *string);

#endif // MAQUINADEBUSCA_H_INCLUDED
