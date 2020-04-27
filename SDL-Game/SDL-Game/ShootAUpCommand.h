//
//  ShootAUpCommand.h
//  SDL-Game
//
//  Created by ngchenghow on 18/01/2019.
//  Copyright © 2019 ngchenghow. All rights reserved.
//

#ifndef ShootAUpCommand_h
#define ShootAUpCommand_h

#include "GraphicObject.h"

class ShootAUpCommand:public Command
{
public:
    virtual void execute(GraphicObject* player) override{
        player->shootAUp();
    }
};

#endif /* ShootAUpCommand_h */
