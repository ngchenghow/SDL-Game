//
//  MenuState.h
//  2D-Game-Engine
//
//  Created by ngchenghow on 12/12/2018.
//  Copyright © 2018 ngchenghow. All rights reserved.
//

#ifndef MenuState_h
#define MenuState_h

#include "GameState.h"
#include "EditorState.h"
#include "GameStateMachine.h"

class MenuState:public GameState
{
public:
    
    virtual void update(){
        Game::Instance()->getStage()->update();
    }
    
    virtual void render(){
        Game* game=Game::Instance();
        Graphic* stage=game->getStage();
        
        SDL_RenderClear(game->renderer);
        stage->draw(game->renderer);
        
        SDL_RenderPresent(game->renderer);
    }
    
    virtual bool onEnter(){
        
        Game* game=Game::Instance();
        Graphic* stage=game->getStage();
        
        play_btn=new Graphic("play_btn");
        play_btn->instanceID="play_btn";
        play_btn->width=100;
        play_btn->height=50;
        stage->addChild(play_btn);
        
//        play_btn->gotoAndStop(0);
        
        return true;
    }
    
    virtual bool onExit(){
        Game::Instance()->getStage()->removeChild("play_btn");
        Game::Instance()->resetStage();
        return true;
    }
    
    virtual void clickHandler(){
        int mx;
        int my;
        SDL_GetMouseState(&mx,&my);
        
        if(mx>play_btn->x && my>play_btn->y && mx<play_btn->x+play_btn->getWidth() && my<play_btn->y+play_btn->getHeight()){
            Game::Instance()->getStateMachine()->toPlay();
//            Game::Instance()->getStateMachine()->changeState(new PlayState());
//            Game::Instance()->getStateMachine()->changeState(new EditorState());
        }
    }
    
    virtual void mouseMotionHandler(){
        
    }
    
    virtual void mouseDownHandler(){
        
    }
    
    virtual void mouseUpHandler(){
        
    }
    
    virtual void keyDownHandler(SDL_Event event){
        
    }
    
    virtual void keyUpHandler(SDL_Event event){
        
    }
    
    virtual std::string getStateID() const{
        return s_menuID;
    }
    
private:
    const std::string s_menuID="MENU";
    Graphic* play_btn;
};

#endif /* MenuState_h */
