//
//  ActionUpCommand.h
//  SDL-Game
//
//  Created by ngchenghow on 10/01/2019.
//  Copyright © 2019 ngchenghow. All rights reserved.
//

#ifndef ActionUpCommand_h
#define ActionUpCommand_h

#include "GraphicObject.h"

class ActionUpCommand:public Command
{
public:
    virtual void execute(GraphicObject* player) override{
        player->actionUp();
    }
};

#endif /* ActionUpCommand_h */
