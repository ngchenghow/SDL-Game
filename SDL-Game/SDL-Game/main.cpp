
#include <SDL2/SDL.h>
#include <iostream>
#include "Game.h"

Game* game=nullptr;

int main(int argc, const char * argv[]) {
    
    game=Game::Instance();
    
    game->init("Game Window",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1280,720,false,true);
    
    while(game->running()){
        game->handleEvents();
        game->update();
        game->render();
        game->timeDelay();
    }
    
    game->clean();
    
    return 0;
}
