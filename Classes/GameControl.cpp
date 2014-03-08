//
//  GameControl.cpp
//  jumper-x
//
//  Created by Declan on 14-2-28.
//
//

#include "GameControl.h"
#include "GameScene.h"
#include "AudioEffect.h"
#include "Jumper.h"
#include "FloorGenerator.h"
#include "AdControl.h"

GameStatus GameControl::_gameStatus = Over;

static bool first = true;

void pauseAll()
{
    CCArray *floors = FloorGenerator::floors;
    for (int i=0; i<floors->count(); i++) {
        Floor *f = (Floor *)floors->objectAtIndex(i);
        f->pauseSchedulerAndActions();
    }
}

void resumeAll()
{
    CCArray *floors = FloorGenerator::floors;
    for (int i=0; i<floors->count(); i++) {
        Floor *f = (Floor *)floors->objectAtIndex(i);
        f->resumeSchedulerAndActions();
    }
}

GameStatus GameControl::getGameStatus()
{
    return _gameStatus;
}

void GameControl::startGame()
{
    AdControl::hideAd();
    _gameStatus = On;
    AudioEffect::playBgMusic();
    if (!first) {
        GameScene::scene()->reset();
    }
    first = false;
}

void GameControl::overGame()
{
    AdControl::showAd();
    _gameStatus = Over;
    AudioEffect::stopAll();
    pauseAll();
}

void GameControl::pauseGame()
{
    AdControl::showAd();
    _gameStatus = Pause;
    AudioEffect::stopAll();
    pauseAll();
}

void GameControl::resumeGame()
{
    AdControl::hideAd();
    AudioEffect::playBgMusic();
    _gameStatus = On;
    resumeAll();
}



