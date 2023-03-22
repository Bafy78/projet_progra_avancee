/**************************
 * Includes
 *
 **************************/
#include <stdlib.h>
#include <windows.h>
#include "glut.h"
#include "Graph.h"
#include <stdio.h>
#include <math.h>
#include "evaluateur.h"
#include "analyseur_syntaxique.h"
#include "analyseur_lexical.h"
void categorisation_erreur(int* erreur_pg) {
    switch (*erreur_pg) {
    case 101: printf("Erreur 101 : fonction inconnue\n"); break;
    case 102: printf("Erreur 102 : caractère inconnu\n"); break;
    case 100: printf("Erreur 100 : Caractère inconnu détecté\n"); break;
    case 200: printf("Erreur 200 : Parenthèse fermée manquante\n"); break;
    case 201: printf("Erreur 201 : Parenthèse ouverte manquante\n"); break;
    case 202: printf("Erreur 202 : Lexème non reconnu\n"); break;
    case 204: printf("erreur 204 : Erreur de syntaxe\n"); break;
    case 203: printf("Erreur 203 : Barre de valeur absolue manquante\n"); break;
    case 300: printf("Erreur 300 : Division par 0\n"); break;
    case 301: printf("Erreur 301 : Lexème non reconnu\n"); break;
    case 302: printf("Erreur 302 : log(x) avec x<0\n"); break;
    case 303: printf("Erreur 303 : sqrt(x) avec x<0\n"); break;
    
    }
}


int basculex = 1;
int basculey = 1;
int basculez = 1;
int bascule_Menu = 0;
float coeff_translatX;
float coeff_translatY;

float Distance(float x, float y) {
    return abs(x - y);
}

void myKey(int c)
{
    coeff_translatX = Distance(get_A(), get_B()) / 50;
    coeff_translatY = Distance(get_C(), get_D()) / 50;
    if (bascule_Menu == 0) {
        if (c == 'q') {
            basculex = -1;
            if (get_X0() >= -10000) {
                set_TranslatX(get_TranslatX() + coeff_translatX * basculex);
                basculex = 0;
            }
        }
        if (c == 'd') {
            basculex = 1;
            if (get_X0() <= 10000) {
                set_TranslatX(get_TranslatX() + coeff_translatX * basculex);
                basculex = 0;
            }
        }
        if (c == 's') {
            basculey = -1;
            if (get_Y0() >= -10000) {
                set_TranslatY(get_TranslatY() + coeff_translatY * basculey);
                basculey = 0;
            }
        }
        if (c == 'z') {
            basculey = 1;
            if (get_Y0() <= 10000) {
                set_TranslatY(get_TranslatY() + coeff_translatY * basculey);
                basculey = 0;
            }
        }
        if (c == '=') {
            basculez = 1;
            set_Zoom(get_Zoom() * 0.95);
            basculez = 0;
        }
        if (c == '-') {
            set_Zoom(get_Zoom() / 0.95);
            basculez = 0;
        }
        if (c == 'r') {
            set_TranslatX(0);
            set_TranslatY(0);
            set_Zoom(1);
        }
    }

    if (c == 'm') {
        bascule_Menu ^= 1;
    }
}


void Draw(float x[], float y[]) {

    //tracé de la fonction
    setcolor(0.0F, 0.0F, 1.0F);
    for (int i = 0; i < 99; i++) {
        line(x[i], y[i], x[i + 1], y[i + 1]);
    }

    //Affichage des Coordonnées du curseur
    char valeurX0[100];
    char valeurY0[100];
    sprintf(valeurX0, "X=%f", get_X0());
    sprintf(valeurY0, "Y=%f", get_Y0());
    setcolor(0, 0, 0);
    outtextxy(get_X0() + abs(get_B() - get_X0()) * 0.70, get_Y0() + abs(get_D() - get_Y0()) * 0.90, valeurX0);
    outtextxy(get_X0() + abs(get_B() - get_X0()) * 0.70, get_Y0() + abs(get_D() - get_Y0()) * 0.80, valeurY0);

    //Affichage du menu

    if (bascule_Menu == 1) {
        float Dx;
        float Dy;
        Dx = Distance(get_X0(), get_B());
        Dy = Distance(get_Y0(), get_D());
        setcolor(0.0F, 0.0F, 0.0F);
        bar(get_X0() - Dx * (2.02 / 5), get_Y0() - Dy * (3.1 / 5), get_X0() + Dx * (2.5 / 5), get_Y0() + Dy * (3.02 / 5));
        setcolor(1.0F, 1.0F, 1.0F);
        bar(get_X0() - Dx * (2.0 / 5), get_Y0() - Dy * (3.0 / 5), get_X0() + Dx * (2.4 / 5), get_Y0() + Dy * (3.0 / 5));
        setcolor(0.0F, 0.0F, 0.0F);
        outtextxy(get_X0() - Dx * (2.0 / 5), get_Y0() + Dy * (3.2 / 5), "MENU");
        outtextxy(get_X0() - Dx * (1.9 / 5), get_Y0() + Dy * (2.7 / 5), "COMMANDES :");
        outtextxy(get_X0() - Dx * (1.8 / 5), get_Y0() + Dy * (2.2 / 5), "z : up");
        outtextxy(get_X0() - Dx * (1.8 / 5), get_Y0() + Dy * (1.7 / 5), "s : down");
        outtextxy(get_X0() - Dx * (1.8 / 5), get_Y0() + Dy * (1.2 / 5), "q : left");
        outtextxy(get_X0() - Dx * (1.8 / 5), get_Y0() + Dy * (0.7 / 5), "d : right");
        outtextxy(get_X0() - Dx * (1.8 / 5), get_Y0() + Dy * (0.2 / 5), "+ : zoom in");
        outtextxy(get_X0() - Dx * (1.8 / 5), get_Y0() + Dy * (-0.3 / 5), "- : zoom out");
        outtextxy(get_X0() - Dx * (1.8 / 5), get_Y0() + Dy * (-0.3 / 5), "- : zoom out");
        outtextxy(get_X0() - Dx * (1.8 / 5), get_Y0() + Dy * (-0.8 / 5), "r : reset position");
        outtextxy(get_X0() - Dx * (1.8 / 5), get_Y0() + Dy * (-1.3 / 5), "m : menu");
    }
}



int main(int ac, char* av[])
{
    float borne_inf;
    float borne_sup;
    float pas;
    float Tableau_a_afficher_fonction[100];
    float Tableau_a_afficher_variable[100];
    Arbre Arbre_a_evaluer;
    int erreur = 0;
    int* erreur_pg = &erreur;
    char c[101];
    printf("veuillez entrer la fonction que vous souhaitez visualiser \n");
    fgets(c, 101, stdin);
    c[strlen(c) - 1] = '\0'; //enlève le '\n'
    typejeton* tab[100];
    *tab = analyseur(c, erreur_pg);// on effectue l'analyse lexicale
    if (*erreur_pg == 0) {
        // on demande à l'utilisateur les bornes si il n'y a pas d'erreur
        printf("Donnez a, la borne inferieure d'echantillonage de la fonction\n");
        scanf("%f", &borne_inf);
        printf("Donnez b, la borne superieure d'echantillonage de la fonction\n");
        scanf("%f", &borne_sup);
        pas = (borne_sup - borne_inf) / 100;
        printf("borne inf:%f\nborne sup:%f\npas:%f\n", borne_inf, borne_sup, pas);
        //on initialise l'erreur qui sera un pointeur, elle pourra donc etre transmise hors des fonctions sans problème
        //typejeton Tableau[] = { jetoncinq,jetonfois,jetonvar,jetonfin }; // a remplcer avec anaylseur lexical
    }
    if (*erreur_pg == 0) {
        Arbre_a_evaluer = analyse_syntaxique(*tab, erreur_pg);
    }
    if (*erreur_pg == 0) {
        int i = 0;
        for (float x = borne_inf; x < borne_sup; x += pas) {
            Tableau_a_afficher_fonction[i] = Eval(Arbre_a_evaluer, x, erreur_pg);
            Tableau_a_afficher_variable[i] = x;
            //printf("%f: %f \n", Tableau_a_afficher_variable[i], Tableau_a_afficher_fonction[i]);
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


