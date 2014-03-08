//
//  HelpLayer.cpp
//  jumper-x
//
//  Created by Declan on 14-2-28.
//
//

#include "HelpLayer.h"
#include "GlobalDefine.h"
#include "GameControl.h"
#include "CCControlButton.h"

USING_NS_CC;
USING_NS_CC_EXT;

HelpLayer * HelpLayer::create()
{
    HelpLayer *pRet = new HelpLayer();
    if (pRet && pRet->initWithColor(ccc4(0, 0, 0, 120), kScreenWidth, kScreenHeight))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {

        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

void HelpLayer::onEnter()
{
    CCLayerColor::onEnter();
    this->setTouchEnabled(true);
    GameControl::pauseGame();
    
    CCSprite *block = CCSprite::create(RES_HelpBlock);
    block->setScale(kScaleFactorX);
    this->addChild(block);
    block->setPosition(ccp(kScreenWidth*3/2, kScreenHeight/2));
    block->setTag(20);
    
    CCControlButton *backBnt = CCControlButton::create("Back", "Verdana-Bold", 24*kScaleFactorX);
    this->addChild(backBnt);
    backBnt->setPosition(ccp(kScreenWidth/2, kScreenHeight/8));
    backBnt->setScale(0);
    backBnt->setTag(40);
    backBnt->addTargetWithActionForControlEvents(this, cccontrol_selector(HelpLayer::back), CCControlEventTouchUpInside);
    
    CCMoveTo *action = CCMoveTo::create(0.5, ccp(kScreenWidth/2, kScreenHeight/2));
    block->runAction(action);
    
    CCScaleTo *showBack = CCScaleTo::create(0.5, 1);
    backBnt->runAction(showBack);

}

void HelpLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
}

bool HelpLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCControlButton *btn = (CCControlButton *)this->getChildByTag(40);
    btn->ccTouchBegan(pTouch, pEvent);
    return true;
}

void HelpLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCControlButton *btn = (CCControlButton *)this->getChildByTag(40);
    btn->ccTouchMoved(pTouch, pEvent);
}

void HelpLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCControlButton *btn = (CCControlButton *)this->getChildByTag(40);
    btn->ccTouchEnded(pTouch, pEvent);
}

void HelpLayer::back()
{
    CCNode *block = this->getChildByTag(20);
    CCMoveTo *moveBack = CCMoveTo::create(0.5, ccp(kScreenWidth*3/2, kScreenHeight/2))
    ;
    CCCallFunc *call = CCCallFunc::create(this, callfunc_selector(HelpLayer::continueGame));
    CCAction * act = CCSequence::create(moveBack, call, NULL);
    block->runAction(act);
    
    CCNode *backBtn = this->getChildByTag(40);
    CCScaleTo *hideBack = CCScaleTo::create(0.5, 0);
    backBtn->runAction(hideBack);
}

void HelpLayer::continueGame()
{
    GameControl::resumeGame();
    this->removeFromParent();
}

