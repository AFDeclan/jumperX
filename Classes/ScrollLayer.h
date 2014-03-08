//
//  ScrollLayer.h
//  jumper-x
//
//  Created by Declan on 14-2-28.
//
//

#ifndef __jumper_x__ScrollLayer__
#define __jumper_x__ScrollLayer__

#include "cocos2d.h"
#include "MyLayer.h"

class ScrollLayer : public MyLayer {
    
private:
    
    CCLayer *_upLayer, *_downLayer;
    
    float _curBaseHeight;
    
    void myInit();

protected:
    
    virtual cocos2d::CCLayerColor * unitLayer(float baseHeight) = 0;
    
public:
    
    bool init();
    
    //return whether up down switch
    bool scrollDown(float dy);
    
    void reset();
};

#endif /* defined(__jumper_x__ScrollLayer__) */
