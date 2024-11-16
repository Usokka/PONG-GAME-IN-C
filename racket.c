#include "racket.h"
#include <stdio.h>

void racketCollision(Racket* racket)
{
    if(racket->y < 0)
        racket->y = 0;
    if (racket->y > WINDOW_HEIGHT - racket->h)
        racket->y = WINDOW_HEIGHT - racket->h;
}

void drawRacket(Racket* racket,SDL_Renderer **renderer){

    SDL_Rect rect= {(int) racket->x, (int) racket->y,racket->w,racket->h};
    SDL_SetRenderDrawColor(*renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(*renderer,&rect);
    SDL_RenderFillRect(*renderer,&rect);
}

void updateRacket(Racket *racket){
    racket->y += racket->dy;
}


