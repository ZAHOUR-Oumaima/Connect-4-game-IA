#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "MiniMax.h"
#include "NotreListe.h"
#include "Outil.h"
//#include "LesVarGlobales.h"


int minimax(int T[6][7], int compteur,int p)
{
    //printf("%d",compteur);
    //int c=(compteur%2)+1;
    //printf("p   =   %d\n",p);
    int a,i;
    int D[7];
    Liste l;
    if(partieFinie(1,T) || partieFinie(2,T) || p==0 )
    {
        //printf("partie fini     =      --> %d et  --> %d\n",partieFinie(1,T),partieFinie(2,T));
        nbr++;
        return h(T);
    }
    else
    {
        if(compteur%2==1)
        {
            l=genereSuccesseurs(T,compteur);
            p--;
            compteur++;
            for(i=0;i<tailleListe(l);i++)
            {
                nbr++;
                D[i]=minimax(iemeMatrice(i+1,l),compteur,p);
            }
            return Min(D);
        }
        else
        {
            l=genereSuccesseurs(T,compteur);
            p--;
            compteur++;
            for(i=0;i<tailleListe(l);i++)
            {
                nbr++;
                D[i]=minimax(iemeMatrice(i+1,l),compteur,p);
            }
            return Max(D);

        }
    }
}
