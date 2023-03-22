#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "jeton.h"
#include "evaluateur.h"

//la fonction prend en entrée: un arbre A  qui est la fonction,
//x qui est la valeur numerique de la variable x 
//*erreur_pg un pointeur qui est l'erreur à retourner si il y en a une
//la fonction retourne l'image de x par la fonction représentée par l'arbre A
float Eval(Arbre A, float x, int* erreur_pg) {
	//la fonction est récursive, donc on ne continue que si il n'y a pas eu d'erreur à la récursion précédente
	if (*erreur_pg == 0) {
		//Pour chaque type de lexem, on effectue l'opération associée, avec les éléments du tableau concernés
		switch (A->jeton.lexem) {
		case REEL:
			return((A->jeton.valeur.reel));
			break;
		case VARIABLE:
			return(x);
			break;
		case OPERATEUR:
			switch (A->jeton.valeur.operateur) {
				//Par exemple si on a un opérateur plus, on additione les élément du fils gauche avec ceux du fils droit
			case PLUS:
				return(Eval(A->fg, x, erreur_pg) + Eval(A->fd, x, erreur_pg));
				break;
			case MOINS:
				return(Eval(A->fg, x, erreur_pg) - Eval(A->fd, x, erreur_pg));
				break;
			case FOIS:
				return(Eval(A->fg, x, erreur_pg) * Eval(A->fd, x, erreur_pg));
				break;
			case DIV:
				if (Eval(A->fd, x, erreur_pg) == 0.0 && Eval(A->fd, x + 1, erreur_pg) == 0.0) {
					*erreur_pg = 300;//division par 0
					return 0.0;
				if (Eval(A->fd, x, erreur_pg) == 0.0) {
						return (Eval(A->fg, x, erreur_pg))/1000000000;
					}

				}
				return(Eval(A->fg, x, erreur_pg) / Eval(A->fd, x, erreur_pg));
				break;
			case PUIS:
				return(pow(Eval(A->fg, x, erreur_pg), Eval(A->fd, x, erreur_pg)));
				break;

			}
		case FONCTION:
			switch (A->jeton.valeur.fonction) {
				//Pour les fonctions comme sinus, on effectue la fonction sur les éléments du fils droit
			case SIN:
				return (sin(Eval(A->fd, x, erreur_pg)));
				break;
			case ABS:
				return (sqrt(pow(Eval(A->fd, x, erreur_pg), 2)));
				break;
			case SQRT:
				if (Eval(A->fd, x, erreur_pg) < 0) {
					*erreur_pg = 303;// racine d'une valeur negative
					return 0.0;
				}
				return (sqrt(Eval(A->fd, x, erreur_pg)));
				break;
			case LOG:
				if (Eval(A->fd, x, erreur_pg) <= 0) {
					*erreur_pg = 302;// logarithme d'une valeur nulle ou negative
					return 0.0;
				}
				return (log(Eval(A->fd, x, erreur_pg)));
				break;
			case COS:
				return (cos(Eval(A->fd, x, erreur_pg)));
				break;
			case TAN:
				return (tan(Eval(A->fd, x, erreur_pg)));
				break;
			case EXP:
				return (exp(Eval(A->fd, x, erreur_pg)));
				break;
			case ENTIER:
				return ((int)(floor(Eval(A->fd, x, erreur_pg))));
				break;
			case VAL_NEG:
				return (-1 * (Eval(A->fd, x, erreur_pg)));
				break;
			case SINC:
				return (sin(Eval(A->fd, x, erreur_pg)) / Eval(A->fd, x, erreur_pg));
				break;

				}
				//Si on ne retrouve aucun des lexems précédents, il y a une erreur
			default:
				*erreur_pg = 301; //lexem non reconnu		
			}
		}
		return 0.0;
	}