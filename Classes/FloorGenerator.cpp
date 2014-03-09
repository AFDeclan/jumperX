//
//  FloorGenerator.cpp
//  jumper-x
//
//  Created by Declan on 14-2-28.
//
//

#include "FloorGenerator.h"
#include "Floor.h"


USING_NS_CC;

float minHeightStep()
{
    return 100;
}

float maxHeightStep()
{
    return 150;
}

CCArray * FloorGenerator::floors = NULL;
float FloorGenerator::lastHeight = 0;
float FloorGenerator::nextHeight = 0;

void FloorGenerator::reset()
{
    lastHeight = 0;
    nextHeight = 0;
    if (floors != NULL) {
        floors->release();
    }
    floors = CCArray::create();
    floors->retain();
}

Floor * FloorGenerator::nextFloor(float baseHeight)
{
    Floor *next;
    if (nextHeight == 0) {
        next = Floor::firstFloor();
    } else {
        int maxstage, minstage;
        if (baseHeight < 20 * kDesignHeight) {
            minstage = 1;
            maxstage = MIN(baseHeight / kDesignHeight / 4 + 1, 4);
        } else if (baseHeight < 50 * kDesignHeight) {
            maxstage = 4;
            minstage = MIN(baseHeight / kDesignHeight / 4 - 4, 3);
        } else {
            maxstage = 4;
            minstage = 4;
        }
        next = Floor::getFloor(minstage, maxstage);
        float y = nextHeight - baseHeight;
        float x = (float)rand() / RAND_MAX * (kDesignWidth - contentWidth(next));
        next->setPosition(ccp(x, y));
        if (rand() % 8 == 0) {
            //move
            float tx = (float)rand() / RAND_MAX * kDesignWidth - contentWidth(next)/2;
            float speed = (float)rand() / RAND_MAX * 30 + 20;
            float dur = ABS(tx-x)/speed;
            CCMoveTo *moveTo = CCMoveTo::create(dur, ccp(tx, y));
            CCMoveTo *moveBack = CCMoveTo::create(dur, ccp(x, y));
            CCSequence *actionSeq = CCSequence::create(moveTo, moveBack, NULL);
            CCAction *repeat = CCRepeatForever::create(actionSeq);
            next->runAction(repeat);
        }
    }
    
    floors->addObject(next);
    
    lastHeight = nextHeight;
    float r = (float)rand() / RAND_MAX;
    float min = minHeightStep();
    float max = maxHeightStep();
    nextHeight = min + (max - min) * r + lastHeight;
    return next;
}
