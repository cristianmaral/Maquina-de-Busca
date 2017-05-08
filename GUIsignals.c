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
	TCelula *celula;
	char *saida, *entrada = (char*)gtk_entry_get_text(GTK_ENTRY(widgets->main_searchentry)), *char_idDoc = (char*)malloc(sizeof(char)*5);
	updateSearchTitle(entrada,&saida);
	gtk_label_set_text(widgets->search_title,saida);
	BuscaTermos(raizPat,entrada);
	gtk_stack_set_visible_child(widgets->PilhaDeJanelas,GTK_WIDGET(widgets->search_box));
	/* Imprime os documentos por ordem decrescente de relevância */
	gtk_list_store_clear(widgets->search_lista_dados);
	for (celula = ListaArquivos->primeiro->prox; celula != NULL ; celula = celula->prox) {
		gtk_list_store_append(widgets->search_lista_dados, widgets->iter);
		sprintf(char_idDoc,"%d",(celula->item.arq.idDoc));
		gtk_list_store_set(widgets->search_lista_dados, widgets->iter,0,(const gchar*)char_idDoc,1,(const gchar*)celula->item.arq.nome_arquivo,-1);
	}
	while (celula != NULL) {
		printf("Texto %d (%s)\n", celula->item.arq.idDoc, celula->item.arq.nome_arquivo);
		celula = celula->prox;
	}

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
	GValue nome = {0,}; 
	GtkTreeIter iter;

		//Há algo selecionado
	if(gtk_tree_selection_get_selected(widgets->files_treeview_selection,NULL,&iter)){
		gtk_tree_model_get_value(GTK_TREE_MODEL(widgets->files_lista_dados),&iter,1,&nome);
		RetiraArquivo(strdup((const char*)g_value_get_string(&nome)));
		gtk_list_store_remove(widgets->files_lista_dados,&iter);
		updateFileTitle(widgets);
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
	char *texto = (char*)malloc(sizeof(char)*30*100); //30 caracteres por palavra distinta, inferindo que existem 100 palavras distintas
	imprimePatricia(raizPat,texto);
	gtk_text_buffer_set_text(buffer,(const gchar*)texto,-1);
	gtk_text_view_set_buffer(widgets->index_textviewer,buffer);
	gtk_stack_set_visible_child(widgets->PilhaDeJanelas,GTK_WIDGET(widgets->index_box));
}
void cancelBuildIndex (GtkButton *button, Widgets *widgets){
	cancela = TRUE;
	gtk_widget_hide(GTK_WIDGET(widgets->LoadingWindow));
}
void updateSearchTitle (char *entrada, char **saida){
    char aux[50]; /* String auxiliar para guardar temporariamente cada palavra de busca separadamente */
    char *palavras[30]; /* Vetor de Strings - Consideramos o máximo de 30 palavras de busca */
    char c; /* Caractere auxiliar para ler caractere por caractere da string que contém todas as palavras de busca */
    int i = 0; /* Indica a posição onde c deve ser armazenado na string aux */
    int j = 0; /* Indica a posição onde a string aux deve ser armazenada no vetor palavras e indica a quantidade de termos de busca */
    int cont = 0; /* Indica a posição atual da string que contém todas as palavras de busca */
    *saida = (char*)malloc(sizeof(char)*70); //70 para permitir a que exceda em 25 caracteres antes do processo de redimensionar a string
    strlwr(entrada); /* Passa a string inteira para minúscula */
    (*saida)[0] = '\0';

    /* Enquanto não chegar no final da string */
    while (entrada[cont] != '\0') {
        c = entrada[cont];
        if (c != ' ') { /* Enquanto o caractere não for um espaço, atribui-se ele à posição i da string aux */
            aux[i] = c;
            i++;
        }
        /* Indica o final de uma palavra */
        else{
            aux[i] = '\0';
            i = 0; /* Para armazenar a primeira letra da proxima palavra na posição 0 da string aux */
            palavras[j] = strdup(aux); /* Insere aux na posição j do vetor de palavras */
            j++; /* Incrementa o j */
        }
        cont++; /* Passa para a próxima posição da string */
    }
    /* Tratando a última palavra de busca */
    aux[i] = entrada[cont];
    palavras[j] = strdup(aux); /* Atribui a string auxiliar à j-ésima string do vetor de strings */
    j++;
    /* Insere os termos de busca na string de saída */
    for (i=0; i<j && strlen(*saida) <= 45; i++) {
        if (i == 0)
            strcpy(*saida, palavras[i]);
	else
            strcat(*saida, palavras[i]);
        if (i < j - 1) 
            strcat(*saida, ", ");
    }
    if (strlen(*saida) > 45) {
        i = 44;
        c = (*saida)[i];
        while (c != ',') {
            i--;
            c = (*saida)[i];
            if (c == ',') {
                (*saida)[i] = '.';
		(*saida)[++i] = '.';
		(*saida)[++i] = '.';
                (*saida)[++i] = '\0';
            }
        }
    }
    *saida = (char*)realloc((*saida),sizeof(char)*(i+1));
    printf("%s\n",*saida);
}
