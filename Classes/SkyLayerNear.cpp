//
//  SkyLayerNear.cpp
//  jumper-x
//
//  Created by Declan on 14-2-28.
//
//

#include "GlobalDefine.h"
#include "SkyLayerNear.h"

USING_NS_CC;

CCLayerColor * SkyLayerNear::unitLayer(float baseHeight)
{
    CCLayerColor *layer = CCLayerColor::create(ccc4(0, 0, 0, 0), kDesignWidth, kDesignHeight);
    layer->setAnchorPoint(ccp(0, 0));
    if (baseHeight > 0) {
        CCSprite *c1 = this->cloud(0, kDesignHeight/2);
        layer->addChild(c1);
    }
    CCSprite *c2 = this->cloud(kDesignHeight/2, kDesignHeight);
    layer->addChild(c2);
    return layer;
}


CCSprite * SkyLayerNear::cloud(float low, float high)
{
    CCString * imgName = CCString::createWithFormat("%s%d.png", RES_CloudNearPrefix, rand() % 2 + 1);
    CCSprite * c = CCSprite::create(imgName->getCString());
    c->setScale(0.6);
    c->setAnchorPoint(ccp(0, 0));
    float r = (float)rand() / RAND_MAX;
    float y = r * (high - low) + low;
    c->setPosition(ccp(-realWidth(c), y));
    float dur = (kDesignWidth + realWidth(c)) / (kCloudSpeed * kSkyScrollScaleNear);
    CCDelayTime * delay = CCDelayTime::create(rand() % 5);
    CCMoveTo * moveTo = CCMoveTo::create(dur, ccp(kDesignWidth, y));
    CCPlace * placeBack = CCPlace::create(c->getPosition());
    CCSequence * seq = CCSequence::create(delay, moveTo, placeBack, NULL);
    CCRepeatForever * repeat = CCRepeatForever::create(seq);
    c->runAction(repeat);
    return c;
}
