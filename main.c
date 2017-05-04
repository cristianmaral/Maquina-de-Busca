#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GUIsignals.h"
#include "TST.h"
int main(int argc, char *argv[]){
	inicializaTST(&raiz);
	insereTST(&raiz,"cristian");
	insereTST(&raiz,"cavalo");
	insereTST(&raiz,"coveiro");
	insereTST(&raiz,"armario");
	insereTST(&raiz,"arnaldo");
	/*
	char c[MAXTAM];
	scanf("%s",c);
	AutoPreenchimentoTST(raiz,0,c);
	*/
	gtkMain(argc,argv);
	return 0;
}
