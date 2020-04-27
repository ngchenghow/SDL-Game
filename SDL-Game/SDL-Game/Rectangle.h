//
//  Rectangle.h
//  SDL-Game
//
//  Created by ngchenghow on 11/01/2019.
//  Copyright © 2019 ngchenghow. All rights reserved.
//

#ifndef Rectangle_h
#define Rectangle_h
#include "Vector2D.h"
#include "Graphic.h"

namespace models{
    class Rectangle{
    public:
        
        Vector2D* topLeft;
        Vector2D* bottomRight;
        
        float damageValue=0.0f;
        int damageType=0;
        
        Rectangle(Vector2D* topLeft,Vector2D* bottomRight):topLeft(topLeft),bottomRight(bottomRight){
            
        }
        
        bool isCollision(Rectangle* trect,Graphic* stage){
            if(!trect){
                return false;
            }
            float x1=getX1(stage);
            float y1=getY1(stage);
            float x2=getX2(stage);
            float y2=getY2(stage);
            
            return trect->getX2(stage)>=x1 && trect->getX1(stage)<=x2 && trect->getY1(stage)<=y2 && trect->getY2(stage)>=y1;
        }
        
        float getX1(Graphic* stage){
            return topLeft->x+stage->getX();
        }
        
        float getY1(Graphic* stage){
            return topLeft->y+stage->getY();
        }
        
        float getX2(Graphic* stage){
            return bottomRight->x+stage->getX();
        }
        
        float getY2(Graphic* stage){
            return bottomRight->y+stage->getY();
        }
        
    };
}


#endif /* Rectangle_h */
