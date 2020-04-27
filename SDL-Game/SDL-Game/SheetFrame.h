//
//  SheetFrame.h
//  SDL-Game
//
//  Created by ngchenghow on 30/01/2019.
//  Copyright © 2019 ngchenghow. All rights reserved.
//

#ifndef SheetFrame_h
#define SheetFrame_h

class SheetFrame{
public:
    std::map<int,int> sheetFrames;
    std::map<int,bool> stateLoop;
    
    SheetFrame(){
        sheetFrames[0]=1;
    }
    
    void setFrame(int stateID,int frame,bool loop){
        sheetFrames[stateID]=frame;
        stateLoop[stateID]=loop;
    }
    
    int getFrame(int stateID){
        return sheetFrames[stateID];
    }
    
    bool getLoop(int stateID){
        return stateLoop[stateID];
    }
    
};
#endif /* SheetFrame_h */
