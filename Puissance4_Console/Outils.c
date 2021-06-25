#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "Outil.h"
#include "NotreListe.h"
//#include "LesVarGlobales.h"



int Utilite()
{
    //printf("diag     =      %d\n",diagD4allign(1,Plateau));
    if(PlateauPlein())
            return 0;
    if(horiz4allign(1,Plateau) || vertic4allign(1,Plateau) || diagD4allign(1,Plateau) || diagG4allign(1,Plateau))
            return 1;
    if(horiz4allign(2,Plateau) || vertic4allign(2,Plateau) || diagD4allign(2,Plateau) || diagG4allign(2,Plateau))
            return -1;
}

int player()
{
    if(count %2==0) return 1;
    if(count %2==1) return 2;
}

int PlateauPlein()
{
    int i,j;
    for(i=0;i<6;i++)
    {
        for(j=0;j<7;j++)
        {
            if(Plateau[i][j]==0)
            {
                return 0;   //   plateau non plein
            }
        }
    }
    return 1;  //  plateau plein
}

int vide(Liste l)
{
    return(l.sommet==NULL && l.taille==0);      // =1 si vide et =0 sinon
}

void viderPlateau()   // initialiser le Plateau
{
    int i,j;
    for(i=0;i<6;i++)
    {
        for(j=0;j<7;j++)
        {
            Plateau[i][j]=0;
        }
    }
}

void Color(int couleurDuTexte,int couleurDeFond) // fonction d'affichage de couleurs
{
        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);
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

void initialiser(Liste *l)
{
    l->sommet=NULL;
    l->taille=0;
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

int Hauteur(int j,int etat[6][7])    // nombre de cases pleines d'une colonne donnée
{
    int i=0;
    while(etat[i][j]!=0)
    {
        i++;
    }
    return i;
}

int** iemeMatrice(int i,Liste l)
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

int partieFinie(int player,int Etat[6][5])
{
    if (horiz4allign(player,Etat) || vertic4allign(player,Etat) || diagD4allign(player,Etat) || diagG4allign(player,Etat) || PlateauPlein())
        return 1;
    return 0;
}

int bonnus(int player)
{
    if(player==1)
        return 20;
    return -20;
}


int h(int Etat[6][7])
{
    int x=(score(1,Etat) - score(2,Etat)); //+ bonnus(player());
    return x;
}
// h(n)--->cout d'un etat-----> score(max_dans_un_etat)-score(min_dans_un_etat)
// genereSuccesseurs(liste* L,Case A[6][7])

int scoreHeuristique(int i,int j,int player,int Etat[6][7])
{
    if(Etat[i][j]==player)
    {
        return HEURISTIQUE[i][j];
    }
    else if(Etat[i][j]==adversaire(player))
    {
        return -HEURISTIQUE[i][j];
    }
    else
        return 0;
}



int score(int player,int Etat[6][7])
{
    int resultat=0,i,j;
    for(i=0;i<6;i++)
    {
        for(j=0;j<7;j++)
        {
            if(nbrAllignementVideHoriz(i,j,adversaire(player),Etat)>=4 || nbrAllignementVideVertic(i,j,adversaire(player),Etat)>=4 || nbrAllignementVideDiagD(i,j,adversaire(player),Etat)>=4 || nbrAllignementVideDiagG(i,j,adversaire(player),Etat)>=4)
            {
            resultat= resultat + scoreAlignement(nbrAllignementVideHoriz(i,j,player,Etat))+ scoreAlignement(nbrAllignementVideVertic(i,j,player,Etat))+scoreAlignement(nbrAllignementVideDiagD(i,j,player,Etat))+ scoreAlignement(nbrAllignementVideDiagG(i,j,player,Etat))+ 2*scoreDefense(nbrAllignementDefHoriz(i,j,player,Etat))+ 2*scoreDefense(nbrAllignementDefVertic(i,j,player,Etat))+ 2*scoreDefense(nbrAllignementDefDiagD(i,j,player,Etat))+ 2*scoreDefense(nbrAllignementDefDiagG(i,j,player,Etat))+scoreHeuristique(i,j,player,Etat);//-scoreAlignement(nbrAllignementVideHoriz(i,j,adversaire(player),Etat))-scoreAlignement(nbrAllignementVideDiagG(i,j,adversaire(player),Etat))-scoreAlignement(nbrAllignementVideVertic(i,j,adversaire(player),Etat))-scoreAlignement(nbrAllignementVideDiagD(i,j,adversaire(player),Etat));
            }
            else if(nbrAllignementVideHoriz(i,j,player,Etat)>=4 || nbrAllignementVideVertic(i,j,player,Etat)>=4 || nbrAllignementVideDiagD(i,j,player,Etat)>=4 || nbrAllignementVideDiagG(i,j,player,Etat)>=4)
                resultat= resultat + 2*scoreAlignement(nbrAllignementVideHoriz(i,j,player,Etat))+ 2*scoreAlignement(nbrAllignementVideVertic(i,j,player,Etat))+2*scoreAlignement(nbrAllignementVideDiagD(i,j,player,Etat))+ 2*scoreAlignement(nbrAllignementVideDiagG(i,j,player,Etat))+ scoreDefense(nbrAllignementDefHoriz(i,j,player,Etat))+ scoreDefense(nbrAllignementDefVertic(i,j,player,Etat))+ scoreDefense(nbrAllignementDefDiagD(i,j,player,Etat))+ scoreDefense(nbrAllignementDefDiagG(i,j,player,Etat))+scoreHeuristique(i,j,player,Etat);
            else
                resultat= resultat + scoreAlignement(nbrAllignementVideHoriz(i,j,player,Etat))+ scoreAlignement(nbrAllignementVideVertic(i,j,player,Etat))+scoreAlignement(nbrAllignementVideDiagD(i,j,player,Etat))+ scoreAlignement(nbrAllignementVideDiagG(i,j,player,Etat))+ scoreDefense(nbrAllignementDefHoriz(i,j,player,Etat))+ scoreDefense(nbrAllignementDefVertic(i,j,player,Etat))+ scoreDefense(nbrAllignementDefDiagD(i,j,player,Etat))+ scoreDefense(nbrAllignementDefDiagG(i,j,player,Etat))+scoreHeuristique(i,j,player,Etat);

        }
    }
    return resultat;
}


int adversaire(int player)        // l'adversaire de player
{
    if(player==1)
        return 2;
    return 1;
}


int nbrAllignementVideHoriz(int i,int j,int player,int Etat[6][7])
{
    int horiz=nbrHorizAllign(i,j,player,Etat);
    if( ( horiz!=0 && ((j+horiz)<7 && Etat[i][j+horiz]==0) || (j-1>=0 && Etat[i][j-1]==0)) )
        return horiz;
    return 0;
}


int nbrAllignementVideVertic(int i,int j,int player,int Etat[6][7])
{
    int vertic=nbrVerticAllign(i,j,player,Etat);
    if(vertic!=0 && (i+vertic)<6 && Etat[i+vertic][j]==0)
        return vertic;
    return 0;
}


int nbrAllignementVideDiagD(int i,int j,int player,int Etat[6][7])
{
    int diag=nbrDiagDroiteAllign(i,j,player,Etat);
    if(diag!=0 && (((i+diag)<6 && (j+diag)<7 && Etat[i+diag][j+diag]==0) || (i-1>=0 && j-1>=0 && Etat[i-1][j-1]==0)) && ((j<3 && i<3+j) || (j>3 && i>=j-3) || j==3))
        return diag;
    return 0;
}


int nbrAllignementVideDiagG(int i,int j,int player,int Etat[6][7])
{
    int diag=nbrDiagGaucheAllign(i,j,player,Etat);
    if(diag!=0 && ( ((i+diag)<6 && (j-diag)>=0 && Etat[i+diag][j-diag]==0) || (i-1>=0 && j+1<7 && Etat[i-1][j+1]==0) ) && ((j<3 && i>=3-j) || (j>3 && i<=8-j) || j==3))
        return diag;
    return 0;
}



int nbrAllignementDefHoriz(int i,int j,int player,int Etat[6][7])
{
    int horiz=nbrHorizAllign(i,j,adversaire(player),Etat);
    	if(horiz!=0 && ( ( ((j+horiz)<7 && Etat[i][j+horiz]==player) && (j-1>=0 && Etat[i][j-1]==player) )) || (j-1<0 && Etat[i][j+horiz]==player) || (j+horiz>=7 && Etat[i][j-1]==player) )
    		return -horiz;
        else if(horiz!=0 && ( ((j+horiz)<7 && Etat[i][j+horiz]==player) || (j-1>=0 && Etat[i][j-1]==player)) )
            return horiz;
        else
        	return 0;

}


int nbrAllignementDefVertic(int i,int j,int player,int Etat[6][7])
{
    int vertic=nbrVerticAllign(i,j,adversaire(player),Etat);
        if(vertic!=0 && (i+vertic)<6 && i<3 && Etat[i+vertic][j]==player)
            return vertic;
        return 0;
}


int nbrAllignementDefDiagD(int i,int j,int player,int Etat[6][7])
{
    int diag=nbrDiagDroiteAllign(i,j,adversaire(player),Etat);
        if((diag!=0 && ( ((i+diag)<6 && (j+diag)<7 && Etat[i+diag][j+diag]==player) && (i-1>=0 && j-1>=0 && Etat[i-1][j-1]==player)) || ((j+diag>=7 || i+diag>=6 ) && Etat[i-1][j-1]==player) || ((i-1<0 || j-1<0) && Etat[i+diag][j+diag]==player) ) && ((j<3 && i<3+j) || (j>3 && i>=j-3) || j==3))
            return -diag;
        else if(diag!=0 && (((i+diag)<6 && (j+diag)<7 && Etat[i+diag][j+diag]==player) || (i-1>=0 && j-1>=0 && Etat[i-1][j-1]==player)) && ((j<3 && i<3+j) || (j>3 && i>=j-3) || j==3))
        	return diag;
        else
        	return 0;

}


int nbrAllignementDefDiagG(int i,int j,int player,int Etat[6][7])
{
    int diag=nbrDiagGaucheAllign(i,j,adversaire(player),Etat);
        if(diag!=0 && (((j<3 && i>=3-j) || (j>3 && i<=8-j) || j==3) && ((i+diag<6 && j-diag>=0 && Etat[i+diag][j-diag]==player) && (i-1>=0 && j+1<7 && Etat[i-1][j+1]==player)) || ((i+diag>=6 || j-diag<0) && Etat[i-1][j+1]==player) || ((i-1<0 || j+1>6) && Etat[i+diag][j-diag]==player) ) )
            return -diag;
        else if(diag!=0 && (((j<3 && i>=3-j) || (j>3 && i<=8-j) || j==3) && ((i+diag<6 && j-diag>=0 && Etat[i+diag][j-diag]==player) || (i-1>=0 && j+1<7 && Etat[i-1][j+1]==player))))
        	return diag;
        else
        	return 0;
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


int nbrHorizAllign(int i,int j,int player,int Etat[6][7])
{
    int nbr=0;
    if((Etat[i][j-1]==player && j>0) || Etat[i][j]!=player)  return 0;
    else if(Etat[i][j-1]!=player)
    {
        while(Etat[i][j]==player && j<7)
        {
            nbr++;
            j++;
        }
    }
        return nbr;
}

int nbrVerticAllign(int i,int j,int player,int Etat[6][7])
{
    int nbr=0;
    if((Etat[i-1][j]==player && i>0) || Etat[i][j]!=player)   return 0;
    else if(Etat[i-1][j]!=player)
    {
        if(Etat[i][j]==player)
        {
            while(Etat[i][j]==player && i<6)
            {
                nbr++;
                i++;
            }
        }
        return nbr;
    }
}

int nbrDiagDroiteAllign(int i,int j,int player,int Etat[6][7])
{
    int nbr=0;
    if(Etat[i-1][j-1]==player && i>0 && j>0 || Etat[i][j]!=player)
        return 0;

    else if(Etat[i-1][j-1]!=player)
    {
        while(Etat[i][j]==player && j<7 && i<6)
        {
            nbr++;
            i++;j++;
        }
        return nbr;
    }
}



int nbrDiagGaucheAllign(int i,int j,int player,int Etat[6][7])
{
    int nbr=0;
    if((Etat[i-1][j+1]==player && j+1<7 && i>0) || Etat[i][j]!=player)
        return 0;
    else if((Etat[i-1][j+1]!=player && i-1>=0 && j+1<7) || i==0 || j==6)
    {
        while(Etat[i][j]==player && i<6 && j>=0)
        {
            nbr++;
            i++;
            j--;
        }
        return nbr;
    }

}

int vertic4allign(int player,int Etat[6][7])
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





int horiz4allign(int player,int Etat[6][7])
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

int diagD4allign(int player,int Etat[6][7])
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

int diagG4allign(int player,int Etat[6][7])
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

void Logo()
{
    printf("\n\n\n");
    Color(14,0);
    printf("\t\t  /");Color(5,0);printf("$$$$$$");Color(14,0);printf("                                                      /");Color(5,0);printf("$$");Color(14,0);printf("           /");Color(5,0);printf("$$");Color(14,0);printf("   /");Color(5,0);printf("$$\n");
    Color(14,0);printf("\t\t /");Color(5,0);printf("$$");Color(14,0);printf("__");Color(5,0);printf("  $$");Color(14,0);printf("                                                    | ");Color(5,0);printf("$$");Color(14,0);printf("          | ");Color(5,0);printf("$$");Color(14,0);printf("  | ");Color(5,0);printf("$$\n");
    Color(14,0);printf("\t\t| ");Color(5,0);printf("$$");Color(14,0);printf("  \\__/  /");Color(5,0);printf("$$$$$$");Color(14,0);printf("  /");Color(5,0);printf("$$$$$$$");Color(14,0);printf("  /");Color(5,0);printf("$$$$$$$");Color(14,0);printf("   /");Color(5,0);printf("$$$$$$");Color(14,0);printf("   /");Color(5,0);printf("$$$$$$");Color(14,0);printf(" /");Color(5,0);printf("$$$$$");Color(14,0);printf("          | ");Color(5,0);printf("$$");Color(14,0);printf("  | ");Color(5,0);printf("$$\n");
    Color(14,0);printf("\t\t| ");Color(5,0);printf("$$");Color(14,0);printf("       /");Color(5,0);printf("$$");Color(14,0);printf("__  ");Color(5,0);printf("$$");Color(14,0);printf("| ");Color(5,0);printf("$$");Color(14,0);printf("__  ");Color(5,0);printf("$$");Color(14,0);printf("| ");Color(5,0);printf("$$");Color(14,0);printf("__  ");Color(5,0);printf("$$");Color(14,0);printf(" /");Color(5,0);printf("$$");Color(14,0);printf("__  ");Color(5,0);printf("$$");Color(14,0);printf(" /");Color(5,0);printf("$$");Color(14,0);printf("_____/|_  ");Color(5,0);printf("$$");Color(14,0);printf("_/        | ");Color(5,0);printf("$$$$$$$$\n");
    Color(14,0);printf("\t\t| ");Color(5,0);printf("$$");Color(14,0);printf("      | ");Color(5,0);printf("$$");Color(14,0);printf("  \\ ");Color(5,0);printf("$$");Color(14,0);printf("| ");Color(5,0);printf("$$");Color(14,0);printf("  \\ ");Color(5,0);printf("$$");Color(14,0);printf("| ");Color(5,0);printf("$$");Color(14,0);printf("  \\ ");Color(5,0);printf("$$");Color(14,0);printf("| ");Color(5,0);printf("$$$$$$$$");Color(14,0);printf("| ");Color(5,0);printf("$$");Color(14,0);printf("        | ");Color(5,0);printf("$$");Color(14,0);printf("          |_____  ");Color(5,0);printf("$$\n");
    Color(14,0);printf("\t\t| ");Color(5,0);printf("$$");Color(5,0);printf("    $$");Color(14,0);printf("| ");Color(5,0);printf("$$");Color(14,0);printf("  | ");Color(5,0);printf("$$");Color(14,0);printf("| ");Color(5,0);printf("$$");Color(14,0);printf("  | ");Color(5,0);printf("$$");Color(14,0);printf("| ");Color(5,0);printf("$$");Color(14,0);printf("  | ");Color(5,0);printf("$$");Color(14,0);printf("| ");Color(5,0);printf("$$");Color(14,0);printf("_____/| ");Color(5,0);printf("$$");Color(14,0);printf("        | ");Color(5,0);printf("$$");Color(14,0);printf(" /");Color(5,0);printf("$$");Color(14,0);printf("            | ");Color(5,0);printf("$$\n");
    Color(14,0);printf("\t\t|  ");Color(5,0);printf("$$$$$$");Color(14,0);printf("/|  ");Color(5,0);printf("$$$$$$");Color(14,0);printf("/| ");Color(5,0);printf("$$");Color(14,0);printf("  | ");Color(5,0);printf("$$");Color(14,0);printf("| ");Color(5,0);printf("$$");Color(14,0);printf("  | ");Color(5,0);printf("$$");Color(14,0);printf("|  ");Color(5,0);printf("$$$$$$$");Color(14,0);printf("|  ");Color(5,0);printf("$$$$$$$");Color(14,0);printf("  |  ");Color(5,0);printf("$$$$");Color(14,0);printf("/            | ");Color(5,0);printf("$$\n");
    Color(14,0);printf("\t\t \\______/  \\______/ |__/  |__/|__/  |__/ \\_______/ \\_______/   \\___/              |__/\n");
    Color(15,0);
}

void Menu()
{
    Logo();
    printf("\n\n\n");
    Color(6,0);
    printf("\t\t\t\t\t\t   ********************\n");
    printf("\t\t\t\t\t\t  |                    |     \n");
    printf("\t\t\t\t\t\t  | 1-Player vs Player |   \n");
    printf("\t\t\t\t\t\t  |                    |   \n");
    printf("\t\t\t\t\t\t   ********************\n\n\n");
    printf("\t\t\t\t\t\t   ********************\n");
    printf("\t\t\t\t\t\t  |                    |     \n");
    printf("\t\t\t\t\t\t  |  2-Player vs CPU   |   \n");
    printf("\t\t\t\t\t\t  |                    |   \n");
    printf("\t\t\t\t\t\t   ********************\n\n\n");
    printf("\t\t\t\t\t\t   ********************\n");
    printf("\t\t\t\t\t\t  |                    |     \n");
    printf("\t\t\t\t\t\t  |       3-Exit       |   \n");
    printf("\t\t\t\t\t\t  |                    |   \n");
    printf("\t\t\t\t\t\t   ********************\n");
    Color(15,0);
    printf("\n\tSaisir votre choix : ");
    scanf("%d",&choix);

}


void MenuIA()
{
    Logo();
    printf("\n\n\n");
    Color(6,0);
    printf("\t\t\t\t\t\t   ********************\n");
    printf("\t\t\t\t\t\t  |                    |     \n");
    printf("\t\t\t\t\t\t  |     1-Minimax      |   \n");
    printf("\t\t\t\t\t\t  |                    |   \n");
    printf("\t\t\t\t\t\t   ********************\n\n\n");
    printf("\t\t\t\t\t\t   ********************\n");
    printf("\t\t\t\t\t\t  |                    |     \n");
    printf("\t\t\t\t\t\t  |    2-Alphabeta     |   \n");
    printf("\t\t\t\t\t\t  |                    |   \n");
    printf("\t\t\t\t\t\t   ********************\n\n\n");
    Color(15,0);
}

void tour()
{
    if(count%2==0)
    {
        if(choix==1)
            {Color(15,0);printf("\t| ");Color(9,0);printf(" Tour Joueur1");Color(15,0);printf(" |\n");}
        else if(choix==2)
            {Color(15,0);printf("\t| ");Color(9,0);printf(" Tour Joueur  ");Color(15,0);printf("|\n");}
    }
    else
    {
        if(choix==1)
            {Color(15,0);printf("\t| ");Color(6,0);printf(" Tour Joueur2");Color(15,0);printf(" |\n");}
        else if(choix==2)
            {Color(15,0);printf("\t|");Color(6,0);printf("   Tour CPU   ");Color(15,0);printf(" |\n");}
    }

}

void partieJoueur()
{
    int a;
    printf("saisir votre choix de colonne ");
    scanf("%d",&a);
    while(a>6 || a<0)
    {
        printf("Vous devez choisir une colonne entre 0 et 6 : ");
        scanf("%d",&a);
    }
    while(Hauteur(a,Plateau)==6)
    {
        printf("colonne pleine! choisir une autre colonne");
        scanf("%d",&a);
        while(a>6 || a<0)
        {
            printf("Vous devez choisir une colonne entre 0 et 6 : ");
            scanf("%d",&a);
        }
    }
    Plateau[Hauteur(a,Plateau)][a]=1;
}
