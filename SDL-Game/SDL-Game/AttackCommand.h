//
//  AttackCommand.h
//  SDL-Game
//
//  Created by ngchenghow on 12/01/2019.
//  Copyright © 2019 ngchenghow. All rights reserved.
//

#ifndef AttackCommand_h
#define AttackCommand_h

#include "GraphicObject.h"

class AttackCommand:public Command
{
public:
    virtual void execute(GraphicObject* player) override{
        player->attack();
    }
};

#endif /* AttackCommand_h */
