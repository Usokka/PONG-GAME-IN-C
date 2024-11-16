#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include "gameSettings.h"
#include "racket.h"
#include "ball.h"
#include "button.h"
#include "menu.h"
#include "bot.h"

enum GameMode{normalMode,customMode};
enum EnemyChoice{playerChoice,botChoice};

typedef struct {

    SDL_Window* gameWindow;
    SDL_Renderer* gameRendrer;
    SDL_Surface* text;
    SDL_Texture* texture;
    TTF_Font* gameFont;
    SDL_bool running;

    Menu* menu;
    int menuState;
    int gameMode;
    int enemyChoice;

    Ball ball;
    Ball ball2;
    Racket player;
    Racket enemy;

    int playerScore;
    int enemyScore;
    int whoWon;
}Game;

void error(const char* message);
void initSDL(Game* game);
void initGame(Game *game);
void hoverButtons(Game *game);
void clickButtons(Game* game);
void drawMenus(Game* game);
void handleEvents(Game* game,SDL_Event event);
void updateGame(Game *game);
void collisionsGame(Game* game);
void handleScore(Game* game);
void drawScore(Game* game);
void gameLogic(Game* game);
void resetState(Game *game);
void drawGame(Game* game);