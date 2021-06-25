#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "JoueurVsJoueur.h"
#include "NotreListe.h"
#include "Outil.h"


void JouerVsHumain()
{

    viderPlateau();
    grille();
    while(!partieFinie(1,Plateau) && !partieFinie(2,Plateau))
    {
        if (count%2==0)
           {
            partieJoueur();
           }
        else
           {
            partieJoueur2();
           }
           count++;
           system("cls");
           grille();
    }
    if(Utilite() ==1)
    {
        printf("Bravo Joueur1 vous etes gagnant");
    }
    else if(Utilite() ==-1)
    {
        printf("Bravo Joueur2 vous etes gagnant");
    }
    else
    {
        printf("egalite!");
    }
}

void partieJoueur2()
{
    int a;
    printf("saisir votre choix de colonne ");
    scanf("%d",&a);
    while(a>6 || a<0)
    {
        printf("Vous devez choisir une colonne entre 0 et 6 : ");
        scanf("%d",&a);
    }
    while(Hauteur(a,Plateau)==6)
    {
        printf("colonne pleine! choisir une autre colonne");
        scanf("%d",&a);
        while(a>6 || a<0)
        {
            printf("Vous devez choisir une colonne entre 0 et 6 : ");
            scanf("%d",&a);
        }
    }
    Plateau[Hauteur(a,Plateau)][a]=2;
}


///partie J VS J
