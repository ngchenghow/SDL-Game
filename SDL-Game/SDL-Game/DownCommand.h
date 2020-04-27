//
//  DownCommand.h
//  SDL-Game
//
//  Created by ngchenghow on 23/12/2018.
//  Copyright © 2018 ngchenghow. All rights reserved.
//

#ifndef DownCommand_h
#define DownCommand_h

#include "GraphicObject.h"

class DownCommand:public Command
{
public:
    virtual void execute(GraphicObject* player) override{
        player->down();
    }
};

#endif /* DownCommand_h */
