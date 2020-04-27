//
//  JumpUpCommand.h
//  SDL-Game
//
//  Created by ngchenghow on 23/12/2018.
//  Copyright © 2018 ngchenghow. All rights reserved.
//

#ifndef JumpUpCommand_h
#define JumpUpCommand_h

#include "GraphicObject.h"

class JumpUpCommand:public Command
{
public:
    virtual void execute(GraphicObject* player) override{
        player->jumpUp();
    }
};

#endif /* JumpUpCommand_h */
