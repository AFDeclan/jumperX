//
//  GameScene.h
//  jumper-x
//
//  Created by Declan on 14-2-28.
//
//

#ifndef __jumper_x__GameScene__
#define __jumper_x__GameScene__

#include "cocos2d.h"
#include "GlobalDefine.h"
#include "SkyLayerFar.h"
#include "SkyLayerNear.h"
#include "JumpLayer.h"
#include "Jumper.h"

USING_NS_CC;

class GameScene : public cocos2d::CCScene
{
public:
    virtual bool init();
    //单例
    static GameScene* scene();
    void reset();
    void hint();
    void hintExit();
    void showMenu();
    void showHelp();
    
private:
    CREATE_FUNC(GameScene);
    void update(float delta);
    void gameOver();
    void onEnter();
    void onExit();
    Jumper *_jumper;
    SkyLayerFar *_skyFar;
    SkyLayerNear *_skyNear;
    JumpLayer *_jumpLayer;
    float _baseY;
    CCLayerColor *_powerLine;
    CCLabelAtlas *_label;
};

#endif /* defined(__jumper_x__GameScene__) */
