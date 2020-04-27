//
//  GameLevelParser.h
//  2D-Game-Engine
//
//  Created by ngchenghow on 14/12/2018.
//  Copyright © 2018 ngchenghow. All rights reserved.
//

#ifndef GameLevelParser_h
#define GameLevelParser_h

#include <iostream>
#include <vector>
#include "tinyxml.h"
#include "Vector2D.h"
#include "Block.h"
#include "Quad.h"
#include "Line.h"

using namespace models;

class GameLevelParser
{
public:
    bool parseLevelXML(const char* xmlFile,std::vector<Quad*>* quads,std::vector<Line*>* lines){
        TiXmlDocument xmlDoc;
        
        if(!xmlDoc.LoadFile(xmlFile))
        {
            std::cerr << xmlDoc.ErrorDesc() << "\n";
            return false;
        }
        
        TiXmlElement* pRoot = xmlDoc.RootElement();
        TiXmlElement* pPoint = 0;
        
        int pointCounter=0;
        std::vector<Block*> blocks;
        
        for(TiXmlElement* e=pRoot->FirstChildElement(); e!= NULL; e=e->NextSiblingElement())
        {
            if(strcmp(e->Value(),"blocks")==0){
                
                for(TiXmlElement* f=e->FirstChildElement(); f!= NULL; f=f->NextSiblingElement())
                {
                    int jumpy=0;
                    int weak=0;
                    int water=0;
                    int wet=0;
                    int sand=0;
                    int ctop=1;
                    int cleft=1;
                    int cright=1;
                    int cbottom=1;
                    
                    f->Attribute("jumpy",&jumpy);
                    f->Attribute("weak",&weak);
                    f->Attribute("water",&water);
                    f->Attribute("wet",&wet);
                    f->Attribute("sand",&sand);
                    
                    f->Attribute("ctop",&ctop);
                    f->Attribute("cleft",&cleft);
                    f->Attribute("cright",&cright);
                    f->Attribute("cbottom",&cbottom);
                    
                    if(wet==0)wet=80;
                    //blocks
                    for(TiXmlElement* g=f->FirstChildElement(); g!= NULL; g=g->NextSiblingElement())
                    {
                        //points
                        int x=0;
                        int y=0;
                        
//                        printf("a:%d",jumpy);
                        pPoint = g;
                        parsePoint(pPoint,pointCounter,&x,&y);
                        Block* block=new Block(new Vector2D(x,y),jumpy,weak,water,wet,sand);
                        block->ctop=ctop;
                        block->cleft=cleft;
                        block->cright=cright;
                        block->cbottom=cbottom;
                        
                        blocks.push_back(block);
                        
                        
                    }
                }
            }else if(strcmp(e->Value(),"lines")==0){
                for(TiXmlElement* f=e->FirstChildElement(); f!= NULL; f=f->NextSiblingElement())
                {
                    int x1=0;
                    int y1=0;
                    int x2=0;
                    int y2=0;
                    int amt=0;
                    int slope=0;
                    int gothou=0;
                    int wind=0;
                    int ladder=0;
                    
                    f->Attribute("x1",&x1);
                    f->Attribute("y1",&y1);
                    f->Attribute("x2",&x2);
                    f->Attribute("y2",&y2);
                    f->Attribute("amt",&amt);
                    f->Attribute("slope",&slope);
                    f->Attribute("gothou",&gothou);
                    f->Attribute("wind",&wind);
                    f->Attribute("ladder",&ladder);
                    
                    if(amt==0)amt=1;
                    Line* line;
                    
                    if(slope==0){
                        for(int i=0;i<amt;i++){
                            line=new Line(new Vector2D(x1,y1+i),new Vector2D(x2,y2+i),amt,gothou,wind,ladder);
                            lines->push_back(line);
                        }
                    }else{
                        for(int i=0;i<amt;i++){
                            line=new Line(new Vector2D(x1+i,y1),new Vector2D(x2+i,y2),amt,gothou,wind,ladder);
                            lines->push_back(line);
                        }
                    }
                    
                }
            }
        }
        
        int c=0;
        
        Vector2D* p1=NULL;
        Vector2D* p2=NULL;
        Vector2D* p3=NULL;
        Vector2D* p4=NULL;
        
        for(std::vector<Block*>::iterator it = blocks.begin(); it != blocks.end(); ++it) {
            Block* item=*it;
            
            if(c%4==0){
                p1=item->p;
            }else if(c%4==1){
                p2=item->p;
            }else if(c%4==2){
                p3=item->p;
            }else if(c%4==3){
                p4=item->p;
            }
            
            c++;
            
            if(c%4==0 && c!=0){
                Quad* q=new Quad(p1,p2,p3,p4,item->jumpy,item->weak,item->water,item->wet,item->sand);
                q->ctop=item->ctop;
                q->cleft=item->cleft;
                q->cright=item->cright;
                q->cbottom=item->cbottom;
                
                quads->push_back(q);
            }
        }
        
        
//        for(std::vector<Vector2D*>::iterator it = points->begin(); it != points->end(); ++it) {
//            Vector2D* p=*it;
//            printf("%d",p->x);
//        }
        
        return true;
    }
    
    
private:
    void parsePoint(TiXmlElement* point,int index,int* x,int* y){
        int sx=0;
        int sy=0;
        point->Attribute("x",&sx);
        point->Attribute("y",&sy);
        
        *x=sx;
        *y=sy;
        
    }
};

#endif /* GameLevelParser_h */
