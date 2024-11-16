#include "game.h"

void error(const char* message){
    SDL_Log("ERROR: %s %s",message,SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void initSDL(Game *game)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
        error("SDL could not be loaded.");

    if(TTF_Init()<0)
        error("TTF could not be loaded");

    game->gameFont = TTF_OpenFont("Retro Gaming.ttf",72);

    if(game->gameFont == NULL)
        error("Font not found");

    game->gameWindow = SDL_CreateWindow("pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_SHOWN );

    if(game->gameWindow == NULL)
        error("window could not be created.");

    game->gameRendrer = SDL_CreateRenderer(game->gameWindow, -1, SDL_RENDERER_ACCELERATED);

    if(game->gameRendrer == NULL)
        error("renderer could not be created.");
}

void initGame(Game *game){
    game->menu = malloc(sizeof(Menu));
    *game->menu = initMenu();
    game->menuState = mainMenu;

    game->ball = (Ball) {BALL_SIZE,WINDOW_WIDTH/2 - BALL_SIZE/2,WINDOW_HEIGHT/2 - BALL_SIZE/2,
                BALL_SIZE,BALL_VEL,SDL_FALSE};

    game->player = (Racket) {RACKET_HEIGHT,RACKET_WIDTH,
                            0,WINDOW_HEIGHT/2 - RACKET_HEIGHT/2,0};

    game->enemy = (Racket) {RACKET_HEIGHT,RACKET_WIDTH,
                            WINDOW_WIDTH-RACKET_WIDTH,WINDOW_HEIGHT/2 - RACKET_HEIGHT/2,0}; 

    game->playerScore = 0;
    game->enemyScore = 0;

    game->running = SDL_TRUE;                   

}

void hoverButtons(Game *game){
    hoverButton(&game->menu->chooseBot);
    hoverButton(&game->menu->choosePlayer); 
    hoverButton(&game->menu->chooseCustomMode);
    hoverButton(&game->menu->chooseNormalMode);
    hoverButton(&game->menu->goToMenu);
    hoverButton(&game->menu->play);
    hoverButton(&game->menu->quit);
}

void clickButtons(Game* game){

    switch(game->menuState){
        case enemyMenu:
            if(clickButton(&game->menu->choosePlayer)){
                game->enemyChoice = playerChoice;
                game->menuState = modeMenu;
            }
            
            if(clickButton(&game->menu->chooseBot)){
                game->enemyChoice = botChoice;
                game->menuState = modeMenu;
            }
        break;
            
        case modeMenu:
            if(clickButton(&game->menu->chooseCustomMode)){
                game->gameMode = customMode;
                game->menuState = -1;
            }
        
            if(clickButton(&game->menu->chooseNormalMode)){
                game->gameMode = normalMode;
                game->menuState = -1;
            }
        break;

        case finishedMenu:
            if(clickButton(&game->menu->goToMenu)){
                game->menuState = mainMenu;
                resetState(game);
                game->playerScore = 0;
                game->enemyScore = 0;
            }        
        break;

        default:
            if(clickButton(&game->menu->play)){
                game->menuState = enemyMenu;
            }
        
            if(clickButton(&game->menu->quit))
                game->running = SDL_FALSE;
        break;
    }
}

void handleEvents(Game* game,SDL_Event event){

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                game->running = SDL_FALSE;
            break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_z:
                        game->player.dy = -RACKET_VEL;
                    break;
                    case SDLK_s:
                        game->player.dy = RACKET_VEL;
                    break;

                    case SDLK_UP:
                        if(game->enemyChoice == playerChoice)
                            game->enemy.dy = -RACKET_VEL;
                    break;
                    case SDLK_DOWN:
                        if(game->enemyChoice == playerChoice)
                            game->enemy.dy = RACKET_VEL;
                    break;
                }
            break;

            case SDL_KEYUP:
                switch(event.key.keysym.sym)
                {
                    case SDLK_z:
                        game->player.dy = 0;
                    break;
                    case SDLK_s:
                        game->player.dy = 0;
                    break;

                    case SDLK_UP:
                        if(game->enemyChoice == playerChoice)
                            game->enemy.dy = 0;
                    break;
                    case SDLK_DOWN:
                        if(game->enemyChoice == playerChoice)
                            game->enemy.dy = 0;
                    break;
                }
            break;

            case SDL_MOUSEMOTION:
                hoverButtons(game);                          
            break;

            case SDL_MOUSEBUTTONUP:
                clickButtons(game);     
            break;
        }
    }
}

void drawMenus(Game* game){

    switch(game->menuState){
        case modeMenu:
            chooseModeMenu(game->menu,&game->gameRendrer,&game->text,&game->texture,&game->gameFont);
        break;

        case enemyMenu:
            chooseEnemyMenu(game->menu,&game->gameRendrer,&game->text,&game->texture,&game->gameFont);
        break;

        case finishedMenu:
            finishGameMenu(game->menu,&game->gameRendrer,&game->text,&game->texture,&game->gameFont,game->whoWon);
        break;

        default:
            menu(game->menu,&game->gameRendrer,&game->text,&game->texture,&game->gameFont);
        break;
    }
}

void updateGame(Game *game){

    updateBall(&game->ball);

    if(game->enemyChoice == botChoice)
        followBall(&game->enemy,&game->ball);

    
    updateRacket(&game->player);
    if(game->enemyChoice == playerChoice)
        updateRacket(&game->enemy);
    
}

void collisionsGame(Game* game){

    racketCollision(&game->enemy);
    racketCollision(&game->player);

    handleBallHitRacket(&game->enemy,&game->ball);
    handleBallHitRacket(&game->player,&game->ball);
    ballCollision(&game->ball);
}

void customGameMode(Game* game){

}


void handleScore(Game* game){

    if(game->playerScore >= MAX_SCORE || game->enemyScore >= MAX_SCORE){
        game->menuState = finishedMenu;
        game->whoWon = game->playerScore > game->enemyScore ? player1 : game->enemyChoice == botChoice ? bot : player2;
        return;
    }

    if(game->ball.x + game->ball.bsize > WINDOW_WIDTH){
        game->playerScore+=1;
        resetState(game);
    }
    if(game->ball.x < 0){
        game->enemyScore+=1;
        resetState(game);
    }

}

void drawScore(Game* game){
    char enemyScore[10];
    char player1Score[10];
    sprintf(enemyScore, "%d", game->enemyScore);
    sprintf(player1Score, "%d", game->playerScore);

    renderText(&game->gameRendrer,&game->texture,&game->text,&game->gameFont,
                player1Score,(SDL_Color) {255,255,255,255},
                WINDOW_WIDTH/4,50,normal);
    
    renderText(&game->gameRendrer,&game->texture,&game->text,&game->gameFont,
                enemyScore,(SDL_Color) {255,255,255,255},
                WINDOW_WIDTH/4 + WINDOW_WIDTH/2,50,normal);
}

void gameLogic(Game* game){
    updateGame(game);
    collisionsGame(game);
    handleScore(game);
}

void resetState(Game *game){
    game->player.y = WINDOW_HEIGHT/2 - RACKET_HEIGHT/2;
    game->ball.x = WINDOW_WIDTH/2 - BALL_SIZE/2;
    game->ball.y = WINDOW_HEIGHT/2 - BALL_SIZE/2;

    if(game->playerScore > game->enemyScore)
        game->ball.dy = -BALL_VEL/6;
    else if(game->playerScore < game->enemyScore)
        game->ball.dy = BALL_VEL/6;
    else{
        game->ball.dy = -game->ball.dy;
    }

    game->enemy.y = WINDOW_HEIGHT/2 - RACKET_HEIGHT/2;
}

void drawGame(Game* game){
    
    SDL_SetRenderDrawColor((game->gameRendrer),20,40,50,255);
    SDL_RenderClear((game->gameRendrer));

    if(game->menuState == -1){
        SDL_SetRenderDrawColor((game->gameRendrer),255,255,255,255);
        SDL_RenderDrawLine(game->gameRendrer,WINDOW_WIDTH/2 -1,0,WINDOW_WIDTH/2 -1,WINDOW_HEIGHT);
        SDL_RenderDrawLine(game->gameRendrer,WINDOW_WIDTH/2 -1,0,WINDOW_WIDTH/2 -1,WINDOW_HEIGHT);

        drawBall(&game->ball,&game->gameRendrer,(SDL_Color) {255,255,255,255});
        drawRacket(&game->player,&game->gameRendrer);
        drawRacket(&game->enemy,&game->gameRendrer);
        drawScore(game);
    }
    else{
        drawMenus(game);
    }

    SDL_RenderPresent(game->gameRendrer);
}