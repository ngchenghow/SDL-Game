//
//  RightUpCommand.h
//  SDL-Game
//
//  Created by ngchenghow on 23/12/2018.
//  Copyright © 2018 ngchenghow. All rights reserved.
//

#ifndef RightUpCommand_h
#define RightUpCommand_h

#include "GraphicObject.h"

class RightUpCommand:public Command
{
public:
    virtual void execute(GraphicObject* player) override{
        player->rightUp();
    }
};

#endif /* RightUpCommand_h */
