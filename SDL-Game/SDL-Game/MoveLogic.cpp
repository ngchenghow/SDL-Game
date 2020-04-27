//
//  MoveLogic.cpp
//  SDL-Game
//
//  Created by ngchenghow on 20/01/2019.
//  Copyright © 2019 ngchenghow. All rights reserved.
//

#include <stdio.h>
#include "GraphicObject.h"


void MoveLogic::move(GraphicObject* target){
    
    //change xmove direction
    if(owner->atLeftEdge){
        xmove=1;
    }else if(owner->atRightEdge){
        xmove=-1;
    }
    
    if(target==owner){
        target->vhorizontal=xmove;
    }else{
        target->vhorizontal+=xmove;
    }
    
}

void MoveLogic::init(GraphicObject* owner){
    this->owner=owner;
    oriX=owner->x;
    oriY=owner->y;
}
