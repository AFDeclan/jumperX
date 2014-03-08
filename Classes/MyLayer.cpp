//
//  MyLayer.cpp
//  jumper-x
//
//  Created by Declan on 14-2-28.
//
//

#include "MyLayer.h"
#include "GlobalDefine.h"

USING_NS_CC;

bool MyLayer::init()
{
    if (!CCLayer::init()) return false;
    this->setScaleX(kScaleFactorX);
    this->setScaleY(kScaleFactorY);
    return true;
}