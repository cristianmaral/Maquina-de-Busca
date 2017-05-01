#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>


typedef struct {
	GtkWindow *MainWindow;
	GtkStack *PilhaDeJanelas;
	GtkBox *main_box, *files_box, *index_box, *seachbox;
	//inside main_box
	GtkHeaderBar *main_header;
		//begin main_header
	GtkButton *main_aboutbutton, *main_closebutton;
	GtkImage *main_closebutton_image;
		//end main_header
	GtkBox *main_innerupper_searchbox;
		//begin main_innerupper_seachbox
	GtkSearchEntry *main_searchentry;
	GtkButton *main_searchbutton;
		//end main_innerupper_seachbox
	GtkBox *main_innerlower_buttonbox;
		//begin main_innerlower_buttonbox
	GtkButton *index_visualize_button, *index_build_button, *file_manage_button;
		//end main_innerlower_buttonbox
	//inside search_box
	GtkHeaderBar *seach_header;
		//begin search_header
	GtkButton *search_backbutton,*search_closebutton;
	GtkLabel *search_title;
	GtkImage *search_closebutton_image;
		//end search_header
	GtkBox *search_inner_box;
		//begin search_inner_box
	GtkTreeView *search_lista_viewer;
			//begin search_lista_viewer
	GtkTreeSelection *search_treeview_selection;
	GtkTreeViewColumn *NomeDocumento, *NRecorrencias;
			//end search_lista_viewer
	GtkScrollbar *search_scrollbar;
		//end search_inner_box
	//inside index_box
	GtkHeaderBar *index_header;
		//begin index_header
	GtkLabel *index_title;
	GtkButton *index_backbutton, *index_pagedownbutton, *index_pageupbutton, *index_closebutton;
	GtkImage *index_pagedownbutton_image, *index_pageupbutton_image, *index_closebutton_image;
		//end index_header
	GtkBox *index_inner_box;
		//begin index_inner_box
	GtkTreeView *index_lista_viewer;
			//begin index_lista_viewer
	GtkTreeSelection *index_treeview_selection;
	GtkTreeViewColumn *index_lista_colunaPalavra,*index_lista_colunaArquivo1,*index_lista_colunaArquivo2,*index_lista_colunaArquivo3;
			//end index_lista_viewer
	GtkScrollbar *index_scrollbar;
		//end index_inner_box
	//inside files_box
	GtkHeaderBar *files_header;
		//begin files_header
	GtkButton *files_backbutton, *files_closebutton;
	GtkImage *files_closebutton_image;
	GtkLabel *files_title;
		//end files_header
	GtkBox *files_innerupper_box;
		//begin files_innerupper_box
	GtkTreeView *files_lista_viewer;
			//begin files_lista_viewer
	GtkTreeSelection *files_treeview_selection;
	GtkTreeViewColumn *NomeDoArquivo, *CaminhoDoArquivo, *Remover;
			//end files_lista_viewer
	GtkScrollbar *files_scrollbar;
		//end files_innerupper_box
	GtkBox *files_innerlower_box;
		//begin files_innerlower_box
	GtkFileChooserButton *files_filechooserbutton;
	GtkButton *files_addbutton;
		//end files_innerlower_box
	//Helper Widgets
	GtkListStore *files_lista_dados, *index_lista_dados, *search_lista_dados, *selecionador_combobox_extensao_dados;
	GtkFileChooserDialog *SelecionadorDeArquivo;
		//begin SelecionadorDeArquivo
	GtkBox *selecionador_box;
			//begin selecionador_box
	GtkButtonBox *selecionador_buttonbox;
				//begin selecionador_buttonbox
	GtkButton *selecionador_selectbutton, *selecionador_cancelbutton;
				//end selecionador_buttonbox
	GtkComboBox *selecionador_combobox_extensao;
				//begin selecionador_combobox_extensao
	GtkCellRendererText *Descricao, *ExtensaoSuportada;
				//end selecionador_combobox_extensao
			//end selecionador_box
		//end SelecionadorDeArquivo
	
	
} WidgetsMainWindow;
//inside main_box signals
void buildIndex (GtkButton *button, WidgetsMainWindow *widgets) {
}
void goFilesWindow (GtkButton *button, WidgetsMainWindow *widgets) {
}
void goIndexWindow (GtkButton *button, WidgetsMainWindow *widgets) {
}
void goSearchWindow (GtkButton *button, WidgetsMainWindow *widgets) {
}


void gtkMain(int argc, char *argv[])
{
    GtkBuilder *gtkBuilder;
    WidgetsMainWindow widgets;

    gtk_init(&argc, &argv);

    gtkBuilder = gtk_builder_new();
    gtk_builder_add_from_file(gtkBuilder, "TelaProgramaNovoGoogle.glade", NULL);
    widgets.MainWindow = GTK_WINDOW(gtk_builder_get_object(gtkBuilder, "MainWindow"));

    /* Fazendo ligações com as entradas do glade */

    /* Conectando os sinais */
    gtk_builder_connect_signals(gtkBuilder, &widgets);

    /* Destruindo o builder, já que não precisamos mais dele */
    g_object_unref(G_OBJECT(gtkBuilder));

    /* Mostra a interface do glade */
    gtk_widget_show(GTK_WIDGET(widgets.MainWindow));

    gtk_main();
}
int main(int argc, char *argv[])
{
	gtkMain(argc,argv);
	return 0;
}
