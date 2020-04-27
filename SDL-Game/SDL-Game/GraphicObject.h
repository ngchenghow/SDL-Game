//
//  Player.h
//  2D-Game-Engine
//
//  Created by ngchenghow on 14/12/2018.
//  Copyright © 2018 ngchenghow. All rights reserved.
//

#ifndef GraphicObject_h
#define GraphicObject_h

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>

#include "GraphicObject.h"
#include "Vector2D.h"
#include "Quad.h"
#include "Line.h"
#include "Rectangle.h"
#include "Game.h"
#include "GameStateMachine.h"
#include "Spread.h"
#include "MoveLogic.h"

using namespace models;

class GraphicObject:public Graphic
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
    float vhorizontal=0;
    float vvertical=0;
    
    
    bool jumping=false;
    bool attacking=false;
    bool shootingA=false;
    
    bool jumpOnce_able=true;
    bool attackOnce_able=true;
    
    bool runningLeft=false;
    bool runningRight=false;
    bool runningDown=false;
    bool runningUp=false;
    bool sprinting=false;
    bool actioning=false;
    
    Uint32 runTime=0;
    
    Vector2D* bottomPoint;
    Vector2D* bottomPoint2;
    Vector2D* bottomPoint3;
    
    Line* rightLine;
    Line* leftLine;
    Line* bottomLine;
    Line* topLine;
    
    Line* rightLine0;
    Line* rightLine1;
    Line* rightFarLine;
    
    Line* rightLine3;
    Line* rightLine4;
    
    Line* rightStraightLine;
    Line* rightStraightLine2;
    
    Line* leftLine0;
    Line* leftLine1;
    Line* leftFarLine;
    
    Line* leftLine3;
    Line* leftLine4;
    
    Line* leftStraightLine;
    Line* leftStraightLine2;
    
    Line* bottomLine0;
    Line* bottomLine1;
    
    Line* bottomLine3;
    Line* bottomLine4;
    
    Line* topLine0;
    Line* topLine1;
    
    Line* shootingStart;
    
    Vector2D* leftPoint;
    Vector2D* leftPoint2;
    Vector2D* leftPoint3;
    
    Vector2D* shootingLeft1;
    Vector2D* shootingLeft2;
    Vector2D* shootingRight1;
    Vector2D* shootingRight2;
    
    Vector2D* rightPoint;
    Vector2D* rightPoint2;
    Vector2D* rightPoint3;
    
    Vector2D* topPoint;
    Vector2D* topPoint2;
    Vector2D* topPoint3;
    
    
    Vector2D* shootingTop1;
    Vector2D* shootingTop2;
    
    Quad* bottomColl;
    Quad* bottomColl2;
    Quad* bottomColl3;
    
    Quad* leftColl=NULL;
    Quad* leftColl2=NULL;
    Quad* leftColl3=NULL;
    
    Quad* rightColl;
    Quad* rightColl2;
    Quad* rightColl3;
    
    Quad* topColl;
    Quad* topColl2;
    Quad* topColl3;
    
    Quad* collRect;
    
    float GRAVITY=1.0f;
    float AIRFICTION=0.92f;
    float JUMPUPSTRENGTH=10.0f;
    float RUNSTRENGTH=7.0f;
    float RUNNINGDOWN=10.0f;
    float SPRINTBOTTOM=5.0f;
    float SPRINT=20.0f;
    float OUTWATER=5.0f;
    
    int friction=90;
    bool atEdge=false;
    int lastEdge=-1;
    int lastEdgeCount=0;
    
    int facing=1;
    
    bool jumpPress=false;
    
    float leftSpeed=0;
    float rightSpeed=0;
    float downSpeed=0;
    float upSpeed=0;
    
    enum ControlState{land,water};
    ControlState controlState;
    
    bool stuckfootLeft=false;
    bool stuckfootRight=false;
    
    float pushSpeed=1;
    bool isPlayer=false;
    bool pushing=false;
    
    std::vector<Line*> collLines;
    Vector2D* attackBottomPoint;
    Vector2D* attackLeftPoint;
    Vector2D* attackTopTopPoint;
    Vector2D* attackTopBottomPoint;
    Vector2D* attackBottomTopPoint;
    Vector2D* attackBottomBottomPoint;
    
    Rectangle* attackBox;
    Rectangle* hurtBox;
    Rectangle* attack0;
    Rectangle* attack1;
    Rectangle* attack2;
    Rectangle* attack3;
    
    int attackCountDown=0;
    float health=100.0f;
    float damageValue=1.0f;
    int shootingWait=0;
    
    Line* ladderLine=NULL;
    
    int waitFrames=0;
    
    MoveLogic* moveLogic=NULL;
    bool isPlatform=false;
    
    bool clifing=false;
    int atClifingCountDown=0;
    
    GraphicObject(std::string id,std::string textureID,int w,int h):Graphic(textureID){
        this->instanceID=id;
        
        setSize(w,h);
        
        shootingLeft1=new Vector2D(w*0.5,h*0.3);
        shootingLeft2=new Vector2D(-30,h*0.3);
        
        shootingRight1=new Vector2D(w*0.5,h*0.3);
        shootingRight2=new Vector2D(w+30,h*0.3);
        
        shootingTop1=new Vector2D(w*0.5,30);
        shootingTop2=new Vector2D(w*0.5,-30);
        
        bottomPoint=new Vector2D(3,h+1);
        bottomPoint2=new Vector2D(w/2,h);
        bottomPoint3=new Vector2D(w-3,h+1);
        
        leftPoint=new Vector2D(0,0);
        leftPoint2=new Vector2D(0,h*0.5);
        leftPoint3=new Vector2D(0,h-1);
        
        rightPoint=new Vector2D(w,0);
        rightPoint2=new Vector2D(w,h*0.5);
        rightPoint3=new Vector2D(w,h-1);
        
        topPoint=new Vector2D(0,0);
        topPoint2=new Vector2D(w/2,0);
        topPoint3=new Vector2D(w,0);
        
        attackBottomPoint=new Vector2D(w+getHeight(),h);
        attackLeftPoint=new Vector2D(-getHeight(),0);
        attackTopTopPoint=new Vector2D(-40,-getHeight());
        attackTopBottomPoint=new Vector2D(getWidth()+40,0);
        attackBottomTopPoint=new Vector2D(-40,getHeight());
        attackBottomBottomPoint=new Vector2D(getWidth()+40,getHeight()*2);
        
        Vector2D* p1=parentPoint(topPoint);
        Vector2D* p2=parentPoint(rightPoint);
        Vector2D* p3=parentPoint(rightPoint3);
        Vector2D* p4=parentPoint(leftPoint3);
        
        collRect=new Quad(p1,p2,p3,p4);
        collRect->attach=true;
//        collRect->playerOwner=this->getInstanceID();
        collRect->player=this;
        
        rightLine0=new Line(parentPoint(leftPoint),parentPoint(rightPoint),1,0,0);
        setupLine(rightLine0,4,this->collRect);
        
        rightLine=new Line(parentPoint(leftPoint2),parentPoint(rightPoint2),1,0,0);
        setupLine(rightLine,4,this->collRect);
        
        rightLine1=new Line(parentPoint(leftPoint3),parentPoint(rightPoint3),1,0,0);
        setupLine(rightLine1,4,this->collRect);
        
        rightFarLine=new Line(parentPoint(leftPoint2),parentPoint(rightPoint2),1,0,0);
        setupLine(rightFarLine,4,this->collRect);
        
        rightLine3=new Line(parentPoint(leftPoint),parentPoint(rightPoint),1,0,0);
        setupLine(rightLine3,4,this->collRect);
        
        rightLine4=new Line(parentPoint(leftPoint3),parentPoint(rightPoint3),1,0,0);
        setupLine(rightLine4,4,this->collRect);
        
        rightStraightLine=new Line(parentPoint(topPoint3),parentPoint(bottomPoint3),1,0,0);
        setupLine(rightStraightLine,0,this->collRect);
        
        rightStraightLine2=new Line(parentPoint(topPoint3),parentPoint(bottomPoint3),1,0,0);
        setupLine(rightStraightLine2,0,this->collRect);
        
        leftLine0=new Line(parentPoint(rightPoint),parentPoint(leftPoint),1,0,0);
        setupLine(leftLine0,2,this->collRect);
        
        leftLine=new Line(parentPoint(rightPoint2),parentPoint(leftPoint2),1,0,0);
        setupLine(leftLine,2,this->collRect);
        
        leftLine1=new Line(parentPoint(rightPoint3),parentPoint(leftPoint3),1,0,0);
        setupLine(leftLine1,2,this->collRect);
        
        leftLine3=new Line(parentPoint(rightPoint),parentPoint(leftPoint),1,0,0);
        setupLine(leftLine3,2,this->collRect);
        
        leftLine4=new Line(parentPoint(rightPoint3),parentPoint(leftPoint3),1,0,0);
        setupLine(leftLine4,2,this->collRect);
        
        leftFarLine=new Line(parentPoint(rightPoint2),parentPoint(leftPoint2),1,0,0);
        setupLine(leftFarLine,2,this->collRect);
        
        leftStraightLine=new Line(parentPoint(topPoint),parentPoint(bottomPoint),1,0,0);
        setupLine(leftStraightLine,0,this->collRect);
        
        
        leftStraightLine2=new Line(parentPoint(topPoint),parentPoint(bottomPoint),1,0,0);
        setupLine(leftStraightLine2,0,this->collRect);
        
        bottomLine0=new Line(parentPoint(topPoint),parentPoint(bottomPoint),1,0,0);
        setupLine(bottomLine0,1,this->collRect);
        
        bottomLine=new Line(parentPoint(topPoint2),parentPoint(bottomPoint2),1,0,0);
        setupLine(bottomLine,1,this->collRect);
        
        bottomLine1=new Line(parentPoint(topPoint3),parentPoint(bottomPoint3),1,0,0);
        setupLine(bottomLine1,1,this->collRect);
        
        bottomLine3=new Line(parentPoint(topPoint),parentPoint(bottomPoint),1,0,0);
        setupLine(bottomLine3,1,this->collRect);
        
        bottomLine4=new Line(parentPoint(topPoint3),parentPoint(bottomPoint3),1,0,0);
        setupLine(bottomLine4,1,this->collRect);
        
        topLine0=new Line(parentPoint(bottomPoint),parentPoint(topPoint),1,0,0);
        setupLine(topLine0,3,this->collRect);
        
        topLine=new Line(parentPoint(bottomPoint2),parentPoint(topPoint2),1,0,0);
        setupLine(topLine,3,this->collRect);
        
        topLine1=new Line(parentPoint(bottomPoint3),parentPoint(topPoint3),1,0,0);
        setupLine(topLine1,3,this->collRect);
        
        bottomColl=NULL;
        leftColl=NULL;
        rightColl=NULL;
        topColl=NULL;
        topColl2=NULL;
        
        controlState=land;
        
        attack1=new Rectangle(parentPoint(rightPoint),parentPoint(attackBottomPoint));
        attack0=new Rectangle(parentPoint(attackLeftPoint),parentPoint(bottomPoint));
        attack2=new Rectangle(parentPoint(attackTopTopPoint),parentPoint(attackTopBottomPoint));
        attack3=new Rectangle(parentPoint(attackBottomTopPoint),parentPoint(attackBottomBottomPoint));
        
        hurtBox=new Rectangle(parentPoint(leftPoint),parentPoint(bottomPoint3));
        
    }
    
    ~GraphicObject(){
        delete bottomPoint;
        delete bottomPoint2;
        delete bottomPoint3;
        
        delete leftPoint;
        delete leftPoint2;
        delete leftPoint3;
        
        delete rightPoint;
        delete rightPoint2;
        delete rightPoint3;
        
        delete topPoint;
        delete topPoint2;
        delete topPoint3;
        
        delete attackBottomPoint;
        delete attackLeftPoint;
        delete attackTopTopPoint;
        delete attackTopBottomPoint;
        delete attackBottomTopPoint;
        delete attackBottomBottomPoint;
        
        delete collRect;
        delete rightLine0;
        delete rightLine;
        delete rightFarLine;
        delete rightLine3;
        delete rightLine4;
        
        delete leftLine0;
        delete leftLine;
        delete leftLine1;
        delete leftFarLine;
        delete leftLine3;
        delete leftLine4;
        
        delete bottomLine0;
        delete bottomLine;
        delete bottomLine1;
        delete bottomLine3;
        delete bottomLine4;
        
        delete topLine0;
        delete topLine;
        delete topLine1;
        
        delete attack0;
        delete attack1;
        delete attack2;
        delete attack3;
        
        delete hurtBox;
        
        delete ladderLine;
        delete moveLogic;
    }
    
    void setAsPlatform(){
        this->isPlatform=true;
        this->GRAVITY=0;
    }
    
    void setSize(int w,int h){
        this->width=w;
        this->height=h;
        
        shootingLeft1=new Vector2D(w*0.5,h*0.3);
        shootingLeft2=new Vector2D(-30,h*0.3);
        
        shootingRight1=new Vector2D(w*0.5,h*0.3);
        shootingRight2=new Vector2D(w+30,h*0.3);
        
        shootingTop1=new Vector2D(w*0.5,30);
        shootingTop2=new Vector2D(w*0.5,-30);
        
        bottomPoint=new Vector2D(0,h+1);
        bottomPoint2=new Vector2D(w/2,h);
        bottomPoint3=new Vector2D(w,h+1);
        
        leftPoint=new Vector2D(0,0);
        leftPoint2=new Vector2D(0,h*0.5);
        leftPoint3=new Vector2D(0,h-1);
        
        rightPoint=new Vector2D(w,0);
        rightPoint2=new Vector2D(w,h*0.5);
        rightPoint3=new Vector2D(w,h-1);
        
        topPoint=new Vector2D(0,0);
        topPoint2=new Vector2D(w/2,0);
        topPoint3=new Vector2D(w,0);
    }
    
    void setupLine(Line* line,int targetEdge,Quad* quad){
        line->attach=true;
        line->targetEdge=targetEdge;
        line->playerOwner=this;
    }
    
    Quad* getQuad(){
        return collRect;
    }
    
    Rectangle* getRect(){
        return hurtBox;
    }
    
    void changeAttackBox(Rectangle* rect){
        attackBox=rect;
    }
    
    void clearAttackBox(){
        attackBox=NULL;
    }
    
    Rectangle* getAttackBox(){
        return attackBox;
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
    
    float parentPointX(Vector2D* p){
        return this->getX()+p->x;
    }
    
    float parentPointY(Vector2D* p){
        return this->getY()+p->y;
    }
    
    Vector2D* getBottomPoint(){
        return parentPoint(bottomPoint);
    }
    
    Vector2D* getBottomPoint2(){
        return parentPoint(bottomPoint2);
    }
    
    Vector2D* getBottomPoint3(){
        return parentPoint(bottomPoint3);
    }
    
    Vector2D* getLeftPoint(){
        return parentPoint(leftPoint);
    }
    
    Vector2D* getLeftPoint2(){
        return parentPoint(leftPoint2);
    }
    
    Vector2D* getLeftPoint3(){
        return parentPoint(leftPoint3);
    }
    
    Vector2D* getRightPoint(){
        return parentPoint(rightPoint);
    }
    
    Vector2D* getRightPoint2(){
        return parentPoint(rightPoint2);
    }
    
    Vector2D* getRightPoint3(){
        return parentPoint(rightPoint3);
    }
    
    Vector2D* getTopPoint(){
        return parentPoint(topPoint);
    }
    
    Vector2D* getTopPoint2(){
        return parentPoint(topPoint2);
    }
    
    Vector2D* getTopPoint3(){
        return parentPoint(topPoint3);
    }
    
    void setBottomCollision(Quad* quad){
        bottomColl=quad;
    }
    
    void setBottom2Collision(Quad* quad){
        bottomColl2=quad;
    }
    
    void setBottom3Collision(Quad* quad){
        bottomColl3=quad;
    }
    
    void setLeftCollision(Quad* quad){
        leftColl=quad;
    }
    
    void setLeft2Collision(Quad* quad){
        leftColl2=quad;
    }
    
    void setLeft3Collision(Quad* quad){
        leftColl3=quad;
    }
    
    void setRightCollision(Quad* quad){
        rightColl=quad;
    }
    
    void setRight2Collision(Quad* quad){
        rightColl2=quad;
    }
    
    void setRight3Collision(Quad* quad){
        rightColl3=quad;
    }
    
    void setTopCollision(Quad* quad){
        topColl=quad;
    }
    
    void setTop2Collision(Quad* quad){
        topColl2=quad;
    }
    
    void setTop3Collision(Quad* quad){
        topColl3=quad;
    }
    
    void down(){
        runningDown=true;
        facing=3;
        if(attacking){
            attack();
        }
    }
    
    void left(){
        runningLeft=true;
        facing=0;
        flip=1;
    }
    
    void right(){
        runningRight=true;
        facing=1;
        flip=0;
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
        facing=2;
        if(attacking){
            attack();
        }
    }
    
    void upUp(){
        runningUp=false;
    }
    
    void sprint(){
        if(controlState!=land || sprinting)return;
        
        sprinting=true;
        if(facing==0){
            vhorizontal-=SPRINT;
        }else if(facing==1){
            vhorizontal+=SPRINT;
        }else if(facing==2){
            vvertical-=SPRINT;
        }else if(facing==3){
            vvertical+=SPRINT;
        }
        
    }
    
    void sprintUp(){
        sprinting=false;
    }
    
    void action(){
        actioning=true;
    }
    
    void actionUp(){
        actioning=false;
    }
    
    void shootA(){
        shootingA=true;
    }
    
    void shootAUp(){
        shootingA=false;
    }
    
    bool isLeftColl(){
        return leftLine->stopAt || leftLine1->stopAt || leftLine0->stopAt;
    }
    
    bool isRightColl(){
        return rightLine->stopAt || rightLine1->stopAt || rightLine0->stopAt;
    }
    
    bool isBottomColl(){
        return bottomLine->stopAt || bottomLine1->stopAt || bottomLine0->stopAt;
    }
    
    void attack(){
        if(attackOnce_able){
            attacking=true;
            attackOnce_able=false;
            
            if(facing==2){
                changeAttackBox(attack2);
            }else if(facing==3){
                changeAttackBox(attack3);
            }else if(facing==0){
                changeAttackBox(attack0);
            }else if(facing==1){
                changeAttackBox(attack1);
            }
            
            attackCountDown=30;
        }
    }
    
    void damageTo(GraphicObject* otherPlayer,float damageValue,int damageType){
        otherPlayer->damageBy(this,damageValue,damageType);
    }
    
    void damageBy(GraphicObject* otherPlayer,float damageValue,int damageType){
        int f=otherPlayer->facing;
        if(f==0){
            this->vhorizontal-=0.2;
        }else{
            this->vhorizontal+=0.2;
        }
        this->health=fmax(0,this->health-damageValue);
    }
    
    void attackUp(){
        attackOnce_able=true;
    }
    
    int jumpBuffer=0;
    void jump(){
        
        if((atEdge || atClifingCountDown>0) && jumpOnce_able){
            jumpPress=true;
            jumping=true;
            
            vvertical-=JUMPUPSTRENGTH;
            jumpOnce_able=false;
            jumpBuffer=0;
            
            if(!isBottomColl() && (lastEdgeCount>0 && lastEdge==0)){
                this->x+=5;
                vhorizontal+=JUMPUPSTRENGTH*1.5;
                vvertical-=JUMPUPSTRENGTH*0.3;
            }
            
            if(!isBottomColl() && (lastEdgeCount>0 && lastEdge==1)){
                this->x-=5;
                vhorizontal-=JUMPUPSTRENGTH*1.5;
                vvertical-=JUMPUPSTRENGTH*0.3;
            }
        }
    }
    
    Quad* getLeftColl(bool get3=false){
        if(leftColl){
            return leftColl;
        }else if(leftColl2){
            return leftColl2;
        }else if(leftColl3 && get3){
            return leftColl3;
        }
        return NULL;
    }
    
    Quad* getRightColl(bool get3=false){
        if(rightColl){
            return rightColl;
        }else if(rightColl2){
            return rightColl2;
        }else if(rightColl3 && get3){
            return rightColl3;
        }
        return NULL;
    }
    
    Quad* getBottomColl(){
        if(bottomColl2){
            return bottomColl2;
        }else if(bottomColl){
            return bottomColl;
        }else if(bottomColl3){
            return bottomColl3;
        }
        return NULL;
    }
    
    Quad* getTopColl(){
        if(topColl){
            return topColl;
        }else if(topColl2){
            return topColl2;
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
        }else if(topColl2){
            return topColl2;
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
        vvertical=-value;
        jumping=true;
        jumpOnce_able=false;
    }
    
    void jumpUp(){
        jumpOnce_able=true;
        jumpPress=false;
    }
    
    int offsetUpdate=0;
    
    virtual void update() override{
        if(waitFrames>0){
            return;
        }
        
        if(moveLogic){
            moveLogic->move(this);
        }
        
        if(offsetUpdate%10==0){
            Graphic::updateFrame();
            offsetUpdate=0;
        }
        offsetUpdate++;
        
        Graphic::updateChildren();
        
        lastEdgeCount--;
        switch(controlState){
            case land:
                landUpdate();
                shootingUpdate();
                break;
            case water:
                waterUpdate();
                break;
        }
        
    }
    
    virtual void draw(SDL_Renderer* renderer) override{
        
        //set state id
        int finalState=this->stateID;
        if(vvertical==0){
//            finalState=0;
        }
        if(runningLeft || runningRight){
//            finalState=2;
        }
        if(jumping){
//            finalState=1;
        }
        if(attacking){
//            finalState=13;
        }
        this->setStateID(finalState);
        
        //draw it
        Graphic::draw(renderer);
        
    }
    
    Line* passOutLine=NULL;
    void shootingUpdate(){
        
        if(shootingA && !passOutLine && shootingWait==0){
            if(facing==0){
                passOutLine=new Line(parentPoint(shootingLeft1),parentPoint(shootingLeft2));
                passOutLine->moving=true;
                passOutLine->xmove=-10;
                passOutLine->ymove=-5;
                
                passOutLine->isBullet=true;
//                passOutLine->isBomb=true;
                passOutLine->shooter=getQuad();
                passOutLine->player=this;
                
                passOutLine->ymovea=0.5;
                passOutLine->spread=new Spread();
                passOutLine->boundesCount=50;
                
            }else if(facing==1){
                passOutLine=new Line(parentPoint(shootingRight1),parentPoint(shootingRight2));
                passOutLine->moving=true;
                passOutLine->xmove=10;
                passOutLine->ymove=-5;
                
                passOutLine->isBullet=true;
//                passOutLine->isBomb=true;
                passOutLine->shooter=getQuad();
                passOutLine->player=this;
                
                passOutLine->ymovea=0.5;
                passOutLine->spread=new Spread();
                passOutLine->boundesCount=50;
                
            }else if(facing==2){
                
                passOutLine=new Line(parentPoint(shootingTop1),parentPoint(shootingTop2));
                passOutLine->moving=true;
                passOutLine->ymove=-10;
                
                passOutLine->isBullet=true;
                passOutLine->shooter=getQuad();
                passOutLine->player=this;
                
//                passOutLine->ymovea=0.5;
            }
            shootingWait=10;
        }
        shootingWait=fmax(0,shootingWait-1);
    }
    
    //    float lastTy=0.0f;
    
    void reactUpdate(){
        if(waitFrames>0){
            waitFrames--;
            return;
        }

        switch(controlState){
            case land:
                landReact();
                break;
            case water:
                waterReact();
                break;
        }
        setAttackBox();
    }
    
    void landUpdate(){
        
        Quad* tc=bottomColl;
        
        if(tc && tc->water){
            vhorizontal=0;
            vvertical=0;
            controlState=water;
            return;
        }
        
        //gravity
        
        vgravity=GRAVITY;
        upControly=0;
        downControly=0;
        pushing=false;
        
        //float lastForceX=vhorizontal*0.8;
        //float lastForceY=vvertical*0.8;
        
        
        if(!isPlatform){
            
            //apply friction in air
            if(leftLine->stopAt==NULL && rightLine->stopAt==NULL && bottomLine->stopAt==NULL && topLine->stopAt==NULL && bottomLine0->stopAt==NULL && bottomLine1->stopAt==NULL){
                
                atEdge=false;
                
                if(jumping){
                    vhorizontal*=0.9;
                }
                
            }else if(sprinting){
                vhorizontal*=0.95;
            }else if(!jumping){
                vhorizontal*=0;
            }
            
            //jumping set to false when going down
            if(jumping && vvertical>=0){
                jumping=false;
            }
            
            //reduce gravity when jumping
            if(jumpPress && jumping){
                vgravity*=0.2;
            }else{
                vgravity*=1.1;
            }
            
            //line collision effect:wind, damage, light, arrow weapon, etc
            for(std::vector<Line*>::iterator it = collLines.begin(); it != collLines.end(); ++it) {
                Line* line=*it;
                
                if(line->wind){
                    float x=line->p2->x-line->p1->x;
                    float y=line->p2->y-line->p1->y;
                    
                    float t=x+y;
                    vvertical-=y/t;
                    vhorizontal-=(x/t)*1.5;
                }
            }
            
            //running left air control
            if(runningLeft && !leftLine0->stopAt && !leftLine->stopAt){
                if(atEdge){
                    vLeftControl=-RUNSTRENGTH;
                }else{
                    vLeftControl=-RUNSTRENGTH*0.1;
                }
                vRightControl=0;
            }else{
                vLeftControl=0;
            }
            
            //running right
            if(runningRight && !rightLine0->stopAt && !rightLine->stopAt){
                if(atEdge){
                    vRightControl=RUNSTRENGTH;
                }else{
                    vRightControl=RUNSTRENGTH*0.1;
                }
                vLeftControl=0;
            }else{
                vRightControl=0;
            }
            
            //running down
            if(runningDown){
                if(bottomColl && bottomColl->weak==1){
                    downControly=0.1;
                    upControly=0;
                }
            }else{
                downControly=0;
            }
            
            vhorizontal+=vLeftControl+vRightControl;
            vvertical+=vgravity+upControly+downControly;
            
        }
        
        rightLine->p1->x=parentPointX(this->rightPoint2)-30;
        rightLine->p1->y=parentPointY(this->rightPoint2);
        rightLine->p2->x=parentPointX(this->rightPoint2)+vhorizontal;
        rightLine->p2->y=parentPointY(this->rightPoint2);
        
        rightLine0->p1->x=parentPointX(this->rightPoint)-30;
        rightLine0->p1->y=parentPointY(this->rightPoint);
        rightLine0->p2->x=parentPointX(this->rightPoint)+vhorizontal;
        rightLine0->p2->y=parentPointY(this->rightPoint);
        
        rightLine1->p1->x=parentPointX(this->rightPoint3)-30;
        rightLine1->p1->y=parentPointY(this->rightPoint3);
        rightLine1->p2->x=parentPointX(this->rightPoint3)+vhorizontal;
        rightLine1->p2->y=parentPointY(this->rightPoint3);
        
        rightFarLine->p1->x=parentPointX(this->rightPoint2)-30;
        rightFarLine->p1->y=parentPointY(this->rightPoint2);
        rightFarLine->p2->x=parentPointX(this->rightPoint2)+vhorizontal+20;
        rightFarLine->p2->y=parentPointY(this->rightPoint2);
        
        rightLine3->p1->x=parentPointX(this->rightPoint)-30;
        rightLine3->p1->y=parentPointY(this->rightPoint);
        rightLine3->p2->x=parentPointX(this->rightPoint)+vhorizontal+80;
        rightLine3->p2->y=parentPointY(this->rightPoint);
        
        rightLine4->p1->x=parentPointX(this->rightPoint3)-30;
        rightLine4->p1->y=parentPointY(this->rightPoint3);
        rightLine4->p2->x=parentPointX(this->rightPoint3)+vhorizontal+80;
        rightLine4->p2->y=parentPointY(this->rightPoint3);
        
        rightStraightLine->p1->x=parentPointX(this->topPoint3)-8;
        rightStraightLine->p1->y=parentPointY(this->topPoint3)+vhorizontal+10;
        rightStraightLine->p2->x=parentPointX(this->bottomPoint3)-3;
        rightStraightLine->p2->y=parentPointY(this->bottomPoint3)+vhorizontal-10;
        
        rightStraightLine2->p1->x=parentPointX(this->topPoint3)-3;
        rightStraightLine2->p1->y=parentPointY(this->topPoint3)+vhorizontal+10;
        rightStraightLine2->p2->x=parentPointX(this->bottomPoint3)-8;
        rightStraightLine2->p2->y=parentPointY(this->bottomPoint3)+vhorizontal-10;
        
        leftLine0->p1->x=parentPointX(this->leftPoint)+30;
        leftLine0->p1->y=parentPointY(this->leftPoint);
        leftLine0->p2->x=parentPointX(this->leftPoint)+vhorizontal;
        leftLine0->p2->y=parentPointY(this->leftPoint);
        
        leftLine->p1->x=parentPointX(this->leftPoint2)+30;
        leftLine->p1->y=parentPointY(this->leftPoint2);
        leftLine->p2->x=parentPointX(this->leftPoint2)+vhorizontal;
        leftLine->p2->y=parentPointY(this->leftPoint2);
        
        leftLine1->p1->x=parentPointX(this->leftPoint3)+30;
        leftLine1->p1->y=parentPointY(this->leftPoint3);
        leftLine1->p2->x=parentPointX(this->leftPoint3)+vhorizontal;
        leftLine1->p2->y=parentPointY(this->leftPoint3);
        
        leftFarLine->p1->x=parentPointX(this->leftPoint2)+30;
        leftFarLine->p1->y=parentPointY(this->leftPoint2);
        leftFarLine->p2->x=parentPointX(this->leftPoint2)+vhorizontal-20;
        leftFarLine->p2->y=parentPointY(this->leftPoint2);
        
        leftLine3->p1->x=parentPointX(this->leftPoint)+30;
        leftLine3->p1->y=parentPointY(this->leftPoint);
        leftLine3->p2->x=parentPointX(this->leftPoint)+vhorizontal-80;
        leftLine3->p2->y=parentPointY(this->leftPoint);
        
        leftLine4->p1->x=parentPointX(this->leftPoint3)+30;
        leftLine4->p1->y=parentPointY(this->leftPoint3);
        leftLine4->p2->x=parentPointX(this->leftPoint3)+vhorizontal-80;
        leftLine4->p2->y=parentPointY(this->leftPoint3);
        
        leftStraightLine->p1->x=parentPointX(this->topPoint)+8;
        leftStraightLine->p1->y=parentPointY(this->topPoint)+vhorizontal+10;
        leftStraightLine->p2->x=parentPointX(this->bottomPoint)+3;
        leftStraightLine->p2->y=parentPointY(this->bottomPoint)+vhorizontal-10;
        
        leftStraightLine2->p1->x=parentPointX(this->topPoint)+3;
        leftStraightLine2->p1->y=parentPointY(this->topPoint)+vhorizontal+10;
        leftStraightLine2->p2->x=parentPointX(this->bottomPoint)+8;
        leftStraightLine2->p2->y=parentPointY(this->bottomPoint)+vhorizontal-10;
        
        bottomLine0->p1->x=parentPointX(this->bottomPoint);
        bottomLine0->p1->y=parentPointY(this->bottomPoint)-30;
        bottomLine0->p2->x=parentPointX(this->bottomPoint);
        bottomLine0->p2->y=parentPointY(this->bottomPoint)+vvertical+10;
        
        bottomLine->p1->x=parentPointX(this->bottomPoint2);
        bottomLine->p1->y=parentPointY(this->bottomPoint2)-30;
        bottomLine->p2->x=parentPointX(this->bottomPoint2);
        bottomLine->p2->y=parentPointY(this->bottomPoint2)+vvertical+10;
        
        bottomLine1->p1->x=parentPointX(this->bottomPoint3);
        bottomLine1->p1->y=parentPointY(this->bottomPoint3)-30;
        bottomLine1->p2->x=parentPointX(this->bottomPoint3);
        bottomLine1->p2->y=parentPointY(this->bottomPoint3)+vvertical+10;
        
        bottomLine3->p1->x=parentPointX(this->bottomPoint);
        bottomLine3->p1->y=parentPointY(this->bottomPoint)-30;
        bottomLine3->p2->x=parentPointX(this->bottomPoint);
        bottomLine3->p2->y=parentPointY(this->bottomPoint)+vvertical+80;
        
        bottomLine4->p1->x=parentPointX(this->bottomPoint3);
        bottomLine4->p1->y=parentPointY(this->bottomPoint3)-30;
        bottomLine4->p2->x=parentPointX(this->bottomPoint3);
        bottomLine4->p2->y=parentPointY(this->bottomPoint3)+vvertical+80;
        
        topLine0->p1->x=parentPointX(this->topPoint);
        topLine0->p1->y=parentPointY(this->topPoint)+30;
        topLine0->p2->x=parentPointX(this->topPoint);
        topLine0->p2->y=parentPointY(this->topPoint)+vvertical-3;
        
        topLine->p1->x=parentPointX(this->topPoint);
        topLine->p1->y=parentPointY(this->topPoint)+30;
        topLine->p2->x=parentPointX(this->topPoint);
        topLine->p2->y=parentPointY(this->topPoint)+vvertical-3;
        
        topLine1->p1->x=parentPointX(this->topPoint3);
        topLine1->p1->y=parentPointY(this->topPoint3)+30;
        topLine1->p2->x=parentPointX(this->topPoint3);
        topLine1->p2->y=parentPointY(this->topPoint3)+vvertical;
        
    }
    
    void setAttackBox(){
        setRectValue(attack1,rightPoint,attackBottomPoint);
        setRectValue(attack0,attackLeftPoint,bottomPoint);
        setRectValue(attack2,attackTopTopPoint,attackTopBottomPoint);
        setRectValue(attack3,attackBottomTopPoint,attackBottomBottomPoint);
        setRectValue(hurtBox,leftPoint,bottomPoint3);
        
        if(attackCountDown<=0){
            attacking=false;
            clearAttackBox();
            attackCountDown=0;
        }
    }
    
    void setRectValue(Rectangle* target,Vector2D* p1,Vector2D* p2){
        target->topLeft->x=parentPointX(p1);
        target->topLeft->y=parentPointY(p1);
        target->bottomRight->x=parentPointX(p2);
        target->bottomRight->y=parentPointY(p2);
    }
    
    bool atLeftEdge=false;
    bool atRightEdge=false;
    
    Vector2D* getLeftStopAt(){
        if(leftLine0->stopAt){
            return leftLine0->stopAt;
        }else if(leftLine->stopAt){
            return leftLine->stopAt;
        }else if(leftLine1->stopAt){
            return leftLine1->stopAt;
        }
        return NULL;
    }
    
    Vector2D* getRightStopAt(){
        if(rightLine0->stopAt){
            return rightLine0->stopAt;
        }else if(rightLine->stopAt){
            return rightLine->stopAt;
        }else if(rightLine1->stopAt){
            return rightLine1->stopAt;
        }
        return NULL;
    }
    
    bool stuckRight=false;
    bool stuckLeft=false;
    bool ladding=false;
    
    void landReact(){
        
        if(ladderLine && (runningUp||runningDown)){
            ladding=true;
        }else if(!ladderLine){
            ladding=false;
        }
        
        Line* topline=NULL;
        
        if(topLine->stopAt){
            topline=topLine;
        }else if(topLine0->stopAt){
            topline=topLine0;
        }else if(topLine1->stopAt){
            topline=topLine1;
        }
        
        if(topline && !ladding){
            if(vvertical<0){
                vvertical=0;
            }
        }
        
        Line* bottomline=NULL;
        float minBottom=99999999;
        float minBottomX=999999;
        
        if(bottomLine->stopAt && !jumping){
            bottomline=bottomLine;
            if(minBottom>bottomline->stopAt->y){
                minBottomX=bottomline->stopAt->x;
                minBottom=bottomline->stopAt->y;
            }
        }
        if(bottomLine0->stopAt && !jumping){
            bottomline=bottomLine0;
            if(minBottom>bottomline->stopAt->y){
                minBottomX=bottomline->stopAt->x;
                minBottom=bottomline->stopAt->y;
            }
        }
        if(bottomLine1->stopAt && !jumping){
            bottomline=bottomLine1;
            if(minBottom>bottomline->stopAt->y){
                minBottomX=bottomline->stopAt->x;
                minBottom=bottomline->stopAt->y;
            }
        }
        
        if(bottomline && !ladding){
            //prevend pull from bottom
            if(this->vvertical>0){
                this->y=minBottom-this->getHeight();
            }
            
            atEdge=true;
            vvertical=0;
            vgravity=0;
            
            if(!jumping && bottomLine3->stopAt && bottomLine4->stopAt && !isPlatform){
                float y2=bottomLine4->stopAt->y;
                float x2=bottomLine4->stopAt->x;
                float y1=bottomLine3->stopAt->y;
                float x1=bottomLine3->stopAt->x;
                
                float m=(y2-y1)/(x2-x1);
                double angle=atan(m)*180/PI;
                
                this->angle=angle;

                if(angle>0){
                    this->rotateX=x1-this->x;
                    this->rotateY=y1-this->y;
                }else{
                    this->rotateX=x2-this->x;
                    this->rotateY=y2-this->y;
                }
            }
            
        }else{
            this->angle=0;
        }
        
        if(bottomline){
            if(bottomLine3->stopAtColl && bottomLine3->stopAtColl->player){
                GraphicObject* obj=(GraphicObject*)bottomLine3->stopAtColl->player;
                if(obj->moveLogic){
                    obj->moveLogic->move(this);
                }
            }else if(bottomLine4->stopAtColl && bottomLine4->stopAtColl->player){
                GraphicObject* obj=(GraphicObject*)bottomLine4->stopAtColl->player;
                if(obj->moveLogic){
                    obj->moveLogic->move(this);
                }
            }
        }
         
        
        if(!stuckRight && !stuckLeft && bottomline && topLine->stopAt){
            if(vhorizontal>0){
                stuckRight=true;
            }else{
                stuckLeft=true;
            }
        }else if(bottomline==NULL || topLine->stopAt==NULL){
            stuckRight=stuckLeft=false;
        }
        
        if(stuckRight && vhorizontal>0){
            vhorizontal=0;
            rightSpeed=0;
        }else if(stuckLeft && vhorizontal<0){
            vhorizontal=0;
            leftSpeed=0;
        }
        
        Line* leftline=NULL;
        float maxLeft=-999999999999;
        
        if(leftLine0->stopAt){
            leftline=leftLine0;
            maxLeft=fmax(maxLeft,leftLine0->stopAt->x);
        }
        
        if(leftLine->stopAt){
            leftline=leftLine;
            maxLeft=fmax(maxLeft,leftLine->stopAt->x);
        }
        
        if(leftLine1->stopAt && !bottomline){
            leftline=leftLine1;
            maxLeft=fmax(maxLeft,leftLine1->stopAt->x);
        }
        
        if(leftStraightLine->stopAt){
            leftline=leftStraightLine;
            maxLeft=fmax(maxLeft,parentPointX(topPoint));
        }
        
        if(leftStraightLine2->stopAt){
            leftline=leftStraightLine2;
            maxLeft=fmax(maxLeft,parentPointX(topPoint));
        }
        
        if(leftline && isPlatform && leftline->stopAtColl && leftline->stopAtColl->player){
            leftline=NULL;
        }
        
        
        if(leftline && !stuckRight && !stuckLeft){
            
            atLeftEdge=true;
            lastEdge=0;
            
            if(vhorizontal<=0){
                
                if(leftline->stopAtColl && leftline->stopAtColl->player && runningLeft){
                    GraphicObject* obj=(GraphicObject*)leftline->stopAtColl->player;
                    
                    if(!obj->isPlatform && obj->pushForce(-obj->pushSpeed)){
                        pushing=true;
                        vhorizontal=-obj->pushSpeed;
                        leftSpeed=0;
                    }else if(obj->isPlatform){
                        //same as part below
                        vhorizontal=0;
                        leftSpeed=0;
                        
                        this->x=maxLeft;
                    }else{
                        vhorizontal=0;
                        leftSpeed=0;
                        this->x=maxLeft;
                    }
                    
                }else{
                    vhorizontal=0;
                    leftSpeed=0;
                    
                    this->x=maxLeft;
                }
                
            }
        }else{
            atLeftEdge=false;
        }
        
        if(!bottomline && leftLine3->stopAt && leftLine4->stopAt && !isPlatform){
            float y2=leftLine4->stopAt->y;
            float x2=leftLine4->stopAt->x;
            float y1=leftLine3->stopAt->y;
            float x1=leftLine3->stopAt->x;
            
            float m=(y2-y1)/(x2-x1);
            
            double angle=(atan(m)*180/PI)-90;
            
            if(angle<-90){
                angle+=180;
                this->rotateX=x1-this->x;
                this->rotateY=y1-this->y;
            }else{
                this->rotateX=x2-this->x;
                this->rotateY=y2-this->y;
            }
            
            this->angle=angle;
            
        }
        
        if(actioning && leftFarLine->stopAtColl && leftFarLine->stopAtColl->player){
            GraphicObject* obj=(GraphicObject*)leftFarLine->stopAtColl->player;
            if(runningRight && obj->dragForceTo(this->x+obj->pushSpeed)){
                vhorizontal=obj->pushSpeed;
                leftSpeed=0;
            }
        }
        
        if(leftline && leftline->stopAtColl && leftline->stopAtColl->player){
            GraphicObject* obj=(GraphicObject*)leftline->stopAtColl->player;
            
            if(obj->moveLogic){
                obj->moveLogic->move(this);
            }
            
            maxLeft=fmax(maxLeft,this->x);
        }
        
        
        Line* rightline=NULL;
        float minRight=99999999999;
        
        if(rightLine0->stopAt){
            rightline=rightLine0;
            minRight=fmin(minRight,rightLine0->stopAt->x);
        }
        
        if(rightLine->stopAt){
            rightline=rightLine;
            minRight=fmin(minRight,rightLine->stopAt->x);
        }
        
        if(rightLine1->stopAt && !bottomline){
            rightline=rightLine1;
            minRight=fmin(minRight,rightLine1->stopAt->x);
        }
        
        if(rightStraightLine->stopAt){
            rightline=rightStraightLine;
            minRight=fmin(minRight,parentPointX(topPoint3));
        }
        
        if(rightStraightLine2->stopAt){
            rightline=rightStraightLine2;
            minRight=fmin(minRight,parentPointX(topPoint3));
        }
        
        if(rightline && isPlatform && rightline->stopAtColl && rightline->stopAtColl->player){
            rightline=NULL;
        }
        
        if(rightline && !stuckRight && !stuckLeft){
            
            atRightEdge=true;
            lastEdge=1;
            lastEdgeCount=10;
            
            if(vhorizontal>=0){
                float ttx=minRight-this->getWidth();
                
                if(rightline->stopAtColl && rightline->stopAtColl->player && runningRight){
                    
                    GraphicObject* obj=(GraphicObject*)rightline->stopAtColl->player;
                    
                    if(!obj->isPlatform && obj->pushForce(obj->pushSpeed)){
                        vhorizontal=obj->pushSpeed;
                        rightSpeed=0;
                    }else if(obj->isPlatform){
                        vhorizontal=0;
                        rightSpeed=0;
                        this->x=ttx;
                        
                    }else{
                        vhorizontal=0;
                        rightSpeed=0;
                        this->x=ttx;
                    }
                    
                }else{
                    vhorizontal=0;
                    rightSpeed=0;
                    this->x=ttx;
                }
                
                
            }
            
        }else{
            atRightEdge=false;
        }
        
        if(!bottomline && rightLine3->stopAt && rightLine4->stopAt  && !isPlatform){
            float y2=rightLine4->stopAt->y;
            float x2=rightLine4->stopAt->x;
            float y1=rightLine3->stopAt->y;
            float x1=rightLine3->stopAt->x;
            
            float m=(y2-y1)/(x2-x1);
            
            double angle=(atan(m)*180/PI)-90;
            
            if(angle<-90){
                angle+=180;
                this->rotateX=x2-this->x;
                this->rotateY=y2-this->y;
            }else{
                this->rotateX=x1-this->x;
                this->rotateY=y1-this->y;
            }
            
            this->angle=angle;
            
        }
        
        if(actioning && rightFarLine->stopAtColl && rightFarLine->stopAtColl->player){
            
            GraphicObject* obj=(GraphicObject*)rightFarLine->stopAtColl->player;
            
            if(runningLeft && obj->dragForceTo2(this->x+this->getWidth()-obj->pushSpeed)){
                vhorizontal=-obj->pushSpeed;
                rightSpeed=0;
            }
            
        }
        
        if(rightline && rightline->stopAtColl && rightline->stopAtColl->player){
            GraphicObject* obj=(GraphicObject*)rightline->stopAtColl->player;
            if(obj->moveLogic){
                obj->moveLogic->move(this);
            }
            minRight=fmin(minRight,this->x+this->getWidth());
        }
        
        if(!isPlatform){
            if(leftLine3->stopAtColl && leftLine3->stopAtColl->ctop && leftLine3->p1->distY(leftLine3->stopAtColl->p2)<50 && leftLine3->p1->distX(leftLine3->stopAtColl->p2)<35){
                
                if(!runningRight && !jumping){
                    vvertical=0;
                    atClifingCountDown=60;
                    clifing=true;
                    this->y=leftLine3->stopAtColl->p2->y+1;
//                    this->x=leftLine3->stopAtColl->p2->x-1;
                }
                
            }else if(rightLine3->stopAtColl && rightLine3->stopAtColl->ctop && rightLine3->p1->distY(rightLine3->stopAtColl->p1)<50 && rightLine3->p1->distX(rightLine3->stopAtColl->p1)<35){
                
                if(!runningLeft && !jumping){
                    vvertical=0;
                    clifing=true;
                    atClifingCountDown=60;
                    this->y=rightLine3->stopAtColl->p1->y+1;
//                    this->x=rightLine3->stopAtColl->p1->x-this->getWidth()+2;
                }
                
            }else{
                clifing=false;
                atClifingCountDown--;
            }
        }
        
        //ladder
        if(ladding && ladderLine){
            //printf("is ladderline:%s\n",instanceID.c_str());
            this->vvertical=0;
            if(runningUp){
                float ladderTop=fmin(ladderLine->p1->y,ladderLine->p2->y);
                if(this->y-3+this->getHeight()>ladderTop+10){
                    this->vvertical=-3;
                }
            }else if(runningDown){
                float ladderBottom=fmax(ladderLine->p1->y,ladderLine->p2->y);
                if(bottomline && bottomline->stopAtColl){
                    if(ladderBottom > bottomline->stopAtColl->p4->y){
                        this->vvertical=3;
                    }
                }else{
                    this->vvertical=3;
                }
            }else if(runningLeft || runningRight){
                ladding=false;
            }
            
            this->x=ladderLine->p1->x-20;
            
        }
        
        //set values
        float _vx=vhorizontal;
        float _vy=vvertical;
        
        setValue(_vx,_vy);
        
    }
    
    Quad* waterSurfaceColl=NULL;
    
    void waterUpdate(){
        
        Quad* targetColl=getInQuad();
        if(targetColl==NULL){
            controlState=land;
            return;
        }else if(targetColl->ctop){
            waterSurfaceColl=targetColl;
        }
        
        if(topColl==NULL){
            vgravity=GRAVITY;
        }else{
            vgravity=0;
        }
        
        vLeftControl=0;
        vRightControl=0;
        upControly=0;
        downControly=0;
        
        if(!jumping){
            vhorizontal*=0.7;
            vvertical*=0.7;
        }
        
        float topY=waterSurfaceColl->getHighestY();
        float dy=this->y-topY;
        bool atSurfaceColl=waterSurfaceColl==targetColl;
        
        if(runningRight){
            vhorizontal+=2;
        }else if(runningLeft){
            vhorizontal-=2;
        }
        
        if(runningUp && (!atSurfaceColl || dy>-10)){
            vvertical-=2;
        }else if(runningDown){
            vvertical+=2;
        }
        
        if((dy<=-10 && dy>=-13) || !atSurfaceColl ){
            //swim on surface
            vgravity=0;
            
            //can jump at surface
            atEdge=true;
        }
        
        vhorizontal+=vLeftControl+vRightControl;
        vvertical+=vgravity+upControly+downControly;
        
        rightLine->p1->x=parentPointX(this->rightPoint2)-30;
        rightLine->p1->y=parentPointY(this->rightPoint2);
        rightLine->p2->x=parentPointX(this->rightPoint2)+vhorizontal;
        rightLine->p2->y=parentPointY(this->rightPoint2);
        
        rightLine0->p1->x=parentPointX(this->rightPoint)-30;
        rightLine0->p1->y=parentPointY(this->rightPoint);
        rightLine0->p2->x=parentPointX(this->rightPoint)+vhorizontal;
        rightLine0->p2->y=parentPointY(this->rightPoint);
        
        rightLine1->p1->x=parentPointX(this->rightPoint3)-30;
        rightLine1->p1->y=parentPointY(this->rightPoint3);
        rightLine1->p2->x=parentPointX(this->rightPoint3)+vhorizontal;
        rightLine1->p2->y=parentPointY(this->rightPoint3);
        
        rightFarLine->p1->x=parentPointX(this->rightPoint2)-30;
        rightFarLine->p1->y=parentPointY(this->rightPoint2);
        rightFarLine->p2->x=parentPointX(this->rightPoint2)+vhorizontal+20;
        rightFarLine->p2->y=parentPointY(this->rightPoint2);
        
        rightLine3->p1->x=parentPointX(this->rightPoint)-30;
        rightLine3->p1->y=parentPointY(this->rightPoint);
        rightLine3->p2->x=parentPointX(this->rightPoint)+vhorizontal+80;
        rightLine3->p2->y=parentPointY(this->rightPoint);
        
        rightLine4->p1->x=parentPointX(this->rightPoint3)-30;
        rightLine4->p1->y=parentPointY(this->rightPoint3);
        rightLine4->p2->x=parentPointX(this->rightPoint3)+vhorizontal+80;
        rightLine4->p2->y=parentPointY(this->rightPoint3);
        
        rightStraightLine->p1->x=parentPointX(this->topPoint3)-8;
        rightStraightLine->p1->y=parentPointY(this->topPoint3)+vhorizontal+10;
        rightStraightLine->p2->x=parentPointX(this->bottomPoint3)-3;
        rightStraightLine->p2->y=parentPointY(this->bottomPoint3)+vhorizontal-10;
        
        rightStraightLine2->p1->x=parentPointX(this->topPoint3)-3;
        rightStraightLine2->p1->y=parentPointY(this->topPoint3)+vhorizontal+10;
        rightStraightLine2->p2->x=parentPointX(this->bottomPoint3)-8;
        rightStraightLine2->p2->y=parentPointY(this->bottomPoint3)+vhorizontal-10;
        
        leftLine0->p1->x=parentPointX(this->leftPoint)+30;
        leftLine0->p1->y=parentPointY(this->leftPoint);
        leftLine0->p2->x=parentPointX(this->leftPoint)+vhorizontal;
        leftLine0->p2->y=parentPointY(this->leftPoint);
        
        leftLine->p1->x=parentPointX(this->leftPoint2)+30;
        leftLine->p1->y=parentPointY(this->leftPoint2);
        leftLine->p2->x=parentPointX(this->leftPoint2)+vhorizontal;
        leftLine->p2->y=parentPointY(this->leftPoint2);
        
        leftLine1->p1->x=parentPointX(this->leftPoint3)+30;
        leftLine1->p1->y=parentPointY(this->leftPoint3);
        leftLine1->p2->x=parentPointX(this->leftPoint3)+vhorizontal;
        leftLine1->p2->y=parentPointY(this->leftPoint3);
        
        leftFarLine->p1->x=parentPointX(this->leftPoint2)+30;
        leftFarLine->p1->y=parentPointY(this->leftPoint2);
        leftFarLine->p2->x=parentPointX(this->leftPoint2)+vhorizontal-20;
        leftFarLine->p2->y=parentPointY(this->leftPoint2);
        
        leftLine3->p1->x=parentPointX(this->leftPoint)+30;
        leftLine3->p1->y=parentPointY(this->leftPoint);
        leftLine3->p2->x=parentPointX(this->leftPoint)+vhorizontal-80;
        leftLine3->p2->y=parentPointY(this->leftPoint);
        
        leftLine4->p1->x=parentPointX(this->leftPoint3)+30;
        leftLine4->p1->y=parentPointY(this->leftPoint3);
        leftLine4->p2->x=parentPointX(this->leftPoint3)+vhorizontal-80;
        leftLine4->p2->y=parentPointY(this->leftPoint3);
        
        leftStraightLine->p1->x=parentPointX(this->topPoint)+8;
        leftStraightLine->p1->y=parentPointY(this->topPoint)+vhorizontal+10;
        leftStraightLine->p2->x=parentPointX(this->bottomPoint)+3;
        leftStraightLine->p2->y=parentPointY(this->bottomPoint)+vhorizontal-10;
        
        leftStraightLine2->p1->x=parentPointX(this->topPoint)+3;
        leftStraightLine2->p1->y=parentPointY(this->topPoint)+vhorizontal+10;
        leftStraightLine2->p2->x=parentPointX(this->bottomPoint)+8;
        leftStraightLine2->p2->y=parentPointY(this->bottomPoint)+vhorizontal-10;
        
        bottomLine0->p1->x=parentPointX(this->bottomPoint);
        bottomLine0->p1->y=parentPointY(this->bottomPoint)-30;
        bottomLine0->p2->x=parentPointX(this->bottomPoint);
        bottomLine0->p2->y=parentPointY(this->bottomPoint)+vvertical+10;
        
        bottomLine->p1->x=parentPointX(this->bottomPoint2);
        bottomLine->p1->y=parentPointY(this->bottomPoint2)-30;
        bottomLine->p2->x=parentPointX(this->bottomPoint2);
        bottomLine->p2->y=parentPointY(this->bottomPoint2)+vvertical+10;
        
        bottomLine1->p1->x=parentPointX(this->bottomPoint3);
        bottomLine1->p1->y=parentPointY(this->bottomPoint3)-30;
        bottomLine1->p2->x=parentPointX(this->bottomPoint3);
        bottomLine1->p2->y=parentPointY(this->bottomPoint3)+vvertical+10;
        
        bottomLine3->p1->x=parentPointX(this->bottomPoint);
        bottomLine3->p1->y=parentPointY(this->bottomPoint)-30;
        bottomLine3->p2->x=parentPointX(this->bottomPoint);
        bottomLine3->p2->y=parentPointY(this->bottomPoint)+vvertical+80;
        
        bottomLine4->p1->x=parentPointX(this->bottomPoint3);
        bottomLine4->p1->y=parentPointY(this->bottomPoint3)-30;
        bottomLine4->p2->x=parentPointX(this->bottomPoint3);
        bottomLine4->p2->y=parentPointY(this->bottomPoint3)+vvertical+80;
        
        topLine0->p1->x=parentPointX(this->topPoint);
        topLine0->p1->y=parentPointY(this->topPoint)+30;
        topLine0->p2->x=parentPointX(this->topPoint);
        topLine0->p2->y=parentPointY(this->topPoint)+vvertical-3;
        
        topLine->p1->x=parentPointX(this->topPoint);
        topLine->p1->y=parentPointY(this->topPoint)+30;
        topLine->p2->x=parentPointX(this->topPoint);
        topLine->p2->y=parentPointY(this->topPoint)+vvertical-3;
        
        topLine1->p1->x=parentPointX(this->topPoint3);
        topLine1->p1->y=parentPointY(this->topPoint3)+30;
        topLine1->p2->x=parentPointX(this->topPoint3);
        topLine1->p2->y=parentPointY(this->topPoint3)+vvertical;
        
    }
    
    void waterReact(){
        
        Line* topline=NULL;
        
        if(topLine->stopAt){
            topline=topLine;
        }else if(topLine0->stopAt){
            topline=topLine0;
        }else if(topLine1->stopAt){
            topline=topLine1;
        }
        
        if(topline && !ladding){
            if(vvertical<0){
                vvertical=0;
            }
        }
        
        Line* bottomline=NULL;
        float minBottom=99999999;
        float minBottomX=999999;
        
        if(bottomLine->stopAt && !jumping){
            bottomline=bottomLine;
            if(minBottom>bottomline->stopAt->y){
                minBottomX=bottomline->stopAt->x;
                minBottom=bottomline->stopAt->y;
            }
        }
        if(bottomLine0->stopAt && !jumping){
            bottomline=bottomLine0;
            if(minBottom>bottomline->stopAt->y){
                minBottomX=bottomline->stopAt->x;
                minBottom=bottomline->stopAt->y;
            }
        }
        if(bottomLine1->stopAt && !jumping){
            bottomline=bottomLine1;
            if(minBottom>bottomline->stopAt->y){
                minBottomX=bottomline->stopAt->x;
                minBottom=bottomline->stopAt->y;
            }
        }
        
        if(bottomline){
            //prevend pull from bottom
            if(this->vvertical>0){
                this->y=minBottom-this->getHeight();
            }
            
            atEdge=true;
            vvertical=0;
            vgravity=0;
            
        }
        
        
        if(!stuckRight && !stuckLeft && bottomline && topLine->stopAt){
            if(vhorizontal>0){
                stuckRight=true;
            }else{
                stuckLeft=true;
            }
        }else if(bottomline==NULL || topLine->stopAt==NULL){
            stuckRight=stuckLeft=false;
        }
        
        if(stuckRight && vhorizontal>0){
            vhorizontal=0;
            rightSpeed=0;
        }else if(stuckLeft && vhorizontal<0){
            vhorizontal=0;
            leftSpeed=0;
        }
        
        Line* leftline=NULL;
        float maxLeft=-999999999999;
        
        if(leftLine0->stopAt){
            leftline=leftLine0;
            maxLeft=fmax(maxLeft,leftLine0->stopAt->x);
        }
        
        if(leftLine->stopAt){
            leftline=leftLine;
            maxLeft=fmax(maxLeft,leftLine->stopAt->x);
        }
        
        if(leftLine1->stopAt && !bottomline){
            leftline=leftLine1;
            maxLeft=fmax(maxLeft,leftLine1->stopAt->x);
        }
        
        if(leftStraightLine->stopAt){
            leftline=leftStraightLine;
            maxLeft=fmax(maxLeft,parentPointX(topPoint));
        }
        
        if(leftStraightLine2->stopAt){
            leftline=leftStraightLine2;
            maxLeft=fmax(maxLeft,parentPointX(topPoint));
        }
        
        if(leftline && isPlatform && leftline->stopAtColl && leftline->stopAtColl->player){
            leftline=NULL;
        }
        
        
        if(leftline && !stuckRight && !stuckLeft){
            
            atEdge=true;
            atLeftEdge=true;
            lastEdge=0;
            lastEdgeCount=10;
            
            if(vhorizontal<=0){
                
                vhorizontal=0;
                leftSpeed=0;
                this->x=maxLeft;
                
            }
        }else{
            atLeftEdge=false;
        }
        
        
        
        Line* rightline=NULL;
        float minRight=99999999999;
        
        if(rightLine0->stopAt){
            rightline=rightLine0;
            minRight=fmin(minRight,rightLine0->stopAt->x);
        }
        
        if(rightLine->stopAt){
            rightline=rightLine;
            minRight=fmin(minRight,rightLine->stopAt->x);
        }
        
        if(rightLine1->stopAt && !bottomline){
            rightline=rightLine1;
            minRight=fmin(minRight,rightLine1->stopAt->x);
        }
        
        if(rightStraightLine->stopAt){
            rightline=rightStraightLine;
            minRight=fmin(minRight,parentPointX(topPoint3));
        }
        
        if(rightStraightLine2->stopAt){
            rightline=rightStraightLine2;
            minRight=fmin(minRight,parentPointX(topPoint3));
        }
        
        if(rightline && isPlatform && rightline->stopAtColl && rightline->stopAtColl->player){
            rightline=NULL;
        }
        
        if(rightline && !stuckRight && !stuckLeft){
            
            atRightEdge=true;
            lastEdge=1;
            
            if(vhorizontal>=0){
                float ttx=minRight-this->getWidth();
              
                vhorizontal=0;
                rightSpeed=0;
                this->x=ttx;
                
                
            }
            
        }else{
            atRightEdge=false;
        }
        
        
        if(!isPlatform){
            if(leftLine3->stopAtColl && leftLine3->stopAtColl->ctop && leftLine3->p1->distY(leftLine3->stopAtColl->p2)<50 && leftLine3->p1->distX(leftLine3->stopAtColl->p2)<35){
                
                if(!runningRight && !jumping){
                    vvertical=0;
                    atClifingCountDown=60;
                    clifing=true;
                    this->y=leftLine3->stopAtColl->p2->y+1;
                    
                }
                
            }else if(rightLine3->stopAtColl && rightLine3->stopAtColl->ctop && rightLine3->p1->distY(rightLine3->stopAtColl->p1)<50 && rightLine3->p1->distX(rightLine3->stopAtColl->p1)<35){
                
                if(!runningLeft && !jumping){
                    vvertical=0;
                    clifing=true;
                    atClifingCountDown=60;
                    this->y=rightLine3->stopAtColl->p1->y+1;
                    
                }
                
            }else{
                clifing=false;
                atClifingCountDown--;
            }
        }
        
       
        //set values
        float _vx=vhorizontal;
        float _vy=vvertical;
        
        setValue(_vx,_vy);
    }
    
    void setValue(float _vx,float _vy){
        this->vx=_vx;
        this->vy=_vy;
        
        lastx=this->x;
        lasty=this->y;
        
        this->x+=vx;
        this->y+=vy;
        
        collRect->p1->x=parentPointX(topPoint);
        collRect->p1->y=parentPointY(topPoint);
        
        collRect->p2->x=parentPointX(rightPoint);
        collRect->p2->y=parentPointY(rightPoint);
        
        collRect->p3->x=parentPointX(rightPoint3);
        collRect->p3->y=parentPointY(rightPoint3);
        
        collRect->p4->x=parentPointX(leftPoint3);
        collRect->p4->y=parentPointY(leftPoint3);
        
//        float bottomy=this->y+this->getHeight();
        
    }
    
    bool pushForce(float vh){
        
        if(vh<0 && !isLeftColl()){
            this->vhorizontal+=vh;
            return true;
        }else if(vh>0 && !isRightColl()){
            this->vhorizontal+=vh;
            return true;
        }
        return false;
    }
    
    bool dragForceTo(float tx){
        this->x=tx-this->getWidth();
        return true;
    }
    
    bool dragForceTo2(float tx){
        this->x=tx;
        return true;
    }
    
};

#endif /* Player_h */
