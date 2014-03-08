//
//  MySprite.h
//  jumper-x
//
//  Created by Declan on 14-3-1.
//
//

#ifndef __jumper_x__MySprite__
#define __jumper_x__MySprite__

#include "cocos2d.h"

class MySprite : public cocos2d::CCSprite {
    
public:
    void onEnter();
    void adjustScale(float origin=MAXFLOAT);
    float globalWidth();
    float globalHeight();
    
};

#endif /* defined(__jumper_x__MySprite__) */
