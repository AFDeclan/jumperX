//
//  Floor.cpp
//  jumper-x
//
//  Created by Declan on 14-2-28.
//
//

#include "Floor.h"
#include "GlobalDefine.h"

USING_NS_CC;

Floor* Floor::create(const char *fileName)
{
    Floor *pRet = new Floor();
    if (pRet && pRet->initWithFile(fileName))
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


Floor * Floor::getFloor(int min, int max)
{
    int level_rand = rand() % (max-min+1) + min;
    int color_rand = rand() % 4 + 1;
    CCString *imgName = CCString::createWithFormat("%s%d_%d.png", RES_FloorPrefix, level_rand, color_rand);
    Floor *floor = Floor::create(imgName->getCString());
    floor->setAnchorPoint(ccp(0, 1));
    return floor;
}

Floor * Floor::firstFloor()
{
    Floor *floor = Floor::create(RES_Blank);
    floor->setAnchorPoint(ccp(0, 0));
    floor->setPosition(ccp(0, 0));
    floor->setTextureRect(CCRectMake(0, 0, kDesignWidth, 1));
    return floor;
}