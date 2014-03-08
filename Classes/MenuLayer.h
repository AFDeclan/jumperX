//
//  MenuLayer.h
//  jumperX
//
//  Created by Declan on 14-3-3.
//
//

#ifndef __jumperX__MenuLayer__
#define __jumperX__MenuLayer__

#include "cocos-ext.h"

USING_NS_CC_EXT;

class MenuLayer : public cocos2d::CCLayerColor {
    
private:
    void registerWithTouchDispatcher();
    bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
public:
    static MenuLayer * create();
    void onEnter();
    void btnClicked(CCControlButton *btn);
    void back();
    void continueGame();
};

#endif /* defined(__jumperX__MenuLayer__) */
