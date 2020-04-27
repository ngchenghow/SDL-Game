//
//  GameStateMachine.h
//  2D-Game-Engine
//
//  Created by ngchenghow on 12/12/2018.
//  Copyright © 2018 ngchenghow. All rights reserved.
//

#ifndef GameStateMachine_h
#define GameStateMachine_h

#include "GameState.h"
#include <vector>
#include "SDL2/SDL.h"

class GameState;

class GameStateMachine
{
public:
    
    void changeState(GameState* pState);
    void pushState(GameState* pState);
    void update();
    void clickHandler();
    void mouseDownHandler();
    void mouseUpHandler();
    void mouseMotionHandler();
    void render();
    void popState();
    void keyDownHandler(SDL_Event event);
    void keyUpHandler(SDL_Event event);
    
    void toMenu();
    void toPlay();
    
private:
    std::vector<GameState*> gameStates;
};

#endif /* GameStateMachine_h */
