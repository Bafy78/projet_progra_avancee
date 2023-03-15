#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jeton.h"
#include "analyseur_syntaxique.h"

void generation_tab1(typejeton T[]){
    //tableau au généré:(-5)*x+cos(3/x)
    int i=0;
    T[i].lexem=PAR_OUV;
    i++;
    T[i].lexem=FONCTION;
    T[i].valeur.fonction=VAL_NEG;
    i++;
    T[i].lexem=REEL;
    T[i].valeur.reel=5;
    i++;
    T[i].lexem=PAR_FERM;
    i++;
    T[i].lexem=OPERATEUR;
    T[i].valeur.operateur=FOIS;
    i++;
    T[i].lexem=VARIABLE;
    i++;
    T[i].lexem=OPERATEUR;
    T[i].valeur.operateur=PLUS;
    i++;
    T[i].lexem=FONCTION;
    T[i].valeur.fonction=COS;
    i++;
    T[i].lexem=PAR_OUV;
    i++;
    T[i].lexem=REEL;
    T[i].valeur.reel=3;
    i++;
    T[i].lexem=OPERATEUR;
    T[i].valeur.operateur=DIV;
    i++;
    T[i].lexem=VARIABLE;
    i++;
    T[i].lexem=PAR_FERM;
    i++;
    T[i].lexem=FIN;
}

Arbre generation_arbre1(){
    typejeton jetonplus;
    jetonplus.lexem=OPERATEUR;
    jetonplus.valeur.operateur=PLUS;

    typejeton jetonfois;
    jetonfois.lexem=OPERATEUR;
    jetonfois.valeur.operateur=FOIS;

    typejeton jetondiv;
    jetondiv.lexem=OPERATEUR;
    jetondiv.valeur.operateur=DIV;

    typejeton jetonvar;
    jetonvar.lexem=VARIABLE;

    typejeton jetonvalneg;
    jetonvalneg.lexem=FONCTION;
    jetonvalneg.valeur.fonction=VAL_NEG;

    typejeton jetoncinq;
    jetoncinq.lexem=REEL;
    jetoncinq.valeur.reel=5;

    typejeton jetontrois;
    jetontrois.lexem=REEL;
    jetontrois.valeur.reel=3;

    typejeton jetoncos;
    jetoncos.lexem=FONCTION;
    jetoncos.valeur.fonction=COS;

    Arbre A= creer_noeud(
        jetonplus,
        creer_noeud(
            jetonfois,
            creer_noeud(
                jetonvalneg,NULL,
                creer_noeud(
                    jetoncinq,NULL,NULL
                )
            
            ),
            creer_noeud(
                jetonvar, NULL , NULL
            )
        ),
        creer_noeud(
            jetoncos,NULL,
            creer_noeud(
                jetondiv,
                creer_noeud(
                    jetontrois, NULL, NULL
                ),
                creer_noeud(
                    jetonvar, NULL, NULL
                )
            )
        )
    );
    return A;
}

void generation_tab2(typejeton T[]){
    //tableau au généré:|-5|*x+cos(3/x)
    int i=0;
    T[i].lexem=BAR;
    i++;
    T[i].lexem=FONCTION;
    T[i].valeur.fonction=VAL_NEG;
    i++;
    T[i].lexem=REEL;
    T[i].valeur.reel=5;
    i++;
    T[i].lexem=BAR;
    i++;
    T[i].lexem=OPERATEUR;
    T[i].valeur.operateur=FOIS;
    i++;
    T[i].lexem=VARIABLE;
    i++;
    T[i].lexem=OPERATEUR;
    T[i].valeur.operateur=PLUS;
    i++;
    T[i].lexem=FONCTION;
    T[i].valeur.fonction=COS;
    i++;
    T[i].lexem=PAR_OUV;
    i++;
    T[i].lexem=REEL;
    T[i].valeur.reel=3;
    i++;
    T[i].lexem=OPERATEUR;
    T[i].valeur.operateur=DIV;
    i++;
    T[i].lexem=VARIABLE;
    i++;
    T[i].lexem=PAR_FERM;
    i++;
    T[i].lexem=FIN;
}

Arbre generation_arbre2(){
    typejeton jetonplus;
    jetonplus.lexem=OPERATEUR;
    jetonplus.valeur.operateur=PLUS;

    typejeton jetonfois;
    jetonfois.lexem=OPERATEUR;
    jetonfois.valeur.operateur=FOIS;

    typejeton jetondiv;
    jetondiv.lexem=OPERATEUR;
    jetondiv.valeur.operateur=DIV;

    typejeton jetonvar;
    jetonvar.lexem=VARIABLE;

    typejeton jetonvalneg;
    jetonvalneg.lexem=FONCTION;
    jetonvalneg.valeur.fonction=VAL_NEG;

    typejeton jetonabs;
    jetonabs.lexem=FONCTION;
    jetonabs.valeur.fonction=ABS;
    printf("%d",jetonabs.lexem);

    typejeton jetoncinq;
    jetoncinq.lexem=REEL;
    jetoncinq.valeur.reel=5;

    typejeton jetontrois;
    jetontrois.lexem=REEL;
    jetontrois.valeur.reel=3;

    typejeton jetoncos;
    jetoncos.lexem=FONCTION;
    jetoncos.valeur.fonction=COS;

    Arbre A= creer_noeud(
        jetonplus,
        creer_noeud(
            jetonfois,
            creer_noeud(
                jetonabs,NULL,
                creer_noeud(
                    jetonvalneg,NULL,
                    creer_noeud(
                        jetoncinq,NULL,NULL
                    )
                )
            ),
            creer_noeud(
                jetonvar, NULL , NULL
            )
        ),
        creer_noeud(
            jetoncos,NULL,
            creer_noeud(
                jetondiv,
                creer_noeud(
                    jetontrois, NULL, NULL
                ),
                creer_noeud(
                    jetonvar, NULL, NULL
                )
            )
        )
    );
    return A;
}

void generation_tab3(typejeton T[]){
    //tableau au généré:(-2*|5|)+|-tan(3*x)|)
    int i=0;
    T[i].lexem=PAR_OUV;
    i++;
    T[i].lexem=FONCTION;
    T[i].valeur.fonction=VAL_NEG;
    i++;
    T[i].lexem=REEL;
    T[i].valeur.reel=3;
    i++;
    T[i].lexem=OPERATEUR;
    T[i].valeur.operateur=FOIS;
    i++;
    T[i].lexem=BAR;
    i++;
    T[i].lexem=REEL;
    T[i].valeur.reel=5;
    i++;
    T[i].lexem=BAR;
    i++;
    T[i].lexem=PAR_FERM;
    i++;
    T[i].lexem=OPERATEUR;
    T[i].valeur.operateur=PLUS;
    i++;
    T[i].lexem=BAR;
    i++;
    T[i].lexem=FONCTION;
    T[i].valeur.fonction=VAL_NEG;
    i++;
    T[i].lexem=FONCTION;
    T[i].valeur.fonction=TAN;
    i++;
    T[i].lexem=PAR_OUV;
    i++;
    T[i].lexem=REEL;
    T[i].valeur.reel=3;
    i++;
    T[i].lexem=OPERATEUR;
    T[i].valeur.operateur=FOIS;
    i++;
    T[i].lexem=VARIABLE;
    i++;
    T[i].lexem=PAR_FERM;
    i++;
    T[i].lexem=BAR;
    i++;
    T[i].lexem=FIN;
}

Arbre generation_arbre3(){
    printf("f° generation tab3\n");
    typejeton jetonplus;
    jetonplus.lexem=OPERATEUR;
    jetonplus.valeur.operateur=PLUS;

    typejeton jetonfois;
    jetonfois.lexem=OPERATEUR;
    jetonfois.valeur.operateur=FOIS;

    typejeton jetonvar;
    jetonvar.lexem=VARIABLE;

    typejeton jetonvalneg;
    jetonvalneg.lexem=FONCTION;
    jetonvalneg.valeur.fonction=VAL_NEG;

    typejeton jetonabs;
    jetonabs.lexem=FONCTION;
    jetonabs.valeur.fonction=ABS;

    typejeton jetoncinq;
    jetoncinq.lexem=REEL;
    jetoncinq.valeur.reel=5;

    typejeton jetondeux;
    jetondeux.lexem=REEL;
    jetondeux.valeur.reel=2;

    typejeton jetontrois;
    jetontrois.lexem=REEL;
    jetontrois.valeur.reel=3;

    typejeton jetontan;
    jetontan.lexem=FONCTION;
    jetontan.valeur.fonction=TAN;

    Arbre A= creer_noeud(
        jetonplus,
        creer_noeud(
            jetonvalneg,NULL,
            creer_noeud(
                jetonfois,
                creer_noeud(
                    jetondeux,NULL,NULL
                ),
                creer_noeud(
                    jetonabs,NULL,
                    creer_noeud(
                        jetoncinq,NULL,NULL
                    )
                )
            )
        ),
        creer_noeud(
            jetonabs,NULL,
            creer_noeud(
                jetonvalneg,NULL,
                creer_noeud(
                    jetontan,NULL,
                    creer_noeud(
                        jetonfois,
                        creer_noeud(
                            jetontrois,NULL,NULL
                        ),creer_noeud(
                            jetonvar,NULL,NULL
                        )
                    )
                )
            )
        )
    );
    return A;
}

int test_arbre(Arbre A, Arbre B){
    int tmp=0;
    printf("%d=%d?\n",A->jeton.lexem,B->jeton.lexem);
    if ((A->jeton.lexem)==(B->jeton.lexem)){
        switch (B->jeton.lexem)
        {
        case FONCTION:
            printf("\033[1;33m");
            printf("test fonction detectée\n");
            printf("\033[1;0m");
            if ((A->jeton.valeur.fonction)==(B->jeton.valeur.fonction)){
                tmp=1;
            }else{
                tmp=0;
            }
            break;
        case OPERATEUR:
            printf("\033[1;33m");
            printf("test operateur detectée\n");
            printf("\033[1;0m");
            if ((A->jeton.valeur.operateur)==(B->jeton.valeur.operateur)){
                tmp=1;
            }else{
                tmp=0;
            }
            break;
        case VARIABLE:
            printf("\033[1;33m");
            printf("test variable detectée\n");
            printf("\033[1;0m");
            tmp=1;
            break;
        case REEL:
            printf("\033[1;33m");
            printf("test reel detectée\n");
            printf("\033[1;0m");
            if ((A->jeton.valeur.reel)==(B->jeton.valeur.reel)){
                tmp=1;
            }else{
                tmp=0;
            }
            break;        
        default:
            return 0;
            break;
        }
       
    }else{
        return 0;
    }
    if(A->fd!=NULL||B->fd!=NULL){
        printf("\033[1;33m");
        printf("debut verif fd\n");
        printf("\033[1;0m");
        tmp=tmp&&test_arbre(A->fd,B->fd);
    }else if(A->fd!=B->fd){
        return 1;
    }
    if(A->fg!=NULL||B->fg!=NULL){
        printf("\033[1;33m");
        printf("debut verif fg\n");
        printf("\033[1;0m");
        tmp=tmp&&test_arbre(A->fg,B->fg);
    }else if(A->fg!=B->fg){
        return 1;
    }
    return tmp;
}


int main(){
    int *erreur_pg;
    int erreur=0;
    erreur_pg=&erreur;
    //generation du tableau
    printf("generation du tableau 1\n");
    typejeton T[length_Tab];
    generation_tab2(T);
    printf("generation de l'arbre 1\n");
    //generation de l'arbre de test
    Arbre B =generation_arbre2();
    //passage de la fonction
    printf("envoi dans l'analyseur syntaxique 1\n");
    Arbre A;
    A=analyse_syntaxique(T,erreur_pg);
    //test de l'arbre
    printf("test de l'arbre 1\n");
    int egal =test_arbre(A ,B);
    if(egal!=1){
        printf("\033[1;31m");
        printf("Arbre non egaux\n");
        printf("\033[1;0m");
        return -1;
    }
    //test d'erreurs
    printf("recupération des erreur prg 1\n %d",*erreur_pg);
    if(*erreur_pg!=000){
        printf("%d",*erreur_pg);
        return -1;
    }
}