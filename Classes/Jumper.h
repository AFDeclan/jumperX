//
//  Jumper.h
//  jumper-x
//
//  Created by Declan on 14-2-28.
//
//

#ifndef __jumper_x__Jumper__
#define __jumper_x__Jumper__

#include "cocos-ext.h"
#include "Floor.h"
#include "JumpLayer.h"
#include "MySprite.h"

USING_NS_CC;

class Jumper : public MySprite {

private:
    CCAction *_walkAction, *_powerAction;
    CCSprite *_powerSprite, *_fartSprite, *_powerFrameSprite;
    CCLayerColor *_powerLine;
    Floor *_walkingFloor;
    bool _needHint, _jumping, _leftWalking, _powering;
    float _vx, _vy, _ax, _ay, _power;
    
    void onEnter();
    void startAnimate();
    void startAnimateJump();
    void startAnimateFall();
    void showPowering();
    void showNotPowering();
    void offFloor();
    ~Jumper();
public:
    JumpLayer *jumpLayer;
    
    static Jumper * theJumper();
    
    CREATE_FUNC(Jumper);
    void myInit();
    bool jump();
    void walk(Floor *floor);
    void fall();
    void startPower();
    void setLeftWalking(bool left);
    Floor * getWalkingFloor();
    float getVy();
    float getPower();
    void update(float delta);

};

#endif /* defined(__jumper_x__Jumper__) */

