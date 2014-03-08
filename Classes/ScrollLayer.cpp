//
//  ScrollLayer.cpp
//  jumper-x
//
//  Created by Declan on 14-2-28.
//
//

#include "ScrollLayer.h"
#include "GlobalDefine.h"

USING_NS_CC;

bool ScrollLayer::init()
{
    if (!MyLayer::init()) return false;
    this->myInit();
    return true;
}

void ScrollLayer::myInit()
{
    this->setAnchorPoint(ccp(0, 0));
    this->setPosition(ccp(0, 0));
    _downLayer = this->unitLayer(0);
    _upLayer = this->unitLayer(kDesignHeight);
    _curBaseHeight = kDesignHeight;
    _downLayer->setPosition(ccp(0, 0));
    _upLayer->setPosition(ccp(0, kDesignHeight));
    this->addChild(_upLayer);
    this->addChild(_downLayer);
}

void ScrollLayer::reset()
{
    this->removeAllChildren();
    this->myInit();
}

bool ScrollLayer::scrollDown(float dy)
{
    posAddY(this, -dy);
    if (posY(this) <= -kScreenHeight) {
        posAddY(this, kScreenHeight);
        this->removeChild(_downLayer);
        _downLayer = _upLayer;
        posSetY(_downLayer, 0);
        _curBaseHeight += kDesignHeight;
        _upLayer = this->unitLayer(_curBaseHeight);
        this->addChild(_upLayer);
        _upLayer->setPosition(ccp(0, kDesignHeight));
        _upLayer->setZOrder(1);
        _downLayer->setZOrder(2);
        return true;
    }
    return false;
}

