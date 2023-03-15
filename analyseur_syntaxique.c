#include "jeton.h"
#include "analyseur_syntaxique.h"
#include <string.h>
#include <stdlib.h>

void Copy_Tab (typejeton* tab2, typejeton* tab1, int debut, int end){
	typejeton Tmp;
    Tmp.lexem = FIN;
	int n=0,k=0;
    for (int i=debut; (i<=end)&&(!(tab1[i].lexem==FIN));i++ ){
        tab2[k].lexem=tab1[i].lexem;
		tab2[k].valeur=tab1[i].valeur;
		n=k;
		k++;
    }
	tab2[n+1]=Tmp;
}

Arbre creer_noeud(typejeton T,Arbre fg,Arbre fd){
	Arbre New=NULL;
	New=(Arbre)malloc(sizeof(Node));
	New->jeton=T;
	New->fg=fg;
	New->fd=fd;
	return New;
}

Arbre analyse_syntaxique(typejeton Tab[],int* erreur_pg){
	if(Tab[0].lexem==FIN){
		return NULL;
	}
	typejeton Tabd[length_Tab];
	typejeton Tabg[length_Tab];
	int i=0;
	//verification des parennthèses, barres de valeurs absolues, et nombre de fonction
	int nb_barres=0;
	int nb_parenthese=0;
	while(Tab[i].lexem!=FIN){
		if(Tab[i].lexem==PAR_OUV){
			nb_parenthese++;
		}
		if(Tab[i].lexem==PAR_FERM){
			nb_parenthese--;
		}
		if(Tab[i].lexem==BAR){
			nb_barres++;
		}
		i++;
	}
	if(nb_parenthese>0){
		*erreur_pg=200;//manque de parenthèse fermee

	}else if (nb_parenthese<0){
		*erreur_pg=201;//manque parenthèse ouverte
	}
	
	if(nb_barres%2!=0){
		*erreur_pg=203;//manque barre de valeur absolue
	}
	if(*erreur_pg==0){
		Arbre*A;
		typevaleur VAL;
		//operateur PLUS et MOINS
		/*methode: detection du dernier operateur plus ou moins et recuperation de sa position,
		en omettant les valeurs entre parenthèses et les valeurs entre barres de valeurs absolues*/
		int n=-1;
		nb_parenthese=0;
		nb_barres=0;
		i=0;
		while(Tab[i].lexem!=FIN){
			if(Tab[i].lexem==PAR_OUV){
				nb_parenthese++;
			}
			if(Tab[i].lexem==PAR_FERM){
				nb_parenthese--;
			}
			if(Tab[i].lexem==BAR){
			    nb_barres++;
			}
			if(Tab[i].lexem==OPERATEUR&&nb_parenthese==0&&(nb_barres%2)==0){
				if(Tab[i].valeur.operateur==PLUS||Tab[i].valeur.operateur==MOINS){
					VAL=Tab[i].valeur;
					n=i; 
				}
			}
			i++;
		}
		/*methode: copie des partie du tableau à droite et à gauche de l'operateur.
		puis traîtement de ces parties
		creation du noeud*/
		if (n!=(-1)){
			Copy_Tab(Tabg,Tab,0,n-1);
			Copy_Tab(Tabd,Tab,n+1,length_Tab);
			Arbre fd,fg;
			fd=analyse_syntaxique(Tabd, erreur_pg);
			fg=analyse_syntaxique(Tabg, erreur_pg);
			A=creer_noeud(Tab[n],fg,fd);
			return A;
		}
		//fonction VAL_NEG
		/*methode: detection de la première val_neg et recuperation de sa position,
		en omettant les valeurs entre parenthèses et les valeurs entre barres de valeurs absolues*/
		n=-1;
		nb_parenthese=0;
		nb_barres=0;
		i=0;
		while(Tab[i].lexem!=FIN){
			if(Tab[i].lexem==PAR_OUV){
				nb_parenthese++;
			}
			if(Tab[i].lexem==PAR_FERM){
				nb_parenthese--;
			}
			if(Tab[i].lexem==BAR){
			        nb_barres++;
			}
			if(Tab[i].lexem==FONCTION&&Tab[i].valeur.fonction==VAL_NEG&&nb_parenthese==0&&(nb_barres%2)==0){
				VAL=Tab[i].valeur;
				n=i;
			}
			i++;
		}
		/*methode: copie des partie du tableau à gauche de la fonction Val_Neg.
		puis traîtement de ces parties
		creation du noeud*/
		if (n!=(-1)){
			Copy_Tab(Tabd,Tab,n+1,length_Tab);
			Arbre fd;
			fd=analyse_syntaxique(Tabd, erreur_pg);
			A=creer_noeud(Tab[n],NULL,fd);
			return A;
		}

		//operateur FOIS et DIV
		/*methode: detection du dernier operateur fois ou div et recuperation de sa position,
		en omettant les valeurs entre parenthèses et les valeurs entre barres de valeurs absolues*/
		i=0;
		n=-1;
		nb_parenthese=0;
		nb_barres=0;
		while(Tab[i].lexem!=FIN){
			if(Tab[i].lexem==PAR_OUV){
				nb_parenthese++;
			}
			if(Tab[i].lexem==PAR_FERM){
				nb_parenthese--;
			}
			if(Tab[i].lexem==BAR){
			        nb_barres++;
			}
			if(Tab[i].lexem==OPERATEUR&&nb_parenthese==0&&(nb_barres%2)==0){
				if(Tab[i].valeur.operateur==FOIS||Tab[i].valeur.operateur==DIV){
					VAL=Tab[i].valeur;
					n=i;
				}
			}
			i++;
		}
		
		/*methode: copie des partie du tableau à droite et à gauche de l'operateur.
		puis traîtement de ces parties
		creation du noeud*/
		if (n!=(-1)){
			Copy_Tab(Tabg,Tab,0,n-1);
			Copy_Tab(Tabd,Tab,n+1,length_Tab);
			Arbre fd,fg;
			fg=analyse_syntaxique(Tabg, erreur_pg);
			fd=analyse_syntaxique(Tabd, erreur_pg);
			A=creer_noeud(Tab[n],fg,fd);
			return A;
		}
		//operateurs PUIS
		/*methode: detection du dernier operateur puis et recuperation de sa position,
		en omettant les valeurs entre parenthèses et les valeurs entre barres de valeurs absolues*/
		i=0;
		n=-1;
		nb_parenthese=0;
		nb_barres=0;
		while(Tab[i].lexem!=FIN){

			if(Tab[i].lexem==PAR_OUV){
				nb_parenthese++;
			}
			if(Tab[i].lexem==PAR_FERM){
				nb_parenthese--;
			}
			if(Tab[i].lexem==BAR){
			        nb_barres++;
			}
			if(Tab[i].lexem==OPERATEUR&&nb_parenthese==0&&(nb_barres%2)==0){
				if(Tab[i].valeur.operateur==PUIS){
					VAL=Tab[i].valeur;
					n=i;
				}
			}
			i++;
		}
		/*methode: copie des partie du tableau à droite et à gauche de l'operateur.
		puis traîtement de ces parties
		creation du noeud*/		
		if (n!=(-1)){
			Copy_Tab(Tabg,Tab,0,n-1);
			Copy_Tab(Tabd,Tab,n+1,length_Tab);
			Arbre fd,fg;
			fd=analyse_syntaxique(Tabd, erreur_pg);
			fd=analyse_syntaxique(Tabg, erreur_pg);
			A=creer_noeud(Tab[n],fg,fd);
			return A;
		}
		//fonctions
		/*methode: detection de la fonction et recuperation de sa position,
		en omettant les valeurs entre parenthèses et les valeurs entre barres de valeurs absolues
		*/
		i=0;
		n=-1;
		nb_parenthese=0;
		nb_barres=0;
		while(Tab[i].lexem!=FIN&&n==-1){
			if(Tab[i].lexem==PAR_OUV){
				nb_parenthese++;
			}
			if(Tab[i].lexem==PAR_FERM){
				nb_parenthese--;
			}
			if(Tab[i].lexem==BAR){
			        nb_barres++;
			}
			if(Tab[i].lexem==FONCTION&&Tab[i].valeur.fonction!=VAL_NEG&&nb_parenthese==0&&(nb_barres%2)==0){
				n=i;
			}
			i++;
		}
		/*methode: detection de la partie entre parenthèses,
		copie de celle ci
		puis traîtement ce celle ci
		creation du noeud*/
		if(n!=(-1)){
			int k=n+2;
			nb_parenthese=1;
			n=n+1;
			while(nb_parenthese!=0){
				n++;
				if(Tab[n].lexem==PAR_OUV){
					nb_parenthese++;
				}
				if(Tab[n].lexem==PAR_FERM){
					nb_parenthese--;
				}
				
			}
			n--;
			Copy_Tab(Tabd,Tab,k,n);
			Arbre fd;
			fd=analyse_syntaxique(Tabd, erreur_pg);
			A=creer_noeud(Tab[i-1],NULL,fd);
			return A;
		}
		//valeur absolue
		/*methode: detection de la première barre de valeur absolue et recuperation de sa position,
		en omettant les valeurs entre parenthèses*/
		i=0;
		n=-1;
		nb_barres=0;
		nb_parenthese=0;
		while(Tab[i].lexem!=FIN&&n==(-1)){
			if(Tab[i].lexem==PAR_OUV){
			        nb_parenthese++;
			}
			if(Tab[i].lexem==PAR_FERM){
				nb_parenthese--;
			}
			if(Tab[i].lexem==BAR&&nb_parenthese==0){
				n=i;
				/*methode: detection de la partie entre barres,
				copie de celle ci
				puis traîtement ce celle ci
				creation du noeud et ajout du jeton fonction valeur absolue*/
				int k=n+1;
				nb_barres=1;
				n++;
				nb_parenthese=0;
				while(nb_barres!=0){
					n++;
					if(Tab[n].lexem==PAR_OUV){
						nb_parenthese++;
					}
					if(Tab[n].lexem==PAR_FERM){
						nb_parenthese--;
					}
					if(Tab[n].lexem==BAR&&nb_parenthese==0){
						nb_barres--;
					}
				}
				n--;
				Copy_Tab(Tabd,Tab,k,n);
				Arbre fd;
				fd=analyse_syntaxique(Tabd, erreur_pg);
				typejeton tmp;
				tmp.lexem=FONCTION;
				tmp.valeur.fonction=ABS;
				A=creer_noeud(tmp,NULL,fd);
				return A;
			}
			i++;
		}

		//parenthèses
		/*methode: detection de la première parenthèse et recuperation de sa position,
		en omettant les valeurs entre barres de valeurs absolues
		*/
		i=0;
		n=-1;
		nb_barres=0;
		while(Tab[i].lexem!=FIN&&(n==-1)){
			if(Tab[i].lexem==BAR){
			        nb_barres++;
			}if(Tab[i].lexem==PAR_OUV&&(nb_barres%2)==0){
				n=i;
				/*methode: detection de la partie entre parenthèses,
				copie de celle ci
				puis traîtement ce celle ci
				creation du noeud*/
				int k=n+1;
				nb_parenthese=1;
				while(nb_parenthese!=0){
					n++;
					if(Tab[n].lexem==PAR_OUV){
						nb_parenthese++;
					}
					if(Tab[n].lexem==PAR_FERM){
						nb_parenthese--;
					}
					
				}
				n--;
				Copy_Tab(Tabd,Tab,k,n);
				A=analyse_syntaxique(Tabd,erreur_pg);
				return A;
			}
			i++;
		}
		

		//methode: detection des reels, des variables et creation des noeuds
		i=0;
		while(Tab[i].lexem!=FIN){
			
			if(Tab[i].lexem==REEL){
				A=creer_noeud(Tab[i],NULL,NULL);
				return A;
			}
			if(Tab[i].lexem==VARIABLE){
				A=creer_noeud(Tab[i],NULL,NULL);
				return A;
			}else{
				*erreur_pg=202;
			}
			i++;
		}
	} else{
		return NULL;
	}
	
}