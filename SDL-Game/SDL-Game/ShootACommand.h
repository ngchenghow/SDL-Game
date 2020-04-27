//
//  ShootACommand.h
//  SDL-Game
//
//  Created by ngchenghow on 18/01/2019.
//  Copyright © 2019 ngchenghow. All rights reserved.
//

#ifndef ShootACommand_h
#define ShootACommand_h

#include "GraphicObject.h"

class ShootACommand:public Command
{
public:
    virtual void execute(GraphicObject* player) override{
        player->shootA();
    }
};

#endif /* ShootACommand_h */
