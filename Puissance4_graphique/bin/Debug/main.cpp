#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

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



void Puissance4(int choix)
{

}






void menu2(SDL_Surface *Screen)
{
    int choix;
    int cont=1;
    SDL_Event event;
    while(cont)
    {
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
    SDL_BlitSurface(Fond2,NULL,Screen,&posFond);
    SDL_WaitEvent(&event);
    if(event.type==SDL_MOUSEMOTION)
    {
        if(event.button.x>360 && event.button.x<640 && event.button.y>300 && event.button.y<446)
        {
            SDL_BlitSurface(MediumV2,NULL,Screen,&posMed);
            SDL_BlitSurface(HardV1,NULL,Screen,&posHard);
            SDL_Flip(Screen);
            SDL_FreeSurface(MediumV2);
            SDL_FreeSurface(HardV1);
        }
        else if(event.button.x>360 && event.button.x<640 && event.button.y>500 && event.button.y<646)
        {
            SDL_BlitSurface(MediumV1,NULL,Screen,&posMed);
            SDL_BlitSurface(HardV2,NULL,Screen,&posHard);
            SDL_Flip(Screen);
            SDL_FreeSurface(MediumV1);
            SDL_FreeSurface(HardV2);
        }
        else
        {
            SDL_BlitSurface(MediumV1,NULL,Screen,&posMed);
            SDL_BlitSurface(HardV1,NULL,Screen,&posHard);
            SDL_Flip(Screen);
            SDL_FreeSurface(MediumV1);
            SDL_FreeSurface(HardV1);
        }
    }
    if(event.type==SDL_MOUSEBUTTONDOWN)
    {
        if(event.button.x>360 && event.button.x<640 && event.button.y>300 && event.button.y<446)
        {
            cont=0;
            choix=1;  // minimax
            Puissance4(choix);
        }
        else if(event.button.x>700 && event.button.x<952 && event.button.y>550 && event.button.y<668)
        {
            cont=0;
            choix=2;   // alphabeta
            Puissance4(choix);
        }
    }
    if(event.type==SDL_QUIT)
        {
            cont=0;
            SDL_FreeSurface(Fond2);SDL_FreeSurface(MediumV1);SDL_FreeSurface(MediumV2);SDL_FreeSurface(HardV1);SDL_FreeSurface(HardV2);
            SDL_Quit();
        }
    }


}







void menu(SDL_Surface *Screen)
{
    int cont=1;

    SDL_Event event;

    //SDL_BlitSurface(PlayV1,NULL,Screen,&posPlay);
    //SDL_BlitSurface(ExitV1,NULL,Screen,&posExit);
    while(cont)
    {
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
    SDL_BlitSurface(Fond,NULL,Screen,&posFond);
    SDL_WaitEvent(&event);
    if(event.type==SDL_MOUSEMOTION)
    {
        if(event.button.x>50 && event.button.x<302 && event.button.y>540 && event.button.y<658)
        {
            SDL_BlitSurface(PlayV2,NULL,Screen,&posPlay);
            SDL_BlitSurface(ExitV1,NULL,Screen,&posExit);
            SDL_Flip(Screen);
            SDL_FreeSurface(PlayV2);
            SDL_FreeSurface(ExitV1);
        }
        else if(event.button.x>700 && event.button.x<952 && event.button.y>550 && event.button.y<668)
        {
            SDL_BlitSurface(PlayV1,NULL,Screen,&posPlay);
            SDL_BlitSurface(ExitV2,NULL,Screen,&posExit);
            SDL_Flip(Screen);
            SDL_FreeSurface(PlayV2);
            SDL_FreeSurface(ExitV1);
        }
        else
        {
            SDL_BlitSurface(PlayV1,NULL,Screen,&posPlay);
            SDL_BlitSurface(ExitV1,NULL,Screen,&posExit);
            SDL_Flip(Screen);
            SDL_FreeSurface(PlayV1);
            SDL_FreeSurface(ExitV1);
        }
    }
    if(event.type==SDL_MOUSEBUTTONDOWN)
    {
        if(event.button.x>50 && event.button.x<302 && event.button.y>540 && event.button.y<658)
        {
            SDL_FreeSurface(Fond);SDL_FreeSurface(PlayV1);SDL_FreeSurface(PlayV2);SDL_FreeSurface(ExitV1);SDL_FreeSurface(ExitV2);
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


}





int main ( int argc, char** argv )
{
    int continu=1;
    SDL_Event event;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface *Screen=NULL;   // surface de travail
    Screen=SDL_SetVideoMode(1000,708,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
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
