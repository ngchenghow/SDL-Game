//
//  SprintUpCommand.h
//  SDL-Game
//
//  Created by ngchenghow on 24/12/2018.
//  Copyright © 2018 ngchenghow. All rights reserved.
//

#ifndef SprintUpCommand_h
#define SprintUpCommand_h

#include "GraphicObject.h"

class SprintUpCommand:public Command
{
public:
    virtual void execute(GraphicObject* player) override{
        player->sprintUp();
    }
};

#endif /* SprintUpCommand_h */
