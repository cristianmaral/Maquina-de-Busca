#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GUIsignals.h"
#include "TST.h"

int main(int argc, char *argv[]){
	inicializaPatricia(&raizPat); /* Inicializando a Patricia */
	inicializaTST(&raizTST); /* Inicializando a TST */
	inicializaLista(&ListaArquivos); /* Inicializando a Lista de Arquivos */
	inicializaLista(&palavras); /* Inicializando a Lista de palavras de busca */

	gtkMain(argc,argv);
	FechaArquivos ();
	return 0;
}
