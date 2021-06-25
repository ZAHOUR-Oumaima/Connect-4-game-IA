#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "JoueurVsMachine.h"
#include "NotreListe.h"
#include "Outil.h"
#include "MiniMax.h"
#include "AlphaBeta.h"

// apres chaque appel de genereSuccesseur ON DOIT INCREMENTER LA VARIABLE COMPTEUR
void partieMachine(int choixIA)
{
    nbr=0;
    int compteur=0,i=0;
    Liste listeSuccesseurs;
    initialiser(&listeSuccesseurs);
    int listScore[7]={0,0,0,0,0,0,0};
    Noeud* n;
    int a,aMin;
    int EtatCourant[6][7];
    egalite(EtatCourant,Plateau);
    listeSuccesseurs=genereSuccesseurs(EtatCourant,compteur);
    compteur++;
    for(n=listeSuccesseurs.sommet;n!=NULL;n=n->suivant)
    {
        if(choixIA==1)
        {
            a=minimax(n->M,compteur,4);
        }
        if(choixIA==2)
        {
            a=alphabeta(-1000000,1000000,compteur,4,n->M);
        }
        listScore[i]=a;
        i++;
    }
    Inverser(listScore);// on a besoin d'inverser le tableau pour que les elements de listScore et listeSuccesseurs soient dans le meme ordre
    aMin=iMin(listScore);//l'indice du minimum dans un tableau des entiers*/
    egalite(EtatCourant,iemeMatrice(aMin+1,listeSuccesseurs));// ieme retourne le ieme etat (la ieme matrice) dans la liste
    egalite(Plateau,EtatCourant);
}


void JouerVsIA(int choixIA)
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
            partieMachine(choixIA);
           }

           count++;
           system("cls");
           grille();
    }
    if(Utilite() ==1)
    {
        printf("Bravo Joueur vous etes gagnant\n");
    }
    else if(Utilite() ==-1)
    {
        printf("Dommage! vous etes perdant\n");
    }
    else
    {
        printf("egalite!");
    }
    printf("Entrer n'importe quel caractere pour revenir au menu :");
    getch();
    system("cls");
    Menu();
}
