//
//  GameStateMachine.cpp
//  SDL-Game
//
//  Created by ngchenghow on 14/01/2019.
//  Copyright © 2019 ngchenghow. All rights reserved.
//

#include <stdio.h>

#include "GameState.h"
#include <vector>
#include "SDL2/SDL.h"

#include "MenuState.h"
#include "PlayState.h"

void GameStateMachine::toMenu(){
    changeState(new MenuState());
}

void GameStateMachine::toPlay(){
    changeState(new PlayState());
}

void GameStateMachine::update(){
    gameStates.back()->update();
}

void GameStateMachine::render(){
    gameStates.back()->render();
}

void GameStateMachine::clickHandler(){
    gameStates.back()->clickHandler();
}

void GameStateMachine::mouseDownHandler(){
    gameStates.back()->mouseDownHandler();
}

void GameStateMachine::mouseUpHandler(){
    gameStates.back()->mouseUpHandler();
}

void GameStateMachine::mouseMotionHandler(){
    gameStates.back()->mouseMotionHandler();
}

void GameStateMachine::pushState(GameState* pState){
    gameStates.push_back(pState);
    gameStates.back()->onEnter();
}

void GameStateMachine::changeState(GameState* pState){
    if(!gameStates.empty()){
        if(gameStates.back()->getStateID()==pState->getStateID()){
            return;
        }
        
        popState();
        
        gameStates.push_back(pState);
        gameStates.back()->onEnter();
    }
}

void GameStateMachine::popState(){
    if(gameStates.empty()){
        return;
    }
    if(gameStates.back()->onExit()){
        gameStates.pop_back();
    }
}

void GameStateMachine::keyDownHandler(SDL_Event event){
    gameStates.back()->keyDownHandler(event);
}

void GameStateMachine::keyUpHandler(SDL_Event event){
    gameStates.back()->keyUpHandler(event);
}
