//
//  MoveLogic.h
//  SDL-Game
//
//  Created by ngchenghow on 20/01/2019.
//  Copyright © 2019 ngchenghow. All rights reserved.
//

#ifndef MoveLogic_h
#define MoveLogic_h

#include "GraphicObject.h"
class GraphicObject;

class MoveLogic{
public:
    
    void move(GraphicObject* target);
    float xmove;
    GraphicObject* owner;
    float oriX;
    float oriY;
    
    MoveLogic(GraphicObject* owner):owner(owner){
        xmove=1;
        init(owner);
    }
    
    void init(GraphicObject* owner);
    
};

#endif /* MoveLogic_h */
