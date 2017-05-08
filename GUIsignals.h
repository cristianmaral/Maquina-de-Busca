#ifndef GUISIGNALS_H_INCLUDED
#define GUISIGNALS_H_INCLUDED
#include "GUI.h"
#include "MaquinaDeBusca.h"

TLista palavras; /* Variável global - Lista de palavras de busca */

/* Help Funcions */
void updateFileTitle(Widgets *widgets);
void splitPath(gchar *filepath,gchar **filename);
void updateSearchTitle (char *entrada, char **saida);
void atualizarCampo(GtkSearchEntry *entry, char *value);
void AutoPreenchimentoTST(TipoTSTNo *no, int indice, char *prefixo,TLista *retorno);

/* Signals */
gboolean proximaDica(GtkEntryCompletion *entry, GtkTreeModel *model, GtkTreeIter *iter, Widgets *widgets);
void pesquisaAlterada(GtkSearchEntry *entry, Widgets *widgets);
void goSearchWindow (GtkButton *button, Widgets *widgets);
void goMainWindow (GtkButton *button, Widgets *widgets);
void closeProgram (GtkButton *button, Widgets *widgets);
void addFile (GtkButton *button, Widgets *widgets);
void remFile (GtkButton *button, Widgets *widgets);
void goFilesWindow (GtkButton *button, Widgets *widgets);
void buildIndex (GtkButton *button, Widgets *widgets);
void goIndexWindow (GtkButton *button, Widgets *widgets);
void cancelBuildIndex (GtkButton *button, Widgets *widgets);
void openAboutWindow (GtkButton *button, Widgets *widgets);
void ArqAnt(GtkButton *button, Widgets *widgets);
void ProxArq(GtkButton *button, Widgets *widgets);
void updateIndexTitleTotalPages(Widgets *widgets);
void updateIndexTitleCurrentPage(Widgets *widgets, int n);

#endif
