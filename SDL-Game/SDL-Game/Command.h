//
//  Command.h
//  SDL-Game
//
//  Created by ngchenghow on 23/12/2018.
//  Copyright © 2018 ngchenghow. All rights reserved.
//

#ifndef Command_h
#define Command_h

#include "GraphicObject.h"
class GraphicObject;

class Command{
public:
    virtual void execute(GraphicObject* player)=0;
};

#endif /* Command_h */
