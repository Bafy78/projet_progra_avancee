#include <math.h>
#include <stdio.h>
#include "jeton.h"
#include "evaluateur.h"

Arbre creer_noeud(typejeton T,Arbre fg,Arbre fd){ //Fonction qui créer un noeud a partir de paramètres en entrée
    Arbre New;
    New=(Arbre)malloc(sizeof(Node));
    New->jeton=T;
    New->fg=fg;
    New->fd=fd;
    return New;
}

Arbre generation_arbre_A(){ //On crée la fonction -5x+cos(3/x)

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

Arbre generation_arbre_B(){ // On crée la fonction 5/0

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

Arbre generation_arbre_C(){ //On crée l'arber qui définit la fonction -5x*log(-3/x)


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

    typejeton jetonlog;
    jetonlog.lexem=FONCTION;
    jetonlog.valeur.fonction=LOG;


    Arbre A= creer_noeud(               
        jetonfois,
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
            jetonlog,NULL,
            creer_noeud(
                jetondiv,
                creer_noeud(
                    jetonvalneg,NULL,
                    creer_noeud(
                        jetontrois, NULL, NULL
                    )
                ),
                creer_noeud(
                    jetonvar, NULL, NULL
                )
            )
        )
    );
    return A;
}

Arbre generation_arbre_D(){ //On crée l'arbre qui définit la fonction -5x*sqrt(-3/x)


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

    typejeton jetonracine;
    jetonracine.lexem=FONCTION;
    jetonracine.valeur.fonction=SQRT;


    Arbre A= creer_noeud(               
        jetonfois,
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
            jetonracine,NULL,
            creer_noeud(
                jetondiv,
                creer_noeud(
                    jetonvalneg,NULL,
                    creer_noeud(
                        jetontrois, NULL, NULL
                    )
                ),
                creer_noeud(
                    jetonvar, NULL, NULL
                )
            )
        )
    );
    return A;
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
        printf("l'erreur divison par 0 detectee\n");
    }
    else{
        printf("l'erreur division par 0  non detectee\n");
        return -1;
    }
    Arbre C= generation_arbre_C();
    *erreur_pg=0;
    Eval(C,54.78,erreur_pg);
    if (*erreur_pg==302){
        printf("l'erreur valeur dans un log negative detectee\n");
    }
    else{
         printf("l'erreur valeur dans un log non detectee\n");
    }
    *erreur_pg=0;
    Arbre D= generation_arbre_D();
    Eval(D,2,erreur_pg);
    if (*erreur_pg==303){
        printf("l'erreur valeur negative dans une racine detectee\n");
    }
    else{
         printf("l'erreur valeur negative dans une racine non detectee\n");
    }
}

