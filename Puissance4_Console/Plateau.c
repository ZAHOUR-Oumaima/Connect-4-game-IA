#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "NotreListe.h"
#include "Plateau.h"
#include "Outil.h"


void Afficher(int i,int j)   // Colorer les cases du plateau
{
    if(Plateau[i][j]==1)
    {
        Color(9,9);printf("   ");Color(15,0);
    }
    else if(Plateau[i][j]==2)
    {
        Color(6,6);printf("   ");Color(15,0);
    }
    else
    {
        Color(0,0);printf("   ");Color(15,0);
    }
}


void Ajouter(int C[6][7],Liste *l)
{
    int i,j;
    Liste l0=*l;
    Noeud* nouveau=(Noeud*)malloc(sizeof(Noeud));
    for(i=0;i<6;i++)
    {
        for(j=0;j<7;j++)
        {
            nouveau->M[i][j]=C[i][j];
        }
    }
    l0.taille++;
    nouveau->suivant=l0.sommet;
    l0.sommet=nouveau;
    *l=l0;

}

void grille()
{
    Logo();
    printf("\n\n\n");
    printf("                             +-----+-----+-----+-----+-----+-----+-----+\n");
  printf("                             | ");Afficher(5,0);printf(" | ");Afficher(5,1);printf(" | ");Afficher(5,2);printf(" | ");Afficher(5,3);printf(" | ");Afficher(5,4);printf(" | ");Afficher(5,5);printf(" | ");Afficher(5,6);printf(" |\n");
  printf("                             | ");Afficher(5,0);printf(" | ");Afficher(5,1);printf(" | ");Afficher(5,2);printf(" | ");Afficher(5,3);printf(" | ");Afficher(5,4);printf(" | ");Afficher(5,5);printf(" | ");Afficher(5,6);printf(" |\n");
  printf("                             +-----+-----+-----+-----+-----+-----+-----+\n");
  printf("                             | ");Afficher(4,0);printf(" | ");Afficher(4,1);printf(" | ");Afficher(4,2);printf(" | ");Afficher(4,3);printf(" | ");Afficher(4,4);printf(" | ");Afficher(4,5);printf(" | ");Afficher(4,6);printf(" |\n");
  printf("                             | ");Afficher(4,0);printf(" | ");Afficher(4,1);printf(" | ");Afficher(4,2);printf(" | ");Afficher(4,3);printf(" | ");Afficher(4,4);printf(" | ");Afficher(4,5);printf(" | ");Afficher(4,6);printf(" |\n");
  printf("                             +-----------------------------------------+\n");
  printf("                             | ");Afficher(3,0);printf(" | ");Afficher(3,1);printf(" | ");Afficher(3,2);printf(" | ");Afficher(3,3);printf(" | ");Afficher(3,4);printf(" | ");Afficher(3,5);printf(" | ");Afficher(3,6);printf(" |\n");
  printf("                             | ");Afficher(3,0);printf(" | ");Afficher(3,1);printf(" | ");Afficher(3,2);printf(" | ");Afficher(3,3);printf(" | ");Afficher(3,4);printf(" | ");Afficher(3,5);printf(" | ");Afficher(3,6);printf(" |\n");
  printf("                             +-----------------------------------------+\n");
  printf("                             | ");Afficher(2,0);printf(" | ");Afficher(2,1);printf(" | ");Afficher(2,2);printf(" | ");Afficher(2,3);printf(" | ");Afficher(2,4);printf(" | ");Afficher(2,5);printf(" | ");Afficher(2,6);printf(" |\n");
  printf("                             | ");Afficher(2,0);printf(" | ");Afficher(2,1);printf(" | ");Afficher(2,2);printf(" | ");Afficher(2,3);printf(" | ");Afficher(2,4);printf(" | ");Afficher(2,5);printf(" | ");Afficher(2,6);printf(" |");      printf("\t _______________\n");
  printf("                             +-----------------------------------------+");                                                                                                                                                                printf("\t|               |\n");
  printf("                             | ");Afficher(1,0);printf(" | ");Afficher(1,1);printf(" | ");Afficher(1,2);printf(" | ");Afficher(1,3);printf(" | ");Afficher(1,4);printf(" | ");Afficher(1,5);printf(" | ");Afficher(1,6);printf(" |");      tour();
  printf("                             | ");Afficher(1,0);printf(" | ");Afficher(1,1);printf(" | ");Afficher(1,2);printf(" | ");Afficher(1,3);printf(" | ");Afficher(1,4);printf(" | ");Afficher(1,5);printf(" | ");Afficher(1,6);printf(" |");      printf("\t|_______________|\n");
  printf("                             +-----------------------------------------+\n");
  printf("                             | ");Afficher(0,0);printf(" | ");Afficher(0,1);printf(" | ");Afficher(0,2);printf(" | ");Afficher(0,3);printf(" | ");Afficher(0,4);printf(" | ");Afficher(0,5);printf(" | ");Afficher(0,6);printf(" |");printf("\tnombre de noeud traites: %d\n",nbr);
  printf("                             | ");Afficher(0,0);printf(" | ");Afficher(0,1);printf(" | ");Afficher(0,2);printf(" | ");Afficher(0,3);printf(" | ");Afficher(0,4);printf(" | ");Afficher(0,5);printf(" | ");Afficher(0,6);printf(" |\n");
  printf("                             +-----+-----+-----+-----+-----+-----+-----+\n");
  printf("                              ||0|| ||1|| ||2|| ||3|| ||4|| ||5|| ||6||\n\n");
}
