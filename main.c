#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "GUIsignals.h"
#include "TST.h"

int main(){
	No *raiz;
	char c[MAX];
	scanf("%s",c);
	inicializaTST(&raiz);
	insereTST(&raiz,"cristian");
	insereTST(&raiz,"cavalo");
	insereTST(&raiz,"coveiro");
	insereTST(&raiz,"armario");
	insereTST(&raiz,"arnaldo");
	AutoPreenchimentoTST(raiz,0,c);
	//gtkMain(argc,argv);
	return 0;
}
