#ifndef Graphic_h
#define Graphic_h

#include <iostream>
#include <map>
#include "SDL2/SDL.h"
#include "TextureManager.h"
#include "SheetFrame.h"

class Graphic
{
public:
    std::map<std::string,Graphic*> children;
    
    Graphic* parent;
    Graphic* stage;
    std::string instanceID="";
    
    float x=0;
    float y=0;
    float stageWidth=0;
    float stageHeight=0;
    
    float width=0;
    float height=0;
    
    double angle=0;
    int rotateX=0;
    int rotateY=0;
    
    int stateID=0;
    int currentFrame=0;
    SheetFrame* sheet=NULL;
    int flip=0;
    
    Graphic(std::string textureID){
        this->textureID=textureID;
    }
    
    ~Graphic(){
        
    }
    
    Graphic(){
        
    }
    
    void setSheet(){
        if(sheet==NULL){
            sheet=new SheetFrame();
        }
    }
    
    void setStateIDFrame(int stateID,int frame,bool loop){
        if(!sheet){
            return;
        }
        sheet->setFrame(stateID,frame,loop);
//        printf("set frame");
    }
    
    void setStateID(int stateID){
        if(this->stateID!=stateID){
            this->stateID=stateID;
            this->currentFrame=0;
        }
    }
    
    std::string getInstanceID(){
        return instanceID;
    }
    
    bool initTexture(std::string fileName,std::string id,int w,int h,SDL_Renderer* pRenderer,bool cacheSurface){
        bool t=TheTextureManager::Instance()->load(fileName,id,pRenderer,cacheSurface);
        TheTextureManager::Instance()->setFrameSize(id,w,h);
        return t;
    }
    
    void unloadTexture(std::string id){
        TheTextureManager::Instance()->unload(id);
    }
    
    void stop(){
        stopFrame=true;
    }
    
    void gotoAndStop(int frame){
        stopFrame=true;
        currentFrame=frame;
    }
    
    void play(){
        stopFrame=false;
    }
    
    virtual void update(){
        updateFrame();
        updateChildren();
    }
    
    void updateFrame(){
        if(textureID!="" && !stopFrame && sheet){
            this->currentFrame++;
            int f=sheet->getFrame(this->stateID);
            if((currentFrame+1)>=f){
                if(sheet->getLoop(this->stateID)){
                    currentFrame=0;
                }else{
                    currentFrame=f-1;
                }
            }
        }
    }
    
    virtual void draw(SDL_Renderer* renderer){
        if(textureID!=""){
            TheTextureManager::Instance()->draw(textureID,this->getScreenX(),this->getScreenY(),renderer,this->stateID,this->currentFrame,angle,rotateX,rotateY,this->flip,this->width,this->height);
        }
        drawChildren(renderer);
    }
    
    void updateChildren(){
        //update children
        std::map<std::string,Graphic*>::iterator it;
        
        for (it = children.begin(); it != children.end(); it++)
        {
            Graphic* g=it->second;
            g->update();
        }
    }
    
    void drawChildren(SDL_Renderer* renderer){
        std::map<std::string,Graphic*>::iterator it;
        for (it = children.begin(); it != children.end(); it++)
        {
            Graphic* g=it->second;
            g->draw(renderer);
        }
    }
    
    Graphic* addChild(Graphic* child){
        std::string id=child->getInstanceID();
        children[id]=child;
        child->setParent(this);
        return child;
    }
    
    void removeChild(std::string childID){
        std::map<std::string,Graphic*>::iterator it;
        it=children.find(childID);
        
        if(it!=children.end()){
            children.erase(it);
        }
    }
    
    void removeAllChild(){
        std::map<std::string,Graphic*>::iterator it;
        for (it = children.begin(); it != children.end(); it++)
        {
            Graphic* g=it->second;
            delete g;
        }
        children.clear();
    }
    
    void removeChild(Graphic* child){
        std::string id=child->getInstanceID();
        removeChild(id);
    }
    
    Graphic* getChild(std::string childID){
        Graphic* obj=children.at(childID);
        return obj;
    }
   
    virtual void cleanData(){
        textureID="";
        std::map<std::string,Graphic*>::iterator it;
        
        for (it = children.begin(); it != children.end(); it++)
        {
            Graphic* g=it->second;
            g->cleanData();
        }
    }
    
    //getter and setter
    
    void setStageWidth(float width){
        stage->stageWidth=width;
    }
    
    void setStageHeight(float height){
        stage->stageHeight=height;
    }
    
    float getStageWidth(){
        return stage->stageWidth;
    }
    
    float getStageHeight(){
        return stage->stageHeight;
    }
    
    float getWidth(){
        return this->width;
    }
    
    float getHeight(){
//        return TextureManager::Instance()->m_height[this->textureID];
        return this->height;
    }
    
    float getX(){
        return x;
    }
    
    float getY(){
        return y;
    }
    
    float getCenterX(){
        return x+this->getWidth()/2;
    }
    
    float getCenterY(){
        return y+this->getHeight()/2;
    }
    
    float getScreenX(){
        return x+stage->getX();
    }
    
    float getScreenY(){
        return y+stage->getY();
    }
    
    std::string getTextureID(){
        return textureID;
    }
    
private:
    std::string textureID="";
    bool stopFrame=false;
    
    void setParent(Graphic* parent){
        this->parent=parent;
        this->stage=parent->stage;
    }
    
};

#endif /* Graphic_h */
