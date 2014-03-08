//
//  MySprite.cpp
//  jumper-x
//
//  Created by Declan on 14-3-1.
//
//

#include "MySprite.h"
#include "GameScene.h"

USING_NS_CC;

float MySprite::globalHeight()
{
    float height = this->getContentSize().height;
    CCNode *n = (CCNode *)this;
    while (n) {
        height *= n->getScaleY();
        n = n->getParent();
    }
    return height;
}

float MySprite::globalWidth()
{
    float width = this->getContentSize().width;
    CCNode *n = this;
    while (n) {
        width *= n->getScaleX();
        n = n->getParent();
    }
    return width;
}

void MySprite::onEnter()
{
    CCSprite::onEnter();
    this->adjustScale();
}

void MySprite::adjustScale(float origin)
{
    if (origin < MAXFLOAT) {
        this->setScale(origin);
    }
    float scaleX=1, scaleY=1;
    CCNode *n = (CCNode *)this->getParent();
    while (n) {
        scaleX *= n->getScaleX();
        scaleY *= n->getScaleY();
        n = n->getParent();
    }
    this->setScaleY(this->getScaleY()*scaleX/scaleY);
}