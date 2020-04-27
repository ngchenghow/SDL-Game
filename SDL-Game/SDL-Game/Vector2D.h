//
//  Vector2D.h
//  2D-Game-Engine
//
//  Created by ngchenghow on 14/12/2018.
//  Copyright © 2018 ngchenghow. All rights reserved.
//

#ifndef Vector2D_h
#define Vector2D_h

#include <cmath>

namespace models{
    class Vector2D
    {
    public:
        float x;
        float y;
        
        Vector2D(float x,float y):x(x),y(y){
            
        }
        
        Vector2D(){
            
        }
        
        float distX(Vector2D* p2){
            return abs(this->x-p2->x);
        }
        float distY(Vector2D* p2){
            return abs(this->y-p2->y);
        }
    };
}

#endif /* Vector2D_h */
