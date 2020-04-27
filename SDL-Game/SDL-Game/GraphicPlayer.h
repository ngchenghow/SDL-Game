//
//  Player.h
//  2D-Game-Engine
//
//  Created by ngchenghow on 14/12/2018.
//  Copyright © 2018 ngchenghow. All rights reserved.
//

#ifndef GraphicPlayer_h
#define GraphicPlayer_h

#include "Vector2D.h"

class GraphicPlayer:public Graphic
{
public:
    
    float lastx=0;
    float lasty=0;
    
    float vx=0;
    float vy=0;
    
    float ax=0;
    float ay=0;
    
    float vLeftControl=0;
    float vRightControl=0;
    float upControly=0;
    float downControly=0;
    
    float vgravity=0;
    float vvertical=0;
    float vhorizontal=0;
    
    bool jumping=false;
    bool jumpOnce_able=true;
    bool runningLeft=false;
    bool runningRight=false;
    bool runningDown=false;
    bool runningUp=false;
    
    Uint32 runTime=0;
    
    Vector2D* bottomPoint;
    Vector2D* bottomPoint2;
    
    Vector2D* leftPoint;
    Vector2D* leftPoint2;
    
    Vector2D* rightPoint;
    Vector2D* rightPoint2;
    
    Vector2D* topPoint;
    
    Quad* bottomColl;
    Quad* bottomColl2;

    Quad* leftColl;
    Quad* leftColl2;
    
    Quad* rightColl;
    Quad* rightColl2;
    
    Quad* topColl;
    
    const float GRAVITY=0.8f;
    int friction=80;
    bool atEdge=false;
    
    float leftSpeed=0;
    float rightSpeed=0;
    float downSpeed=0;
    float upSpeed=0;

    enum ControlState{land,water};
    ControlState controlState;
    float w=50;
    float h=50;
    
    std::vector<Line*> collLines;
    
    GraphicPlayer(std::string textureID):Graphic(textureID){
        w=50;
        h=50;
        
        bottomPoint=new Vector2D(w/2,h+1);
        bottomPoint2=new Vector2D(w/2,h+1);
        
        leftPoint=new Vector2D(0,h*0.1);
        leftPoint2=new Vector2D(0,h*0.3);
        
        rightPoint=new Vector2D(w,0);
        rightPoint2=new Vector2D(w,h*0.3);
        
        topPoint=new Vector2D(w/2,0);
        
        bottomColl=NULL;
        leftColl=NULL;
        rightColl=NULL;
        topColl=NULL;
        
        controlState=land;
    }
    
    Quad* getRect(){
        Vector2D* p1=parentPoint(new Vector2D(0,0));
        Vector2D* p2=parentPoint(new Vector2D(w,0));
        Vector2D* p3=parentPoint(new Vector2D(w,h));
        Vector2D* p4=parentPoint(new Vector2D(0,h));
        
        Quad* rect=new Quad(p1,p2,p3,p4);
        return rect;
    }
    
    void resetCollisionLine(){
        collLines.clear();
    }
    
    void addCollisionLine(Line* line){
        collLines.push_back(line);
    }
    
    Vector2D* parentPoint(Vector2D* p){
        return new Vector2D(this->getX()+p->x,this->getY()+p->y);
    }
    
    Vector2D* getBottomPoint(){
        return parentPoint(bottomPoint);
    }
    
    Vector2D* getBottomPoint2(){
        return parentPoint(bottomPoint2);
    }
    
    Vector2D* getLeftPoint(){
        return parentPoint(leftPoint);
    }
    
    Vector2D* getLeftPoint2(){
        return parentPoint(leftPoint2);
    }
    
    Vector2D* getRightPoint(){
        return parentPoint(rightPoint);
    }
    
    Vector2D* getRightPoint2(){
        return parentPoint(rightPoint2);
    }
    
    Vector2D* getTopPoint(){
        return parentPoint(topPoint);
    }
    
    void setBottomCollision(Quad* quad){
        bottomColl=quad;
    }
    
    void setBottom2Collision(Quad* quad){
        bottomColl2=quad;
    }
    
    void setLeftCollision(Quad* quad){
        leftColl=quad;
    }
    
    void setLeft2Collision(Quad* quad){
        leftColl2=quad;
    }
    
    void setRightCollision(Quad* quad){
        rightColl=quad;
    }
    
    void setRight2Collision(Quad* quad){
        rightColl2=quad;
    }
    
    void setTopCollision(Quad* quad){
        topColl=quad;
    }
    
    void down(){
        runningDown=true;
    }
    
    void left(){
        runningLeft=true;
        
    }
    
    void right(){
        runningRight=true;
    }
    
    void downUp(){
        runningDown=false;
    }
    
    void leftUp(){
        runningLeft=false;
    }
    
    void rightUp(){
        runningRight=false;
    }
    
    void up(){
        runningUp=true;
    }
    
    void upUp(){
        runningUp=false;
    }
    
    void jump(){
        
        if(atEdge && jumpOnce_able){
            vhorizontal-=30;
            jumping=true;
            jumpOnce_able=false;
            
            if(leftColl || leftColl2){
                Quad* q=getLeftColl();
                if(q->getLeftSlope()<0){
                    vvertical+=25;
                }else{
                    vvertical+=10;
                }
            }
            
            if(rightColl || rightColl2){
                Quad* q=getRightColl();
//                printf("%f\n",q->getRightSlope());
                if(q->getRightSlope()>0){
                    vvertical-=25;
                }else{
                    vvertical-=10;
                }
            }
        }
    }
    
    Quad* getLeftColl(){
        if(leftColl){
            return leftColl;
        }else if(leftColl2){
            return leftColl2;
        }
        return NULL;
    }
    
    Quad* getRightColl(){
        if(rightColl){
            return rightColl;
        }else if(rightColl2){
            return rightColl2;
        }
        return NULL;
    }
    
    Quad* getBottomColl(){
        if(bottomColl){
            return bottomColl;
        }else if(bottomColl2){
            return bottomColl2;
        }
        return NULL;
    }
    
    Quad* getTopColl(){
        if(topColl){
            return topColl;
        }
        return NULL;
    }
    
    Quad* getTargetColl(){
        if(bottomColl){
            return bottomColl;
        }else if(bottomColl2){
            return bottomColl2;
        }else if(topColl){
            return topColl;
        }else if(leftColl){
            return leftColl;
        }else if(leftColl2){
            return leftColl2;
        }else if(rightColl){
            return rightColl;
        }else if(rightColl2){
            return rightColl2;
        }
        return NULL;
    }
    
    Quad* getInQuad(){
        if(bottomColl){
            return bottomColl;
        }else if(topColl){
            return topColl;
        }else if(leftColl){
            return leftColl;
        }else if(rightColl){
            return rightColl;
        }
        return NULL;
    }
    
    void jumpyAt(float value){
        vhorizontal=-value;
        jumping=true;
        jumpOnce_able=false;
    }
    
    void jumpUp(){
        jumpOnce_able=true;
    }
    
    void update() override{
        Graphic::update();
        
        switch(controlState){
            case land:
                landUpdate();
                break;
            case water:
                waterUpdate();
                break;
        }
    }
    
    //    float lastTy=0.0f;
    
    void reactUpdate(){
        
        switch(controlState){
            case land:
                landReact();
                break;
            case water:
                waterReact();
                break;
                
        }
    }
    
    void landUpdate(){
        //gravity
        
        atEdge=false;
        vgravity=GRAVITY;
        upControly=0;
        downControly=0;
        
        if(jumping && vhorizontal>=0){
            jumping=false;
        }
        
        //wind up effect
        for(std::vector<Line*>::iterator it = collLines.begin(); it != collLines.end(); ++it) {
            Line* line=*it;
            if(line->wind){
                vhorizontal-=1;
            }
        }
        
        if(runningLeft){
            leftSpeed+=100-friction;
            
            vLeftControl=-leftSpeed*0.01;
            vLeftControl=fmax(-2,vLeftControl);
            vRightControl=0;
            
            if(bottomColl||bottomColl2){
                vhorizontal+=10;
            }
            
        }else{
            vLeftControl=0;
            leftSpeed=0;
        }
        
        if(runningRight){
            rightSpeed+=100-friction;
            
            vRightControl=rightSpeed*0.01;
            vRightControl=fmin(2,vRightControl);
            vLeftControl=0;
            
            if(bottomColl||bottomColl2){
                vhorizontal+=10;
            }
            
            //            vRightControl=fmin(3,vRightControl);
        }else{
            vRightControl=0;
            rightSpeed=0;
        }
        
        if(runningDown){
            if(bottomColl && bottomColl->weak==1){
                downSpeed+=0.1;
                downControly=downSpeed;
                upControly=0;
            }
        }else{
            downControly=0;
        }
        
        vvertical+=vLeftControl+vRightControl;
        vhorizontal+=vgravity+upControly+downControly;
        
        //apply friction
        if(!topColl && !bottomColl && !leftColl && !rightColl){
            vvertical*=0.89;
        }else{
            vvertical*=(float)friction/100;
        }
        
        //set values
        float _vx=vvertical;
        float _vy=vhorizontal;
        
        setValue(_vx,_vy);
    }
   
    
    void landReact(){
        float ty=0.0f;
        float lx=0.0f;
        float rx=0.0f;
        
        this->x=lastx;
        this->y=lasty;
        
        if(this->topColl!=NULL && topColl->weak!=1 && bottomColl==NULL && bottomColl2==NULL){
            
            ty=this->topColl->getBottomYAt(this->getTopPoint());
            if(vhorizontal<0){
                vhorizontal=0;
            }
            this->y=ty;
            this->leftColl=NULL;
            this->rightColl=NULL;
            
            
        }else if((bottomColl && bottomColl2) && topColl==NULL){
            
            Quad* targetColl;
            
            targetColl=getBottomColl();
            
            if(targetColl->jumpy!=0){
                jumpyAt(targetColl->jumpy);
            }else if(targetColl->water!=0){
                controlState=water;
                waterUpdate();
                return;
            }else if(friction!=targetColl->wet){
                friction=targetColl->wet;
            }
            
            
            ty=targetColl->getTopYAt(this->getBottomPoint());
            
            
            int tline=targetColl->getClosestLine(this->getBottomPoint());
            
            if(downControly>0 && targetColl->weak==1){
                vhorizontal+=5;
            }else if(tline==1){
                atEdge=true;
                if(vhorizontal>0){
                    vhorizontal=0;
                }
                vgravity=0;
                upControly=0;
                downControly=0;
                downSpeed=0;
                this->y=ty-this->getHeight();
            }
            
            //sand quad
            if(targetColl->sand==1){
                
            }
            
        }
        
        if((this->leftColl || this->leftColl2)){
            
            Quad* targetColl;
            
            if(leftColl){
                targetColl=leftColl;
            }else{
                targetColl=leftColl2;
            }
            
            if(targetColl->weak!=1){
            
                lx=targetColl->getRightXAt(this->getLeftPoint());
                int tline=targetColl->getClosestLine(this->getBottomPoint());
                
                if(tline==2){
                    this->x=lx;
                    if(vvertical<0){
                        vvertical=0;
                        vhorizontal=0;
                    }
                    atEdge=true;
                }
            }
            
            
        }else if((this->rightColl || this->rightColl2)){
            Quad* targetColl;
            targetColl=getRightColl();
            
            if(targetColl->weak!=1){
                rx=targetColl->getLeftXAt(this->getRightPoint());
                int tline=targetColl->getClosestLine(this->getBottomPoint());
                if(tline==4){
                    this->x=rx-this->getWidth();
                    if(vvertical>0){
                        vvertical=0;
                        vhorizontal=0;
                    }
                    atEdge=true;
                }
            }
        }
        
        
        
        //set values
        float _vx=vvertical;
        float _vy=vhorizontal;
        
        setValue(_vx,_vy);
        
    }
    
    void waterUpdate(){
        
        Quad* targetColl=getInQuad();
        if(targetColl==NULL){
            controlState=land;
            return;
        }
        
        float topY=targetColl->getHighestY();
        
        upControly=0;
        downControly=0;
        
        if(jumping){
            vhorizontal+=0.1;
            if(vhorizontal>=0){
                jumping=false;
            }
        }
        
        if(runningLeft){
            leftSpeed+=0.03;
            vLeftControl=-leftSpeed*1;
            vLeftControl=fmax(-1,vLeftControl);
            vRightControl=0;
        }else{
            vLeftControl=0;
            leftSpeed=0;
        }
        
        if(runningRight){
            rightSpeed+=0.03;
            vRightControl=rightSpeed*1;
            vRightControl=fmin(1,vRightControl);
            vLeftControl=0;
        }else{
            vRightControl=0;
            rightSpeed=0;
        }
        
        if(runningDown){
            downSpeed+=0.03;
            downControly=downSpeed*1;
            downControly=fmin(1,downControly);
            upControly=0;
        }else{
            downControly=0;
        }
        
        if(runningUp){
            upSpeed+=0.03;
            upControly=-upSpeed*1;
            upControly=fmax(-1,upControly);
            downControly=0;
        }else{
            upControly=0;
        }
        
        vvertical+=vLeftControl+vRightControl;
        vhorizontal+=vgravity+upControly+downControly;
        
        float dy=this->y-topY;
        if(!atEdge){
            if(topColl && topColl->water==1){
                vgravity=0;
                vvertical*=0.5;
                vhorizontal*=0.5;
            }else if(!jumping){
                if(dy<0){
                    vgravity=0.9;
                    vvertical*=0.7;
                    vhorizontal*=0.7;
                }else if(dy<20){
                    vvertical*=0.7;
                    vhorizontal*=0.7;
                }else if(dy<30){
                    vgravity=3/dy;
                    vvertical*=0.6;
                    vhorizontal*=0.6;
                }else if(dy<80){
                    vgravity=0.01;
                    vvertical*=0.5;
                    vhorizontal*=0.5;
                }else{
                    vgravity=0;
                    vvertical*=0.5;
                    vhorizontal*=0.5;
                }
            }
        }else{
            vgravity=0;
            vvertical*=0.5;
            vhorizontal*=0.5;
        }
        
        //set values
        float _vx=vvertical;
        float _vy=vhorizontal;
        
        setValue(_vx,_vy);
    }
    
    
    
    void waterReact(){
        float lx=0.0f;
        float rx=0.0f;
        
        this->x=lastx;
        this->y=lasty;
        Quad* targetColl=getInQuad();
        if(targetColl==NULL){
            controlState=land;
            return;
        }
        
        float topY=targetColl->getHighestY();
        
        float dy=this->y-topY;
        
        if(topColl==NULL && !jumping){
            if(dy<-10){
                upControly=0;
                if(vhorizontal<0){
                    vhorizontal=0;
                    vgravity=0;
                }
            }
        }else if(topColl==NULL && bottomColl==NULL && jumping){
            controlState=land;
            return;
        }
    
        if(leftColl && leftColl->water==0){
           
            lx=leftColl->getRightXAt(this->getLeftPoint());
            
            this->x=lx;
            if(vvertical<0){
                atEdge=true;
                vvertical=0;
                vhorizontal*=1.1;
            }
            
            vLeftControl=0;
        }
        
        if(rightColl && rightColl->water==0){
            
            rx=rightColl->getLeftXAt(this->getRightPoint());
            //            int tline=leftColl->getClosestLine(this->getLeftPoint());
            
            this->x=rx;
            if(vvertical>0){
                atEdge=true;
                vvertical=0;
                vhorizontal*=0.3;
            }
            vRightControl=0;
        }
        
        if((getLeftColl() && getLeftColl()->water==0) || (getRightColl() && getRightColl()->water==0)){
            atEdge=true;
        }else{
            atEdge=false;
        }
        
        vvertical+=vLeftControl+vRightControl;
        vhorizontal+=vgravity+upControly+downControly;
        
        //set values
        float _vx=vvertical;
        float _vy=vhorizontal;
        
        setValue(_vx,_vy);
    }
    
    
    void setValue(float _vx,float _vy){
        this->vx=_vx;
        this->vy=_vy;
        
        lastx=this->x;
        lasty=this->y;
        
        this->x+=vx;
        this->y+=vy;
    }
    
};

#endif /* Player_h */
