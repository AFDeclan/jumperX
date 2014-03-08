//
//  AudioEffect.h
//  jumper-x
//
//  Created by Declan on 14-3-1.
//
//

#ifndef __jumper_x__AudioEffect__
#define __jumper_x__AudioEffect__

#include "cocos-ext.h"

class AudioEffect {
    
public:

    static void playBgMusic();
    static void playWalkEffect();
    static void playPowerEffect();
    static void playJumpEffect();
    static void stopAllEffects();
    static void stopAll();
    static void pause();
    static void resume();
};

#endif /* defined(__jumper_x__AudioEffect__) */
