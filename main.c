#include <math.h>
#include <stdio.h>
#include "jeton.h"
#include "evaluateur.h"
#include "analyseur_syntaxique.h"
//fonction associant les erreurs a leur correspondance
void categorisation_erreur(int *erreur_pg){
    switch(*erreur_pg){
        case 100 : printf("Erreur 100 : Caractère inconnu détecté");
        case 200 : printf("Erreur 200 : Parenthèse fermée manquante");
        case 201 : printf("Erreur 201 : Parenthèse ouverte manquante");
        case 202 : printf("Erreur 202 : Lexème non reconnu");
        case 203 : printf("Erreur 203 : Barre de valeur absolue manquante");
        case 300 : printf("Erreur 300 : Division par 0");
        case 301 : printf("Erreur 301 : Lexème non reconnu");
        case 302 : printf("Erreur 302 : log(x) avec x<0");
        case 303 : printf("Erreur 303 : sqrt(x) avec x<0");
    }
}

int main(){
    // création de jetons pour les tests

    typejeton jetonfois;
    jetonfois.lexem=OPERATEUR;
    jetonfois.valeur.operateur=FOIS;

    typejeton jetonvar;
    jetonvar.lexem=VARIABLE;

    typejeton jetoncinq;
    jetoncinq.lexem=REEL;
    jetoncinq.valeur.reel=5;

    typejeton jetonfin;
    jetonfin.lexem=FIN;
    // on demande à l'utilisateur les bornes
    float borne_inf;
    float borne_sup; 
    float pas;
    printf("Donnez a, la borne inférieure d'échantillonage de la fonction\n");
    scanf("%f", &borne_inf);
    printf("Donnez b, la borne supérieure d'échantillonage de la fonction\n");
    scanf("%f", &borne_sup);
    pas=(borne_sup-borne_inf)/1000;
    printf("borne inf:%f , borne sup:%f pas:%f", borne_inf, borne_sup, pas);
    //on initialise l'erreur qui sera un pointeur, elle pourra donc etre transmise hors des fonctions sans problème
    void *memory=malloc(sizeof(int));
    int *erreur_pg=(int *)memory;
    *erreur_pg=0;
    float Tableau_a_afficher[1000];
    Arbre Arbre_a_evaluer;
    typejeton Tableau[]={jetonvar,jetonfois,jetoncinq,jetonfin}; // a remplcer avec anaylseur lexical
    if(*erreur_pg==0){
        Arbre_a_evaluer=analyse_syntaxique(Tableau,erreur_pg);
    }
    if(*erreur_pg==0){
        int i=0;
        for(float x=borne_inf;x<borne_sup;x+=pas){
            Tableau_a_afficher[i]=Eval(Arbre_a_evaluer,x,erreur_pg);
            i++;
        }
    }
    for (int i=0;i<1000;i++){
        printf(" %f ",Tableau_a_afficher[i]);
    }
    if (*erreur_pg!=0){
        categorisation_erreur(erreur_pg);
        return -1;
    }
}
