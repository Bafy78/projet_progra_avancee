#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "analyseur_lexical.h"


// Récupère le jeton suivant dans l'entrée
typejeton get_next_token(const char** input, typejeton prev_jeton,int *erreur_pg)
{
    typejeton token;
    token.lexem = NO_TOKEN;

    // Si l'entrée est vide, retourne un jeton sans type
    if (!*input)
    {
        return token;
    }
    // Ignorer les espaces
    while (isspace(**input))
    {
        (*input)++;
    }

    // Lecture du caractère suivant
    char c = **input;

    // Détection des lexèmes
    if (isdigit(c) || c == '.')
    {
        // Extrait le nb REEL
        token.lexem = REEL;
        sscanf(*input, "%f", &token.valeur.reel);
        while (isdigit(**input) || **input == '.')
        {
            (*input)++;
        }
    }
    else if (isalpha(c))
    {
        // FONCTION ou VARIABLE
        if (c == 'x' || c == 'X')
        {
            token.lexem = VARIABLE;
            (*input)++;
        }
        else
        {
            token.lexem = FONCTION;
            int found = 0;

            // Comparaison avec les noms de fonctions supportées
            const char* fonctions[] = { "abs", "sin", "sqrt", "log", "cos", "tan", "exp", "entier", "val_neg", "sinc" };
            for (int i = 0; i < sizeof(fonctions) / sizeof(fonctions[0]); i++)
            {
                int len = strlen(fonctions[i]);
                if (strncmp(*input, fonctions[i], len) == 0)
                {
                    token.valeur.fonction = (typefonction)i;
                    *input += len;
                    found = 1;
                    break;
                }
            }

            // Si aucune fonction trouvée, retourne un jeton d'erreur
            if (!found)
            {
                *erreur_pg = 101; // Code d'erreur pour fonction inconnue
                token.lexem = ERREUR;
                (*input)++;
            }
        }
    }
    else
    {
        // Autres caractères
        switch (c)
        {
        case '+':
            token.lexem = OPERATEUR;
            token.valeur.operateur = PLUS;
            (*input)++;
            break;
        case '-':
            // Si '-' est un signe moins ou une fonction pour une valeur négative
            if (prev_jeton.lexem == NO_TOKEN || prev_jeton.lexem == PAR_OUV || prev_jeton.lexem == ABSOLU)
            {
                token.lexem = FONCTION;

                token.valeur.fonction = VAL_NEG;
            }
            else
            {

                token.lexem = OPERATEUR;

                token.valeur.operateur = MOINS;
            }
            (*input)++;
            break;
        case '*':
            token.lexem = OPERATEUR;
            token.valeur.operateur = FOIS;
            (*input)++;
            break;
        case '/':
            token.lexem = OPERATEUR;
            token.valeur.operateur = DIV;
            (*input)++;
            break;
        case '^':
            token.lexem = OPERATEUR;
            token.valeur.operateur = PUIS;
            (*input)++;
            break;
        case '(':
            token.lexem = PAR_OUV;
            (*input)++;
            break;
        case ')':
            token.lexem = PAR_FERM;
            (*input)++;
            break;
        case '|':
            /*       if ((*input)[1] == '|')
                  { */
            token.lexem = ABSOLU;
            (*input)++;

            /*             else
                        {
                            token.lexem = ERREUR;
                            token.valeur.erreur = 102; // Code d'erreur pour caractère inconnu
                        } */
            break;
        case '\0':
            token.lexem = FIN;
            break;
        default:
            token.lexem = ERREUR;
            *erreur_pg = 102; // Code d'erreur pour caractère inconnu
            (*input)++;
            break;
        }
    }

    return token;
}

// Fonction qui prend une expression et retourne un tableau de jetons
typejeton* analyseur(const char* expression,int *erreur_pg)

{
    typejeton static result[length_Tab];
    typejeton prev_jeton;
    prev_jeton.lexem = NO_TOKEN;
    // const char *expression = "(-5cos(-x))";
    int i = 0;

    const char* input = expression;

    typejeton token;
    typejeton inserted_times;

    // Ajoutez ces tableaux pour stocker les noms des opérateurs et des fonctions
    const char* operateur_names[] = { "PLUS", "MOINS", "FOIS", "DIV", "PUIS" };
    const char* fonction_names[] = { "ABS", "SIN", "SQRT", "LOG", "COS", "TAN", "EXP", "ENTIER", "VAL_NEG", "SINC" };

    do
    {
        token = get_next_token(&input, prev_jeton,erreur_pg);
        // printf("%d\n", prev_jeton.lexem);

        if ((prev_jeton.lexem == REEL || prev_jeton.lexem == VARIABLE) &&
            (token.lexem == FONCTION || token.lexem == PAR_OUV || token.lexem == VARIABLE))
        {
            result[i].lexem = OPERATEUR;
            result[i].valeur.operateur = FOIS;
            printf("OPERATEUR: %s\n", operateur_names[result[i].valeur.operateur]);

            i++;
        }
        result[i] = token;

        // Affichage des jetons pour le débogage
        switch (token.lexem)
        {
        case REEL:
            printf("REEL: %f\n", token.valeur.reel);
            break;
        case OPERATEUR:
            printf("OPERATEUR: %s\n", operateur_names[token.valeur.operateur]);
            break;
        case FONCTION:
            printf("FONCTION: %s\n", fonction_names[token.valeur.fonction]);
            break;
        case ERREUR:
            break;
        case FIN:
            printf("FIN\n");
            break;
        case PAR_OUV:
            printf("PAR_OUVR\n");
            break;
        case PAR_FERM:
            printf("PAR_FERM\n");
            break;
        case VARIABLE:
            printf("VARIABLE\n");
            break;
        case ABSOLU:
            printf("ABSOLU\n");
            break;
        default:
            printf("NO_TOKEN\n");
            break;
        }
        i++;
        prev_jeton = token;

    } while (token.lexem != FIN);
    printf("===================\n");
    printf("NB of token %d \n", i);

    return result;
}

/*int main()
{
    const char* expression = "|-4xcos(5X)|";
    typejeton* result = analyseur(expression);

        for (int i = 0; i < 14; i++)
        {
            printf("i = %d, lexem : %d, fonction :  %d, operateur : %d, reel : %f \n\n", i, result[i].lexem, result[i].valeur.fonction, result[i].valeur.operateur, result[i].valeur.reel);
        }
     
    return 0;

}*/