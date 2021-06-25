#ifndef NOTRELISTE_H_INCLUDED
#define NOTRELISTE_H_INCLUDED


typedef struct
{
    int M[6][7];
    struct Noeud* suivant;
}Noeud;

typedef struct
{
    Noeud* sommet;
    int taille;   // la taille de la liste
}Liste;

#endif // NOTRELISTE_H_INCLUDED
