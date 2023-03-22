#ifndef jeton_h
#define jeton_h

#define length_Tab 100


// �num�ration des diff�rents types de lexems existants
typedef enum
{
    REEL,
    OPERATEUR,
    FONCTION,
    ERREUR,
    FIN,
    PAR_OUV,
    PAR_FERM,
    VARIABLE,
    BAR,
    ABSOLU,
    NO_TOKEN
} typelexem;

// �num�ration des diff types d'op�rateurs existants
typedef enum
{
    PLUS,
    MOINS,
    FOIS,
    DIV,
    PUIS
} typeoperateur;

// �num�ration des diff types de fonctions existantes
typedef enum
{
    ABS,
    SIN,
    SQRT,
    LOG,
    COS,
    TAN,
    EXP,
    ENTIER,
    VAL_NEG,
    SINC
} typefonction;

// �num�ration des diff types de valeurs existantes
typedef union
{
    float reel;
    typefonction fonction;
    typeoperateur operateur;
    int erreur;
} typevaleur;

// �num�ration des diff types de jetons existants
typedef struct
{
    typelexem lexem;
    typevaleur valeur;
} typejeton;

// d�claration de l'arbre
typedef struct Node
{
    typejeton jeton;
    struct Node* fg;
    struct Node* fd;
} Node;
typedef Node* Arbre;
#endif