//
//  UpCommand.h
//  SDL-Game
//
//  Created by ngchenghow on 23/12/2018.
//  Copyright © 2018 ngchenghow. All rights reserved.
//

#ifndef UpCommand_h
#define UpCommand_h

#include "GraphicObject.h"

class UpCommand:public Command
{
public:
    virtual void execute(GraphicObject* player) override{
        player->up();
    }
};

#endif /* UpCommand_h */
