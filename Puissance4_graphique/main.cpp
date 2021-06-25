#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>



int compt=0,nbr=0;


typedef struct Matrice Matrice;
struct Matrice
{
    int A[6][7];
};


typedef struct Noeud Noeud;
struct Noeud
{
    Matrice M;
    struct Noeud* suivant;
};

typedef struct Liste Liste;
struct Liste
{
    Noeud* sommet;
    int taille;   // la taille de la liste
};

typedef struct Coordonnees Coordonnees;
struct Coordonnees
{
    int x;
    int y;
};



Matrice Grille;
int HEURISTIQUE[6][7]={{3,4,5,7,5,4,3},{4,6,8,10,8,6,4},{5,8,11,13,11,8,5},{5,8,11,13,11,8,5},{4,6,8,10,8,6,4},{3,4,5,7,5,4,3}};


void menu(SDL_Surface *Screen);
int comparaison(int EtatCourant[6][7]) ;
int PlateauPlein();
void viderPlateau();
void Color(int couleurDuTexte,int couleurDeFond);
int iMax(int T[7]);
void Inverser(int T[7]);
int iMin(int T[7]);
void initialiser(Liste *l);
int tailleListe(Liste l);
int Hauteur(int j,int etat[6][7]);
Matrice iemeMatrice(int i,Liste l);
Liste genereSuccesseurs(int etat[6][7],int compteur);
void egalite(int T[6][7],int C[6][7]);
int MAX(int a,int b);
int MIN(int a,int b);
int Max(int T[7]);
int Min(int T[7]);
int partieFinie(int player,Matrice Etat);
int Utilite();
int bonnus(int player);
int h(Matrice Etat);
int scoreHeuristique(int i,int j,int player,Matrice Etat);
int score(int player,Matrice Etat);
int adversaire(int player);
int nbrAllignementVideHoriz(int i,int j,int player,Matrice Etat);
int nbrAllignementVideVertic(int i,int j,int player,Matrice Etat);
int nbrAllignementVideDiagD(int i,int j,int player,Matrice Etat);
int nbrAllignementVideDiagG(int i,int j,int player,Matrice Etat);
int nbrAllignementDefHoriz(int i,int j,int player,Matrice Etat);
int nbrAllignementDefVertic(int i,int j,int player,Matrice Etat);
int nbrAllignementDefDiagD(int i,int j,int player,Matrice Etat);
int nbrAllignementDefDiagG(int i,int j,int player,Matrice Etat);
int scoreDefense(int a);
int scoreAlignement(int a);
int nbrHorizAllign(int i,int j,int player,Matrice Etat);
int nbrVerticAllign(int i,int j,int player,Matrice Etat);
int nbrDiagDroiteAllign(int i,int j,int player,Matrice Etat);
int nbrDiagGaucheAllign(int i,int j,int player,Matrice Etat);
int vertic4allign(int player,Matrice Etat);
int horiz4allign(int player,Matrice Etat);
int diagD4allign(int player,Matrice Etat);
int diagG4allign(int player,Matrice Etat);
int player();
int vide(Liste l);
int minimax(int T[6][7], int compteur,int p);
int alphabeta(int a,int b,int compteur,int p,int T[6][7]);
void menu2(SDL_Surface *Screen);




void viderPlateau()   // initialiser le Plateau
{
    int i,j;
    for(i=0;i<6;i++)
    {
        for(j=0;j<7;j++)
        {
            Grille.A[i][j]=0;
        }
    }
}
int tailleListe(Liste l)
{
    int i=0;
    Noeud *n=l.sommet;
    while(n!=NULL)
    {
        i++;
        n=n->suivant;
    }
    return i;
}

int PlateauPlein()
{
    int i,j;
    for(i=0;i<6;i++)
    {
        for(j=0;j<7;j++)
        {
            if(Grille.A[i][j]==0)
            {
                return 0;   //   plateau non plein
            }
        }
    }
    return 1;  //  plateau plein
}

int nbrHorizAllign(int i,int j,int player,Matrice Etat)
{
    int nbr=0;
    if((Etat.A[i][j-1]==player && j>0) || Etat.A[i][j]!=player)  return 0;
    else if(Etat.A[i][j-1]!=player)
    {
        while(Etat.A[i][j]==player && j<7)
        {
            nbr++;
            j++;
        }
    }
        return nbr;
}




int nbrVerticAllign(int i,int j,int player,Matrice Etat)
{
    int nbr=0;
    if((Etat.A[i-1][j]==player && i>0) || Etat.A[i][j]!=player)   return 0;
    else if(Etat.A[i-1][j]!=player)
    {
        if(Etat.A[i][j]==player)
        {
            while(Etat.A[i][j]==player && i<6)
            {
                nbr++;
                i++;
            }
        }
        return nbr;
    }
}

int nbrDiagDroiteAllign(int i,int j,int player,Matrice Etat)
{
    int nbr=0;
    if((Etat.A[i-1][j-1]==player && i>0 && j>0) || Etat.A[i][j]!=player)
        return 0;

    else if(Etat.A[i-1][j-1]!=player)
    {
        while(Etat.A[i][j]==player && j<7 && i<6)
        {
            nbr++;
            i++;j++;
        }
        return nbr;
    }
}



int nbrDiagGaucheAllign(int i,int j,int player,Matrice Etat)
{
    int nbr=0;
    if((Etat.A[i-1][j+1]==player && j+1<7 && i>0) || Etat.A[i][j]!=player)
        return 0;
    else if((Etat.A[i-1][j+1]!=player && i-1>=0 && j+1<7) || i==0 || j==6)
    {
        while(Etat.A[i][j]==player && i<6 && j>=0)
        {
            nbr++;
            i++;
            j--;
        }
        return nbr;
    }

}




int nbrAllignementVideHoriz(int i,int j,int player,Matrice Etat)
{
    int horiz=nbrHorizAllign(i,j,player,Etat);
    if((horiz!=0 && ((j+horiz)<7 && Etat.A[i][j+horiz]==0)) || (j-1>=0 && Etat.A[i][j-1]==0) )
        return horiz;
    return 0;
}


int nbrAllignementVideVertic(int i,int j,int player,Matrice Etat)
{
    int vertic=nbrVerticAllign(i,j,player,Etat);
    if(vertic!=0 && (i+vertic)<6 && Etat.A[i+vertic][j]==0)
        return vertic;
    return 0;
}


int nbrAllignementVideDiagD(int i,int j,int player,Matrice Etat)
{
    int diag=nbrDiagDroiteAllign(i,j,player,Etat);
    if(diag!=0 && (((i+diag)<6 && (j+diag)<7 && Etat.A[i+diag][j+diag]==0) || (i-1>=0 && j-1>=0 && Etat.A[i-1][j-1]==0)) && ((j<3 && i<3+j) || (j>3 && i>=j-3) || j==3))
        return diag;
    return 0;
}


int nbrAllignementVideDiagG(int i,int j,int player,Matrice Etat)
{
    int diag=nbrDiagGaucheAllign(i,j,player,Etat);
    if(diag!=0 && ( ((i+diag)<6 && (j-diag)>=0 && Etat.A[i+diag][j-diag]==0) || (i-1>=0 && j+1<7 && Etat.A[i-1][j+1]==0) ) && ((j<3 && i>=3-j) || (j>3 && i<=8-j) || j==3))
        return diag;
    return 0;
}

int adversaire(int player)        // l'adversaire de player
{
    if(player==1)
        return 2;
    return 1;
}

int nbrAllignementDefHoriz(int i,int j,int player,Matrice Etat)
{
    int horiz=nbrHorizAllign(i,j,adversaire(player),Etat);
    	if(horiz!=0 && ( ( ((j+horiz)<7 && Etat.A[i][j+horiz]==player) && (j-1>=0 && Etat.A[i][j-1]==player) )) || (j-1<0 && Etat.A[i][j+horiz]==player) || (j+horiz>=7 && Etat.A[i][j-1]==player) )
    		return -horiz;
        else if(horiz!=0 && ( ((j+horiz)<7 && Etat.A[i][j+horiz]==player) || (j-1>=0 && Etat.A[i][j-1]==player)) )
            return horiz;
        else
        	return 0;

}


int nbrAllignementDefVertic(int i,int j,int player,Matrice Etat)
{
    int vertic=nbrVerticAllign(i,j,adversaire(player),Etat);
        if(vertic!=0 && (i+vertic)<6 && i<3 && Etat.A[i+vertic][j]==player)
            return vertic;
        return 0;
}


int nbrAllignementDefDiagD(int i,int j,int player,Matrice Etat)
{
    int diag=nbrDiagDroiteAllign(i,j,adversaire(player),Etat);
        if((diag!=0 && ( ((i+diag)<6 && (j+diag)<7 && Etat.A[i+diag][j+diag]==player) && (i-1>=0 && j-1>=0 && Etat.A[i-1][j-1]==player)) || ((j+diag>=7 || i+diag>=6 ) && Etat.A[i-1][j-1]==player) || ((i-1<0 || j-1<0) && Etat.A[i+diag][j+diag]==player) ) && ((j<3 && i<3+j) || (j>3 && i>=j-3) || j==3))
            return -diag;
        else if(diag!=0 && (((i+diag)<6 && (j+diag)<7 && Etat.A[i+diag][j+diag]==player) || (i-1>=0 && j-1>=0 && Etat.A[i-1][j-1]==player)) && ((j<3 && i<3+j) || (j>3 && i>=j-3) || j==3))
        	return diag;
        else
        	return 0;

}


int nbrAllignementDefDiagG(int i,int j,int player,Matrice Etat)
{
    int diag=nbrDiagGaucheAllign(i,j,adversaire(player),Etat);
        if(diag!=0 && (((j<3 && i>=3-j) || (j>3 && i<=8-j) || j==3) && ((i+diag<6 && j-diag>=0 && Etat.A[i+diag][j-diag]==player) && (i-1>=0 && j+1<7 && Etat.A[i-1][j+1]==player)) || ((i+diag>=6 || j-diag<0) && Etat.A[i-1][j+1]==player) || ((i-1<0 || j+1>6) && Etat.A[i+diag][j-diag]==player) ) )
            return -diag;
        else if(diag!=0 && (((j<3 && i>=3-j) || (j>3 && i<=8-j) || j==3) && ((i+diag<6 && j-diag>=0 && Etat.A[i+diag][j-diag]==player) || (i-1>=0 && j+1<7 && Etat.A[i-1][j+1]==player))))
        	return diag;
        else
        	return 0;
}


int vertic4allign(int player,Matrice Etat)
{
    int i,j;
    for(i=0;i<6;i++)
    {
        for(j=0;j<7;j++)
        {
            if(nbrVerticAllign(i,j,player,Etat)>=4)
                return 1;
        }
    }
    return 0;
}





int horiz4allign(int player,Matrice Etat)
{
    int i,j;
    for(i=0;i<6;i++)
    {
        for(j=0;j<7;j++)
        {
            if(nbrHorizAllign(i,j,player,Etat)>=4)
            {
                return 1;     // Player est gagnant
            }
        }
    }
    return 0;
}

int diagD4allign(int player,Matrice Etat)
{
    int i,j;
    for(i=0;i<6;i++)
    {
        for(j=0;j<7;j++)
        {
            if(nbrDiagDroiteAllign(i,j,player,Etat)>=4)
            {
                return 1;     // Player est gagnant
            }
        }
    }
    return 0;
}

int diagG4allign(int player,Matrice Etat)
{
    int i,j;
    for(i=0;i<6;i++)
    {
        for(j=0;j<7;j++)
        {
            if(nbrDiagGaucheAllign(i,j,player,Etat)>=4)
            {
                return 1;     // Player est gagnant
            }
        }
    }
    return 0;
}




int partieFinie(int player,Matrice Etat)
{
    if (horiz4allign(player,Etat) || vertic4allign(player,Etat) || diagD4allign(player,Etat) || diagG4allign(player,Etat) || PlateauPlein())
        return 1;
    return 0;
}



int Hauteur(int j,int etat[6][7])    // nombre de cases pleines d'une colonne donnée
{
    int i=0;
    while(etat[i][j]!=0)
    {
        i++;
    }
    return i;
}

void Ajouter(int C[6][7],Liste *l)
{
    int i,j;
    Liste l0=*l;
    Noeud* nouveau=(Noeud*)malloc(sizeof(Noeud));
    for(i=0;i<6;i++)
    {
        for(j=0;j<7;j++)
        {
            nouveau->M.A[i][j]=C[i][j];
        }
    }
    l0.taille++;
    nouveau->suivant=l0.sommet;
    l0.sommet=nouveau;
    *l=l0;

}

Matrice iemeMatrice(int i,Liste l)
{
    int a=tailleListe(l);
    Noeud *n0;
    n0=l.sommet;
        while(n0!=NULL && a!=i)
        {
            n0=n0->suivant;
            a--;
        }
    return n0->M;
}


void egalite(int T[6][7],int C[6][7]) // copie la matrice C dans la matrice T
{
    int i,j;
    for(i=0;i<6;i++)
    {
        for(j=0;j<7;j++)
        {
            T[i][j]=C[i][j];
        }
    }
}


void initialiser(Liste *l)
{
    l->sommet=NULL;
    l->taille=0;
}

Liste genereSuccesseurs(int etat[6][7],int compteur)
{
    int i,j;
    int C[6][7];
    Liste l;
    initialiser(&l);
    egalite(C,etat);
    if(!PlateauPlein())
    {
        for(j=0;j<7;j++)
        {
            i=Hauteur(j,etat);
            if(i<6)
            {
                if(compteur%2==0)
                    {
                        C[i][j]=2;
                        Ajouter(C,&l);
                        egalite(C,etat);
                    }
                if(compteur%2!=0)
                {
                    C[i][j]=1;
                    Ajouter(C,&l);
                    egalite(C,etat);
                }

            }
        }
    }
    return l;
}

int iMax(int T[7])
{
   int imax=0,i,maximum=T[0];
   for(i=0;i<7;i++)
   {
        if(T[i]>maximum)
        {
            maximum=T[i];
            imax=i;
        }
   }
   return imax;
}
int iMin(int T[7])
{
   int imin=0,i,minimum=T[0];
   for(i=0;i<7;i++)
   {
        if(T[i]<minimum)
        {
            minimum=T[i];
            imin=i;
        }
   }
   return imin;
}



int Max(int T[7])
{
   int i,maximum=T[0];
   for(i=0;i<7;i++)
   {
        if(T[i]>maximum)
            maximum=T[i];
   }
   return maximum;
}

int Min(int T[7])
{
   int i,minimum=T[0];
   for(i=0;i<7;i++)
   {
        if(T[i]<minimum)
            minimum=T[i];
   }
   return minimum;
}



int Utilite()
{
    if(PlateauPlein())
    {
            return 0;
    }

    if(horiz4allign(1,Grille) || vertic4allign(1,Grille) || diagD4allign(1,Grille) || diagG4allign(1,Grille))
    {
            return 1;
    }

    if(horiz4allign(2,Grille) || vertic4allign(2,Grille) || diagD4allign(2,Grille) || diagG4allign(2,Grille))
    {
            return -1;
    }

}

int bonnus(int player)
{
    if(player==1)
        return 20;
    return -20;
}


int h(Matrice Etat)
{
    int x=(score(1,Etat) - score(2,Etat)); //+ bonnus(player());
    //printf("h(n) =  %d\n",x);
    //printf("bonnus =  %d\n",bonnus(player()));
    return x;
}
// h(n)--->cout d'un etat-----> score(max_dans_un_etat)-score(min_dans_un_etat)
// genereSuccesseurs(liste* L,Case A[6][7])


void Inverser(int T[7])
{
    int i;
    int M[7];
    for(i=0;i<7;i++)
    {
        M[i]=T[i];
    }
    for(i=0;i<7;i++)
    {
        T[i]=M[6-i];
    }
}


int minimax(Matrice T, int compteur,int p)
{

    int a,i;
    int D[7];
    Liste l;
    if(partieFinie(1,T) || partieFinie(2,T) || p==0 )
    {

        return h(T);
    }
    else
    {
        if(compteur%2==1)
        {
            l=genereSuccesseurs(T.A,compteur);
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
            l=genereSuccesseurs(T.A,compteur);
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


int MAX(int a,int b)
{
	if(a>b)
		return a;
	return b;
}

int MIN(int a,int b)
{
	if(a>b)
		return b;
	return a;
}





int alphabeta(int a,int b,int compteur,int p,Matrice T)
{
	int i,v;
	Liste l;
	if(partieFinie(1,T) || partieFinie(2,T) || p==0)
	{
	    //printf("partie fini     =      --> %d et  --> %d\n",partieFinie(1,T),partieFinie(2,T));
	    //nbr++;
		return h(T);
	}
	else
	{
		if(compteur%2==0)    //turn MAX
		{
			v=-1000000;
			l=genereSuccesseurs(T.A,compteur);
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
		else   // turn MIN
		{
			v=1000000;
			l=genereSuccesseurs(T.A,compteur);
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


int scoreHeuristique(int i,int j,int player,Matrice Etat)
{
    if(Etat.A[i][j]==player)
    {
        return HEURISTIQUE[i][j];
    }
    else if(Etat.A[i][j]==adversaire(player))
    {
        return -HEURISTIQUE[i][j];
    }
    else
        return 0;
}



int score(int player,Matrice Etat)
{
    int resultat=0,i,j;
    for(i=0;i<6;i++)
    {
        for(j=0;j<7;j++)
        {
            if(nbrAllignementVideHoriz(i,j,adversaire(player),Etat)>=4 || nbrAllignementVideVertic(i,j,adversaire(player),Etat)>=4 || nbrAllignementVideDiagD(i,j,adversaire(player),Etat)>=4 || nbrAllignementVideDiagG(i,j,adversaire(player),Etat)>=4)
            {
                return 0;
            }
            else if(nbrAllignementVideHoriz(i,j,player,Etat)>=4 || nbrAllignementVideVertic(i,j,player,Etat)>=4 || nbrAllignementVideDiagD(i,j,player,Etat)>=4 || nbrAllignementVideDiagG(i,j,player,Etat)>=4)
                resultat= resultat + 2*scoreAlignement(nbrAllignementVideHoriz(i,j,player,Etat))+ 2*scoreAlignement(nbrAllignementVideVertic(i,j,player,Etat))+2*scoreAlignement(nbrAllignementVideDiagD(i,j,player,Etat))+ 2*scoreAlignement(nbrAllignementVideDiagG(i,j,player,Etat))+ scoreDefense(nbrAllignementDefHoriz(i,j,player,Etat))+ scoreDefense(nbrAllignementDefVertic(i,j,player,Etat))+ scoreDefense(nbrAllignementDefDiagD(i,j,player,Etat))+ scoreDefense(nbrAllignementDefDiagG(i,j,player,Etat))+scoreHeuristique(i,j,player,Etat);
            else
                resultat= resultat + scoreAlignement(nbrAllignementVideHoriz(i,j,player,Etat))+ scoreAlignement(nbrAllignementVideVertic(i,j,player,Etat))+scoreAlignement(nbrAllignementVideDiagD(i,j,player,Etat))+ scoreAlignement(nbrAllignementVideDiagG(i,j,player,Etat))+ scoreDefense(nbrAllignementDefHoriz(i,j,player,Etat))+ scoreDefense(nbrAllignementDefVertic(i,j,player,Etat))+ scoreDefense(nbrAllignementDefDiagD(i,j,player,Etat))+ scoreDefense(nbrAllignementDefDiagG(i,j,player,Etat))+scoreHeuristique(i,j,player,Etat);

        }
    }
    return resultat;
}












int scoreDefense(int a)
{
	if(a==-1)
        return 10;
    if(a==-2)
        return 150;
    if(a==-3)
        return 500;
    if(a==0)
        return 0;
    if(a==1)
        return 1;
    if(a==2)
        return 100;
    if(a==3)
        return 300;
    //if(a==4)
       //return 100000000;
}



int scoreAlignement(int a)
{
    if(a==0)
        return 0;
    if(a==1)
        return 20;
    if(a==2)
        return 200;
    if(a==3)
        return 1000;
    else
        return 1000000;
}






int player()
{
    if(compt %2==0) return 1;
    if(compt %2==1) return 2;
}


int colonne(int x)    // la position x du curseur
{
    int j=0;   // colonne
    int i=0;    // nbr de pixel
    while(x<353+i || x>438+i)
    {
        j++;
        i=i+85;  // la colonne suivante
    }
    return j;
}


int HauteurPx(int Colonne,int Etat[6][7])
{
    int lignePX;
    int a=Hauteur(Colonne,Etat);
    lignePX=a*84;  // nbr de px plein pour une colonne
    return lignePX;
}


int colonnePlein(int colonne,int Etat[6][7])
{
    if(Hauteur(colonne,Etat)==6)
        return 1;
    return 0;
}


int curseur(int x)
{
    int pos=360;
    int i=0;
    while(x<353+i || x>438+i)
    {
        pos=pos+85;
        i=i+85;  // la colonne suivante
    }
    return pos;
}


Coordonnees coordonneesPX(int i,int j)
{
    Coordonnees pos;
    pos.x=353+85*j;
    pos.y=561-84*i;
    return pos;
}


void Affichage(SDL_Surface *Screen)
{
    int i,j;
    SDL_Surface *PionJ,*PionM;
    SDL_Rect posPion;
    PionJ=IMG_Load("Images/PionJ.png");
    PionM=IMG_Load("Images/PionM.png");
    for(i=0;i<6;i++)
    {
        for(j=0;j<7;j++)
        {
            posPion.x=coordonneesPX(i,j).x;posPion.y=coordonneesPX(i,j).y;
            if(Grille.A[i][j]==1)
            {
                SDL_BlitSurface(PionJ,NULL,Screen,&posPion);
            }
            else if(Grille.A[i][j]==2)
            {
                SDL_BlitSurface(PionM,NULL,Screen,&posPion);
            }
        }
    }
    SDL_FreeSurface(PionJ);
    SDL_FreeSurface(PionM);
}



void partieJoueur(SDL_Surface *Screen)
{
    int i;
    SDL_Event event;
    int Colonne;
    int cont=1;
    int a=360;
    SDL_Surface *PionJ,*Plateau,*Cursor,*Fond2,*FondP,*CursorR,*TourJ,*cadre;
    SDL_Rect posPlateau,posPion,posCursor,posCadre,posPCadre;
    SDL_Rect posFond,posFondP;
    posFond.x=0;posFond.y=0;posFondP.x=355;posFondP.y=140;posCadre.x=20;posCadre.y=465;posPCadre.x=65;posPCadre.y=575;
    posPlateau.x=350;posPlateau.y=130;posCursor.y=40;posPion.x=Colonne;posPion.y=141;
    Plateau=IMG_Load("Images/Plateau.png");
    Cursor=IMG_Load("Images/Cursor.png");
    CursorR=IMG_Load("Images/CursorR.png");
    PionJ=IMG_Load("Images/PionJ.png");
    Fond2=IMG_Load("images/Fond3.png");
    FondP=IMG_Load("Images/FondP.png");
    cadre=IMG_Load("Images/cadre.png");
    SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 255, 255, 255));
    while(cont)
    {
        SDL_BlitSurface(Fond2,NULL,Screen,&posFond);
        SDL_BlitSurface(cadre,NULL,Screen,&posCadre);
        SDL_BlitSurface(PionJ,NULL,Screen,&posPCadre);
        SDL_BlitSurface(FondP,NULL,Screen,&posFondP);
        Affichage(Screen);
        SDL_BlitSurface(Plateau,NULL,Screen,&posPlateau);
        SDL_WaitEvent(&event);
        if(event.type==SDL_MOUSEMOTION)
        {
            if(event.button.y>35 && event.button.y<687 && event.button.x>353 && event.button.x<948)
            {
                a=curseur(event.button.x);
                posCursor.x=a;
            }
            else
            {
                posCursor.x=a;
            }
            SDL_BlitSurface(Cursor,NULL,Screen,&posCursor);
            SDL_Flip(Screen);
            SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 255, 255, 255));
        }
        if(event.type==SDL_QUIT)
        {
            cont=0;
            SDL_Quit();
        }
        if(event.type==SDL_MOUSEBUTTONDOWN)
        {
            if(event.button.y>35 && event.button.y<687 && event.button.x>353 && event.button.x<948)
            {
                if(colonnePlein(colonne(event.button.x),Grille.A)==1)
                {
                    SDL_BlitSurface(CursorR,NULL,Screen,&posCursor);
                    SDL_Flip(Screen);
                    SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 255, 255, 255));
                }
                else
                {
                    for(i=141;i<=561-HauteurPx(colonne(event.button.x),Grille.A);i=i+15)     // i ---> y
                    {
                        SDL_Rect posPion;
                        posPion.x=curseur(event.button.x);posPion.y=i;
                        SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 255, 255, 255));
                        SDL_BlitSurface(Fond2,NULL,Screen,&posFond);
                        SDL_BlitSurface(cadre,NULL,Screen,&posCadre);
                        SDL_BlitSurface(PionJ,NULL,Screen,&posPCadre);
                        SDL_BlitSurface(FondP,NULL,Screen,&posFondP);
                        Affichage(Screen);
                        SDL_BlitSurface(PionJ,NULL,Screen,&posPion);
                        SDL_BlitSurface(Plateau,NULL,Screen,&posPlateau);
                        SDL_Flip(Screen);
                    }
                    Grille.A[Hauteur(colonne(event.button.x),Grille.A)][colonne(event.button.x)]=1;
                    cont=0;
                }
            }
        }

    }
    SDL_FreeSurface(PionJ);SDL_FreeSurface(Plateau);SDL_FreeSurface(Cursor);SDL_FreeSurface(Fond2);SDL_FreeSurface(FondP);SDL_FreeSurface(CursorR);

}


int comparaison(int EtatCourant[6][7])    // le choix de la machine
{
    int i,j;
    for(i=0;i<6;i++)
    {
        for(j=0;j<7;j++)
        {
            if(EtatCourant[i][j]!=Grille.A[i][j])
                return j;
        }
    }
}




void partieMachine(SDL_Surface *Screen,int choixIA)
{
    int x;
    nbr=0;
    int j;
    int compteur=0,i=0;
    Liste listeSuccesseurs;
    initialiser(&listeSuccesseurs);
    int listScore[7]={0,0,0,0,0,0,0};
    Noeud* n;
    int a,aMin;
    int EtatCourant[6][7];
    egalite(EtatCourant,Grille.A);
    listeSuccesseurs=genereSuccesseurs(EtatCourant,compteur);
    compteur++;
    for(n=listeSuccesseurs.sommet;n!=NULL;n=n->suivant)
    {
        if(choixIA==1)
        {
            a=minimax(n->M,compteur,4);
        }
        else if(choixIA==2)
        {
            a=alphabeta(-1000000,1000000,compteur,5,n->M);
        }
        listScore[i]=a;
        i++;
    }
    Inverser(listScore);// on a besoin d'inverser le tableau pour que les elements de listScore et listeSuccesseurs soient dans le meme ordre
    aMin=iMin(listScore);//l'indice du minimum dans un tableau des entiers
    egalite(EtatCourant,iemeMatrice(aMin+1,listeSuccesseurs).A);// ieme retourne le ieme etat (la ieme matrice) dans la liste
    x=comparaison(EtatCourant);   // la colonne jouée par la machine
    SDL_Surface *PionM,*Plateau,*Fond2,*FondP,*TourM,*cadre;
    SDL_Rect posPlateau,posPion,posCadre,posPCadre;
    SDL_Rect posFond,posFondP;
    posFond.x=0;posFond.y=0;posFondP.x=355;posFondP.y=140;posCadre.x=20;posCadre.y=465;posPCadre.x=65;posPCadre.y=575;
    posPlateau.x=350;posPlateau.y=130;posPion.x=coordonneesPX(0,x).x;posPion.y=141;
    Plateau=IMG_Load("Images/Plateau.png");
    PionM=IMG_Load("Images/PionM.png");
    Fond2=IMG_Load("images/Fond3.png");
    FondP=IMG_Load("Images/FondP.png");
    cadre=IMG_Load("Images/cadre.png");
    SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 255, 255, 255));
    SDL_BlitSurface(Fond2,NULL,Screen,&posFond);
    SDL_BlitSurface(cadre,NULL,Screen,&posCadre);
    SDL_BlitSurface(PionM,NULL,Screen,&posPCadre);
    SDL_BlitSurface(FondP,NULL,Screen,&posFondP);
    Affichage(Screen);
    SDL_Flip(Screen);
    for(j=141;j<=561-HauteurPx(x,Grille.A);j=j+15)     // j ---> y
        {
            posPion.y=j;
            SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 255, 255, 255));
            SDL_BlitSurface(Fond2,NULL,Screen,&posFond);
            SDL_BlitSurface(cadre,NULL,Screen,&posCadre);
            SDL_BlitSurface(PionM,NULL,Screen,&posPCadre);
            SDL_BlitSurface(FondP,NULL,Screen,&posFondP);
            SDL_BlitSurface(PionM,NULL,Screen,&posPion);
            Affichage(Screen);
            SDL_BlitSurface(Plateau,NULL,Screen,&posPlateau);
            SDL_Flip(Screen);
        }
        SDL_FreeSurface(PionM);SDL_FreeSurface(Plateau);SDL_FreeSurface(Fond2);SDL_FreeSurface(FondP);SDL_FreeSurface(TourM);
    egalite(Grille.A,EtatCourant);
}



void Puissance4(SDL_Surface *Screen,int choix)
{
    int cont=0;
    viderPlateau();
    SDL_Surface *Fond3,*FondP,*Plateau,*cadre,*PionJ;
    SDL_Rect posFond,posFondP,posPlateau,posCadre,posPCadre;
    posFond.x=0;posFond.y=0;posFondP.x=355;posFondP.y=140;posPlateau.x=350;posPlateau.y=130;posCadre.x=20;posCadre.y=465;posPCadre.x=65;posPCadre.y=575;
    Fond3=IMG_Load("Images/Fond3.png");
    PionJ=IMG_Load("Images/PionJ.png");
    FondP=IMG_Load("Images/FondP.png");
    cadre=IMG_Load("Images/cadre.png");
    Plateau=IMG_Load("Images/Plateau.png");
    SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 255, 255, 255));
    SDL_BlitSurface(Fond3,NULL,Screen,&posFond);
    SDL_BlitSurface(FondP,NULL,Screen,&posFondP);
    SDL_BlitSurface(Plateau,NULL,Screen,&posPlateau);
    SDL_BlitSurface(cadre,NULL,Screen,&posCadre);
    SDL_BlitSurface(PionJ,NULL,Screen,&posPCadre);
    SDL_Flip(Screen);
    while(!partieFinie(1,Grille) && !partieFinie(2,Grille))
    {
        if (compt%2==0)
           {
                partieJoueur(Screen);    // le tour du joueur
           }
        else
           {
                partieMachine(Screen,choix);    // le tour de la machine
           }
           compt++;
    }
    SDL_Event event;
    cont=1;
    if(Utilite()==1)
    {
        SDL_Surface *Fond,*retourV1,*retourV2;
        SDL_Rect posFond,posRetour;
        posFond.x=0;posFond.y=0;posRetour.x=14;posRetour.y=598;
        Fond=IMG_Load("Images/WIN.png");
        retourV1=IMG_Load("Images/retourV1.png");
        retourV2=IMG_Load("Images/retourV2.png");
        while(cont)
        {
            SDL_WaitEvent(&event);
            if(event.type==SDL_MOUSEMOTION)
            {
                if(event.button.x>14 && event.button.x<110 && event.button.y>598 && event.button.y<694)
                {
                    SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 255, 255, 255));
                    SDL_BlitSurface(Fond,NULL,Screen,&posFond);
                    SDL_BlitSurface(retourV2,NULL,Screen,&posRetour);
                    SDL_Flip(Screen);
                }
                else
                {
                    SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 255, 255, 255));
                    SDL_BlitSurface(Fond,NULL,Screen,&posFond);
                    SDL_BlitSurface(retourV1,NULL,Screen,&posRetour);
                    SDL_Flip(Screen);
                }
            }
            if(event.type==SDL_MOUSEBUTTONUP)
            {
                if(event.button.x>14 && event.button.x<110 && event.button.y>598 && event.button.y<694)
                {
                    SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 255, 255, 255));
                    viderPlateau();
                    compt=0;
                    cont=0;
                    SDL_FreeSurface(Fond3);SDL_FreeSurface(FondP);SDL_FreeSurface(Plateau);SDL_FreeSurface(Fond);SDL_FreeSurface(retourV1);SDL_FreeSurface(retourV2);
                    menu(Screen);
                }
            }
            if(event.type==SDL_QUIT)
            {
                cont=0;
                SDL_FreeSurface(Fond3);SDL_FreeSurface(FondP);SDL_FreeSurface(Plateau);SDL_FreeSurface(Fond);SDL_FreeSurface(retourV1);SDL_FreeSurface(retourV2);
                SDL_Quit();
            }
        }
    }
    if(Utilite()==-1)
    {
        SDL_Surface *Fond,*retourV1,*retourV2;
        SDL_Rect posFond,posRetour;
        posFond.x=0;posFond.y=0;posRetour.x=14;posRetour.y=598;
        Fond=IMG_Load("Images/LOSE.png");
        retourV1=IMG_Load("Images/retourV1.png");
        retourV2=IMG_Load("Images/retourV2.png");
        while(cont)
        {
            SDL_WaitEvent(&event);
            if(event.type==SDL_MOUSEMOTION)
            {
                if(event.button.x>14 && event.button.x<110 && event.button.y>598 && event.button.y<694)
                {
                    SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 255, 255, 255));
                    SDL_BlitSurface(Fond,NULL,Screen,&posFond);
                    SDL_BlitSurface(retourV2,NULL,Screen,&posRetour);
                    SDL_Flip(Screen);
                }
                else
                {
                    SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 255, 255, 255));
                    SDL_BlitSurface(Fond,NULL,Screen,&posFond);
                    SDL_BlitSurface(retourV1,NULL,Screen,&posRetour);
                    SDL_Flip(Screen);
                }
            }
            if(event.type==SDL_MOUSEBUTTONUP)
            {
                if(event.button.x>14 && event.button.x<110 && event.button.y>598 && event.button.y<694)
                {
                    SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 255, 255, 255));
                    viderPlateau();
                    cont=0;
                    compt=0;
                    SDL_FreeSurface(Fond3);SDL_FreeSurface(FondP);SDL_FreeSurface(Plateau);SDL_FreeSurface(Fond);SDL_FreeSurface(retourV1);SDL_FreeSurface(retourV2);
                    menu(Screen);
                }
            }
            if(event.type==SDL_QUIT)
            {
                cont=0;
                SDL_FreeSurface(Fond3);SDL_FreeSurface(FondP);SDL_FreeSurface(Plateau);SDL_FreeSurface(Fond);SDL_FreeSurface(retourV1);SDL_FreeSurface(retourV2);
                SDL_Quit();
            }
        }
    }
    if(Utilite()==0)
    {
        SDL_Surface *Fond,*retourV1,*retourV2;
        SDL_Rect posFond,posRetour;
        posFond.x=0;posFond.y=0;posRetour.x=14;posRetour.y=598;
        Fond=IMG_Load("Images/EX-AEQUO.png");
        retourV1=IMG_Load("Images/retourV1.png");
        retourV2=IMG_Load("Images/retourV2.png");
        while(cont)
        {
            SDL_WaitEvent(&event);
            if(event.type==SDL_MOUSEMOTION)
            {
                if(event.button.x>14 && event.button.x<110 && event.button.y>598 && event.button.y<694)
                {
                    SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 255, 255, 255));
                    SDL_BlitSurface(Fond,NULL,Screen,&posFond);
                    SDL_BlitSurface(retourV2,NULL,Screen,&posRetour);
                    SDL_Flip(Screen);
                }
                else
                {
                    SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 255, 255, 255));
                    SDL_BlitSurface(Fond,NULL,Screen,&posFond);
                    SDL_BlitSurface(retourV1,NULL,Screen,&posRetour);
                    SDL_Flip(Screen);
                }
            }
            if(event.type==SDL_MOUSEBUTTONUP)
            {
                if(event.button.x>14 && event.button.x<110 && event.button.y>598 && event.button.y<694)
                {
                    SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 255, 255, 255));
                    viderPlateau();
                    compt=0;
                    cont=0;
                    SDL_FreeSurface(Fond3);SDL_FreeSurface(FondP);SDL_FreeSurface(Plateau);SDL_FreeSurface(Fond);SDL_FreeSurface(retourV1);SDL_FreeSurface(retourV2);
                    menu(Screen);
                }
            }
            if(event.type==SDL_QUIT)
            {
                cont=0;
                SDL_FreeSurface(Fond3);SDL_FreeSurface(FondP);SDL_FreeSurface(Plateau);SDL_FreeSurface(Fond);SDL_FreeSurface(retourV1);SDL_FreeSurface(retourV2);
                SDL_Quit();
            }
        }
    }

    SDL_FreeSurface(Fond3);SDL_FreeSurface(FondP);SDL_FreeSurface(Plateau);
}






void menu2(SDL_Surface *Screen)
{
    int choix;
    int cont=1;
    SDL_Event event;
    SDL_Surface *Fond2=NULL ,*MediumV1,*MediumV2,*HardV1,*HardV2;
    SDL_Rect posFond,posMed,posHard;
    posFond.x=0;posFond.y=0;
    posMed.x=360;posMed.y=300;
    posHard.x=360;posHard.y=500;
    MediumV1=IMG_Load("images/MEDIUM.png");
    MediumV2=IMG_Load("images/MEDIUM2.png");
    HardV1=IMG_Load("images/HARD.png");
    HardV2=IMG_Load("images/HARD2.png");
    Fond2=IMG_Load("images/Fond2.png");
    while(cont)
    {
    SDL_BlitSurface(Fond2,NULL,Screen,&posFond);
    SDL_WaitEvent(&event);
    if(event.type==SDL_MOUSEMOTION)
    {
        if(event.button.x>360 && event.button.x<640 && event.button.y>300 && event.button.y<446)
        {
            SDL_BlitSurface(MediumV2,NULL,Screen,&posMed);
            SDL_BlitSurface(HardV1,NULL,Screen,&posHard);
            SDL_Flip(Screen);
        }
        else if(event.button.x>360 && event.button.x<640 && event.button.y>500 && event.button.y<646)
        {
            SDL_BlitSurface(MediumV1,NULL,Screen,&posMed);
            SDL_BlitSurface(HardV2,NULL,Screen,&posHard);
            SDL_Flip(Screen);
        }
        else
        {
            SDL_BlitSurface(MediumV1,NULL,Screen,&posMed);
            SDL_BlitSurface(HardV1,NULL,Screen,&posHard);
            SDL_Flip(Screen);
        }
    }
    if(event.type==SDL_MOUSEBUTTONDOWN)
    {
        if(event.button.x>360 && event.button.x<640 && event.button.y>300 && event.button.y<446)
        {
            cont=0;
            choix=1;  // minimax
            Puissance4(Screen,choix);
        }
        else if(event.button.x>360 && event.button.x<640 && event.button.y>500 && event.button.y<646)
        {
            cont=0;
            choix=2;   // alphabeta
            Puissance4(Screen,choix);
        }
    }
    if(event.type==SDL_QUIT)
        {
            cont=0;
            SDL_FreeSurface(Fond2);SDL_FreeSurface(MediumV1);SDL_FreeSurface(MediumV2);SDL_FreeSurface(HardV1);SDL_FreeSurface(HardV2);
            SDL_Quit();
        }
    }
    SDL_FreeSurface(Fond2);SDL_FreeSurface(MediumV1);SDL_FreeSurface(MediumV2);SDL_FreeSurface(HardV1);SDL_FreeSurface(HardV2);


}







void menu(SDL_Surface *Screen)
{
    int cont=1;
    SDL_Event event;
    SDL_Surface *Fond=NULL ,*PlayV1,*PlayV2,*ExitV1,*ExitV2;
    SDL_Rect posFond,posPlay,posExit;
    posFond.x=0;posFond.y=0;
    posPlay.x=50;posPlay.y=550;
    posExit.x=700;posExit.y=550;
    PlayV1=IMG_Load("images/Play.png");
    PlayV2=IMG_Load("images/Play2.png");
    ExitV1=IMG_Load("images/EXIT.png");
    ExitV2=IMG_Load("images/EXIT2.png");
    Fond=IMG_Load("images/Fond.png");
    while(cont)
    {
    SDL_BlitSurface(Fond,NULL,Screen,&posFond);
    SDL_WaitEvent(&event);
    if(event.type==SDL_MOUSEMOTION)
    {
        if(event.button.x>50 && event.button.x<302 && event.button.y>540 && event.button.y<658)
        {
            SDL_BlitSurface(PlayV2,NULL,Screen,&posPlay);
            SDL_BlitSurface(ExitV1,NULL,Screen,&posExit);
            SDL_Flip(Screen);
        }
        else if(event.button.x>700 && event.button.x<952 && event.button.y>550 && event.button.y<668)
        {
            SDL_BlitSurface(PlayV1,NULL,Screen,&posPlay);
            SDL_BlitSurface(ExitV2,NULL,Screen,&posExit);
            SDL_Flip(Screen);
        }
        else
        {
            SDL_BlitSurface(PlayV1,NULL,Screen,&posPlay);
            SDL_BlitSurface(ExitV1,NULL,Screen,&posExit);
            SDL_Flip(Screen);
        }
    }
    if(event.type==SDL_MOUSEBUTTONDOWN)
    {
        if(event.button.x>50 && event.button.x<302 && event.button.y>540 && event.button.y<658)
        {
            menu2(Screen);
        }
        if(event.button.x>700 && event.button.x<952 && event.button.y>550 && event.button.y<668)
        {
            cont=0;
            SDL_FreeSurface(Fond);SDL_FreeSurface(PlayV1);SDL_FreeSurface(PlayV2);SDL_FreeSurface(ExitV1);SDL_FreeSurface(ExitV2);
            SDL_Quit();
        }
    }
    if(event.type==SDL_QUIT)
        {
            cont=0;
            SDL_FreeSurface(Fond);SDL_FreeSurface(PlayV1);SDL_FreeSurface(PlayV2);SDL_FreeSurface(ExitV1);SDL_FreeSurface(ExitV2);
            SDL_Quit();
        }
    }
    SDL_FreeSurface(Fond);SDL_FreeSurface(PlayV1);SDL_FreeSurface(PlayV2);SDL_FreeSurface(ExitV1);SDL_FreeSurface(ExitV2);

}





int main ( int argc, char** argv )
{
    int continu=1;
    SDL_Event event;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface *Screen=NULL;
    Screen=SDL_SetVideoMode(1000,708,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Connect 4 game", NULL);
    while(continu)
    {
        SDL_WaitEvent(&event);
        menu(Screen);
        switch(event.type)
        {
        case SDL_QUIT:
            continu=0;
        }

    }
    SDL_FreeSurface(Screen);
    SDL_Quit();
}




/*
void pause()
{
    int cont=1;
    SDL_Event event;
    while(cont)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                cont=0;
        }
    }
}
*/
