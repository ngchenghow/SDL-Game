//
//  DownUpCommand.h
//  SDL-Game
//
//  Created by ngchenghow on 23/12/2018.
//  Copyright © 2018 ngchenghow. All rights reserved.
//

#ifndef DownUpCommand_h
#define DownUpCommand_h

#include "GraphicObject.h"
#include "Command.h"

class DownUpCommand:public Command
{
public:
    virtual void execute(GraphicObject* player) override{
        player->downUp();
    }
};

#endif /* DownUpCommand_h */
