//
//  MenuLayer.cpp
//  jumper-x
//
//  Created by Declan on 14-2-28.
//
//

#include "MenuLayer.h"
#include "GlobalDefine.h"
#include "GameControl.h"
#include "CCControlButton.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define UDKForMenu(i)  ((i==1)?kUDK_Setting_BgMusic:kUDK_Setting_SoundEffects)

MenuLayer * MenuLayer::create()
{
    MenuLayer *pRet = new MenuLayer();
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

void MenuLayer::onEnter()
{
    CCLayerColor::onEnter();
    this->setTouchEnabled(true);
    GameControl::pauseGame();
    
    CCSprite *block = CCSprite::create(RES_MenuBlock);
    block->setScale(kScaleFactorX);
    this->addChild(block);
    block->setPosition(ccp(kScreenWidth*3/2, kScreenHeight/2));
    block->setTag(20);
    
    for (int i=1; i<=2; i++) {
        const char * title = i == 1? "背景音乐(Bg Music)" : "音效(Sound Effect)";
        CCControlButton *btn = CCControlButton::create(title, "Verdana-Bold", 18);
        btn->setAnchorPoint(ccp(0.5, 0.5));
        block->addChild(btn);
        btn->setTag(i);
        btn->setPosition(ccp(contentWidth(block)/2, contentHeight(block)*i/3));
        CCSprite *check = CCSprite::create(RES_MenuCheck);
        block->addChild(check);
        check->setTag(-i*2);
        check->setVisible(LoadBooleanFromUD(UDKForMenu(i)));
        check->setPosition(ccp(contentWidth(block)/2 - contentWidth(btn)/2-10, contentHeight(block)*i/3));
        btn->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuLayer::btnClicked), CCControlEventTouchUpInside);
    }
    
    CCControlButton *backBnt = CCControlButton::create("Back", "Verdana-Bold", 24*kScaleFactorX);
    this->addChild(backBnt);
    backBnt->setPosition(ccp(kScreenWidth/2, kScreenHeight/8));
    backBnt->setScale(0);
    backBnt->setTag(40);
    backBnt->addTargetWithActionForControlEvents(this, cccontrol_selector(MenuLayer::back), CCControlEventTouchUpInside);
    
    CCMoveTo *action = CCMoveTo::create(0.5, ccp(kScreenWidth/2, kScreenHeight/2));
    block->runAction(action);
    
    CCScaleTo *showBack = CCScaleTo::create(0.5, 1);
    backBnt->runAction(showBack);

}

void MenuLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
}

bool MenuLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    for (int i=1; i<3; i++) {
        CCControlButton *btn = (CCControlButton *)this->getChildByTag(20)->getChildByTag(i);
        btn->ccTouchBegan(pTouch, pEvent);
    }
    CCControlButton *btn = (CCControlButton *)this->getChildByTag(40);
    btn->ccTouchBegan(pTouch, pEvent);
    return true;
}

void MenuLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    for (int i=1; i<3; i++) {
        CCControlButton *btn = (CCControlButton *)this->getChildByTag(20)->getChildByTag(i);
        btn->ccTouchMoved(pTouch, pEvent);
    }
    CCControlButton *btn = (CCControlButton *)this->getChildByTag(40);
    btn->ccTouchMoved(pTouch, pEvent);
}

void MenuLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    for (int i=1; i<3; i++) {
        CCControlButton *btn = (CCControlButton *)this->getChildByTag(20)->getChildByTag(i);
        btn->ccTouchEnded(pTouch, pEvent);
    }
    CCControlButton *btn = (CCControlButton *)this->getChildByTag(40);
    btn->ccTouchEnded(pTouch, pEvent);
}

void MenuLayer::btnClicked(CCControlButton *btn)
{
    int tag = btn->getTag();
    SaveBooleanToUD(UDKForMenu(tag), !LoadBooleanFromUD(UDKForMenu(tag)));
    this->getChildByTag(20)->getChildByTag(-tag*2)->setVisible(LoadBooleanFromUD(UDKForMenu(tag)));
}

void MenuLayer::back()
{
    CCNode *block = this->getChildByTag(20);
    CCMoveTo *moveBack = CCMoveTo::create(0.5, ccp(kScreenWidth*3/2, kScreenHeight/2))
    ;
    CCCallFunc *call = CCCallFunc::create(this, callfunc_selector(MenuLayer::continueGame));
    CCAction * act = CCSequence::create(moveBack, call, NULL);
    block->runAction(act);
    
    CCNode *backBtn = this->getChildByTag(40);
    CCScaleTo *hideBack = CCScaleTo::create(0.5, 0);
    backBtn->runAction(hideBack);
}

void MenuLayer::continueGame()
{
    GameControl::resumeGame();
    this->removeFromParent();
}

