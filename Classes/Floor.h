//
//  Floor.h
//  jumper-x
//
//  Created by Declan on 14-2-28.
//
//

#ifndef __jumper_x__Floor__
#define __jumper_x__Floor__

#include "cocos2d.h"
#include "MySprite.h"

class Floor : public MySprite {
    
public:
    static Floor* create(const char * fileName);
    static Floor * getFloor(int min, int max);
    static Floor * firstFloor();
};

#endif /* defined(__jumper_x__Floor__) */
