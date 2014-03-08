//
//  GlobalDefine.h
//  jumper
//
//  Created by Declan on 14-2-25.
//  Copyright (c) 2014骞�Declan. All rights reserved.
//

#ifndef jumper_GlobalDefine_h
#define jumper_GlobalDefine_h

#include "GameDefine.h"
#include "Umeng.h"
#include "Resources.h"

#define kScreenHeight cocos2d::CCDirector::sharedDirector()->getWinSize().height
#define kScreenWidth cocos2d::CCDirector::sharedDirector()->getWinSize().width
#define kDesignHeight 480
#define kDesignWidth  320
#define kScaleFactorY (kScreenHeight / kDesignHeight)
#define kScaleFactorX (kScreenWidth / kDesignWidth)
#define posAddX(node, dx)  node->setPosition(ccp(node->getPosition().x+dx, node->getPosition().y))
#define posAddY(node, dy)  node->setPosition(ccp(node->getPosition().x, node->getPosition().y+dy))
#define posSetX(node, x)  node->setPosition(ccp(x, node->getPosition().y))
#define posSetY(node, y)  node->setPosition(ccp(node->getPosition().x, y))
#define posX(node) node->getPosition().x
#define posY(node) node->getPosition().y
#define contentWidth(node) node->getContentSize().width
#define contentHeight(node) node->getContentSize().height
#define realWidth(node) node->getContentSize().width * node->getScaleX()
#define realHeight(node) node->getContentSize().height * node->getScaleY()
#define ABS(x) (x>=0 ? x : -x)

#define SaveStringToUD(k, v)    cocos2d::CCUserDefault::sharedUserDefault()->setStringForKey(k, v)
#define SaveIntegerToUD(k, v)   cocos2d::CCUserDefault::sharedUserDefault()->setIntegerForKey(k, v)
#define SaveBooleanToUD(k, v)   cocos2d::CCUserDefault::sharedUserDefault()->setBoolForKey(k, v)
#define SaveDoubleToUD(k, v)    cocos2d::CCUserDefault::sharedUserDefault()->setDoubleForKey(k, v)
#define LoadStringFromUD(key)   cocos2d::CCUserDefault::sharedUserDefault()->getStringForKey(key)
#define LoadIntegerFromUD(key)  cocos2d::CCUserDefault::sharedUserDefault()->getIntegerForKey(key)
#define LoadBooleanFromUD(key)  cocos2d::CCUserDefault::sharedUserDefault()->getBoolForKey(key)
#define LoadDoubleFromUD(key)   cocos2d::CCUserDefault::sharedUserDefault()->getDoubleForKey(key)


#define kUDK_BestScore              "UDK_BestScore"
#define kUDK_Setting_BgMusic        "UDK_Setting_BgMusic"
#define kUDK_Setting_SoundEffects   "UDK_Setting_SoundEffects"
#define kUDK_Setting_Initialed      "UDK_Setting_Initialed"

#endif
