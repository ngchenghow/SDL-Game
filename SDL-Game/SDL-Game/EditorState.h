//
//  EditorState.h
//  SDL-Game
//
//  Created by ngchenghow on 17/12/2018.
//  Copyright © 2018 ngchenghow. All rights reserved.
//

#ifndef EditorState_h
#define EditorState_h

#include <iostream>
#include <fstream>
#include "PlayState.h"

class EditorState:public PlayState{
public:
    
    float editorX=0;
    float editorY=0;
    int dragStartX=-1;
    int dragStartY=-1;
    bool mousePressed=false;
    
    bool handMove=false;
    Uint8 *keyStates;
    
    Quad* selectedQuad=NULL;
    Vector2D* selectedPoint=NULL;
    Line* selectedLine=NULL;
    
    std::vector<Vector2D*> newPoints;
    std::vector<Vector2D*> newPointsLine;
    
    bool addQuadPress=false;
    bool addLinePress=false;
    
    EditorState(){
        PlayState();
    }
    
    virtual void update() override{
        PlayState::update();
//        cameraUpdate();
    }
    
    virtual void render() override{
//        PlayState::render();
        Game* game=Game::Instance();
        Graphic* stage=game->getStage();
        SDL_Renderer* renderer=game->renderer;

        SDL_RenderClear(renderer);

        stage->draw(renderer);

        drawPlatforms(renderer,stage);
        drawPoints(renderer,stage);
        
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF );
        drawNewPoints(renderer,stage);

        //draw selected
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF );
        drawSelected(renderer,stage);

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderPresent(renderer);
    }
    
    virtual bool onEnter() override{
        return PlayState::onEnter();
//        PlayState::onEnter();
//
//        Game* game=Game::Instance();
//        Graphic* stage=game->getStage();
//
//        editorX=stage->getStageWidth()/2;
//        editorY=stage->getStageHeight()/2;
//
//        return true;
        
    }
    
    void drawSelected(SDL_Renderer* renderer,Graphic* stage){
        
        int rad=5;
        
        Quad* rect=selectedQuad;
        Line* line=selectedLine;
        
        if(rect!=NULL){
            DrawCircle(renderer,rect->p1->x+stage->getX(),rect->p1->y+stage->getY(),rad);
            DrawCircle(renderer,rect->p2->x+stage->getX(),rect->p2->y+stage->getY(),rad);
            DrawCircle(renderer,rect->p3->x+stage->getX(),rect->p3->y+stage->getY(),rad);
            DrawCircle(renderer,rect->p4->x+stage->getX(),rect->p4->y+stage->getY(),rad);
        }else if(line!=NULL){
            DrawCircle(renderer,line->p1->x+stage->getX(),line->p1->y+stage->getY(),rad);
            DrawCircle(renderer,line->p2->x+stage->getX(),line->p2->y+stage->getY(),rad);
        }
        
    }
    
    void drawPoints(SDL_Renderer* renderer,Graphic* stage){
        
        int rad=5;
        
        for(std::vector<Quad*>::iterator it = quads.begin(); it != quads.end(); ++it) {
            Quad* rect=*it;
            
            DrawCircle(renderer,rect->p1->x+stage->getX(),rect->p1->y+stage->getY(),rad);
            DrawCircle(renderer,rect->p2->x+stage->getX(),rect->p2->y+stage->getY(),rad);
            DrawCircle(renderer,rect->p3->x+stage->getX(),rect->p3->y+stage->getY(),rad);
            DrawCircle(renderer,rect->p4->x+stage->getX(),rect->p4->y+stage->getY(),rad);
            
        }
        
        for(std::vector<Line*>::iterator it2=lines.begin();it2!=lines.end();++it2){
            Line* item=*it2;
            
            Vector2D* p1=item->p1;
            Vector2D* p2=item->p2;
            
            DrawCircle(renderer,p1->x+stage->getX(),p1->y+stage->getY(),rad);
            DrawCircle(renderer,p2->x+stage->getX(),p2->y+stage->getY(),rad);
            
        }
        
    }
    
    void drawNewPoints(SDL_Renderer* renderer,Graphic* stage){
        int rad=5;
        
        for(std::vector<Vector2D*>::iterator it3=newPoints.begin();it3!=newPoints.end();++it3){
            Vector2D* p=*it3;
            DrawCircle(renderer,p->x+stage->getX(),p->y+stage->getY(),rad);
        }
        
    }
    
    void DrawCircle(SDL_Renderer* renderer , int _x, int _y, int radius)
    {
        int x1=_x-radius;
        int y1=_y-radius;
        int x2=_x+radius;
        int y2=_y-radius;
        int x3=_x+radius;
        int y3=_y+radius;
        int x4=_x-radius;
        int y4=_y+radius;
        
        SDL_RenderDrawLine(renderer,x1,y1,x2,y2);
        SDL_RenderDrawLine(renderer,x2,y2,x3,y3);
        SDL_RenderDrawLine(renderer,x3,y3,x4,y4);
        SDL_RenderDrawLine(renderer,x4,y4,x1,y1);
    }
    
    float getCamFollowX() override{
        return editorX;
    }
    
    float getCamFollowY() override{
        return editorY;
    }
    
    virtual bool onExit() override{
        return PlayState::onExit();
    }
    
    virtual void clickHandler() override{
        
        int mx,my;
        SDL_GetMouseState(&mx, &my);
        
        if(addQuadPress){
            Game* game=Game::Instance();
            Graphic* stage=game->getStage();
            
            pushPoint(mx-stage->getX(),my-stage->getY());
        }else if(addLinePress){
            Game* game=Game::Instance();
            Graphic* stage=game->getStage();
            
            pushPointLine(mx-stage->getX(),my-stage->getY());
        }
    }
    
    virtual void mouseDownHandler() override{
        SDL_GetMouseState(&dragStartX,&dragStartY);
        mousePressed=true;
        
        collisionPoint();
        
    }
    
    void collisionPoint(){
        int mx;
        int my;
        
        SDL_GetMouseState(&mx,&my);
        float radSquard=25;
        
        Game* game=Game::Instance();
        Graphic* stage=game->getStage();
        
        for(std::vector<Quad*>::iterator it = quads.begin(); it != quads.end(); ++it) {
            Quad* rect=*it;
            float d1=disSquare(new Vector2D(mx-stage->getX(),my-stage->getY()),rect->p1);
            float d2=disSquare(new Vector2D(mx-stage->getX(),my-stage->getY()),rect->p2);
            float d3=disSquare(new Vector2D(mx-stage->getX(),my-stage->getY()),rect->p3);
            float d4=disSquare(new Vector2D(mx-stage->getX(),my-stage->getY()),rect->p4);
            
            if(d1<=radSquard){
                selectedPoint=rect->p1;
                selectedQuad=rect;
                selectedLine=NULL;
                return;
            }else if(d2<=radSquard){
                selectedPoint=rect->p2;
                selectedQuad=rect;
                selectedLine=NULL;
                return;
            }else if(d3<=radSquard){
                selectedPoint=rect->p3;
                selectedQuad=rect;
                selectedLine=NULL;
                return;
            }else if(d4<=radSquard){
                selectedPoint=rect->p4;
                selectedQuad=rect;
                selectedLine=NULL;
                return;
            }
        }
        
        for(std::vector<Line*>::iterator it2=lines.begin();it2!=lines.end();++it2){
            Line* item=*it2;
            
            float d5=disSquare(new Vector2D(mx-stage->getX(),my-stage->getY()),item->p1);
            float d6=disSquare(new Vector2D(mx-stage->getX(),my-stage->getY()),item->p2);
            
            if(d5<=radSquard){
                selectedPoint=item->p1;
                selectedLine=item;
                selectedQuad=NULL;
                return;
            }else if(d6<=radSquard){
                selectedPoint=item->p2;
                selectedLine=item;
                selectedQuad=NULL;
                return;
            }
            
        }
        
        selectedPoint=NULL;
        selectedLine=NULL;
        selectedQuad=NULL;
        
    }
    
    virtual void mouseUpHandler() override{
        mousePressed=false;
    }
    
    virtual void mouseMotionHandler() override{
        int mx;
        int my;
        SDL_GetMouseState(&mx,&my);
        
        if(handMove && mousePressed){
            editorX-=mx-dragStartX;
            editorY-=my-dragStartY;
            SDL_GetMouseState(&dragStartX,&dragStartY);
        }else if(selectedPoint && mousePressed){
            
            Game* game=Game::Instance();
            Graphic* stage=game->getStage();
            
            selectedPoint->x=mx-stage->getX();
            selectedPoint->y=my-stage->getY();
        }
    }
    
    float disSquare(Vector2D* p1,Vector2D* p2){
        float dx=abs(p1->x-p2->x);
        float dy=abs(p1->y-p2->y);
        return dx*dx+dy*dy;
    }
    
    void deleteQuad(Quad* quad){
        if(quad==NULL){
            return;
        }
        std::vector<Quad*>::iterator i = std::find(quads.begin(), quads.end(), quad);
        quads.erase(i);
    }
    
    void deleteLine(Line* line){
        if(line==NULL){
            return;
        }
        std::vector<Line*>::iterator i = std::find(lines.begin(), lines.end(), line);
        lines.erase(i);
    }
    
    virtual float getCamSpeed(float d) override{
        return 1;
    }
    
    virtual void keyDownHandler(SDL_Event event) override{
        
        PlayState::keyDownHandler(event);
        
        if(event.key.keysym.scancode==SDL_SCANCODE_SPACE){
            handMove=true;
        }else if(event.key.keysym.scancode==SDL_SCANCODE_DELETE){
            if(selectedQuad){
                deleteQuad(selectedQuad);
                selectedPoint=0;
                selectedQuad=NULL;
                selectedLine=NULL;
            }else if(selectedLine){
                deleteLine(selectedLine);
                selectedPoint=0;
                selectedQuad=NULL;
                selectedLine=NULL;
            }
        }else if(event.key.keysym.scancode==SDL_SCANCODE_P){
            addQuadPress=true;
        }else if(event.key.keysym.scancode==SDL_SCANCODE_Z){
            saveXML("/Users/ngchenghow/Desktop/level-2.xml");
        }else if(event.key.keysym.scancode==SDL_SCANCODE_T){
            
            if(selectedQuad){
                selectedQuad->ctop=!selectedQuad->ctop;
            }
        }else if(event.key.keysym.scancode==SDL_SCANCODE_F){
            if(selectedQuad){
                selectedQuad->cleft=!selectedQuad->cleft;
            }
        }else if(event.key.keysym.scancode==SDL_SCANCODE_H){
            if(selectedQuad){
                selectedQuad->cright=!selectedQuad->cright;
            }
        }else if(event.key.keysym.scancode==SDL_SCANCODE_G){
            if(selectedQuad){
                selectedQuad->cbottom=!selectedQuad->cbottom;
            }
        }else if(event.key.keysym.scancode==SDL_SCANCODE_N){
            addLinePress=true;
        }else if(event.key.keysym.scancode==SDL_SCANCODE_1){
            if(selectedQuad){
                selectedQuad->water=int(!selectedQuad->water);
            }
        }else if(event.key.keysym.scancode==SDL_SCANCODE_2){
            if(selectedLine){
                selectedLine->ladder=int(!selectedLine->ladder);
                selectedLine->gothou=1;
            }
        }
        
        
    }
    
    void pushPointLine(int x,int y){
        Vector2D* newPoint=new Vector2D(x,y);
        
        newPointsLine.push_back(newPoint);
        int size=(int)newPointsLine.size();
        
        if(size==2){
            lines.push_back(new Line(newPointsLine.at(0),newPointsLine.at(1),1,1,1));
            newPointsLine.clear();
        }
    }
    
    void pushPoint(int x,int y){
        Vector2D* newPoint=new Vector2D(x,y);
        float rad=25;
        
        for(std::vector<Quad*>::iterator it = quads.begin(); it != quads.end(); ++it) {
            Quad* rect=*it;
            
            if(disSquare(newPoint,rect->p1)<=rad){
                newPoint->x=rect->p1->x;
                newPoint->y=rect->p1->y;
            }else if(disSquare(newPoint,rect->p2)<=rad){
                newPoint->x=rect->p2->x;
                newPoint->y=rect->p2->y;
            }else if(disSquare(newPoint,rect->p3)<=rad){
                newPoint->x=rect->p3->x;
                newPoint->y=rect->p3->y;
            }else if(disSquare(newPoint,rect->p4)<=rad){
                newPoint->x=rect->p4->x;
                newPoint->y=rect->p4->y;
            }
            
        }
        
        newPoints.push_back(newPoint);
        int size=(int)newPoints.size();
        
        if(size==4){
            quads.push_back(new Quad(newPoints.at(0),newPoints.at(1),newPoints.at(2),newPoints.at(3)));
            
            newPoints.clear();
        }
    }
    
    virtual void keyUpHandler(SDL_Event event) override{
        PlayState::keyUpHandler(event);
        
        if(event.key.keysym.scancode==SDL_SCANCODE_SPACE){
            handMove=false;
        }else if(event.key.keysym.scancode==SDL_SCANCODE_DELETE){
            
        }else if(event.key.keysym.scancode==SDL_SCANCODE_P){
            addQuadPress=false;
        }else if(event.key.keysym.scancode==SDL_SCANCODE_N){
            addLinePress=false;
        }
    }
    
    void saveXML(std::string filepath){
        std::ofstream myfile;
        myfile.open(filepath);
        myfile << getXMLString();
        myfile.close();
    }
    
    std::string getXMLString(){
        
        std::string xml="<?xml version='1.0' ?>\n";
        xml+="<root>\n";
        xml+="<blocks>\n";
        
        for(std::vector<Quad*>::iterator it = quads.begin(); it != quads.end(); ++it) {
            Quad* item=*it;
            if(item->attach){
                continue;
            }
            float x1=item->p1->x;
            float y1=item->p1->y;
            
            float x2=item->p2->x;
            float y2=item->p2->y;
            
            float x3=item->p3->x;
            float y3=item->p3->y;
            
            float x4=item->p4->x;
            float y4=item->p4->y;
            
            xml+="<block ctop='"+std::to_string(int(item->ctop))+"' cleft='"+std::to_string(int(item->cleft))+"' cright='"+std::to_string(int(item->cright))+"' cbottom='"+std::to_string(int(item->cbottom))+"' water='"+std::to_string(item->water)+"'>\n";
            
            xml+="<point x='"+std::to_string(x1)+"' y='"+std::to_string(y1)+"'/>\n";
            xml+="<point x='"+std::to_string(x2)+"' y='"+std::to_string(y2)+"'/>\n";
            xml+="<point x='"+std::to_string(x3)+"' y='"+std::to_string(y3)+"'/>\n";
            xml+="<point x='"+std::to_string(x4)+"' y='"+std::to_string(y4)+"'/>\n";
            xml+="</block>\n";
        }
        xml+="</blocks>\n";
        
        xml+="<lines>\n";
        for(std::vector<Line*>::iterator it2=lines.begin();it2!=lines.end();++it2){
            Line* item=*it2;
            if(item->attach==true){
                continue;
            }
            float x1=item->p1->x;
            float y1=item->p1->y;
            float x2=item->p2->x;
            float y2=item->p2->y;
            int wind=item->wind;
            int ladder=item->ladder;
            
            xml+="<line x1='"+std::to_string(x1)+"' y1='"+std::to_string(y1)+"' x2='"+std::to_string(x2)+"' y2='"+std::to_string(y2)+"' wind='"+std::to_string(wind)+"' ladder='"+std::to_string(ladder)+"' gothou='0'/>\n";
            
            
            
        }
        xml+="</lines>\n";
        
        xml+="</root>\n";
        return xml;
    }
    
    virtual std::string getStateID() const override{
        return "EDITOR";
    }
    
};

#endif /* EditorState_h */
