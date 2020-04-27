//
//  Block.h
//  SDL-Game
//
//  Created by ngchenghow on 16/12/2018.
//  Copyright © 2018 ngchenghow. All rights reserved.
//

#ifndef Block_h
#define Block_h

#include "Vector2D.h"

namespace models{
    class Block
    {
    public:
        Vector2D* p;
        
        int jumpy=0;
        int weak=0;
        int water=0;
        int wet=80;
        int sand=0;
        int ctop=1;
        int cleft=1;
        int cright=1;
        int cbottom=1;
        
        Block(Vector2D* p,int jumpy,int weak,int water,int wet,int sand):p(p),jumpy(jumpy),weak(weak),water(water),wet(wet),sand(sand){
            
        }
        
    };
}

#endif /* Block_h */
