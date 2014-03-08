//
//  SkyLayerFar.h
//  jumper-x
//
//  Created by Declan on 14-2-28.
//
//

#ifndef __jumper_x__SkyLayerFar__
#define __jumper_x__SkyLayerFar__

#include "ScrollLayer.h"

class SkyLayerFar : public ScrollLayer {
    
private:
    
    cocos2d::CCLayerColor * unitLayer(float baseHeight);
    
    cocos2d::CCSprite * cloud(float low, float high);
    
public:
    
    CREATE_FUNC(SkyLayerFar);
};

#endif /* defined(__jumper_x__SkyLayerFar__) */
