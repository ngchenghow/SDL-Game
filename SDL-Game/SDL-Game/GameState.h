//
//  GameState.h
//  2D-Game-Engine
//
//  Created by ngchenghow on 12/12/2018.
//  Copyright © 2018 ngchenghow. All rights reserved.
//

#ifndef GameState_h
#define GameState_h

#include <string>
#include "SDL2/SDL.h"
#include "Command.h"
#include "GraphicObject.h"

class GameState
{
public:
    virtual void update()=0;
    virtual void render()=0;
    virtual bool onEnter()=0;
    virtual bool onExit()=0;
    virtual void clickHandler()=0;
    virtual void mouseDownHandler()=0;
    virtual void mouseUpHandler()=0;
    virtual void mouseMotionHandler()=0;
    virtual void keyDownHandler(SDL_Event event)=0;
    virtual void keyUpHandler(SDL_Event event)=0;
    virtual std::string getStateID() const=0;
};

#endif /* GameState_h */
