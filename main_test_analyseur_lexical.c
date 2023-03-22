#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "analyseur_lexical.h"
#include "jeton.h"


int main()
{
    const char *expression = "|-4xcos(5X)|";
    /*typejeton *result = analyse_lexicale(expression);
    for (int i = 0; i < 14; i++)
    {
        printf("i = %d, lexem : %d, fonction :  %d, operateur : %d, reel : %f \n\n", i, result[i].lexem, result[i].valeur.fonction, result[i].valeur.operateur, result[i].valeur.reel);
    }
    */
    return 0;
}