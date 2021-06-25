#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "NotreListe.h"
#include "JoueurVsMachine.h"

int nbr=0;
int count=0;
int choix;
int HEURISTIQUE[6][7]={{3,4,5,7,5,4,3},{4,6,8,10,8,6,4},{5,8,11,13,11,8,5},{5,8,11,13,11,8,5},{4,6,8,10,8,6,4},{3,4,5,7,5,4,3}};
int Plateau[6][7];   // plateau du Jeu


int main()
{
    int choixIA;
    Menu:
        system("cls");
    Menu();
    switch(choix)
    {
    case 1:
        system("cls");
        JouerVsHumain();
    case 2:
        system("cls");
        MenuIA();
        printf("\n\tSaisir votre choix : ");
        IA:
        scanf("%d",&choixIA);
        if(choixIA!= 1 && choixIA!=2)
        {
            printf("\tEntrez l'un des choix disponible ");
            goto IA;
        }
        else
        {
            system("cls");
            JouerVsIA(choixIA);
        }
    case 3:
        exit(EXIT_SUCCESS);
    default:
        printf("\tEntrez l'un des choix disponible ");
        getch();
        goto Menu;
    }

}
