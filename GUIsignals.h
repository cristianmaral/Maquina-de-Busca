#ifndef GUISIGNALS_H_INCLUDED
#define GUISIGNALS_H_INCLUDED
#include "GUI.h"

void goSearchWindow (GtkButton *button, Widgets *widgets);
void goMainWindow (GtkButton *button, Widgets *widgets);
void filtrarExtensao (GtkButton *button, Widgets *widgets);
void cancelarSelecao (GtkButton *button, Widgets *widgets);
void selecionarArquivo (GtkButton *button, Widgets *widgets);
void closeProgram (GtkButton *button, Widgets *widgets);
void addFile (GtkButton *button, Widgets *widgets);
void goFilesWindow (GtkButton *button, Widgets *widgets);
void buildIndex (GtkButton *button, Widgets *widgets);
void goIndexWindow (GtkButton *button, Widgets *widgets);
void cancelBuildIndex (GtkButton *button, Widgets *widgets);
void openAboutWindow (GtkButton *button, Widgets *widgets);

#endif
