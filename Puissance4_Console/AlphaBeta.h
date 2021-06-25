#ifndef ALPHABETA_H_INCLUDED
#define ALPHABETA_H_INCLUDED

extern int nbr;
extern int count;

extern int HEURISTIQUE[6][7];
extern int Plateau[6][7];   // plateau du Jeu

int alphabeta(int a,int b,int compteur,int p,int T[6][7]);

#endif // ALPHABETA_H_INCLUDED
