#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <time.h>
typedef struct Enemy
{
  SDL_Surface *image[3];
  SDL_Surface *Hit;
  SDL_Surface *imageActuel;
  SDL_Rect position;
  SDL_Rect positionO;
  int fram;
  int direction;

}Enemy;
Enemy InitEnemy(Enemy Ennemie,int x, int y)
{
  Ennemie.image[0]=IMG_Load("rpg1.png");
  Ennemie.image[1]=IMG_Load("rpg2.png");
  Ennemie.image[2]=IMG_Load("rpg3.png");
  Ennemie.Hit=IMG_Load("rpg4.png");
  Ennemie.imageActuel=Ennemie.image[0];
  Ennemie.position.x=x;
  Ennemie.position.y=y;
  Ennemie.positionO=Ennemie.position;
  Ennemie.fram=0;
  Ennemie.direction=0;
  return Ennemie;
}
void  AfficherEnemy(Enemy Ennemie,SDL_Surface *screen)
{
  SDL_BlitSurface(Ennemie.imageActuel,NULL,screen,&Ennemie.position);
}
Enemy AnimateEnemy(Enemy Ennemie,int stat)
{
  if (Ennemie.fram==2) {
    Ennemie.fram=0;
  }
  else
  Ennemie.fram++;
  Ennemie.imageActuel=Ennemie.image[Ennemie.fram];
  if(stat==1)
    Ennemie.imageActuel=Ennemie.Hit;
  return Ennemie;

}
Enemy MoveEnemy(Enemy Ennemie,SDL_Rect personnage,int *stat)
{

int distance;

  if(Ennemie.position.x>=personnage.x)
    distance=Ennemie.position.x-personnage.x;
  else
    distance=personnage.x-Ennemie.position.x;
if(distance<50)*stat=1;
else *stat=0;
    if(distance<200)
      {
        if(Ennemie.position.x>=personnage.x)
          Ennemie.direction=0;
        else
          Ennemie.direction=1;
      }

      else
    {  if(Ennemie.positionO.x+100==Ennemie.position.x)
          Ennemie.direction=0;

      if(Ennemie.positionO.x-100==Ennemie.position.x)

        Ennemie.direction=1;}


      if(Ennemie.direction==1)
      {
        Ennemie.position.x+=5;
      }
      if(Ennemie.direction==0)
      {
        Ennemie.position.x-=5;
      }


  return Ennemie;
}
int main(int argc, char *argv[])
{SDL_Surface *ecran;
  SDL_Surface *personnage =NULL;
   SDL_Init(SDL_INIT_VIDEO);
   Enemy e;
e=InitEnemy(e,0,250);
ecran = SDL_SetVideoMode(800, 600,32,SDL_HWSURFACE || SDL_DOUBLEBUF||SDL_FULLSCREEN );
	SDL_Rect positiondetective;

positiondetective.y=250;
positiondetective.x=0;

    SDL_Event event;
    int continuer = 1,a;
    SDL_WM_SetCaption("jeux", NULL);
personnage=IMG_Load("Bee_0000_Capa-1.png");




    while (continuer)
    { SDL_PollEvent(&event);


      
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
		case SDL_KEYUP:
break;
            case SDL_KEYDOWN :

                 switch(event.key.keysym.sym)
                {


                    case SDLK_RIGHT:
positiondetective.x+=30;

                        break;
                    case SDLK_LEFT :

positiondetective.x-=30;

                    break;




                }
                break;


        }
SDL_Delay(90);

e=MoveEnemy(e,positiondetective,&a);
e=AnimateEnemy(e,a);
 SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

 SDL_BlitSurface(personnage,NULL,ecran, &positiondetective);
  AfficherEnemy(e,ecran);
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(personnage);

    SDL_Quit();

    return EXIT_SUCCESS;


}
