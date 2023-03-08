#include <math.h>
#include <stdlib.h>
#include "jeton.h"
#include "evaluateur.h"

//retourne l'image de x par la fonction représentée par l'arbre A
float Eval( Arbre A,int x,int *erreur_pg){
    //la fonction est récursive, donc on ne continue que si il n'y a pas eu d'erreur à la récursion précédente
	if (erreur_pg==0){
        //Pour chaque type de lexem, on effectue l'opération associée, avec les éléments du tableau concernés
		switch(A->jeton.lexem){
			case REEL :
				return((float)(A->jeton.valeur.reel));
				break;
			case VARIABLE :
				return(x);
				break;
			case OPERATEUR:
				switch(A->jeton.valeur.operateur){
                    //Par exemple si on a un opérateur plus, on additione les élément du fils gauche avec ceux du fils droit
					case PLUS:
						return(Eval(A->fg,x,erreur_pg)+Eval(A->fd,x,erreur_pg));
						break;
					case MOINS:
						return(Eval(A->fg,x,erreur_pg)-Eval(A->fd,x,erreur_pg));
						break;
					case FOIS:
						return(Eval(A->fg,x,erreur_pg)*Eval(A->fd,x,erreur_pg));
						break;
					case DIV:
						return(Eval(A->fg,x,erreur_pg)/Eval(A->fd,x,erreur_pg));
						break;
					case PUIS:
						return(pow(Eval(A->fg,x,erreur_pg),Eval(A->fd,x,erreur_pg)));
						break;
					
				}					
			case FONCTION:
				switch(A->jeton.valeur.fonction){
                    //Pour les fonctions comme sinus, on effectue la fonction sur les éléments du fils droit
					case SIN:
						return (sin (Eval(A->fd,x,erreur_pg)));
						break;
					case ABS:
						return (abs(Eval(A->fd,x,erreur_pg)));
						break;
					case SQRT:
						return (sqrt(Eval(A->fd,x,erreur_pg)));
						break;
					case LOG:
						return (log(Eval(A->fd,x,erreur_pg)));
						break;
					case COS:
						return (cos(Eval(A->fd,x,erreur_pg)));
						break;
					case TAN:
						return (tan(Eval(A->fd,x,erreur_pg)));
						break;
					case EXP:
						return (exp(Eval(A->fd,x,erreur_pg)));
						break;
					case ENTIER:
						return ((int)(floor(Eval(A->fd,x,erreur_pg))));
						break;
					case VAL_NEG:
						return (-1*(Eval(A->fd,x,erreur_pg)));
						break;
					case SINC:
						return (sin(Eval(A->fd,x,erreur_pg))/Eval(A->fd,x,erreur_pg));
						break;
					
				}
            //Si on ne retrouve aucun des lexems précédents, il y a une erreur
			default:
				*erreur_pg=301; //lexem non reconnu		
		}
	}
	return 0.0;
}