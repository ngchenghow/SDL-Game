
#ifndef Game_hpp
#define Game_hpp

#include "SDL2/SDL.h"
#include <stdio.h>
#include "Graphic.h"
#include "GameStateMachine.h"

class Game{
  
public:
    SDL_Renderer* renderer;
    
    ~Game();
    
    void init(const char* title, int xpos,int ypos,int width,int height,bool fullscreen,bool resizable);
    void handleEvents();
    
    void update();
    void render();
    void clean();
    Graphic* getStage();
    void clickHandler();
    void mouseDownHandler();
    void mouseUpHandler();
    void mouseMotionHandler();
    void keyDownHandler(SDL_Event event);
    void keyUpHandler(SDL_Event event);
    void timeDelay();
    void resetStage();
    
    GameStateMachine* getStateMachine();
    
    bool running(){
        return isRunning;
    }
    
    static Game* Instance()
    {
        if(s_pInstance == 0){
            s_pInstance = new Game();
            return s_pInstance;
        }
        return s_pInstance;
    }
    
    
private:
    bool isRunning;
    SDL_Window* window;
    
    Uint32 windowID;
    Graphic* stage;
    int stageWidth;
    int stageHeight;
    std::map <std::string,Graphic*> childsMap;
    
    Game(){}
    static Game* s_pInstance;
    void initGraphics();
};

#endif /* Game_hpp */
