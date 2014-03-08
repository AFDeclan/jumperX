//
//  SkyLayerFar.cpp
//  jumper-x
//
//  Created by Declan on 14-2-28.
//
//

#include "SkyLayerFar.h"
#include "GlobalDefine.h"

USING_NS_CC;

CCLayerColor * SkyLayerFar::unitLayer(float baseHeight)
{
    CCLayerColor *layer = CCLayerColor::create(ccc4(49.0, 144.0, 188.0, 255), kDesignWidth, kDesignHeight);
    layer->setAnchorPoint(ccp(0, 0));
    if (baseHeight > 0) {
        CCSprite *c1 = this->cloud(0, kDesignHeight/2);
        layer->addChild(c1);
    }
    CCSprite *c2 = this->cloud(kDesignHeight/2, kDesignHeight);
    layer->addChild(c2);
    return layer;
}

CCSprite * SkyLayerFar::cloud(float low, float high)
{
    CCString * imgName = CCString::createWithFormat("%s%d.png", RES_CloudFarPrefix, rand() % 2 + 1);
    CCSprite * c = CCSprite::create(imgName->getCString());
    c->setScale(0.6);
    c->setAnchorPoint(ccp(0, 0));
    float r = (float)rand() / RAND_MAX;
    float y = r * (high - low) + low;
    c->setPosition(ccp(-realWidth(c), y));
    float dur = (kDesignWidth + realWidth(c)) / (kCloudSpeed * kSkyScrollScaleFar);
    CCDelayTime * delay = CCDelayTime::create(rand() % 5);
    CCMoveTo * moveTo = CCMoveTo::create(dur, ccp(kDesignWidth, y));
    CCPlace * placeBack = CCPlace::create(c->getPosition());
    CCSequence * seq = CCSequence::create(delay, moveTo, placeBack, NULL);
    CCRepeatForever * repeat = CCRepeatForever::create(seq);
    c->runAction(repeat);
    return c;
}


