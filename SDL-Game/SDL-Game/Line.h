//
//  Line.h
//  SDL-Game
//
//  Created by ngchenghow on 19/12/2018.
//  Copyright © 2018 ngchenghow. All rights reserved.
//

#ifndef Line_h
#define Line_h

#include "Quad.h"
#include "Spread.h"
#include <cmath>

namespace models{
    class Line{
    public:
        Vector2D* p1;
        Vector2D* p2;
        Vector2D* stopAt;
        Vector2D* original;
        
        Quad* stopAtColl=NULL;
        int stopAtEdge=0;
        
        Quad* quad=NULL;
        void* playerOwner=NULL;
        
        float shortest=0.0f;
        int amt=1;
        int direction=0;
        int gothou=0;
        int wind=0;
        int ladder=0;
        bool attach=false;
        
        //1,2,3,4 edge
        int targetEdge=0;
        
        bool moving=false;
        float xmove=0;
        float ymove=0;
        float xmovea=0;
        float ymovea=0;
        
        bool isBullet=false;
        
        Quad* shooter=NULL;
        void* player=NULL;
        void* stopAtPlayer=NULL;
        float damageValue=0.0f;
        int damageType=0;
        
        int cleanUpCount=0;
        
        Spread* spread=NULL;
        
        int boundesCount=-1;
        
        ~Line(){
            delete p1;
            delete p2;
        }
        
        Line(Vector2D* p1,Vector2D* p2,int amt=1,int gothou=0,int wind=0,int ladder=0):p1(p1),p2(p2),amt(amt),gothou(gothou),wind(wind),ladder(ladder){
//            delete stopAt;
            stopAt=NULL;
            stopAtColl=NULL;
            stopAtPlayer=NULL;
        }
        
        void setStopAt(Vector2D* v){
            stopAt=v;
        }
        
        void resetCollision(){
            shortest=999999999;
//            delete stopAt;
            stopAt=NULL;
            stopAtColl=NULL;
            stopAtPlayer=NULL;
        }
        
        Vector2D* getStopAt(){

            if(stopAt!=NULL){
                return stopAt;
            }
            return p2;
        }
        
        bool collisionAndSet(Quad* qq){
            
            Vector2D* v=NULL;
            float shortest2=9999999999999;
            bool isColl=false;
            int stopAtEdge=0;
            //v 's initialize not NULL in this case
            if(stopAt){
                shortest2=this->shortest;
                v=stopAt;
            }
            
            float d;
            Vector2D* coll=NULL;
            Vector2D* coll2=NULL;
            Vector2D* coll3=NULL;
            Vector2D* coll4=NULL;
            
            if(qq->ctop && (!targetEdge || targetEdge==1)){
                coll=lineLine(p1->x,p1->y,p2->x,p2->y,qq->p1->x,qq->p1->y,qq->p2->x,qq->p2->y);
            }
            
            if(qq->cright && (!targetEdge || targetEdge==2)){
                coll2=lineLine(p1->x,p1->y,p2->x,p2->y,qq->p2->x,qq->p2->y,qq->p3->x,qq->p3->y);
            }
            
            if(qq->cbottom && (!targetEdge || targetEdge==3)){
                coll3=lineLine(p1->x,p1->y,p2->x,p2->y,qq->p3->x,qq->p3->y,qq->p4->x,qq->p4->y);
            }
            
            if(qq->cleft && (!targetEdge || targetEdge==4)){
                coll4=lineLine(p1->x,p1->y,p2->x,p2->y,qq->p4->x,qq->p4->y,qq->p1->x,qq->p1->y);
            }
            
            if(!targetEdge || targetEdge==1){
                if(coll){
                    d=disSquare(coll,p1);
                    if(shortest2>d){
                        shortest2=d;
                        v=coll;
                        isColl=true;
                        stopAtEdge=1;
                    }
                }
            }
            
            if(!targetEdge || targetEdge==2){
                if(coll2){
                    d=disSquare(coll2,p1);
                    if(shortest2>d){
                        shortest2=d;
                        v=coll2;
                        isColl=true;
                        stopAtEdge=2;
                    }
                    
                }
            }
            
            if(!targetEdge || targetEdge==3){
                if(coll3){
                    d=disSquare(coll3,p1);
                    if(shortest2>d){
                        shortest2=d;
                        v=coll3;
                        isColl=true;
                        stopAtEdge=3;
                    }
                   
                }
            }
            
            if(!targetEdge || targetEdge==4){
                if(coll4){
                    d=disSquare(coll4,p1);
                    if(shortest2>d){
                        shortest2=d;
                        v=coll4;
                        isColl=true;
                        stopAtEdge=4;
                    }
                    
                }
            }
            
            if(isColl){
                this->stopAt=v;
                this->shortest=shortest2;
                this->stopAtColl=qq;
                this->stopAtEdge=stopAtEdge;
                if(qq->player!=NULL){
                    this->stopAtPlayer=qq->player;
                }
                return true;
            }
            
            return false;
        }
        
        float disSquare(Vector2D* p1,Vector2D* p2){
            float dx=abs(p1->x-p2->x);
            float dy=abs(p1->y-p2->y);
            return dx*dx+dy*dy;
        }
        
        float getDegree(){
            float dx=p2->x-p1->x;
            float dy=p2->y-p1->y;
            return atan(dy/dx);
        }
        
        
        Vector2D* lineLine(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4){
            
            if(x1<x3 && x1<x4 && x2<x3 && x2<x4){
                return NULL;
            }if(x1>x3 && x1>x4 && x2>x3 && x2>x4){
                return NULL;
            }else if(y1<y3 && y1<y4 && y2<y3 && y2<y4){
                return NULL;
            }else if(y1>y3 && y1>y4 && y2>y3 && y2>y4){
                return NULL;
            }
            
            float uA = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
            
            float uB = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
            
            if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {
                float intersectionX = x1 + (uA * (x2-x1));
                float intersectionY = y1 + (uA * (y2-y1));
                
                return new Vector2D(intersectionX,intersectionY);
            }
            
            return NULL;
        }
    };
}

#endif /* Line_h */
