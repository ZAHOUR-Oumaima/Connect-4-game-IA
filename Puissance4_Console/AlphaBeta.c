#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "AlphaBeta.h"
#include "NotreListe.h"
#include "Outil.h"
//#include "LesVarGlobales.h"

///partieFinie
///genereSuccesseurs
///tailleListe
///MAX
///MIN
///iemeMatrice
///h

int alphabeta(int a,int b,int compteur,int p,int T[6][7])
{
	int i,v;
	Liste l;
	if(partieFinie(1,T) || partieFinie(2,T) || p==0)
	{
	    nbr++;
		return h(T);
	}
	else
	{
		if(compteur%2 +1==0)
		{
			v=-1000000;
			l=genereSuccesseurs(T,compteur);
			p--;
			compteur++;
			for(i=0;i<tailleListe(l);i++)
			{
			    nbr++;
				v=MAX(v,alphabeta(a,b,compteur,p,iemeMatrice(i+1,l)));
				if(v>b)
					return v;
                else
                    a=MAX(a,v);
			}
		}
		else
		{
			v=1000000;
			l=genereSuccesseurs(T,compteur);
			p--;
			compteur++;
			for(i=0;i<tailleListe(l);i++)
			{
			    nbr++;
				v=MIN(v,alphabeta(a,b,compteur,p,iemeMatrice(i+1,l)));
				if(a>v)
					return v;
                else
                    b=MIN(b,v);
			}
		}
		return v;
	}
}
