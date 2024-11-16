#ifndef RAQUETTE_H_INCLUDED
#define RAQUETTE_H_INCLUDED

#include "gameSettings.h"
#include <SDL.h>

typedef struct
{
        int h,w;            //La structure repr�sentant la raquette
        float x,y;
        float dy;
}Racket;

void racketCollision(Racket* racket);
void drawRacket(Racket* racket,SDL_Renderer **renderer);
void updateRacket(Racket* racket);

#endif // RAQUETTE_H_INCLUDED
