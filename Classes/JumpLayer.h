//
//  JumpLayer.h
//  jumper-x
//
//  Created by Declan on 14-2-28.
//
//

#ifndef __jumper_x__JumpLayer__
#define __jumper_x__JumpLayer__

#include "ScrollLayer.h"


class JumpLayer : public ScrollLayer {

private:
    
    bool init();
    cocos2d::CCLayerColor * unitLayer(float baseHeight);
    void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    void registerWithTouchDispatcher();
    void hint();
    
public:
    
    CREATE_FUNC(JumpLayer);
    void keyBackClicked();
    void keyMenuClicked();
    
    bool touching;
};


#endif /* defined(__jumper_x__JumpLayer__) */
