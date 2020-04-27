//
//  PlayState.h
//  2D-Game-Engine
//
//  Created by ngchenghow on 12/12/2018.
//  Copyright © 2018 ngchenghow. All rights reserved.
//

#ifndef PlayState_h
#define PlayState_h

#include "GameState.h"
#include "Graphic.h"
#include "GameLevelParser.h"
#include "Quad.h"
#include "GraphicObject.h"
#include "Line.h"
#include "Command.h"
#include "UpCommand.h"
#include "UpUpCommand.h"
#include "DownCommand.h"
#include "DownUpCommand.h"
#include "LeftCommand.h"
#include "LeftUpCommand.h"
#include "RightCommand.h"
#include "RightUpCommand.h"
#include "JumpCommand.h"
#include "JumpUpCommand.h"
#include "SprintCommand.h"
#include "SprintUpCommand.h"
#include "ActionCommand.h"
#include "ActionUpCommand.h"
#include "AttackCommand.h"
#include "AttackUpCommand.h"
#include "ShootACommand.h"
#include "ShootAUpCommand.h"

#include "Game.h"
#include "GameStateMachine.h"

#include <algorithm>
#include <vector>
#include <cstdlib>

class GameStateMachine;

class PlayState:public GameState
{
public:
    std::vector<Quad*> quads;
    std::vector<Line*> lines;
    
    std::vector<Vector2D*> lights;
    
    GraphicObject* player_box;
    GraphicObject* player_box2;
    
    float cameraTx=0;
    float cameraTy=0;
    
    bool isEditor=false;
    
    Command* buttonUpCommand;
    Command* buttonUpUpCommand;
    Command* buttonDownCommand;
    Command* buttonDownUpCommand;
    Command* buttonLeftCommand;
    Command* buttonLeftUpCommand;
    Command* buttonRightCommand;
    Command* buttonRightUpCommand;
    Command* buttonJumpCommand;
    Command* buttonJumpUpCommand;
    Command* buttonSprintCommand;
    Command* buttonSprintUpCommand;
    Command* buttonActionCommand;
    Command* buttonActionUpCommand;
    Command* buttonAttackCommand;
    Command* buttonAttackUpCommand;
    Command* buttonShootACommand;
    Command* buttonShootAUpCommand;
    
    SDL_Scancode rightButtonCode;
    SDL_Scancode leftButtonCode;
    SDL_Scancode upButtonCode;
    SDL_Scancode downButtonCode;
    SDL_Scancode jumpButtonCode;
    SDL_Scancode sprintButtonCode;
    SDL_Scancode actionButtonCode;
    SDL_Scancode attackButtonCode;
    SDL_Scancode shootAButtonCode;
    
    std::vector<GraphicObject*> players;
    
    Game* game;
    
    int lineCount=0;
    
    PlayState(){
        game=Game::Instance();
        lines.reserve(2500);
        
        buttonUpCommand=new UpCommand();
        buttonUpUpCommand=new UpUpCommand();
        buttonDownCommand=new DownCommand();
        buttonDownUpCommand=new DownUpCommand();
        buttonLeftCommand=new LeftCommand();
        buttonLeftUpCommand=new LeftUpCommand();
        buttonRightCommand=new RightCommand();
        buttonRightUpCommand=new RightUpCommand();
        buttonJumpCommand=new JumpCommand();
        buttonJumpUpCommand=new JumpUpCommand();
        buttonSprintCommand=new SprintCommand();
        buttonSprintUpCommand=new SprintUpCommand();
        buttonActionCommand=new ActionCommand();
        buttonActionUpCommand=new ActionUpCommand();
        buttonAttackCommand=new AttackCommand();
        buttonAttackUpCommand=new AttackUpCommand();
        buttonShootACommand=new ShootACommand();
        buttonShootAUpCommand=new ShootAUpCommand();
        
        rightButtonCode=SDL_SCANCODE_D;
        leftButtonCode=SDL_SCANCODE_A;
        upButtonCode=SDL_SCANCODE_W;
        downButtonCode=SDL_SCANCODE_S;
        jumpButtonCode=SDL_SCANCODE_J;
        sprintButtonCode=SDL_SCANCODE_L;
        actionButtonCode=SDL_SCANCODE_I;
        attackButtonCode=SDL_SCANCODE_O;
        shootAButtonCode=SDL_SCANCODE_P;
        
    }
    
    virtual void update(){
        
        Graphic* stage=game->getStage();
        
        //stage->player, object, laser normal gravity,last speed update
        stage->update();
        
        //add passOutLine to lines
        shootOutBulletByPlayers();
        
        //terrain laser collision test
        terrainLaserCollision();
        
        //collsion for attack to two side: my attack and enemy attack
        enemyCollisionAttackBy(player_box);
        
        //player attach by enemies
        playerCollisionAttachByEnemies(player_box);
        
        //hit by bullets
        hitBullets();
        
        //cleanup bullets
        cleanUpBullets();
        
        //update bullets
        updateBullets();
        
        //terrain collision test
        terrainCollisionPlayer(player_box);
        
        //check player health and clean up
        cleanUpPlayers();
        
        
        //reaction update
        player_box->reactUpdate();
        player_box2->reactUpdate();
        
        cameraUpdate();
    }
    
    void shootOutBulletByPlayers(){
        for(std::vector<GraphicObject*>::iterator it = players.begin(); it != players.end(); ++it) {
            GraphicObject* player=*it;
            shootOutBullet(player);
        }
    }
    
    void shootOutBullet(GraphicObject* player){
        
        Line* bullet=player->passOutLine;
        if(bullet==NULL){
            return;
        }
        
        player->passOutLine=NULL;
        lines.push_back(bullet);
        lineCount++;
    }
    
    void hitBullets(){
        //loop though lines for bullet hit
        for(std::vector<Line*>::iterator li = lines.begin(); li != lines.end(); ++li) {
            Line* line=*li;
            GraphicObject* player=(GraphicObject*)line->player;
            GraphicObject* otherPlayer=(GraphicObject*)line->stopAtPlayer;
            
            line->boundesCount=fmax(0,line->boundesCount-1);
            
            if(!line->isBullet || !line->stopAt){
                continue;
            }
            float degree=line->stopAtColl->getDegreeAtEdge(line->stopAtEdge);
            float lineDegree=line->getDegree();
            float finalDegree=degree-lineDegree;
            
            if(line->boundesCount>0){
                
                line->ymove=cos(finalDegree)*-line->ymove;
                line->xmove=cos(finalDegree)*line->xmove;
                
                line->p2->x=line->p1->x;
                line->p2->y=line->p1->y;
                
            }else if(line->spread!=NULL){
                
                //spread line
//                Spread* spread=line->spread;
                float p1x=line->p1->x+cos(finalDegree)*10;
                float p1y=line->p1->y+cos(finalDegree)*-10;
                
                int amt=line->spread->amount;
                int xm=line->spread->xmove;
                int ym=line->spread->ymove;
                
                for(int i=0;i<amt;i++){
                    float dx;
                    float dy;
                    Line* l;
                    float r=rand()%90-45;
                    dx=cos(finalDegree+r)*xm;
                    
                    r=rand()%90-45;
                    dy=cos(finalDegree+r)*-ym;
                    
                    Vector2D* p1=new Vector2D(p1x,p1y);
                    Vector2D* p2=new Vector2D(p1x,p1y);
                    
                    l=new Line(p1,p2);
                    
                    l->isBullet=true;
                    l->xmove=dx;
                    l->ymove=dy;
                    l->moving=true;
                    l->shooter=line->shooter;
                    l->player=line->player;
                    l->ymovea=0.5;
                    l->boundesCount=-1;
                    
                    lines.push_back(l);
                    lineCount++;
                }
                
                line->moving=false;
                
            }else if(line->stopAtPlayer){
                player->damageTo(otherPlayer,line->damageValue,line->damageType);
            }else{
                line->moving=false;
            }
        }
    }
    
    void cleanUpBullets(){
        for(std::vector<Line*>::iterator li = lines.begin(); li != lines.end(); ++li) {
            Line* line=*li;
            line->cleanUpCount+=1;
            
            if(line->isBullet && line->boundesCount<0){
                if(line->stopAt || line->cleanUpCount>500){
                    lines.erase(li);
                    li--;
                }
            }else if(line->isBullet && !line->moving){
                lines.erase(li);
                li--;
            }
        }
    }
    
    void updateBullets(){
        for(std::vector<Line*>::iterator li = lines.begin(); li != lines.end(); ++li) {
            Line* line=*li;
            if(line->moving){
                //update line movement
                float np2x=line->p2->x;
                float np2y=line->p2->y;
                
                line->p2->x+=line->xmove;
                line->p2->y+=line->ymove;
                
                line->p1->x=np2x;
                line->p1->y=np2y;
                
                line->xmove+=line->xmovea;
                line->ymove+=line->ymovea;
            }
        }
    }
    
    void cleanUpPlayers(){
        for(std::vector<GraphicObject*>::iterator it = players.begin(); it != players.end(); ++it) {
            GraphicObject* player=*it;
            if(player->health<=0){
                destroyPlayer(player);
            }
        }
    }
    
    void playerCollisionAttachByEnemies(GraphicObject* player){
        
    }
    
    void enemyCollisionAttackBy(GraphicObject* player){
        
        Graphic* stage=game->getStage();
        
        Rectangle* attackBox=player->getAttackBox();
        if(!attackBox){
            return;
        }

        for(std::vector<GraphicObject*>::iterator it = players.begin(); it != players.end(); ++it) {
            
            GraphicObject* otherPlayer=*it;
            Rectangle* rect=otherPlayer->getRect();
            
            if(otherPlayer==player){
                continue;
            }
            
            if(attackBox->isCollision(rect,stage)){
                player->damageTo(otherPlayer,rect->damageValue,rect->damageType);
            }
            
        }
        
        player->attackCountDown--;
        
    }
    
    void cameraUpdate(){
        
        Graphic* stage=game->getStage();
        
        float cameraX=getCamFollowX();
        float cameraY=getCamFollowY();
        
        cameraTx=-cameraX+stage->getStageWidth()/2;
        cameraTy=-cameraY+stage->getStageHeight()/2;
        
        float dx=abs(cameraTx-stage->x);
        float dy=abs(cameraTy-stage->y);
        
        float speed=getCamSpeed(dx+dy);
        
        if(speed){
            stage->x+=(cameraTx-stage->x)/speed;
            stage->y+=(cameraTy-stage->y)/speed;
        }
    }
    
    virtual float getCamSpeed(float d){
        float speed;
        if(d<50){
            speed=50;
        }else if(d<100){
            speed=30;
        }else if(d<200){
            speed=20;
        }else if(d<300){
            speed=10;
        }else{
            speed=10;
        }
        return speed;
    }
    
    bool quadCollision(Quad* quad,Vector2D* p,int delta){
        Vector2D* p1=quad->p1;
        Vector2D* p2=quad->p2;
        Vector2D* p3=quad->p3;
        Vector2D* p4=quad->p4;
        
        //1,2,3 triangle
        
        float areaOrig=getArea(p1,p2,p3);
        float area1=getArea(p,p1,p2);
        float area2=getArea(p,p2,p3);
        float area3=getArea(p,p3,p1);
        
        if(abs(areaOrig-(area1+area2+area3))<=delta){
            return true;
        }
        
        //3,4,1 triangle
        float areaOrig2=getArea(p3,p4,p1);
        float area4=getArea(p,p3,p4);
        float area5=getArea(p,p4,p1);
        float area6=getArea(p,p1,p3);
        
        if(abs(areaOrig2-(area4+area5+area6))<=delta){
            return true;
        }
        
        return false;
    }
    
    void terrainLaserCollision(){
        
        //reset line
        for(std::vector<Line*>::iterator li = lines.begin(); li != lines.end(); ++li) {
            Line* line=*li;
            line->resetCollision();
        }
        
        //reset player
        for(std::vector<GraphicObject*>::iterator player=players.begin();player!=players.end();++player){
            GraphicObject* p=*player;
            p->ladderLine=NULL;
        }
        
        for(std::vector<Quad*>::iterator it = quads.begin(); it != quads.end(); ++it) {
            Quad* rect=*it;
            
            if(rect->water){
                continue;
            }
            
            for(std::vector<Line*>::iterator li = lines.begin(); li != lines.end(); ++li) {
                Line* line=*li;
                bool isColled=false;
                
                if(line->isBullet && line->shooter==rect){
                    continue;
                }
                
                if(line->gothou==0 && line->ladder==0){
                    isColled=line->collisionAndSet(rect);
                }else if(line->ladder==1 && rect->player){
                    //player meet ladder
                    isColled=line->collisionAndSet(rect);
                    
                    if(isColled){
                        setLadder(rect->player,line);
                    }
                }
            }
        }
    }
    
    void setLadder(void* p,Line* line){
        GraphicObject* player=(GraphicObject*)p;
        player->ladderLine=line;
    }
    
    void terrainLaserCollisionPlayer(GraphicObject* player){
        player->resetCollisionLine();
        for(std::vector<Line*>::iterator li = lines.begin(); li != lines.end(); ++li) {
            
            Line* line=*li;
            Quad* rect=player->getQuad();
            
            if(line->attach && line->quad==rect){
                continue;
            }
            
            bool c=line->collisionAndSet(rect);
            
            if(c){
                player->addCollisionLine(line);
            }
        }
    }
    
    void terrainCollisionPlayer(GraphicObject* player){
        
        Quad* bottomQuad=NULL;
        Quad* bottomQuad2=NULL;
        Quad* bottomQuad3=NULL;
        Quad* leftQuad=NULL;
        Quad* leftQuad2=NULL;
        Quad* leftQuad3=NULL;
        Quad* rightQuad=NULL;
        Quad* rightQuad2=NULL;
        Quad* rightQuad3=NULL;
        Quad* topQuad=NULL;
        Quad* topQuad2=NULL;
        Quad* topQuad3=NULL;
        
        Quad* playerQuad=player->getQuad();
        
        for(std::vector<Quad*>::iterator it = quads.begin(); it != quads.end(); ++it) {
            Quad* item=*it;
            if(item==playerQuad){
                continue;
            }
            
            Vector2D* bp=player->getBottomPoint();
            Vector2D* bp2=player->getBottomPoint2();
            Vector2D* bp3=player->getBottomPoint3();
            
            //1000 so make it able to jump when a bit distance from bottom
            if(bottomQuad==NULL && quadCollision(item,bp,300)){
                player->setBottomCollision(item);
                bottomQuad=item;
            }
            
            if(bottomQuad2==NULL && quadCollision(item,bp2,300)){
                player->setBottom2Collision(item);
                bottomQuad2=item;
            }
            
            if(bottomQuad3==NULL && quadCollision(item,bp3,300)){
                player->setBottom3Collision(item);
                bottomQuad3=item;
            }
            
            Vector2D* lp=player->getLeftPoint();
            Vector2D* lp2=player->getLeftPoint2();
            Vector2D* lp3=player->getLeftPoint3();
            
            if(leftQuad==NULL && quadCollision(item,lp,300)){
                player->setLeftCollision(item);
                leftQuad=item;
            }
            
            if(leftQuad2==NULL && quadCollision(item,lp2,300)){
                player->setLeft2Collision(item);
                leftQuad2=item;
            }
            
            if(leftQuad3==NULL && quadCollision(item,lp3,300)){
                player->setLeft3Collision(item);
                leftQuad3=item;
            }
            
            Vector2D* rp=player->getRightPoint();
            Vector2D* rp2=player->getRightPoint2();
            Vector2D* rp3=player->getRightPoint3();
            
            if(rightQuad==NULL && quadCollision(item,rp,300)){
                player->setRightCollision(item);
                rightQuad=item;
            }
            
            if(rightQuad2==NULL && quadCollision(item,rp2,300)){
                player->setRight2Collision(item);
                rightQuad2=item;
            }
            
            if(rightQuad3==NULL && quadCollision(item,rp3,300)){
                player->setRight3Collision(item);
                rightQuad3=item;
            }
            
            Vector2D* tp=player->getTopPoint();
            Vector2D* tp2=player->getTopPoint2();
            Vector2D* tp3=player->getTopPoint3();
            
            
            
            if(topQuad==NULL && quadCollision(item,tp,300)){
                player->setTopCollision(item);
                topQuad=item;
            }
            
            if(topQuad2==NULL && quadCollision(item,tp2,300)){
                player->setTop2Collision(item);
                topQuad2=item;
            }
            
            if(topQuad3==NULL && quadCollision(item,tp3,300)){
                player->setTop3Collision(item);
                topQuad3=item;
            }
            
        }
        
        if(bottomQuad==NULL)
            player->setBottomCollision(NULL);
        
        if(bottomQuad2==NULL)
            player->setBottom2Collision(NULL);
        
        if(bottomQuad3==NULL)
            player->setBottom3Collision(NULL);
        
        if(leftQuad==NULL)
            player->setLeftCollision(NULL);
        
        if(leftQuad2==NULL)
            player->setLeft2Collision(NULL);
        
        if(leftQuad3==NULL)
            player->setLeft3Collision(NULL);
        
        if(rightQuad==NULL)
            player->setRightCollision(NULL);
        
        
        if(rightQuad2==NULL)
            player->setRight2Collision(NULL);
        
        if(rightQuad3==NULL)
            player->setRight3Collision(NULL);
        
        if(topQuad==NULL)
            player->setTopCollision(NULL);
        
        
        if(topQuad2==NULL)
            player->setTop2Collision(NULL);
        
    }
    
    float getArea(Vector2D* p1,Vector2D* p2,Vector2D* p3){
        float area = abs((p2->x-p1->x)*(p3->y-p1->y) - (p3->x-p1->x)*(p2->y-p1->y));
        return area;
    }
    
    virtual void render(){
        Graphic* stage=game->getStage();
        SDL_Renderer* renderer=game->renderer;
        
        SDL_RenderClear(renderer);
        
        stage->draw(renderer);
        
        drawPlatforms(renderer,stage);
        
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderPresent(renderer);
    }
    
    void drawPlatforms(SDL_Renderer* renderer,Graphic* stage){
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF );
        
        for(std::vector<Quad*>::iterator it = quads.begin(); it != quads.end(); ++it) {
            Quad* item=*it;
            
            if(item->ctop){
                SDL_RenderDrawLine(renderer,item->p1->x+stage->getX(),item->p1->y+stage->getY(),item->p2->x+stage->getX(),item->p2->y+stage->getY());
            }
            
            if(item->cright){
                SDL_RenderDrawLine(renderer,item->p2->x+stage->getX(),item->p2->y+stage->getY(),item->p3->x+stage->getX(),item->p3->y+stage->getY());
            }
            
            if(item->cbottom){
                SDL_RenderDrawLine(renderer,item->p3->x+stage->getX(),item->p3->y+stage->getY(),item->p4->x+stage->getX(),item->p4->y+stage->getY());
            }
            
            if(item->cleft){
                SDL_RenderDrawLine(renderer,item->p4->x+stage->getX(),item->p4->y+stage->getY(),item->p1->x+stage->getX(),item->p1->y+stage->getY());
            }
            
        }
        
        for(std::vector<Line*>::iterator it2=lines.begin();it2!=lines.end();++it2){
            Line* item=*it2;

            Vector2D* p1=item->p1;
            Vector2D* p2=item->getStopAt();

            SDL_RenderDrawLine(renderer,p1->x+stage->getX(),p1->y+stage->getY(),p2->x+stage->getX(),p2->y+stage->getY());

        }
        
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF );
        Rectangle* attackBox=player_box->getAttackBox();
        if(attackBox){
            
            float x1=attackBox->getX1(stage);
            float y1=attackBox->getY1(stage);
            float x2=attackBox->getX2(stage);
            float y2=attackBox->getY2(stage);
            
            SDL_RenderDrawLine(renderer,x1,y1,x2,y1);
            SDL_RenderDrawLine(renderer,x2,y1,x2,y2);
            SDL_RenderDrawLine(renderer,x2,y2,x1,y2);
            SDL_RenderDrawLine(renderer,x1,y2,x1,y1);
            
        }
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF );
    }
    
    
    void destroyPlayer(GraphicObject* player){
        
        Graphic* stage=game->getStage();
        Quad* q=player->getQuad();
        
        std::vector<Quad*>::iterator it=std::find(quads.begin(),quads.end(),q);
        if(it!=quads.end()){
            quads.erase(it);
        }
        
        removeLine(player->rightLine0);
        removeLine(player->rightLine);
        removeLine(player->rightLine1);
        removeLine(player->rightFarLine);
        removeLine(player->rightLine3);
        removeLine(player->rightLine4);

        removeLine(player->leftLine0);
        removeLine(player->leftLine);
        removeLine(player->leftLine1);
        removeLine(player->leftFarLine);
        removeLine(player->leftLine3);
        removeLine(player->leftLine4);
        
        removeLine(player->bottomLine0);
        removeLine(player->bottomLine);
        removeLine(player->bottomLine1);
        removeLine(player->bottomLine3);
        removeLine(player->bottomLine4);

        removeLine(player->topLine0);
        removeLine(player->topLine);
        removeLine(player->topLine1);
        
        stage->removeChild(player);
        
    }
    
    void removeLine(Line* line){
        std::vector<Line*>::iterator it=std::find(lines.begin(),lines.end(),line);
        if(it!=lines.end()){
            lines.erase(it);
        }
    }
    
    void initPlayerCollision(GraphicObject* p){
        quads.push_back(p->getQuad());
        players.push_back(p);
        
        lines.push_back(p->rightLine0);
        lines.push_back(p->rightLine);
        lines.push_back(p->rightLine1);
        lines.push_back(p->rightFarLine);
        lines.push_back(p->rightLine3);
        lines.push_back(p->rightLine4);
        lines.push_back(p->rightStraightLine);
        lines.push_back(p->rightStraightLine2);
//
        lines.push_back(p->leftLine0);
        lines.push_back(p->leftLine);
        lines.push_back(p->leftLine1);
        lines.push_back(p->leftFarLine);
        lines.push_back(p->leftLine3);
        lines.push_back(p->leftLine4);
        lines.push_back(p->leftStraightLine);
        lines.push_back(p->leftStraightLine2);
        
        lines.push_back(p->bottomLine0);
        lines.push_back(p->bottomLine);
        lines.push_back(p->bottomLine1);
        lines.push_back(p->bottomLine3);
        lines.push_back(p->bottomLine4);
        
        lines.push_back(p->topLine0);
        lines.push_back(p->topLine);
        lines.push_back(p->topLine1);
        
    }
    
    virtual float getCamFollowX(){
        return player_box->getCenterX();
    }
    
    virtual float getCamFollowY(){
        return player_box->getCenterY();
    }
    
    virtual void parseXML(){
        //load xml
        GameLevelParser* parser=new GameLevelParser();
        
        parser->parseLevelXML("/Users/ngchenghow/Desktop/level-2.xml",&quads,&lines);
    }
    
    virtual bool onEnter(){
        
        Graphic* stage=game->getStage();
        
        parseXML();
        
        //add player
        
        //collision box size
        player_box=(GraphicObject*)stage->addChild(new GraphicObject("player_box","char_sheet",32,52));
        
        player_box->isPlayer=true;
        player_box->setSheet();
//        player_box->setFrameSize
        player_box->setStateIDFrame(0,1,true);
//        player_box->setStateIDFrame(1,6,false);
//        player_box->setStateIDFrame(2,6,true);
//        player_box->setStateIDFrame(3,2,true);
//        player_box->setStateIDFrame(13,4,false);
        player_box->setStateID(0);
        
        player_box->x=907;
        player_box->y=-1002;
        
        player_box2=(GraphicObject*)stage->addChild(new GraphicObject("player_box2","grey_box",200,50));
        
        player_box2->x=1000;
        player_box2->y=-1102;
        
        initPlayerCollision(player_box);
        initPlayerCollision(player_box2);
        
        //configure object to make it a platform
        //or platform should use another class better
        player_box2->setAsPlatform();
        player_box2->moveLogic=new MoveLogic(player_box2);
        
        
        cameraToPoint();
        
        return true;
    }
    
    void cameraToPoint(){
        
        Graphic* stage=game->getStage();
        
        float cameraX=getCamFollowX();
        float cameraY=getCamFollowY();
        
        stage->x=-cameraX+stage->getStageWidth()/2;
        stage->y=-cameraY+stage->getStageHeight()/2;
    }
    
    virtual bool onExit(){
        
        quads.clear();
        lines.clear();
        
        Game::Instance()->getStage()->removeAllChild();
        Game::Instance()->resetStage();
        
        return true;
    }
    
    virtual void clickHandler(){
        
    }
    
    virtual void mouseDownHandler(){
        
    }
    
    virtual void mouseUpHandler(){
        
    }
    
    virtual void mouseMotionHandler(){
        
    }
    
    Uint8 *keyStates;
    
    virtual void keyDownHandler(SDL_Event event){
        Command* command=getKeyDownCommand(event);
        if(command){
            command->execute(player_box);
        }
    }
    
    virtual void keyUpHandler(SDL_Event event){
        Command* command=getKeyUpCommand(event);
        if(command){
            command->execute(player_box);
        }
    }
    
    virtual Command* getKeyDownCommand(SDL_Event event){
        keyStates  = (Uint8*) SDL_GetKeyboardState(0);
        
        if(event.key.keysym.scancode==rightButtonCode){
            return buttonRightCommand;
        }
        
        if(event.key.keysym.scancode==leftButtonCode){
            return buttonLeftCommand;
        }
        
        if(event.key.keysym.scancode==downButtonCode){
            return buttonDownCommand;
        }
        
        if(event.key.keysym.scancode==upButtonCode){
            return buttonUpCommand;
        }
        
        if(event.key.keysym.scancode==jumpButtonCode){
            return buttonJumpCommand;
        }
        
        if(event.key.keysym.scancode==sprintButtonCode){
            return buttonSprintCommand;
        }
        
        if(event.key.keysym.scancode==actionButtonCode){
            return buttonActionCommand;
        }
        
        if(event.key.keysym.scancode==attackButtonCode){
            return buttonAttackCommand;
        }
        
        if(event.key.keysym.scancode==shootAButtonCode){
            return buttonShootACommand;
        }
        
        return NULL;
    }
    
    virtual Command* getKeyUpCommand(SDL_Event event){
        keyStates  = (Uint8*) SDL_GetKeyboardState(0);
        
        if(event.key.keysym.scancode==rightButtonCode){
            return buttonRightUpCommand;
        }
        
        if(event.key.keysym.scancode==leftButtonCode){
            return buttonLeftUpCommand;
        }
        
        if(event.key.keysym.scancode==downButtonCode){
            return buttonDownUpCommand;
        }
        
        if(event.key.keysym.scancode==upButtonCode){
            return buttonUpUpCommand;
        }
        
        if(event.key.keysym.scancode==jumpButtonCode){
            return buttonJumpUpCommand;
        }
        
        if(event.key.keysym.scancode==sprintButtonCode){
            return buttonSprintUpCommand;
        }
        
        if(event.key.keysym.scancode==actionButtonCode){
            return buttonActionUpCommand;
        }
        
        if(event.key.keysym.scancode==attackButtonCode){
            return buttonAttackUpCommand;
        }
        
        if(event.key.keysym.scancode==shootAButtonCode){
            return buttonShootAUpCommand;
        }
        
        return NULL;
    }
    
    virtual std::string getStateID() const{
        return s_playID;
    }
    
private:
    const std::string s_playID="PLAY";
    
};


#endif /* PlayState_h */
