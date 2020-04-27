//
//  BCommand.h
//  SDL-Game
//
//  Created by ngchenghow on 10/01/2019.
//  Copyright © 2019 ngchenghow. All rights reserved.
//

#ifndef BCommand_h
#define BCommand_h

#include "GraphicObject.h"

class ActionCommand:public Command
{
public:
    virtual void execute(GraphicObject* player) override{
        player->action();
    }
};

#endif /* BCommand_h */
