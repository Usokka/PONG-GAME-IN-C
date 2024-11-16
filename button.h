#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string.h>

enum btnSize{little,big,normal};

typedef struct{
    const char* message;
    SDL_bool selected;
    SDL_Color color;
    int x,y,w,h;
}Button;


void renderText(SDL_Renderer** renderer,SDL_Texture** texture,SDL_Surface** text,TTF_Font** font, const char* message, SDL_Color color, int x,int y,int size);
void drawBtn(SDL_Renderer** renderer,SDL_Texture** texture,SDL_Surface** text,TTF_Font** font, Button* button,int size);
void hoverButton(Button* button);
SDL_bool clickButton(Button* button);


#endif // BUTTON_H_INCLUDED
