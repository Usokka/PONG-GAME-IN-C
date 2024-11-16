#include <stdio.h>
#include "game.h"

int main(int argc, char** argv){

    Game game;

    initGame(&game);
    initSDL(&game);
    SDL_Event event;
    const int FPS = 60;

    while(game.running){
        Uint32 startTime = SDL_GetTicks();
        handleEvents(&game,event);

        if(game.menuState == -1){
            gameLogic(&game);
        }
        drawGame(&game);
        Uint32 endTime = SDL_GetTicks();
        Uint32 elapsedTime = endTime - startTime;

        if(1000/FPS > elapsedTime)
            SDL_Delay(1000/FPS - elapsedTime);
    }

    return 0;
}