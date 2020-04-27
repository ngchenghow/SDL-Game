#ifndef __TEXTURE_MANAGER_H__
#define __TEXTURE_MANAGER_H__

#include <iostream>
#include <map>

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"

class TextureManager
{
public:
    std::map<std::string,SDL_Texture*> m_textureMap;
    std::map<std::string,float> m_width;
    std::map<std::string,float> m_height;
    std::map<std::string,SDL_Surface*> m_surfaceMap;
    
    //load bmp file to texture, get filename, id for texture, and renderer
    bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer,bool cacheSurface){
        //get surface first
        SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());
        if(pTempSurface == NULL){
            return false;
        }
        
        //create texture from surface
        SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
        
        //free surface that is no use anymore
        if(!cacheSurface)
            SDL_FreeSurface(pTempSurface);
        else
            m_surfaceMap[id]=pTempSurface;
        
        //if texture not null
        if(pTexture != NULL){
            //save to map so can get in next time with id
            m_textureMap[id] = pTexture;
            
            SDL_Rect srcRect;
            SDL_QueryTexture(m_textureMap[id], NULL, NULL,&srcRect.w, &srcRect.h);
            
            m_width[id]=srcRect.w;
            m_height[id]=srcRect.h;
            
            return true;
        }
        
        return false;
    }
    
    void setFrameSize(std::string textureID,int width,int height){
        m_width[textureID]=width;
        m_height[textureID]=height;
    }
    
    void unload(std::string textureID){
        std::map<std::string,SDL_Texture*>::iterator it_texture;
        std::map<std::string,int>::iterator it_frame;
        std::map<std::string,float>::iterator it_width;
        std::map<std::string,float>::iterator it_height;
        
        it_texture=m_textureMap.find(textureID);
        
        if(it_texture==m_textureMap.end()){
            return;
        }
        
        m_textureMap.erase(it_texture);
        
        it_width=m_width.find(textureID);
        m_width.erase(it_width);
        
        it_height=m_height.find(textureID);
        m_height.erase(it_height);
        
    }
    
    //draw loaded texture
    void draw(std::string id, int x, int y, SDL_Renderer* pRenderer,int stateID,int frame,double angle,int rotateX=0,int rotateY=0,int flip=0,float collWidth=0,float collHeight=0){
        
        SDL_Rect srcRect;
        SDL_Rect destRect;
        
        SDL_QueryTexture(m_textureMap[id], NULL, NULL,&srcRect.w, &srcRect.h);
        
        int w=m_width[id];
        int h=m_height[id];
        
        srcRect.x = frame*w;
        srcRect.y = stateID*h;
        
        srcRect.w=w;
        srcRect.h=h;
        
        float dw=(w-collWidth);
        float dh=(h-collHeight);
        
        destRect.w = w;
        destRect.h = h;
        destRect.x = x-dw/2;
        destRect.y = y-dh;
        
        SDL_Point rotateCenter={rotateX+int(dw/2),rotateY+int(dh)};
        
        if(!flip){
            SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect,angle, &rotateCenter,SDL_FLIP_NONE);
        }else{
            SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect,angle, &rotateCenter,SDL_FLIP_HORIZONTAL);
        }
        
    }
    
    //draw loaded texture to a frame
    void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE){
        
        SDL_Rect srcRect;
        SDL_Rect destRect;
        
        srcRect.x = width * currentFrame;
        srcRect.y = height * (currentRow - 1);
        srcRect.w = destRect.w = width;
        srcRect.h = destRect.h = height;
        destRect.x = x;
        destRect.y = y;
        
        SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
        
    }
    
    static TextureManager* Instance()
    {
        if(s_pInstance == 0){
            s_pInstance = new TextureManager();
            return s_pInstance;
        }
        
        return s_pInstance;
    }
    
private:
    TextureManager(){}
    static TextureManager* s_pInstance;
    
};

typedef    TextureManager TheTextureManager;
#endif
