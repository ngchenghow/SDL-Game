//
//  RightCommand.h
//  SDL-Game
//
//  Created by ngchenghow on 23/12/2018.
//  Copyright © 2018 ngchenghow. All rights reserved.
//

#ifndef RightCommand_h
#define RightCommand_h

#include "GraphicObject.h"

class RightCommand:public Command
{
public:
    virtual void execute(GraphicObject* player) override{
        player->right();
    }
};

#endif /* RightCommand_h */
