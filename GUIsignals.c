#include "GUIsignals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//inside main_box signals
void pesquisaAlterada(GtkSearchEntry *entry, Widgets *widgets){
	const gchar* text=	gtk_entry_get_text(GTK_ENTRY(entry));
	if(strcmp((char*)text,"") != 0)
		AutoPreenchimentoTST(raiz,0,(char*)text);
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
	exit(0);
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


