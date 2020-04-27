//
//  Quad.h
//  2D-Game-Engine
//
//  Created by ngchenghow on 14/12/2018.
//  Copyright © 2018 ngchenghow. All rights reserved.
//

#ifndef Quad_h
#define Quad_h
#include "Vector2D.h"
#define PI 3.14159265
#include <cmath>

namespace models{
    class Quad
    {
    public:
        Vector2D* p1;
        Vector2D* p2;
        Vector2D* p3;
        Vector2D* p4;
        
        int jumpy;
        int weak;
        int water;
        int wet=80;
        int sand;
        bool enabled=true;
        
        bool ctop=true;
        bool cbottom=true;
        bool cleft=true;
        bool cright=true;
        
        bool attach=false;
        
        void* player=NULL;
        
        ~Quad(){
            delete p1;
            delete p2;
            delete p3;
            delete p4;
        }
        
        Quad(Vector2D* p1,Vector2D* p2,Vector2D* p3,Vector2D* p4,int jumpy=0,int weak=0,int water=0,int wet=80,int sand=0):p1(p1),p2(p2),p3(p3),p4(p4),jumpy(jumpy),weak(weak),water(water),wet(wet),sand(sand){
        }
        
        float getBottomYAt(Vector2D* p){
            float m=(p4->y-p3->y)/(p4->x-p3->x);
            float b=p4->y-m*(p4->x);
            
            float ty=m*p->x+b;
            
            return ty;
        }
        
        float getLeftSlope(){
            float m=(p1->y-p4->y)/(p1->x-p4->x);
            
            if(m<-9999999){
                return 0;
            }
            
            return m;
        }
        
        float getRightSlope(){
            float m=(p1->y-p4->y)/(p1->x-p4->x);
            
//            if(m<-9999999){
//                return 0;
//            }
            
            return m;
        }
        
        float getRightXAt(Vector2D* p){
            //straight line vertical
            
            float m=(p2->y-p3->y)/(p2->x-p3->x);
            float b=p2->y-m*(p2->x);
            
            float tx=(p->y-b)/m;
            
            if(m>9999999){
                return p->x;
            }else if(m<-9999999){
                return p3->x;
            }
            
            return tx;
        }
        
        float getLeftXAt(Vector2D* p){
            
            float m=(p1->y-p4->y)/(p1->x-p4->x);
            float b=p1->y-m*(p1->x);
            
            float tx=(p->y-b)/m;
            
            if(m>9999999){
                return p->x;
            }else if(m<-9999999){
                return p1->x;
            }
            
            return tx;
        }
        
        double getTopAngle(){
            float m=(p2->y-p1->y)/(p2->x-p1->x);
            double angle=atan(m)*180/PI;
            return angle;
        }
        
        float getTopYAt(Vector2D* bp){
            //p1,p2
            float m=(p2->y-p1->y)/(p2->x-p1->x);
            float b=p1->y-m*(p1->x);
            
            float ty1=m*bp->x+b;
//            float ty2=m*bp2->x+b;
            float ty=ty1;
            return ty;
            
        }
        
        int getClosestLine(Vector2D* p){
            float d1=getDistance(p,p1,p2);
            float d2=getDistance(p,p2,p3);
            float d3=getDistance(p,p3,p4);
            float d4=getDistance(p,p4,p1);
            
            float lowest=d4;
            int result=4;
            
            if(d2<lowest){
                lowest=d2;
                result=2;
            }
            
            if(d3<lowest){
                lowest=d3;
                result=3;
            }
            
            if(d1<lowest){
                lowest=d4;
                result=1;
            }
            
//            printf("%d,%f\n",result,lowest);
            return result;
            
        }
        
        float get3PointDistance(Vector2D* target,Vector2D* p1,Vector2D* p2){
            float d1=disSquare(target,p1);
            float d2=disSquare(target,p2);
            
            return d1+d2;
        }
        
        float disSquare(Vector2D* p1,Vector2D* p2){
            float dx=abs(p1->x-p2->x);
            float dy=abs(p1->y-p2->y);
            return dx*dx+dy*dy;
        }
        
        float getDistance(Vector2D* target,Vector2D* p1,Vector2D* p2){
            float cx=target->x;
            float cy=target->y;
            
            float x1=p1->x;
            float y1=p1->y;
            float x2=p2->x;
            float y2=p2->y;
            
            float dot = ( ((cx-x1)*(x2-x1)) + ((cy-y1)*(y2-y1)) )/disSquare(p1,p2);
            
            float closestX = x1 + (dot * (x2-x1));
            float closestY = y1 + (dot * (y2-y1));
            
            return disSquare(target,new Vector2D(closestX,closestY));
        }
        
        float getHighestY(){
            
            float highest=p1->y;
            if(p2->y>highest){
                highest=p2->y;
            }
            if(p3->y>highest){
                highest=p2->y;
            }
            if(p4->y>highest){
                highest=p2->y;
            }
            return highest;
        }
        
        float getLowestY(){
            float lowest=p1->y;
            if(p2->y<lowest){
                lowest=p2->y;
            }
            if(p3->y<lowest){
                lowest=p2->y;
            }
            if(p4->y<lowest){
                lowest=p2->y;
            }
            return lowest;
        }
        
        float getDegreeAtEdge(int edge){
            
            Vector2D* p1;
            Vector2D* p2;
            
            if(edge==1){
                p1=this->p1;
                p2=this->p2;
            }else if(edge==2){
                p1=this->p2;
                p2=this->p3;
            }else if(edge==3){
                p1=this->p3;
                p2=this->p4;
            }else if(edge==4){
                p1=this->p4;
                p2=this->p1;
            }else{
                return 0.0f;
            }
            
            float dx=p2->x-p1->x;
            float dy=p2->y-p1->y;
            
            return atan(dy/dx);
        }
        
    };
}

#endif /* Quad_h */
