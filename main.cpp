/**************************
 * Includes
 *
 **************************/
#include <stdlib.h>
#include <windows.h>
#include "glut.h"
#include "graph.h"
#include <stdio.h>
#include <math.h>
#include "evaluateur.h"
#include "analyseur_syntaxique.h"
#include "analyseur_lexical.h"
float x = 1;

int basculex = 0;
int basculey = 0;
int basculez = 0;
/**
* myKey
*
* Gestion des touches du clavier
*
* @parma c code ascci definissant une touche du clavier
*
*/
void categorisation_erreur(int* erreur_pg) {
    switch (*erreur_pg) {
    case 100: printf("Erreur 100 : Caractère inconnu détecté");
    case 200: printf("Erreur 200 : Parenthèse fermée manquante");
    case 201: printf("Erreur 201 : Parenthèse ouverte manquante");
    case 202: printf("Erreur 202 : Lexème non reconnu");
    case 203: printf("Erreur 203 : Barre de valeur absolue manquante");
    case 300: printf("Erreur 300 : Division par 0");
    case 301: printf("Erreur 301 : Lexème non reconnu");
    case 302: printf("Erreur 302 : log(x) avec x<0");
    case 303: printf("Erreur 303 : sqrt(x) avec x<0");
    }
}

void myKey(int c)
{

    if (c == 'q') {
        basculex = -1;
    }
    else if (c == 'd') {
        basculex = 1;
    }
    else if (c == 's') {
        basculey = -1;
    }
    else if (c == 'z') {
        basculey = 1;
    }
    else if (c == '+') {
        basculez = 1;
    }
    else if (c == '-') {
        basculez = -1;
    }
}



void Draw(float x[], float y[]) {

    /* trace une ligne blanche diagonale*/
    setcolor(0.67F, 0.80F, 1.0F);
    int i = -25;
    int j = -25;
    while (i < 25) {                //trac� du quadrillage
        while (j < 75) {
            line(-25, i, 25, i);
            line(j, -25, j, 75);
            line(i, -25, i, 25);
            line(-25, j, 75, j);
            j++;
        }i++;
    }
    setcolor(0.0F, 0.0F, 0.0F);
    line(-25, 25, 25, 25);          //trac� des axes
    line(0, -25, 0, 125);

    /* trace une ligne blanche diagonale */

    setcolor(0.0F, 0.0F, 1.0F);
    for (int i = 0; i < 99; i++) {      //trac� de la fonction
        line(x[i], y[i], x[i + 1], y[i + 1]);
    }
    setcolor(0.0F, 0.0F, 0.0F);
    if ((basculex == -1) || (basculex == 1)) {
        set_TranslatX(get_TranslatX() + basculex * 0.4);
        line(-25 + basculex * 0.4, 25, 25 + basculex * 0.4, 25);
        basculex = 0;
    }
    else if ((basculey == -1) || (basculey == 1)) {
        set_TranslatY(get_TranslatY() + basculey * 0.4);
        line(0, -25 + basculey * 0.4, 0, 125 + basculey * 0.4);
        basculey = 0;
    }
    else if (basculez == 1) {
        set_Zoom(get_Zoom() * 0.95);
    }
    else if (basculez == -1) {
        set_Zoom(get_Zoom() * 1.05);
    }

}
/**
* main
*
* La fonction principale avec deux arguments permettant de r�cup�rer les �l�ments en ligne de comment.
*
* Dans  cet  exemple  les  fonctions  (dites  callback)  myDraw  et  myKey  sont  install�es  ici  par
* l'appel  InitGraph  en  tant  que fonctions  r�agissantes  aux  �v�nements  de  "re-dessinage"  (pour  myDraw)
* et  aux  �v�nements  d'appui  sur  une  touche  du
* clavier (myKey).
�
* @parma ac : nombre de parametres
* @parma av : tableau contenant les parametres
*
*/
int main(int ac, char* av[])
{
    typejeton jetonfois;
    jetonfois.lexem = OPERATEUR;
    jetonfois.valeur.operateur = FOIS;

    typejeton jetonvar;
    jetonvar.lexem = VARIABLE;

    typejeton jetoncinq;
    jetoncinq.lexem = REEL;
    jetoncinq.valeur.reel = 5;

    typejeton jetonfin;
    jetonfin.lexem = FIN;
    // on demande à l'utilisateur les bornes
    float borne_inf;
    float borne_sup;
    float pas;
    int erreur = 0;
    int* erreur_pg = &erreur;
    char c[101];
    printf("veuillez entrer la fonction que vous souhaitez visualiser \n");
    fgets(c, 101, stdin);
    c[strlen(c) - 1] = '\0'; //enlève le '\n'
    typejeton tab[100];
    analyse_lexicale(tab, erreur_pg, c);
    printf("Donnez a, la borne inférieure d'échantillonage de la fonction\n");
    scanf("%f", &borne_inf);
    printf("Donnez b, la borne supérieure d'échantillonage de la fonction\n");
    scanf("%f", &borne_sup);
    pas = (borne_sup - borne_inf) / 1000;
    printf("borne inf:%f , borne sup:%f pas:%f", borne_inf, borne_sup, pas);
    //on initialise l'erreur qui sera un pointeur, elle pourra donc etre transmise hors des fonctions sans problème
    float Tableau_a_afficher_fonction[1000];
    float Tableau_a_afficher_variable[1000];
    Arbre Arbre_a_evaluer;
    typejeton Tableau[] = { jetonvar,jetonfois,jetoncinq,jetonfin }; // a remplcer avec anaylseur lexical
    if (*erreur_pg == 0) {
        Arbre_a_evaluer =  analyse_syntaxique(Tableau, erreur_pg);
    }
    if (*erreur_pg == 0) {
        int i = 0;
        for (float x = borne_inf; x < borne_sup; x += pas) {
            Tableau_a_afficher_fonction[i] = Eval(Arbre_a_evaluer, x, erreur_pg);
            Tableau_a_afficher_variable[i] = x;
            i++;
        }
    }
    if (*erreur_pg != 0) {
        categorisation_erreur(erreur_pg);
        return -1;
    }
    InitGraph(ac, av, "fonction", 1920, 1080, Draw, myKey, Tableau_a_afficher_variable, Tableau_a_afficher_fonction);
    return 0;

}


