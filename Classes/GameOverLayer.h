//
//  GameOverLayer.h
//  jumper-x
//
//  Created by Declan on 14-2-28.
//
//

#ifndef __jumper_x__GameOverLayer__
#define __jumper_x__GameOverLayer__

#include "cocos-ext.h"

class GameOverLayer : public cocos2d::CCLayerColor {
    
private:
    float _score, _best;
    
    void onEnter();
    void registerWithTouchDispatcher();
    bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
public:
    static GameOverLayer *create();
    void show(float score, float best);
    void toRestart();
    void toShare();
    void restart();
};

#endif /* defined(__jumper_x__GameOverLayer__) */
