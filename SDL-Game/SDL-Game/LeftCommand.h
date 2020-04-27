//
//  LeftCommand.h
//  SDL-Game
//
//  Created by ngchenghow on 23/12/2018.
//  Copyright © 2018 ngchenghow. All rights reserved.
//

#ifndef LeftCommand_h
#define LeftCommand_h

#include "GraphicObject.h"

class LeftCommand:public Command
{
public:
    virtual void execute(GraphicObject* player) override{
        player->left();
    }
};

#endif /* LeftCommand_h */
