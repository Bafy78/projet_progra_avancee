#ifndef analyseur_lexical_h
#define analyseur_lexical_h

#include "jeton.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typejeton* analyseur(const char* expression,int *erreur_pg);

#endif