#ifndef MINIMAX_H_INCLUDED
#define MINIMAX_H_INCLUDED
extern int nbr;
extern int count;

extern int HEURISTIQUE[6][7];
extern int Plateau[6][7];   // plateau du Jeu

int minimax(int T[6][7], int compteur,int p);

#endif // MINIMAX_H_INCLUDED
