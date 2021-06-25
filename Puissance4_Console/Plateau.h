#ifndef PLATEAU_H_INCLUDED
#define PLATEAU_H_INCLUDED

extern int nbr;
extern int count;

extern int HEURISTIQUE[6][7];
extern int Plateau[6][7];   // plateau du Jeu

void Afficher(int i,int j);
void Ajouter(int C[6][7],Liste *l);
void grille();

#endif // PLATEAU_H_INCLUDED
