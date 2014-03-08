//
//  AudioEffect.cpp
//  jumper-x
//
//  Created by Declan on 14-3-1.
//
//

#include "AudioEffect.h"
#include "SimpleAudioEngine.h"
#include "GlobalDefine.h"
#include "cocos2d.h"

USING_NS_CC;

#define sAudioEngine CocosDenshion::SimpleAudioEngine::sharedEngine()

void AudioEffect::playBgMusic()
{
    if (!LoadBooleanFromUD(kUDK_Setting_BgMusic)) return;
    sAudioEngine->playBackgroundMusic(RES_BgMusic, true);
}

void AudioEffect::pause()
{
    sAudioEngine->pauseBackgroundMusic();
    sAudioEngine->pauseAllEffects();
}

void AudioEffect::resume()
{
    sAudioEngine->resumeAllEffects();
    sAudioEngine->resumeBackgroundMusic();
}

void AudioEffect::playWalkEffect()
{
    stopAllEffects();
    if (!LoadBooleanFromUD(kUDK_Setting_SoundEffects)) return;
    sAudioEngine->playEffect(RES_WalkEffect, true);
}

void AudioEffect::playPowerEffect()
{
    stopAllEffects();
    if (!LoadBooleanFromUD(kUDK_Setting_SoundEffects)) return;
    sAudioEngine->playEffect(RES_PowerEffect, true);
}

void AudioEffect::playJumpEffect()
{
    stopAllEffects();
    if (!LoadBooleanFromUD(kUDK_Setting_SoundEffects)) return;
    CCString *fileName = CCString::createWithFormat("%s%d.mp3", RES_JumpEffectPrefix, 1);
    sAudioEngine->playEffect(fileName->getCString());
}

void AudioEffect::stopAllEffects()
{
    sAudioEngine->stopAllEffects();
}

void AudioEffect::stopAll()
{
    stopAllEffects();
    sAudioEngine->stopBackgroundMusic();
}
