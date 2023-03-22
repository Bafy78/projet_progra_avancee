#include "jeton.h"
#include "analyseur_syntaxique.h"
#include <string.h>
#include <stdlib.h>

void Copy_Tab (typejeton* tab2, typejeton* tab1, int debut, int end){
	/*
		génere une copie du tableau envoyé en 2ème argument entre la valeur du 3ème argument et celle du 4ème
		et si besoin rajoute le lexem fin à la copie renvoyé dans le 1er argument	
	*/
	int k=0;
    for (int i=debut; (i<=end)&&(tab1[i].lexem!=FIN);i++ ){
        tab2[k].lexem=tab1[i].lexem;
		tab2[k].valeur=tab1[i].valeur;
		k++;
    }
	tab2[k].lexem=FIN;
}

Arbre creer_noeud(typejeton T,Arbre fg,Arbre fd){
	/*
		génère un noeud et y ajoute sonb fils droit, gauche et son jeton passés en arguments
	*/
	Arbre New=NULL;
	New=(Arbre)malloc(sizeof(Node));
	New->jeton=T;
	New->fg=fg;
	New->fd=fd;
	return New;
}

Arbre analyse_syntaxique(typejeton Tab[],int* erreur_pg){
	//gestion des erreurs
	// si le tableau recu par la fonction est vide
	if(Tab[0].lexem==FIN){
		*erreur_pg=204; //tableau vide
		return NULL;
	}
	//verification des parennthèses, barres de valeurs absolues, et nombre de fonction
	int i=0;
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

	//analyseur syntaxique
	if(*erreur_pg==0){
		//operateur PLUS et MOINS
		/*
			methode: detection du dernier operateur PLUS ou MOINS et recuperation de sa position,
			en omettant les operateurs entre parenthèses et les valeurs entre barres de valeurs absolues
		*/
		i=0;
		int n=-1;
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
				if(Tab[i].valeur.operateur==PLUS||Tab[i].valeur.operateur==MOINS){
					n=i; 
				}
			}
			i++;
		}
		/*
			methode: copie des partie du tableau à droite et à gauche de l'operateur.
			puis traîtement de ces parties et creation du noeud
		*/
		if (n!=(-1)){
			typejeton Tabd[length_Tab];
			typejeton Tabg[length_Tab];
			Copy_Tab(Tabg,Tab,0,n-1);
			Copy_Tab(Tabd,Tab,n+1,length_Tab);
			Arbre fd,fg;
			fd=analyse_syntaxique(Tabd, erreur_pg);
			fg=analyse_syntaxique(Tabg, erreur_pg);

			return creer_noeud(Tab[n],fg,fd);
		}


		//operateur FOIS et DIV
		/*
			methode: detection du dernier operateur FOIS ou DIV et recuperation de sa position,
			en omettant les operateurs entre parenthèses et les valeurs entre barres de valeurs absolues
		*/

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
					n=i;
				}
			}
			i++;
		}
		/*
			methode: copie des partie du tableau à droite et à gauche de l'operateur.
			puis traîtement de ces parties et creation du noeud
		*/
		if (n!=(-1)){
			typejeton Tabd[length_Tab];
			typejeton Tabg[length_Tab];
			Copy_Tab(Tabg,Tab,0,n-1);
			Copy_Tab(Tabd,Tab,n+1,length_Tab);
			Arbre fd,fg;
			fd=analyse_syntaxique(Tabd, erreur_pg);
			return creer_noeud(Tab[n],fg,fd);
		}


		//operateur PUIS
		/*
			methode: detection du dernier operateur PUIS et recuperation de sa position,
			en omettant les operateurs entre parenthèses et les valeurs entre barres de valeurs absolues
		*/
		i=0;
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
			if(Tab[i].lexem==OPERATEUR&&nb_parenthese==0&&(nb_barres%2)==0){
				if(Tab[i].valeur.operateur==PUIS){
					n=i;
				}
			}
			i++;
		}
		/*
			methode: copie des partie du tableau à droite et à gauche de l'operateur.
			puis traîtement de ces parties et creation du noeud
		*/		
		if (n!=(-1)){
			typejeton Tabd[length_Tab];
			typejeton Tabg[length_Tab];
			Copy_Tab(Tabg,Tab,0,n-1);
			Copy_Tab(Tabd,Tab,n+1,length_Tab);
			Arbre fd;
			fd=analyse_syntaxique(Tabd, erreur_pg);
			fg=analyse_syntaxique(Tabg, erreur_pg);
			return creer_noeud(Tab[n],fg,fd);
		}


		//fonction VAL_NEG
		/*
			methode: detection de la première val_neg et recuperation de sa position,
			en omettant les VAL_NEG entre parenthèses et les valeurs entre barres de valeurs absolues
		*/
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
			if(Tab[i].lexem==FONCTION&&Tab[i].valeur.fonction==VAL_NEG&&nb_parenthese==0&&(nb_barres%2)==0){
				n=i;
			}
			i++;
		}
		/*
			methode: copie des partie du tableau à gauche de la fonction Val_Neg.
			puis traîtement de ces parties
			creation du noeud
		*/
		if (n!=(-1)){
			typejeton Tabd[length_Tab];
			Copy_Tab(Tabd,Tab,n+1,length_Tab);
			Arbre fd;
			fd=analyse_syntaxique(Tabd, erreur_pg);
			return creer_noeud(Tab[n],NULL,fd);
		}


		//valeur absolue
		/*
			methode: detection de la première barre de valeur absolue et recuperation de sa position,
			en omettant les barres entre parenthèses
		*/
		i=0;
		n=-1;
		nb_parenthese=0;
		nb_barres=0;
		while(Tab[i].lexem!=FIN&&n==(-1)){
			if(Tab[i].lexem==PAR_OUV){
				nb_parenthese++;
			}
			if(Tab[i].lexem==PAR_FERM){
				nb_parenthese--;
			}
			if(Tab[i].lexem==BAR&&nb_parenthese==0){
				n=i;
				/*
					methode: detection de la partie entre barres,
					copie puis traîtement ce celle ci
					creation du noeud et ajout du jeton fonction valeur absolue
				*/
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
					if(Tab[n].lexem==FIN&&nb_barres!=0){
						*erreur_pg=203;//manque parenthèse fermée
						return NULL;
					}
				}
				n--;
				typejeton Tabd[length_Tab];
				Copy_Tab(Tabd,Tab,k,n);
				Arbre fd;
				fd=analyse_syntaxique(Tabd, erreur_pg);
				typejeton tmp;
				tmp.lexem=FONCTION;
				tmp.valeur.fonction=ABS;
				return creer_noeud(tmp,NULL,fd);
			}
			i++;
		}


		//fonctions
		/*
			methode: detection de la fonction et recuperation de sa position,
			en omettant les fonctions entre parenthèses et les fonctions entre barres de valeurs absolues
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
		/*
			methode: detection de la partie entre parenthèses,
			copie puis traîtement ce celle ci
			creation du noeud
		*/
		if(n!=(-1)){
			if(Tab[n+1].lexem!=PAR_OUV){
				*erreur_pg=201;//manque parenthèse ouverte
				return NULL;
			}
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
				if(Tab[n].lexem==FIN&&nb_parenthese!=0){
					*erreur_pg=200;//manque parenthèse fermée
					return NULL;
				}
			}
			n--;
			typejeton Tabd[length_Tab];
			Copy_Tab(Tabd,Tab,k,n);
			Arbre fd;
			fd=analyse_syntaxique(Tabd, erreur_pg);
			return creer_noeud(Tab[i-1],NULL,fd);
		}


		//parenthèses
		/*
			methode: detection de la première parenthèse ouvert du tableau et recuperation de sa position,
			en omettant les parenthèses entre les barres de valeurs absolues
		*/
		i=0;
		n=-1;
		nb_parenthese=0;
		nb_barres=0;
		while(Tab[i].lexem!=FIN&&(n==-1)){
			if(Tab[i].lexem==BAR){
				nb_barres++;
			}if(Tab[i].lexem==PAR_OUV&&(nb_barres%2)==0){
				n=i;
				/*
					methode: detection de la partie entre parenthèses,
					copie puis traîtement ce celle ci
					creation du noeud
				*/
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
					if(Tab[n].lexem==FIN&&nb_parenthese!=0){
						*erreur_pg=200;//manque parenthèse fermée
						return NULL;
					}
				}
				n--;
				typejeton Tabd[length_Tab];
				Copy_Tab(Tabd,Tab,k,n);
				return analyse_syntaxique(Tabd,erreur_pg);
			}
			i++;
		}
		

		//methode: detection des reels, des variables et creation des noeuds et si le lexem est inconnu, mise en place de l'erreur 202
		switch (Tab[0].lexem){
		case REEL:
			return creer_noeud(Tab[0],NULL,NULL);
			break;
		case VARIABLE:
			return creer_noeud(Tab[0],NULL,NULL);
			break;
		default:
			*erreur_pg=202;//lexem non reconnu
			break;
		}
	}else{
		//si *erreur_pg!=000
		return NULL;
	}
}
/*
	codes d'erreurs associés à l'analyseur syntaxique:
	200 parenthèse fermée manquante
	201 parenthèse ouverte manquante
	202 lexem non reconnu
	203 barre de valeur absolue manquante
	204 tableau vide
*/