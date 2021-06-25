#ifndef OUTIL_H_INCLUDED
#define OUTIL_H_INCLUDED
#include "NotreListe.h"

extern int nbr;
extern int count;
extern int choix;
extern int HEURISTIQUE[6][7];
extern int Plateau[6][7];   // plateau du Jeu

int PlateauPlein();
void viderPlateau();
void Color(int couleurDuTexte,int couleurDeFond);
int iMax(int T[7]);
void Inverser(int T[7]);
int iMin(int T[7]);
void initialiser(Liste *l);
int tailleListe(Liste l);
int Hauteur(int j,int etat[6][7]);
int** iemeMatrice(int i,Liste l);
Liste genereSuccesseurs(int etat[6][7],int compteur);
void egalite(int T[6][7],int C[6][7]);
int MAX(int a,int b);
int MIN(int a,int b);
int Max(int T[7]);
int Min(int T[7]);
int partieFinie(int player,int Etat[6][5]);
int Utilite();
int bonnus(int player);
int h(int Etat[6][7]);
int scoreHeuristique(int i,int j,int player,int Etat[6][7]);
int score(int player,int Etat[6][7]);
int adversaire(int player);
int nbrAllignementVideHoriz(int i,int j,int player,int Etat[6][7]);
int nbrAllignementVideVertic(int i,int j,int player,int Etat[6][7]);
int nbrAllignementVideDiagD(int i,int j,int player,int Etat[6][7]);
int nbrAllignementVideDiagG(int i,int j,int player,int Etat[6][7]);
int nbrAllignementDefHoriz(int i,int j,int player,int Etat[6][7]);
int nbrAllignementDefVertic(int i,int j,int player,int Etat[6][7]);
int nbrAllignementDefDiagD(int i,int j,int player,int Etat[6][7]);
int nbrAllignementDefDiagG(int i,int j,int player,int Etat[6][7]);
int scoreDefense(int a);
int scoreAlignement(int a);
int nbrHorizAllign(int i,int j,int player,int Etat[6][7]);
int nbrVerticAllign(int i,int j,int player,int Etat[6][7]);
int nbrDiagDroiteAllign(int i,int j,int player,int Etat[6][7]);
int nbrDiagGaucheAllign(int i,int j,int player,int Etat[6][7]);
int vertic4allign(int player,int Etat[6][7]);
int horiz4allign(int player,int Etat[6][7]);
int diagD4allign(int player,int Etat[6][7]);
int diagG4allign(int player,int Etat[6][7]);
int player();
int vide(Liste l);
void Logo();
void Menu();
void MenuIA();
void tour();
void partieJoueur();

#endif // OUTIL_H_INCLUDED
