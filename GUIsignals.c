#include "GUIsignals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//inside main_box signals
void pesquisaAlterada(GtkSearchEntry *entry, Widgets *widgets){
	TLista palavras;
	inicializaLista(&palavras);

	TCelula *itercel;
	int i,j = 0;
	const gchar* text = gtk_entry_get_text(GTK_ENTRY(entry));
	gtk_list_store_clear(widgets->main_lista_completion);
	if(strcmp((char*)text,"") != 0){
		for (i = 0; text[i] != '\0'; i++) {
			if(text[i] == ' '){ 	//capturar começo da ultima palavra
				j = i+1;
			}
		}
		AutoPreenchimentoTST(raiz,0,((char*)text) + j,&palavras);
		for (itercel = palavras.primeiro->prox; itercel != NULL ; itercel = itercel->prox) {
			gtk_list_store_append(widgets->main_lista_completion, widgets->iter);
			gtk_list_store_set(widgets->main_lista_completion, widgets->iter,0,(const gchar*)itercel->palavra,-1);
		}
		imprimeListaDePalavras(&palavras);
	}
	gtk_entry_completion_complete(widgets->entrycompletion);
}
void goMainWindow (GtkButton *button, Widgets *widgets){
	gtk_stack_set_visible_child(widgets->PilhaDeJanelas,GTK_WIDGET(widgets->main_box));
}
void openAboutWindow (GtkButton *button, Widgets *widgets){
	gtk_dialog_run(GTK_DIALOG(widgets->AboutWindow));
	gtk_widget_hide(GTK_WIDGET(widgets->AboutWindow));
}
void goSearchWindow (GtkButton *button, Widgets *widgets){
	gtk_stack_set_visible_child(widgets->PilhaDeJanelas,GTK_WIDGET(widgets->search_box));
}
void filtrarExtensao (GtkButton *button, Widgets *widgets){
	printf("Apertou\n");
}
void cancelarSelecao (GtkButton *button, Widgets *widgets){
	printf("Apertou\n");
}
void selecionarArquivo (GtkButton *button, Widgets *widgets){
	printf("Apertou\n");
}
void closeProgram (GtkButton *button, Widgets *widgets){
	gtk_main_quit();
}
void addFile (GtkButton *button, Widgets *widgets){
	printf("Apertou\n");
}
void goFilesWindow (GtkButton *button, Widgets *widgets){
	gtk_stack_set_visible_child(widgets->PilhaDeJanelas,GTK_WIDGET(widgets->files_box));
}
void buildIndex (GtkButton *button, Widgets *widgets){
	gtk_widget_show(GTK_WIDGET(widgets->LoadingWindow));
}
void goIndexWindow (GtkButton *button, Widgets *widgets){
	gtk_stack_set_visible_child(widgets->PilhaDeJanelas,GTK_WIDGET(widgets->index_box));
}
void cancelBuildIndex (GtkButton *button, Widgets *widgets){
	gtk_widget_hide(GTK_WIDGET(widgets->LoadingWindow));
}


