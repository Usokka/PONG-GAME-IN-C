#include "menu.h"

Menu initMenu(){
    Menu menu;

    menu.play.message = "play";
    menu.play.selected = SDL_FALSE;
    menu.play.x = WINDOW_WIDTH/2 - strlen(menu.play.message)*LITTLE_TEXT_SIZE/4;
    menu.play.y = WINDOW_HEIGHT/2;
    menu.play.color.r = 0;
    menu.play.color.g = 0;
    menu.play.color.b = 0;
    menu.play.color.a = 255;

    menu.quit.message = "quit";
    menu.quit.selected = SDL_FALSE;
    menu.quit.x = WINDOW_WIDTH/2 - strlen(menu.quit.message)*LITTLE_TEXT_SIZE/4;
    menu.quit.y = WINDOW_HEIGHT/2 + 100;
    menu.quit.color.r = 0;
    menu.quit.color.g = 0;
    menu.quit.color.b = 0;
    menu.quit.color.a = 255;

    menu.goToMenu.message = "go to menu";
    menu.goToMenu.selected = SDL_FALSE;
    menu.goToMenu.x = WINDOW_WIDTH/2 - strlen(menu.goToMenu.message)*LITTLE_TEXT_SIZE/4;
    menu.goToMenu.y = WINDOW_HEIGHT/2;
    menu.goToMenu.color.r = 0;
    menu.goToMenu.color.g = 0;
    menu.goToMenu.color.b = 0;
    menu.goToMenu.color.a = 255;

    menu.choosePlayer.message = "Player vs Player";
    menu.choosePlayer.selected = SDL_FALSE;
    menu.choosePlayer.x = WINDOW_WIDTH/2 - strlen(menu.choosePlayer.message)*LITTLE_TEXT_SIZE/4;
    menu.choosePlayer.y = WINDOW_HEIGHT/2;
    menu.choosePlayer.color.r = 0;
    menu.choosePlayer.color.g = 0;
    menu.choosePlayer.color.b = 0;
    menu.choosePlayer.color.a = 255;

    menu.chooseBot.message = "Player vs Bot";
    menu.chooseBot.selected = SDL_FALSE;
    menu.chooseBot.x = WINDOW_WIDTH/2 - strlen(menu.chooseBot.message)*LITTLE_TEXT_SIZE/4;
    menu.chooseBot.y = WINDOW_HEIGHT/2 + 100;
    menu.chooseBot.color.r = 0;
    menu.chooseBot.color.g = 0;
    menu.chooseBot.color.b = 0;
    menu.chooseBot.color.a = 255;

    menu.chooseNormalMode.message = "normal";
    menu.chooseNormalMode.selected = SDL_FALSE;
    menu.chooseNormalMode.x = WINDOW_WIDTH/2 - strlen(menu.chooseNormalMode.message)*LITTLE_TEXT_SIZE/4;
    menu.chooseNormalMode.y = WINDOW_HEIGHT/2;
    menu.chooseNormalMode.color.r = 0;
    menu.chooseNormalMode.color.g = 0;
    menu.chooseNormalMode.color.b = 0;
    menu.chooseNormalMode.color.a = 255;

    menu.chooseCustomMode.message = "custom";
    menu.chooseCustomMode.selected = SDL_FALSE;
    menu.chooseCustomMode.x = WINDOW_WIDTH/2 - strlen(menu.chooseCustomMode.message)*LITTLE_TEXT_SIZE/4;
    menu.chooseCustomMode.y = WINDOW_HEIGHT/2 + 100;
    menu.chooseCustomMode.color.r = 0;
    menu.chooseCustomMode.color.g = 0;
    menu.chooseCustomMode.color.b = 0;
    menu.chooseCustomMode.color.a = 255;

    return menu;
}

void menu(Menu* menu,SDL_Renderer** renderer,SDL_Surface **text,  SDL_Texture **texture, TTF_Font** font){
    renderText(renderer,texture,text,font,"PONG GAME",(SDL_Color){255,255,255,255},WINDOW_WIDTH/2 - strlen("PONG GAME")*BIG_TEXT_SIZE/4,WINDOW_HEIGHT/4,big);
    drawBtn(renderer,texture,text,font,&menu->play,little);
    drawBtn(renderer,texture,text,font,&menu->quit,little);
}

void chooseEnemyMenu(Menu* menu,SDL_Renderer** renderer,SDL_Surface **text,  SDL_Texture **texture, TTF_Font** font){
    renderText(renderer,texture,text,font,"PONG GAME",(SDL_Color){255,255,255,255},WINDOW_WIDTH/2 - strlen("PONG GAME")*BIG_TEXT_SIZE/4,WINDOW_HEIGHT/4,big);
    renderText(renderer,texture,text,font,"choose your opponent:",(SDL_Color){255,255,255,255},WINDOW_WIDTH/2 - strlen("choose your opponent")*LITTLE_TEXT_SIZE/4,WINDOW_HEIGHT/2 - 50,little);
    drawBtn(renderer,texture,text,font,&menu->choosePlayer,little);
    drawBtn(renderer,texture,text,font,&menu->chooseBot,little);
}

void chooseModeMenu(Menu* menu,SDL_Renderer** renderer,SDL_Surface **text,  SDL_Texture **texture, TTF_Font** font){
    renderText(renderer,texture,text,font,"PONG GAME",(SDL_Color){255,255,255,255},WINDOW_WIDTH/2 - strlen("PONG GAME")*BIG_TEXT_SIZE/4,WINDOW_HEIGHT/4,big);
    renderText(renderer,texture,text,font,"choose the gamemode:",(SDL_Color){255,255,255,255},WINDOW_WIDTH/2 - strlen("choose the gamemode:")*11,WINDOW_HEIGHT/2 - 50,little);
    drawBtn(renderer,texture,text,font,&menu->chooseNormalMode,little);
    drawBtn(renderer,texture,text,font,&menu->chooseCustomMode,little);
}

void finishGameMenu(Menu* menu,SDL_Renderer** renderer,SDL_Surface **text,  SDL_Texture **texture, TTF_Font** font,int whoWon){

    if(whoWon == player1){
        renderText(renderer,texture,text,font,
            "PLAYER 1 WON",(SDL_Color) {255,255,255,255},
            WINDOW_WIDTH/2 - strlen("PLAYER 1 WON")*25,WINDOW_HEIGHT/4,big);
    }
    else if(whoWon == player2)
    {
        renderText(renderer,texture,text,font,
            "PLAYER 2 WON",(SDL_Color) {255,255,255,255},
            WINDOW_WIDTH/2 - strlen("PLAYER 2 WON")*25,WINDOW_HEIGHT/4,big);
    }
    else if(whoWon == bot){
        renderText(renderer,texture,text,font,
            "BOT WON",(SDL_Color) {255,255,255,255},
            WINDOW_WIDTH/2 - strlen("BOT WON")*25,WINDOW_HEIGHT/4,big);
    }
    
    drawBtn(renderer,texture,text,font,&menu->goToMenu,little);
}