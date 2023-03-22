/**
* @file Graph.h
*
* @brief presente quelques outils d'affichage nécessaires dans le cadre de ce
* projet.
* Il contient la declaration des procedures disponibles pour ouvrir une fenetre
* et y dessiner des figures. Les coordonnees des points dans la fenetre sont
* definies sur l'intervalle [-1;1], (-1,-1) etant le coin inferieur gauche de
* la fenetre et (1,1) le coin superieur droit.
*
* Pour une demonstration de l'utilisation de ces procedures, voir le fichier
* main.cpp.
*
*/

float get_TranslatX();
float get_TranslatY();
float get_Zoom();
float get_A();
float get_B();
float get_C();
float get_D();
float get_X0();
float get_Y0();
float get_toggle(); 
void set_toggle(int t);

void set_TranslatX(float x);
void set_TranslatY(float y);
void set_Zoom(float z);

//Fonctions utiles aux calculs de coordonnées
float Calcul_milieu(float Coord1, float Coord2);
float abs(float x);

/**
* InitGraph
*
* Procedure d'initialisation de la fenetre et de l'environnement OpenGL
*
* @param ac nombre de parametres
* @param av tableau contenant les parametres
* @param WinName le nom (titre) de la fenetre d'affichage
* @param w la largeur de la fenetre
* @param h la hauteur de la fenetre
* @param Draw fonction qui affiche le graphique dans la fenetre
* @param Key fonction appelée lors de l'appui sur une touche c du clavier,
*	 c designant le code ascii de la touche
*
*/
void InitGraph(int ac, char* av[], const char* WinName,
    const int w, const int h, void (*Draw)(float x[], float y[]),
    void (*Key)(int c), float x[], float y[]);
/**
* line
*
* Cette procedure permet de tracer une ligne entre deux points (x0, y0) et
* (x1,y1)
*
* @param x0 abscisse du 1er point
* @param y0 ordonnée du 1er point
* @param x0 abscisse du 2eme point
* @param y0 ordonnée du 2eme point
*
*/
void line(const float x0, const float y0, const float x1, const float y1);


/**
* setcolor
*
* Cette procedure permet de definir la couleur utilisée pour tracer les lignes.
* La couleur par les valeurs des composantes rouge, vert et bleue.
*
* @param r composante rouge
* @param v composante verte
* @param b composante bleue
*
*/
void setcolor(const float r, const float v, const float b);

/**
* beginlines
*
* Cette procedure permet de commencer le trace d'une ligne brisee composee
* de n segments de droite définis par (n+1) points.
*
* @param x0 l'abscisse du premier point de la ligne brisee
* @param y0 l'ordonnée du premier point de la ligne brisee
*
*/
void beginlines(const float x0, const float y0);

/**
* lineto
*
* Cette procedure permet de d'ajouter un point a la ligne brisee en cours. Le
* dernier point defini et le nouveau point delimitent un nouveau segment de
* droite dans la ligne brisee.
*
* @param x l'abscisse du nouveau point de la ligne brisee
* @param y l'ordonnee du nouveau point de la ligne brisee
*
*/
void lineto(const float x, const float y);

/**
* finishlines
*
* Cette procedure permet de terminer le trace de la ligne brisee en cours.
*
*/
void finishlines(void);

/**
* bar
*
* Cette procédure permet de tracer un rectangle defini par son coin superieur
* gauche et son coin inferieur droit.
*
* @param x0 abscisse du coin superieur gauche du rectangle
* @param y0 ordonnee du coin superieur gauche du rectangle
* @param x1 abscisse du coin inferieur droit du rectangle
* @param y1 ordonnee du coin inferieur droit du rectangle
*
*/
void bar(const float x0, const float y0, const float x1, const float y1);

/**
* outtextxy
*
* Cette procedure permet d'ecrire une chaine de characteres s dans une zone de
* texte definie par les coordonnees x et y
*
* @param x abscisse de l'origine (coin gauche superieur) de la zone de texte
* @param y ordonnee de l'origine (coin gauche superieur) de la zone de texte
* @param s chaine de caracteres contenant le texte a afficher
*
*/
void outtextxy(const float x, const float y, const char* s);



