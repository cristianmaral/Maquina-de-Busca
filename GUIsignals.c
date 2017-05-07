#include "GUIsignals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//inside main_box signals
void pesquisaAlterada(GtkSearchEntry *entry, Widgets *widgets){
	reinicializaLista(&palavras);

	TCelula *itercel;
	int i,j = 0;
	const gchar* text = gtk_entry_get_text(GTK_ENTRY(entry));
	gtk_list_store_clear(widgets->main_lista_completion);
	if(strcmp((char*)text,"") != 0){
		palavras.tamanho = 1;
		for (i = 0; text[i] != '\0'; i++) {
			if(text[i] == ' '){ 	//capturar começo da ultima palavra
				j = i+1;
				palavras.tamanho++;
			}
		}
		AutoPreenchimentoTST(raizTST,0,((char*)text) + j,&palavras);
		for (itercel = palavras.primeiro->prox; itercel != NULL ; itercel = itercel->prox) {
			gtk_list_store_append(widgets->main_lista_completion, widgets->iter);
			gtk_list_store_set(widgets->main_lista_completion, widgets->iter,0,(const gchar*)itercel->item.palavra,-1);
		}
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
	char *texto = (char*)gtk_entry_get_text(GTK_ENTRY(widgets->main_searchentry));
	/*
	int i, j, pos = 0;
	gchar *label = (gchar*)malloc(sizeof(gchar)*palavras.tamanho*20);
	TCelula *iterator = palavras.primeiro->prox;
	printf("%d\n",palavras.tamanho);
	for (i = 0; i < palavras.tamanho; i++) {
		for (j = 0; iterator->item.palavra[j] != '\0'; j++) {
			label[pos++] = iterator->item.palavra[j];
		}
	}
	gtk_label_set_text(widgets->search_title, label);
	*/
	BuscaTermos(raizPat,texto);
	gtk_stack_set_visible_child(widgets->PilhaDeJanelas,GTK_WIDGET(widgets->search_box));

}
void closeProgram (GtkButton *button, Widgets *widgets){
	gtk_main_quit();
}
void splitPath(gchar *filepath,gchar **filename){
	int i, j;
	for (i = 0; filepath[i] != '\0'; i++) {
		if(filepath[i] == '/'){ 	//capturar começo do nome do arquivo
			j = i+1;
		}
	}
	*filename = filepath + j;
	
}
void updateFileTitle(Widgets *widgets){
	gint n = gtk_tree_model_iter_n_children(GTK_TREE_MODEL(widgets->files_lista_dados),NULL);
	gchar *str = (gchar*)gtk_label_get_text(widgets->files_title);
	gchar *label = (gchar*)malloc(sizeof(str)+sizeof(gchar)*3);
	sprintf(label,"%d%s",n,str+1);
	gtk_label_set_text(widgets->files_title, label);
}
void updateIndexTitle(Widgets *widgets){
	gint n_files = gtk_tree_model_iter_n_children(GTK_TREE_MODEL(widgets->files_lista_dados),NULL);
	gchar *label = (gchar*)malloc(sizeof(gchar)*22); // 18 chars para "Total de Arquivos ", 4 chars para o numero de arquivos
	sprintf(label,"Total de Arquivos %d",n_files);
	gtk_label_set_text(widgets->index_title, label);
}
void remFile (GtkButton *button, Widgets *widgets){
	if(gtk_tree_selection_get_selected(widgets->files_treeview_selection,NULL,widgets->iter)){
		gtk_list_store_remove(widgets->files_lista_dados,widgets->iter);
		updateFileTitle(widgets);
		//Há algo selecionado
		gtk_widget_set_sensitive(GTK_WIDGET(widgets->index_build_button),TRUE);
		return;
	}
}
void addFile (GtkButton *button, Widgets *widgets){
	gchar *filename,*filepath = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(widgets->files_filechooserbutton));
	if(filepath == NULL) return; //Nao Há arquivo selecionado
	splitPath(filepath,&filename);
	printf("%s em %s\n",filename,filepath);
	gtk_list_store_append(widgets->files_lista_dados, widgets->iter);
	gtk_list_store_set(widgets->files_lista_dados, widgets->iter,0,filename,1,filepath,-1);
	updateFileTitle(widgets);
	AdicionaArquivo (filepath);
	gtk_widget_set_sensitive(GTK_WIDGET(widgets->index_build_button),TRUE);

}
void goFilesWindow (GtkButton *button, Widgets *widgets){
	updateFileTitle(widgets);
	gtk_stack_set_visible_child(widgets->PilhaDeJanelas,GTK_WIDGET(widgets->files_box));
}
void buildIndex (GtkButton *button, Widgets *widgets){
	gtk_widget_show(GTK_WIDGET(widgets->LoadingWindow));
	MontaIndiceInvertido();
	gtk_widget_hide(GTK_WIDGET(widgets->LoadingWindow));
	gtk_widget_set_sensitive(GTK_WIDGET(widgets->index_build_button),FALSE);
	gtk_widget_set_sensitive(GTK_WIDGET(widgets->index_visualize_button),TRUE);
	gtk_widget_set_sensitive(GTK_WIDGET(widgets->main_searchbutton),TRUE);
	updateIndexTitle(widgets);
}
void goIndexWindow (GtkButton *button, Widgets *widgets){
	GtkTextBuffer *buffer = gtk_text_view_get_buffer(widgets->index_textviewer);
	char *texto = (char*)malloc(sizeof(char)*30*100); //30 caracteres por palavra distinta, inferindo que palavras distintas sao 100
	imprimePatricia(raizPat,texto);
	gtk_text_buffer_set_text(buffer,(const gchar*)texto,-1);
	gtk_text_view_set_buffer(widgets->index_textviewer,buffer);
	gtk_stack_set_visible_child(widgets->PilhaDeJanelas,GTK_WIDGET(widgets->index_box));
}
void cancelBuildIndex (GtkButton *button, Widgets *widgets){
	cancela = TRUE;
	gtk_widget_hide(GTK_WIDGET(widgets->LoadingWindow));
}
