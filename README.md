# Pong Game in C

This is the first project I ever made (in 2023). It is a Pong game with a menu, developed in C using the SDL2 library, including SDL_ttf for text rendering.

## Features
- Classic Pong gameplay.
- Main menu for navigation.
- Player vs. bot mode.
- Bot implemented with basic AI logic.

## Requirements
To run or edit this project, you will need:
- **SDL2** library.
- **SDL2_ttf** library.

## Compilation Instructions
To compile the project, use the following command:

```bash
gcc main.c game.c racket.c ball.c bot.c button.c menu.c -o bin/'name of the exe file' -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf
