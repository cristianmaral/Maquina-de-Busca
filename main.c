#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GUIsignals.h"
#include "TST.h"
int main(int argc, char *argv[]){
	inicializaPatricia(&raizPat); /* Inicializando a Patricia */
	inicializaTST(&raizTST); /* Inicializando a TST */
	ListaArquivos = (TLista*)malloc(sizeof(TLista));
	inicializaLista(ListaArquivos);
	inicializaLista(&palavras);
	/*
	inicializaTST(&raiz);
	insereTST(&raiz,"cristian");
	insereTST(&raiz,"cavalo");
	insereTST(&raiz,"coveiro");
	insereTST(&raiz,"armario");
	insereTST(&raiz,"arnaldo");
	*/
	/*
	char c[MAXTAM];
	scanf("%s",c);
	AutoPreenchimentoTST(raiz,0,c);
	*/
	gtkMain(argc,argv);
	FechaArquivos ();
	return 0;
}
