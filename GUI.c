#include "GUI.h"
void gtkMain(int argc, char *argv[]){
	GtkBuilder *gtkBuilder;
	Widgets widgets;
	
	gtk_init(&argc, &argv);
	
	gtkBuilder = gtk_builder_new();
	gtk_builder_add_from_file(gtkBuilder, "TelaProgramaNovoGoogle.glade", NULL);
	widgets.MainWindow = GTK_WINDOW(gtk_builder_get_object(gtkBuilder, "MainWindow"));
	widgets.PilhaDeJanelas = GTK_STACK(gtk_builder_get_object(gtkBuilder, "PilhaDeJanelas"));
	widgets.main_box = GTK_BOX(gtk_builder_get_object(gtkBuilder, "main_box"));
	widgets.files_box = GTK_BOX(gtk_builder_get_object(gtkBuilder, "files_box"));
	widgets.index_box = GTK_BOX(gtk_builder_get_object(gtkBuilder, "index_box"));
	widgets.search_box = GTK_BOX(gtk_builder_get_object(gtkBuilder, "search_box"));
	widgets.main_header = GTK_HEADER_BAR(gtk_builder_get_object(gtkBuilder, "main_header"));
		//begin main_header
	widgets.main_aboutbutton = GTK_BUTTON(gtk_builder_get_object(gtkBuilder, "main_aboutbutton"));
	widgets.main_closebutton = GTK_BUTTON(gtk_builder_get_object(gtkBuilder, "main_closebutton"));
	widgets.main_closebutton_image = GTK_IMAGE(gtk_builder_get_object(gtkBuilder, "main_closebutton_image"));
		//end main_header
	widgets.main_innerupper_searchbox = GTK_BOX(gtk_builder_get_object(gtkBuilder, "main_innerupper_searchbox"));
		//begin main_innerupper_seachbox
	widgets.main_searchentry = GTK_SEARCH_ENTRY(gtk_builder_get_object(gtkBuilder, "main_searchentry"));
	widgets.main_searchbutton = GTK_BUTTON(gtk_builder_get_object(gtkBuilder, "main_searchbutton"));
		//end main_innerupper_seachbox
	widgets.main_innerlower_buttonbox = GTK_BOX(gtk_builder_get_object(gtkBuilder, "main_innerlower_buttonbox"));
		//begin main_innerlower_buttonbox
	widgets.index_visualize_button = GTK_BUTTON(gtk_builder_get_object(gtkBuilder, "index_visualize_button"));
	widgets.index_build_button = GTK_BUTTON(gtk_builder_get_object(gtkBuilder, "index_build_button"));
	widgets.file_manage_button = GTK_BUTTON(gtk_builder_get_object(gtkBuilder, "file_manage_button"));
		//end main_innerlower_buttonbox
	//inside search_box
	widgets.seach_header = GTK_HEADER_BAR(gtk_builder_get_object(gtkBuilder, "seach_header"));
		//begin search_header
	widgets.search_backbutton = GTK_BUTTON(gtk_builder_get_object(gtkBuilder, "search_backbutton"));
	widgets.search_closebutton = GTK_BUTTON(gtk_builder_get_object(gtkBuilder, "search_closebutton"));
	widgets.search_title = GTK_LABEL(gtk_builder_get_object(gtkBuilder, "search_title"));
	widgets.search_closebutton_image = GTK_IMAGE(gtk_builder_get_object(gtkBuilder, "search_closebutton_image"));
		//end search_header
	widgets.search_inner_box = GTK_SCROLLED_WINDOW(gtk_builder_get_object(gtkBuilder, "search_inner_box"));
		//begin search_inner_box
	widgets.search_lista_viewer = GTK_TREE_VIEW(gtk_builder_get_object(gtkBuilder, "search_lista_viewer"));
			//begin search_lista_viewer
	widgets.search_treeview_selection = GTK_TREE_SELECTION(gtk_builder_get_object(gtkBuilder, "search_treeview_selection"));
	widgets.NomeDocumento = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(gtkBuilder, "NomeDocumento"));
	widgets.NRecorrencias = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(gtkBuilder, "NRecorrencias"));
			//end search_lista_viewer
		//end search_inner_box
	//inside index_box
	widgets.index_header = GTK_HEADER_BAR(gtk_builder_get_object(gtkBuilder, "index_header"));
		//begin index_header
	widgets.index_title = GTK_LABEL(gtk_builder_get_object(gtkBuilder, "index_title"));
	widgets.index_backbutton = GTK_BUTTON(gtk_builder_get_object(gtkBuilder, "index_backbutton"));
	widgets.index_pagedownbutton = GTK_BUTTON(gtk_builder_get_object(gtkBuilder, "index_pagedownbutton"));
	widgets.index_pageupbutton = GTK_BUTTON(gtk_builder_get_object(gtkBuilder, "index_pageupbutton"));
	widgets.index_closebutton = GTK_BUTTON(gtk_builder_get_object(gtkBuilder, "index_closebutton"));
	widgets.index_pagedownbutton_image = GTK_IMAGE(gtk_builder_get_object(gtkBuilder, "index_pagedownbutton_image"));
	widgets.index_pageupbutton_image = GTK_IMAGE(gtk_builder_get_object(gtkBuilder, "index_pageupbutton_image"));
	widgets.index_closebutton_image = GTK_IMAGE(gtk_builder_get_object(gtkBuilder, "index_closebutton_image"));
		//end index_header
	widgets.index_inner_box = GTK_SCROLLED_WINDOW(gtk_builder_get_object(gtkBuilder, "index_inner_box"));
		//begin index_inner_box
	widgets.index_lista_viewer = GTK_TREE_VIEW(gtk_builder_get_object(gtkBuilder, "index_lista_viewer"));
			//begin index_lista_viewer
	widgets.index_treeview_selection = GTK_TREE_SELECTION(gtk_builder_get_object(gtkBuilder, "index_treeview_selection"));
	widgets.index_lista_colunaPalavra = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(gtkBuilder, "index_lista_colunaPalavra"));
	widgets.index_lista_colunaArquivo1 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(gtkBuilder, "index_lista_colunaArquivo1"));
	widgets.index_lista_colunaArquivo2 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(gtkBuilder, "index_lista_colunaArquivo2"));
	widgets.index_lista_colunaArquivo3 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(gtkBuilder, "index_lista_colunaArquivo3"));
			//end index_lista_viewer
		//end index_inner_box
	//inside files_box
	widgets.files_header = GTK_HEADER_BAR(gtk_builder_get_object(gtkBuilder, "files_header"));
		//begin files_header
	widgets.files_backbutton = GTK_BUTTON(gtk_builder_get_object(gtkBuilder, "files_backbutton"));
	widgets.files_closebutton = GTK_BUTTON(gtk_builder_get_object(gtkBuilder, "files_closebutton"));
	widgets.files_closebutton_image = GTK_IMAGE(gtk_builder_get_object(gtkBuilder, "files_closebutton_image"));
	widgets.files_title = GTK_LABEL(gtk_builder_get_object(gtkBuilder, "files_title"));
		//end files_header
	widgets.files_innerupper_box = GTK_SCROLLED_WINDOW(gtk_builder_get_object(gtkBuilder, "files_innerupper_box"));
		//begin files_innerupper_box
	widgets.files_lista_viewer = GTK_TREE_VIEW(gtk_builder_get_object(gtkBuilder, "files_lista_viewer"));
			//begin files_lista_viewer
	widgets.files_treeview_selection = GTK_TREE_SELECTION(gtk_builder_get_object(gtkBuilder, "files_treeview_selection"));
	widgets.NomeDoArquivo = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(gtkBuilder, "NomeDoArquivo"));
	widgets.CaminhoDoArquivo = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(gtkBuilder, "CaminhoDoArquivo"));
	widgets.Remover = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(gtkBuilder, "Remover"));
			//end files_lista_viewer
		//end files_innerupper_box
	widgets.files_innerlower_box = GTK_BOX(gtk_builder_get_object(gtkBuilder, "files_innerlower_box"));
		//begin files_innerlower_box
	widgets.files_filechooserbutton = GTK_FILE_CHOOSER_BUTTON(gtk_builder_get_object(gtkBuilder, "files_filechooserbutton"));
	widgets.files_addbutton = GTK_BUTTON(gtk_builder_get_object(gtkBuilder, "files_addbutton"));
		//end files_innerlower_box
	//Helper Widgets
	widgets.files_scrollbar_config = GTK_ADJUSTMENT(gtk_builder_get_object(gtkBuilder, "files_scrollbar_config"));
	widgets.index_scrollbar_config = GTK_ADJUSTMENT(gtk_builder_get_object(gtkBuilder, "index_scrollbar_config"));
	widgets.search_scrollbar_config = GTK_ADJUSTMENT(gtk_builder_get_object(gtkBuilder, "search_scrollbar_config"));

	widgets.agrupamento_tamanho_telas = GTK_SIZE_GROUP(gtk_builder_get_object(gtkBuilder, "agrupamento_tamanho_telas"));
	widgets.entrycompletion = GTK_ENTRY_COMPLETION(gtk_builder_get_object(gtkBuilder, "entrycompletion"));
	widgets.main_lista_completion = GTK_LIST_STORE(gtk_builder_get_object(gtkBuilder, "main_lista_completion"));
	widgets.files_lista_dados = GTK_LIST_STORE(gtk_builder_get_object(gtkBuilder, "files_lista_dados"));
	widgets.index_lista_dados = GTK_LIST_STORE(gtk_builder_get_object(gtkBuilder, "index_lista_dados"));
	widgets.search_lista_dados = GTK_LIST_STORE(gtk_builder_get_object(gtkBuilder, "search_lista_dados"));
	widgets.selecionador_combobox_extensao_dados = GTK_LIST_STORE(gtk_builder_get_object(gtkBuilder, "selecionador_combobox_extensao_dados"));
	widgets.SelecionadorDeArquivo = GTK_FILE_CHOOSER_DIALOG(gtk_builder_get_object(gtkBuilder, "SelecionadorDeArquivo"));
		//begin SelecionadorDeArquivo
	widgets.selecionador_box = GTK_BOX(gtk_builder_get_object(gtkBuilder, "selecionador_box"));
			//begin selecionador_box
	widgets.selecionador_buttonbox = GTK_BUTTON_BOX(gtk_builder_get_object(gtkBuilder, "selecionador_buttonbox"));
				//begin selecionador_buttonbox
	widgets.selecionador_selectbutton = GTK_BUTTON(gtk_builder_get_object(gtkBuilder, "selecionador_selectbutton"));
	widgets.selecionador_cancelbutton = GTK_BUTTON(gtk_builder_get_object(gtkBuilder, "selecionador_cancelbutton"));
				//end selecionador_buttonbox
	widgets.selecionador_combobox_extensao = GTK_COMBO_BOX(gtk_builder_get_object(gtkBuilder, "selecionador_combobox_extensao"));
				//begin selecionador_combobox_extensao
	widgets.Descricao = GTK_CELL_RENDERER_TEXT(gtk_builder_get_object(gtkBuilder, "Descricao"));
	widgets.ExtensaoSuportada = GTK_CELL_RENDERER_TEXT(gtk_builder_get_object(gtkBuilder, "ExtensaoSuportada"));
				//end selecionador_combobox_extensao
			//end selecionador_box
		//end SelecionadorDeArquivo
	widgets.LoadingWindow = GTK_WINDOW(gtk_builder_get_object(gtkBuilder, "LoadingWindow"));
		//begin LoadingWindow
	widgets.loading_box = GTK_BOX(gtk_builder_get_object(gtkBuilder, "loading_box"));
			//begin loading_box
	widgets.loading_label = GTK_LABEL(gtk_builder_get_object(gtkBuilder, "loading_label"));
	widgets.loading_image = GTK_SPINNER(gtk_builder_get_object(gtkBuilder, "loading_image"));
	widgets.loading_cancelbutton = GTK_BUTTON(gtk_builder_get_object(gtkBuilder, "loading_cancelbutton"));
			//end loading_box
		//end LoadingWindow
	widgets.AboutWindow = GTK_ABOUT_DIALOG(gtk_builder_get_object(gtkBuilder, "AboutWindow"));
		//begin AboutWindow
	widgets.about_box = GTK_BOX(gtk_builder_get_object(gtkBuilder, "about_box"));
			//begin about_box
	widgets.about_buttonbox = GTK_BUTTON_BOX(gtk_builder_get_object(gtkBuilder, "about_buttonbox"));
			//end about_box
		//end AboutWindow
	
	

	/* Fazendo ligações com as entradas do glade */
	GtkTreeIter iter;
	widgets.iter = &iter;
	
	/* Conectando os sinais */
	gtk_builder_connect_signals(gtkBuilder, &widgets);
	
	/* Destruindo o builder, já que não precisamos mais dele */
	g_object_unref(G_OBJECT(gtkBuilder));

	gtk_entry_completion_set_match_func(widgets.entrycompletion,func,NULL,NULL);
	gtk_entry_completion_set_minimum_key_length(widgets.entrycompletion,0);
	
	/* Mostra a interface do glade */
	gtk_widget_show(GTK_WIDGET(widgets.MainWindow));
	
	gtk_main();
}
gboolean func(GtkEntryCompletion *completion,const gchar *key,GtkTreeIter *iter,gpointer user_data){
	return TRUE;
}
