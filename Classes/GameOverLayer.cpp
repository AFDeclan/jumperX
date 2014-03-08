//
//  GameOverLayer.cpp
//  jumper-x
//
//  Created by Declan on 14-2-28.
//
//

#include "GameOverLayer.h"
#include "GlobalDefine.h"
#include "GameControl.h"
#include "CCControlButton.h"
#include "SocialControl.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define Tag_backBtn     40
#define Tag_shareBtn     50

GameOverLayer * GameOverLayer::create()
{
    GameOverLayer *pRet = new GameOverLayer();
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

void GameOverLayer::onEnter()
{
    CCLayerColor::onEnter();
    this->setTouchEnabled(true);
}

void GameOverLayer::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);
}

void GameOverLayer::show(float score, float best)
{
    _score = score;
    _best = best;
    
    CCSprite *block = CCSprite::create(RES_MenuBlock);
    block->setScale(kScaleFactorX);
    this->addChild(block);
    block->setPosition(ccp(kScreenWidth*3/2, kScreenHeight/2));
    block->setTag(20);

    char *str = new char[60];
    sprintf(str, "Score: %.1f", score);
    CCLabelTTF *label1 = CCLabelTTF::create(str, "Verdana-Bold", 24);
    block->addChild(label1);
    label1->setPosition(ccp(contentWidth(block)/2, contentHeight(block)*2/3));
    
    sprintf(str, "Best: %.1f", best);
    CCLabelTTF *label2 = CCLabelTTF::create(str, "Verdana-Bold", 18);
    block->addChild(label2);
    label2->setPosition(ccp(contentWidth(block)/2, contentHeight(block)/3));

    delete [] str;
    
    CCControlButton *backBtn = CCControlButton::create(CCScale9Sprite::create(RES_RetryBtn));
    backBtn->setPreferredSize(CCSizeMake(96, 96));
    backBtn->setScale(0.5*kScaleFactorX);
    this->addChild(backBtn);
    backBtn->setPosition(ccp(kScreenWidth/3, kScreenHeight/8));
    backBtn->setScale(0);
    backBtn->setTag(Tag_backBtn);
    backBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameOverLayer::toRestart), CCControlEventTouchUpInside);
    CCScaleTo *showBack = CCScaleTo::create(0.5, 1);
    backBtn->runAction(showBack);
    
    CCControlButton *shareBtn = CCControlButton::create(CCScale9Sprite::create(RES_ShareBtn));
    shareBtn->setPreferredSize(CCSizeMake(96, 96));
    shareBtn->setScale(0.5*kScaleFactorX);
    this->addChild(shareBtn);
    shareBtn->setPosition(ccp(kScreenWidth*2/3, kScreenHeight/8));
    shareBtn->setScale(0);
    shareBtn->setTag(Tag_shareBtn);
    shareBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(GameOverLayer::toShare), CCControlEventTouchUpInside);
    CCScaleTo *showShare = CCScaleTo::create(0.5, 1);
    shareBtn->runAction(showShare);

    
    CCMoveTo *action = CCMoveTo::create(0.5, ccp(kScreenWidth/2, kScreenHeight/2));
    block->runAction(action);

}

void GameOverLayer::toShare()
{
    CCString * shareText = CCString::createWithFormat("我在'扑满Jump'中取得了%.1f分的好成绩，个人历史最高纪录：%.1f分，这是一个很萌很有爱的游戏，快来挑战我吧~~", _score, _best);
    SocialControl::showSocial(shareText->getCString());
}

void GameOverLayer::toRestart()
{
    CCNode *block = this->getChildByTag(20);
    CCMoveTo *moveBack = CCMoveTo::create(0.5, ccp(kScreenWidth*3/2, kScreenHeight/2))
    ;
    CCCallFunc *call = CCCallFunc::create(this, callfunc_selector(GameOverLayer::restart));
    CCAction * act = CCSequence::create(moveBack, call, NULL);
    block->runAction(act);
    
    CCNode *backBtn = this->getChildByTag(Tag_backBtn);
    CCScaleTo *hideBack = CCScaleTo::create(0.5, 0);
    backBtn->runAction(hideBack);
    
    CCNode *shareBtn = this->getChildByTag(Tag_shareBtn);
    CCScaleTo *hideShare = CCScaleTo::create(0.5, 0);
    shareBtn->runAction(hideShare);
}

void GameOverLayer::restart()
{
    GameControl::startGame();
    this->removeFromParent();
}


bool GameOverLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCControlButton *btn = (CCControlButton *)this->getChildByTag(Tag_backBtn);
    btn->ccTouchBegan(pTouch, pEvent);
    btn = (CCControlButton *)this->getChildByTag(Tag_shareBtn);
    btn->ccTouchBegan(pTouch, pEvent);
    return true;
}

void GameOverLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCControlButton *btn = (CCControlButton *)this->getChildByTag(Tag_backBtn);
    btn->ccTouchMoved(pTouch, pEvent);
    btn = (CCControlButton *)this->getChildByTag(Tag_shareBtn);
    btn->ccTouchMoved(pTouch, pEvent);

}

void GameOverLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCControlButton *btn = (CCControlButton *)this->getChildByTag(Tag_backBtn);
    btn->ccTouchEnded(pTouch, pEvent);
    btn = (CCControlButton *)this->getChildByTag(Tag_shareBtn);
    btn->ccTouchEnded(pTouch, pEvent);
}
