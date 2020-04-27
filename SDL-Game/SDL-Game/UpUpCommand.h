//
//  UpUpCommand.h
//  SDL-Game
//
//  Created by ngchenghow on 23/12/2018.
//  Copyright © 2018 ngchenghow. All rights reserved.
//

#ifndef UpUpCommand_h
#define UpUpCommand_h

#include "GraphicObject.h"

class UpUpCommand:public Command
{
public:
    virtual void execute(GraphicObject* player) override{
        player->upUp();
    }
};

#endif /* UpUpCommand_h */
