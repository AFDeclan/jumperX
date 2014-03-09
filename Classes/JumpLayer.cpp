//
//  JumpLayer.cpp
//  jumper-x
//
//  Created by Declan on 14-2-28.
//
//

#include "JumpLayer.h"
#include "GlobalDefine.h"
#include "FloorGenerator.h"
#include "Jumper.h"
#include "GameScene.h"

USING_NS_CC;

static long exitTime = 0;

long millisecondNow()
{
    struct cc_timeval now;
    CCTime::gettimeofdayCocos2d(&now, NULL);
    return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

bool JumpLayer::init()
{
    if (!ScrollLayer::init()) return false;
    setTouchEnabled(true);
    setKeypadEnabled(true);
    touching = false;
    return true;
}

CCLayerColor * JumpLayer::unitLayer(float baseHeight)
{
    CCLayerColor *layer = CCLayerColor::create(ccc4(1,1,1,0), kDesignWidth, kDesignHeight);
    layer->setAnchorPoint(ccp(0, 0));
    int zorder = 20;
    while (FloorGenerator::nextHeight < baseHeight + kDesignHeight) {
        Floor *next = FloorGenerator::nextFloor(baseHeight);
        next->setZOrder(zorder--);
        layer->addChild(next);
        
    }
    return layer;
}

void JumpLayer::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    Jumper *jumper = Jumper::theJumper();
    touching = true;
    if (jumper->getWalkingFloor()) {
        jumper->startPower();
    }
}

void JumpLayer::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    Jumper *jumper = Jumper::theJumper();
    touching = false;
    if (jumper->jump()) {
        //hint
        this->hint();
    }
}

void JumpLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this, 0);
}

void JumpLayer::hint()
{
    GameScene::scene()->hint();
}

void JumpLayer::keyBackClicked()
{
    long now = millisecondNow();
    if (now - exitTime < 1400 && now > exitTime) {
        CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
#endif
    } else {
        exitTime = now;
        GameScene::scene()->hintExit();
    }
}

void JumpLayer::keyMenuClicked()
{
//    GameScene::scene()->showMenu();
}
