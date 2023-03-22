#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "analyseur_lexical.h"
#include "jeton.h"

void analyse_lexicale(typejeton tab[], int *erreur_pg, char c[]){
    char ch3[3];
    char ch4[4];
    char ch6[6];
    c="sin(x+3)";
    int j=0,l=0;
    printf("passage dans ana lexixal \n");
    for(int i=0;i<strlen(c);i++){
        printf("%d :",i);
        if(i==0 && c[i]=='-'){
            tab[j].lexem=FONCTION;
            tab[j].valeur.fonction=VAL_NEG;
            j++;
            printf("valneg detecte \n");
        }
        if ((c[i])==' '){
            continue;
        }
        else if (c[i]=='+'){
            tab[j].lexem=OPERATEUR;
            tab[j].valeur.operateur=PLUS;
            j++;
            printf("+ detecte \n");
        }
        else if (c[i]=='-'){
            tab[j].lexem=OPERATEUR;
            tab[j].valeur.operateur=MOINS;
            j++;
            printf("- detecte \n");
        }
        else if (c[i]=='*'){
            tab[j].lexem=OPERATEUR;
            tab[j].valeur.operateur=FOIS;
            j++;
            printf("* detecte \n");
        }
        else if (c[i]=='/'){
            tab[j].lexem=OPERATEUR;
            tab[j].valeur.operateur=DIV;
            j++;
            printf("/ detecte \n");
        }
        else if (c[i]=='^'){
            tab[j].lexem=OPERATEUR;
            tab[j].valeur.operateur=PUIS;
            j++;
            printf("^ detecte \n");
        }  
        else if (isdigit(c[i])){
            tab[j].lexem=REEL;
            tab[j].valeur.reel=c[i];
            j++;
            printf("reel detecte \n");
        }
        else if(c[i]=='x'){
            tab[j].lexem=VARIABLE;
            j++;
            printf("variable detecte \n");
        }
        else if(isalpha(c[i])){
            l=0;
            if(i>=2){
                for(int k=i-2;k<=i;k++){
                    ch3[l]=c[k];
                    l++;
                    if(strcmp(ch3,"ABS")==0){
                        tab[j].valeur.fonction=ABS;
                        j++;
                        printf("abs detecte \n");
                    }
                    else if (strcmp(ch3,"SIN")==0){
                        tab[j].valeur.fonction=SIN;
                        j++;
                        printf("sin detecte \n");
                    }
                    else if (strcmp(ch3,"LOG")==0){
                        tab[j].valeur.fonction=LOG;
                        j++;
                        printf("log detecte \n");
                    }
                    else if(strcmp(ch3,"COS")==0){
                        tab[j].valeur.fonction=COS;
                        j++;
                        printf("cos detecte \n");
                    }
                    else if (strcmp(ch3,"TAN")==0){
                        tab[j].valeur.fonction=TAN;
                        j++;
                        printf("tan detecte \n");
                    }
                    else if (strcmp(ch3,"EXP")==0){
                        tab[j].valeur.fonction=EXP;
                        j++;
                        printf("tan detecte \n");
                    }
                }
            }
            if(i>=3){
                for(int k=i-3;k<=i;k++){
                    ch4[l]=c[k];
                    l++;
                    if (strcmp(ch4,"SQRT")==0){
                        tab[j].valeur.fonction=SQRT;
                        j++;
                        printf("sqrt detecte \n");
                    }
                    else if (strcmp(ch4,"SINC")==0){
                        tab[j].valeur.fonction=SINC;
                        j++;
                        printf("sinc detecte \n");
                    }
                }
            }
            if(i>=5){
                for(int k=i-5;k<=i;k++){
                    ch6[l]=c[k];
                    l++;
                    if (strcmp(ch6,"ENTIER")==0){
                        tab[j].valeur.fonction=ENTIER;
                        j++;
                        printf("fonc entier detecte \n");
                    }
                }
            }
        }
        else if(c[i]=='('){
            tab[j].lexem=PAR_OUV;
            j++;
            printf("( detecte \n");
        }
        else if(c[i]==')'){
            tab[j].lexem=PAR_FERM;
            j++;
            printf(") detecte \n");
        }
        else if(c[i]=='|'){
            tab[j].lexem=BAR;
            j++;
            printf("| detecte \n");
        }
        else if(c[i]=='\0'){
            tab[j].lexem=FIN;
            j++;
            printf("fin detecte \n");
        }
            
      else{
          *erreur_pg=100;
      }
   }
}