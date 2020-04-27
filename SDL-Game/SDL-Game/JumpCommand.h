//
//  JumpCommand.h
//  SDL-Game
//
//  Created by ngchenghow on 23/12/2018.
//  Copyright © 2018 ngchenghow. All rights reserved.
//

#ifndef JumpCommand_h
#define JumpCommand_h

#include "GraphicObject.h"

class JumpCommand:public Command
{
public:
    virtual void execute(GraphicObject* player) override{
        player->jump();
    }
};

#endif /* JumpCommand_h */
