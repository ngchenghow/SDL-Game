//
//  AttackUpCommand.h
//  SDL-Game
//
//  Created by ngchenghow on 12/01/2019.
//  Copyright © 2019 ngchenghow. All rights reserved.
//

#ifndef AttackUpCommand_h
#define AttackUpCommand_h

#include "GraphicObject.h"

class AttackUpCommand:public Command
{
public:
    virtual void execute(GraphicObject* player) override{
        player->attackUp();
    }
};

#endif /* AttackUpCommand_h */
