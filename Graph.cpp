#include <windows.h>
#include "glut.h"
#include "graph.h"
#include <stdio.h>


/**
* @file Graph.cpp
*
* @brief pr�sente les quelques fonctionnalit�s n�cessaires dans le cadre de ce projet
* Il contient la d�finition des m�thodes utilis�es
*
*/

static int WindowNumber;
static int Width, Height;
static void (*AppliDraw)(float*, float*);
static void (*AppliKey)(int);
static float* Abscisse;
static float* Ordonnee;
//Modificateurs de bordures
static float TranslatX = 0;
static float TranslatY = 0;
static float zoom = 1;

//Coordonnees des bordures initiales
static float a = -9; // Init_Left
static float b = 9; // Init_Right
static float c = -5; // Init_Down
static float d = 5; // Init_Up

//Coordonnees des bordures avec modificateur
static float A; // Right
static float B; // Left
static float C; // Down
static float D; // Up

//Parametres curseur
static float t_curs; // taille du curseur
static float X_curseur;
static float Y_curseur;


//initialisation get (transfert de valeurs contenues dans le graph.cpp vers le main.cpp)
float get_TranslatX() {
    return TranslatX;
}
float get_TranslatY() {
    return TranslatY;
}
float get_Zoom() {
    return zoom;
}
float get_A() {
    return A;
}
float get_B() {
    return B;
}
float get_C() {
    return C;
}
float get_D() {
    return D;
}
float get_X0() {
    return X_curseur;
}
float get_Y0() {
    return Y_curseur;
}

/*initialisation set(fonctions pacerelles entre graph.cpp et main.cpp
afin de modifier des variables provenant de graph.cpp dans le main.cpp)*/

void set_TranslatX(float x) {
    TranslatX = x;
}
void set_TranslatY(float y) {
    TranslatY = y;
}
void set_Zoom(float z) {
    zoom = z;
}


/**
* GlutReshape
*
* Cette proc�dure permet de gerer la taille de la fenetre quand (redimensionn�e)
*
* @parma w largeur de la fenetre gl
* @parma h hauteur de la fenetre gl
*/

static void GlutReshape(const int w, const int h)
{
    Width = w;
    Height = h;
    glViewport(0, 0, Width, Height);
}

static void GlutIdle(void)
{
    //  glutPostRedisplay();
}

static void GlutKey(const unsigned char c, const int x, const int y)
{
    switch (c)
    {
    default:
        if (AppliKey) (*AppliKey)(c);
        break;
    }
    glutPostRedisplay();
}

//Calcul la valeur absloue d'un nombre
float abs(float x) {
    if (x < 0) {
        return -x;
    }
    else {
        return x;
    }
}

//Calcul du milieu de la fenetre graphique
float Calcul_milieu(float Coord1, float Coord2) {
    return ((Coord1 + Coord2) / 2);
}

//Calcul des bornes de la fenetre en fonction de la Translation(x,y) et du Zoom
float Calcul_Coordonnees(float Coord1, float Coord2, float Translat) {
    float a;
    float b;
    float milieu;
    int signe = 1;
    a = Coord1 + Translat;
    b = Coord2 + Translat;
    milieu = Calcul_milieu(a, b);
    if (a < milieu) {
        signe = -1;
    }
    return milieu + signe * abs(milieu - a) * zoom;

}

static void Begin2DDisplay() {
    A = Calcul_Coordonnees(a, b, TranslatX);
    B = Calcul_Coordonnees(b, a, TranslatX);
    C = Calcul_Coordonnees(c, d, TranslatY);
    D = Calcul_Coordonnees(d, c, TranslatY);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(A, B, C, D, 0, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0.0F, 0.0F, -1.0F);


}

static void End2DDisplay(void)
{
    /* Fin du trace, retour au parametres normaux */
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

static void InitDisplay(void)
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glClearColor(1.0F, 1.0F, 1.0F, 1.0F);
}

//Fonction servants au tracer du quadrillage
void tracer_ligneX(int i, float distanceY) {
    setcolor(0.7, 0.9, 1);
    if (i == -10000 || i == 10000) {
        setcolor(1.0F, 0.0F, 0.0F);
    }
    line(i, C, i, D);
    setcolor(0.0F, 0.0F, 0.0F);
    line(i, 0 - distanceY / 60, i, 0 + distanceY / 60);
}
void tracer_ligneY(int j, float distanceX) {
    setcolor(0.7, 0.9, 1);
    if (j == -10000 || j == 10000) {
        setcolor(1.0F, 0.0F, 0.0F);
    }
    line(A, j, B, j);
    setcolor(0.0F, 0.0F, 0.0F);
    line(0 - distanceX / 60, j, 0 + distanceX / 60, j);
}

static void GlutDraw(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Begin2DDisplay();

    X_curseur = Calcul_milieu(A, B);
    Y_curseur = Calcul_milieu(C, D);

    //Trace du quadrillage + graduations   
    int i = A;
    int j = C;
    float distanceX;
    float distanceY;
    float y;
    distanceX = abs(X_curseur - B);
    distanceY = abs(Y_curseur - D);
    char valeur[10];
    while (i <= B) {
        if (distanceY < 1000) {
            if (distanceY < 100) {
                if (distanceY < 10) {
                    tracer_ligneX(i, distanceY);
                    sprintf(valeur, "%d", i);
                    if (i != 0) {
                        outtextxy(i - distanceX * 0.01, 0 - distanceY * 0.06, valeur);
                    }
                }
                else if (i % 10 == 0) {
                    tracer_ligneX(i, distanceY);
                    sprintf(valeur, "%d", i);
                    if (i != 0) {
                        outtextxy(i - distanceX * 0.03, 0 - distanceY * 0.06, valeur);
                    }
                }
            }
            else if (i % 100 == 0) {
                tracer_ligneX(i, distanceY);
                sprintf(valeur, "%d", i);
                if (i != 0) {
                    outtextxy(i - distanceX * 0.05, 0 - distanceY * 0.06, valeur);
                }
            }
            i++;
        }
        else { i = B + 1; }

    }
    while (j <= D) {
        if (distanceY < 1000) {
            if (distanceY < 100) {
                if (distanceY < 10) {
                    tracer_ligneY(j, distanceX);
                    sprintf(valeur, "%d", j);
                    if (j != 0) {
                        outtextxy(0 - distanceX * 0.06, j, valeur);
                    }
                }
                else if (j % 10 == 0) {
                    tracer_ligneY(j, distanceX);
                    sprintf(valeur, "%d", j);
                    if (j != 0) {
                        outtextxy(0 - distanceX * 0.08, j, valeur);
                    }
                }
            }
            else if (j % 100 == 0) {
                tracer_ligneY(j, distanceX);
                sprintf(valeur, "%d", j);
                if (j != 0) {
                    outtextxy(0 - distanceX * 0.1, j, valeur);
                }
            }
            j++;
        }
        else { j = D + 1; }

    }
    outtextxy(0 - distanceX * 0.03, 0 - distanceY * 0.03, "0");

    //Trace des axes Ox & Oy
    setcolor(0, 0, 0);
    line(A, 0, B, 0); //axe Ox
    line(0, C, 0, D); //axe Oy

    //Trace curseur    
    t_curs = 40;
    setcolor(0.4F, 0.4F, 0.4F);
    line(X_curseur - abs(C - D) / t_curs, Y_curseur, X_curseur + abs(C - D) / t_curs, Y_curseur);    //curseur axe Ox
    line(X_curseur, Y_curseur - abs(C - D) / t_curs, X_curseur, Y_curseur + abs(C - D) / t_curs);    //curseur axe 0y

    //dessin du graph
    if (AppliDraw && Abscisse && Ordonnee) (*AppliDraw)(Abscisse, Ordonnee);
    End2DDisplay();
    glutSwapBuffers();
}

/**
* InitGraph
*
* Procedure d'initialisation de la fenetre et de l'environement OpenGL
* L'initialisation de GLUT se trouve dans la procedure
* principale, elle necessite l'emploie des argument de
* la ligne de commande
*
* @parma ac
* @parma av[]
* @parma WinName definit le nom (titre) de la fentre d'affichage
* @parma w definit la largeur de la fenetre
* @parma h definit la hauteur de la fenetre
* @parma Draw d�finit une m�thode de tra�age
* @parma Key d�finit une m�thode permettant la d�tection des touche du clavier
* @parma c entier designant le code ascii d'une touche
*
*/
void InitGraph(int ac, char* av[],
    const char* WinName, const int w, const int h, void (*Draw)(float x[], float y[]),
    void (*Key)(int), float x[], float y[])
{
    glutInit(&ac, av);
    Width = w;
    Height = h;
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(Width, Height);
    WindowNumber = glutCreateWindow(WinName);
    glutReshapeFunc(GlutReshape); /* fonction appelee qd fenetre redimensionnee */
    glutIdleFunc(GlutIdle); /* fonction appelee en boucle */
    AppliKey = Key;
    glutKeyboardFunc(GlutKey);
    AppliDraw = Draw;
    Abscisse = x;
    Ordonnee = y;
    glutDisplayFunc(GlutDraw);
    InitDisplay();
    glutMainLoop();
}

/**
* setcolor
*
* Cette proc�dure permet de definire une couleur par ces trois composantes
*
* @parma r composante du plan rouge
* @parma v composante du plan vert
* @parma b composante du plan bleu
*
*/
void setcolor(const float r, const float v, const float b)
{
    glColor3f(r, v, b);
}

/**
* line
*
* Cette proc�dure permet de tracher une ligne entre deux points (x0, y0) et (x1,y1)
*
* @parma x0 abscisse 1er point
* @parma y0 ordonn�e 1er point
* @parma x0 abscisse 2eme point
* @parma y0 ordonn�e 2eme point
*
*/
void line(const float x0, const float y0, const float x1, const float y1)
{
    glBegin(GL_LINES);
    glVertex2f(x0, y0);
    glVertex2f(x1, y1);
    glEnd();
}

/**
* beginlines
*
* Cette proc�dure permet
*
* @parma x0
* @parma y0
*
*/
void beginlines(const float x0, const float y0)
{
    glBegin(GL_LINE_STRIP);
    glVertex2f(x0, y0);
}

void lineto(const float x, const float y)
{
    glVertex2f(x, y);
}

void finishlines(void)
{
    glEnd();
}

void bar(const float x0, const float y0, const float x1, const float y1)
{
    glBegin(GL_QUADS);
    glVertex2f(x0, y0);
    glVertex2f(x0, y1);
    glVertex2f(x1, y1);
    glVertex2f(x1, y0);
    glEnd();
}


/**
* outtextxy
*
* Cette proc�dure permet d'ecrit une chaine de charact�re s dans une zone de texte d�finie par les coordonn�es x et y
*
* @parma x abscisse du point (coint gauche superieur) de la zone de texte
* @parma y ordonn�e du point (coint gauche superieur) de la zone de texte
* @parma s tableau de charct�res
*
*/
void outtextxy(const float x, const float y, const char* str)
{
    const char* s = str;

    glRasterPos2f(x, y);
    while (*s != '\0')
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *s++);
    }
}
