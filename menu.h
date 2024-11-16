#pragma once

#include "button.h"
#include "gameSettings.h"

enum whoWon{player1,player2,bot};
enum MenuState{mainMenu,enemyMenu,modeMenu,finishedMenu};

typedef struct {
    Button play;
    Button quit;
    Button goToMenu;

    Button chooseBot;
    Button choosePlayer;

    Button chooseNormalMode;
    Button chooseCustomMode;
}Menu;

Menu initMenu();
void menu(Menu* menu,SDL_Renderer** renderer,SDL_Surface **text,  SDL_Texture **texture, TTF_Font** font);
void chooseEnemyMenu(Menu* menu,SDL_Renderer** renderer,SDL_Surface **text,  SDL_Texture **texture, TTF_Font** font);
void chooseModeMenu(Menu* menu,SDL_Renderer** renderer,SDL_Surface **text,  SDL_Texture **texture, TTF_Font** font);
void finishGameMenu(Menu* menu,SDL_Renderer** renderer,SDL_Surface **text,  SDL_Texture **texture, TTF_Font** font,int whoWon);

/*

TO DO:

programmer un bon menu avec un render de chaque truc et un handle click de chaque bouton
ajouter un fichier utilities.h (pour afficher du texte etc ...)


*/