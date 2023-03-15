#ifndef analyseur_syntaxique_h
#define analyseur_syntaxique_h

#include "jeton.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Arbre analyse_syntaxique( typejeton Tab[],int* erreur_pg);

Arbre creer_noeud(typejeton T,Arbre fg,Arbre fd);

#endif