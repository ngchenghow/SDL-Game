//
//  SprintCommand.h
//  SDL-Game
//
//  Created by ngchenghow on 24/12/2018.
//  Copyright © 2018 ngchenghow. All rights reserved.
//

#ifndef SprintCommand_h
#define SprintCommand_h

#include "GraphicObject.h"

class SprintCommand:public Command
{
public:
    virtual void execute(GraphicObject* player) override{
        player->sprint();
    }
};

#endif /* SprintCommand_h */
