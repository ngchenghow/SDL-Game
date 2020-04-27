//
//  LeftUpCommand.h
//  SDL-Game
//
//  Created by ngchenghow on 23/12/2018.
//  Copyright © 2018 ngchenghow. All rights reserved.
//

#ifndef LeftUpCommand_h
#define LeftUpCommand_h

#include "GraphicObject.h"

class LeftUpCommand:public Command
{
public:
    virtual void execute(GraphicObject* player) override{
        player->leftUp();
    }
};

#endif /* LeftUpCommand_h */
