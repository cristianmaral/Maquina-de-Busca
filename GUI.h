#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED
#include "TST.h"
#include <gtk/gtk.h>
//TipoTSTNo *raiz;
typedef struct {
	GtkWindow *MainWindow;
	GtkStack *PilhaDeJanelas;
	GtkBox *main_box, *files_box, *index_box, *search_box;
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
	GtkScrolledWindow *search_inner_box;
		//begin search_inner_box
	GtkTreeView *search_lista_viewer;
			//begin search_lista_viewer
	GtkTreeSelection *search_treeview_selection;
	GtkTreeViewColumn *IdDocumento, *NomeDocumento;
			//end search_lista_viewer
		//end search_inner_box
	//inside index_box
	GtkHeaderBar *index_header;
		//begin index_header
	GtkLabel *index_title;
	GtkButton *index_backbutton, *index_pagedownbutton, *index_pageupbutton, *index_closebutton;
	GtkImage *index_pagedownbutton_image, *index_pageupbutton_image, *index_closebutton_image;
		//end index_header
	GtkScrolledWindow *index_inner_box;
		//begin index_inner_box
	GtkTextView *index_textviewer;
		//end index_inner_box
	//inside files_box
	GtkHeaderBar *files_header;
		//begin files_header
	GtkButton *files_backbutton, *files_closebutton;
	GtkImage *files_closebutton_image;
	GtkLabel *files_title;
		//end files_header
	GtkScrolledWindow *files_innerupper_box;
		//begin files_innerupper_box
	GtkTreeView *files_lista_viewer;
			//begin files_lista_viewer
	GtkTreeSelection *files_treeview_selection;
	GtkTreeViewColumn *NomeDoArquivo, *CaminhoDoArquivo;
	GtkCellRendererText *NomeDoArquivo_textrenderer, *CaminhoDoArquivo_textrenderer;
			//end files_lista_viewer
		//end files_innerupper_box
	GtkBox *files_innerlower_box;
		//begin files_innerlower_box
	GtkFileChooserButton *files_filechooserbutton;
	GtkButton *files_addbutton, *files_rembutton;
		//end files_innerlower_box
	//Helper Widgets
	GtkAdjustment *files_scrollbar_config;
	GtkAdjustment *index_scrollbar_config;
	GtkAdjustment *search_scrollbar_config;
	GtkSizeGroup *agrupamento_tamanho_telas;
	GtkEntryCompletion *entrycompletion;
	GtkListStore *main_lista_completion;
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
	GtkWindow *LoadingWindow;
		//begin LoadingWindow
	GtkBox *loading_box;
			//begin loading_box
	GtkLabel *loading_label;
	GtkSpinner *loading_image;
	GtkButton *loading_cancelbutton;
			//end loading_box
		//end LoadingWindow
	GtkAboutDialog *AboutWindow;
		//begin AboutWindow
	GtkBox *about_box;
			//begin about_box
	GtkButtonBox *about_buttonbox;
			//end about_box
		//end AboutWindow
	GtkTreeIter *iter;//Iterador usado para trabalhar com GtkListStore


} Widgets;
gboolean func(GtkEntryCompletion *completion,const gchar *key,GtkTreeIter *iter,gpointer user_data);
void gtkMain(int argc, char *argv[]);

#endif
