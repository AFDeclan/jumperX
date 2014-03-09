//
//  FloorGenerator.h
//  jumper-x
//
//  Created by Declan on 14-2-28.
//
//

#ifndef __jumper_x__FloorGenerator__
#define __jumper_x__FloorGenerator__

#include "cocos2d.h"
#include "GlobalDefine.h"
#include "Floor.h"

class FloorGenerator {
    
public:
    static cocos2d::CCArray * floors;
    static float lastHeight;
    static float nextHeight;
    static Floor * nextFloor(float baseHeight);
    static void reset();
    
};


#endif /* defined(__jumper_x__FloorGenerator__) */
