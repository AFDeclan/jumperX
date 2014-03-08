//
//  SkyLayerNear.h
//  jumper-x
//
//  Created by Declan on 14-2-28.
//
//

#ifndef __jumper_x__SkyLayerNear__
#define __jumper_x__SkyLayerNear__

#include "ScrollLayer.h"

class SkyLayerNear : public ScrollLayer {
    
private:
    cocos2d::CCLayerColor * unitLayer(float baseHeight);
    cocos2d::CCSprite * cloud(float low, float high);
    
public:
    CREATE_FUNC(SkyLayerNear);
};

#endif /* defined(__jumper_x__SkyLayerNear__) */
