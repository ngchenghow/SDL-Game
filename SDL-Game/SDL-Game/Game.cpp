
#include "Game.h"
#include <iostream>
#include "Graphic.h"
#include "stdlib.h"
#include "GameState.h"
#include "GameStateMachine.h"
#include "MenuState.h"
#include "PlayState.h"

Game* Game::s_pInstance = 0;

GameStateMachine* stateMachine;
bool mousePressed=false;
bool mouseClicked=false;

void Game::init(const char* title,int xpos,int ypos,int width,int height,bool fullscreen,bool resizable)
{
    int flags = 0;
    if(fullscreen){
        flags=SDL_WINDOW_FULLSCREEN;
    }
    
    if(SDL_Init(SDL_INIT_EVERYTHING)==0)
    {
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(window)
        {
            //init window
            windowID = SDL_GetWindowID(window);
            SDL_SetWindowResizable(window,resizable?SDL_TRUE:SDL_FALSE);
        }
        
        //init renderer
        renderer = SDL_CreateRenderer(window,-1,0);
        if(renderer){
            SDL_SetRenderDrawColor(renderer,255,255,255,255);
        }
        
        initGraphics();
        //init stage
        stageWidth=width;
        stageHeight=height;
        stage=NULL;
        resetStage();
        
        stateMachine=new GameStateMachine();
        stateMachine->pushState(new MenuState());
        
        isRunning=true;
    }else{
        isRunning=false;
    }
}

void Game::resetStage(){
    if(stage!=NULL){
        delete stage;
    }
    stage=new Graphic();
    stage->stage=stage;
    stage->setStageWidth(stageWidth);
    stage->setStageHeight(stageHeight);
}

void Game::initGraphics(){
    
    stage->initTexture("./assets/play_btn.png","play_btn",100,50,renderer,false);
    stage->initTexture("./assets/char-1.png","player_box",120,141,renderer,false);
    stage->initTexture("./assets/char.png","grey_box",65,120,renderer,false);
//    stage->initTexture("./assets/char-sheet.png","char_sheet",32,32,renderer,false);
    stage->initTexture("./assets/char-0001.png","char_sheet",96,64,renderer,false);
    
}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    
    switch(event.type){
        case SDL_QUIT:
            isRunning=false;
            break;
        
        case SDL_MOUSEBUTTONDOWN:
            mousePressed=true;
            mouseDownHandler();
        break;
            
        case SDL_MOUSEBUTTONUP:
            if(mousePressed){
                clickHandler();
            }
            mousePressed=false;
            mouseUpHandler();
        break;
            
        case SDL_MOUSEMOTION:
            mouseMotionHandler();
            
        case SDL_KEYDOWN:
            keyDownHandler(event);
        break;
            
        case SDL_KEYUP:
            keyUpHandler(event);
        break;
          
        case SDL_WINDOWEVENT:{
            if(event.window.windowID==windowID){
                switch(event.window.event){
                    case SDL_WINDOWEVENT_SIZE_CHANGED:{
//                        int width=event.window.data1;
//                        int height=event.window.data2;
                        //use this width and height to resize items in game
                        
                        break;
                    }
                }
            }
            break;
        }
        default:
            break;
    }
    
}

void Game::clickHandler()
{
    stateMachine->clickHandler();
}

void Game::mouseDownHandler()
{
    stateMachine->mouseDownHandler();
}

void Game::mouseUpHandler()
{
    stateMachine->mouseUpHandler();
}

void Game::mouseMotionHandler()
{
    stateMachine->mouseMotionHandler();
}

void Game::keyDownHandler(SDL_Event event)
{
    stateMachine->keyDownHandler(event);
}

void Game::keyUpHandler(SDL_Event event)
{
    stateMachine->keyUpHandler(event);
}

void Game::update()
{
    stateMachine->update();
    //delay time
}


void Game::render()
{
    stateMachine->render();
}

unsigned int oldt=SDL_GetTicks();
void Game::timeDelay()
{
    unsigned int newt=SDL_GetTicks();
    unsigned int dt=newt-oldt;
    
    if(dt<=(1000/60)){
        SDL_Delay((1000/60)-dt);
    }
//    else{
//        printf("slow %d\n",dt);
//    }
    
    oldt=newt;
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

Graphic* Game::getStage(){
    return stage;
}

GameStateMachine* Game::getStateMachine(){
    return stateMachine;
}
