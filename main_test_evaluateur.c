#include <math.h>
#include <stdio.h>
#include "jeton.h"
#include "evaluateur.h"

Arbre creer_noeud(typejeton T,Arbre fg,Arbre fd){
    Arbre New;
    New=(Arbre)malloc(sizeof(Node));
    New->jeton=T;
    New->fg=fg;
    New->fd=fd;
    return New;
}

Arbre generation_arbre_A(){ //fonction -5x*cos(3/x)

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

Arbre generation_arbre_B(){ //fonction 5/0

    typejeton jetondiv;
    jetondiv.lexem=OPERATEUR;
    jetondiv.valeur.operateur=DIV;

    typejeton jetoncinq;
    jetoncinq.lexem=REEL;
    jetoncinq.valeur.reel=5;

    typejeton jetonzero;
    jetonzero.lexem=REEL;
    jetonzero.valeur.reel=0;

    Arbre B = creer_noeud(
        jetondiv,
        creer_noeud(
            jetoncinq,NULL,NULL
        ),
        creer_noeud(
            jetonzero,NULL,NULL
        )
    );
    return B;
}


int main(){
    void *memory=malloc(sizeof(int));
    int *erreur_pg=(int *)memory;
    *erreur_pg=0;
    Arbre A = generation_arbre_A();
    float resultats=Eval(A,1,erreur_pg);
    printf("le resultat est %f\n", resultats);
    if (resultats>-5.989995 && resultats<-5.989990 ){
        printf("cela correspond au resultat attendu!\n");
    }
    else{
        printf("cela ne correspond pas au resultat attendu!\n");
    if(erreur_pg!=0){
        printf("Il y a eu une erreur %d",*erreur_pg);
    }
    return -1;
    }
    Arbre B = generation_arbre_B();
    Eval(B,1,erreur_pg);
    if(*erreur_pg==300){
        printf("cela est tres tres poggers concernant la division par zero obviously");
    }
    else{
        printf("cela n'est pas tres tres poggers concernant la division par zero obviously");
        return -1;
    }
}