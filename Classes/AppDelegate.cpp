#include "AppDelegate.h"
#include "GlobalDefine.h"
#include "MobClickCpp.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "GameControl.h"

USING_NS_CC;

AppDelegate::AppDelegate() {
}


AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    
    if (!LoadBooleanFromUD(kUDK_Setting_Initialed)) {
        SaveBooleanToUD(kUDK_Setting_Initialed, true);
        SaveBooleanToUD(kUDK_Setting_BgMusic, true);
        SaveBooleanToUD(kUDK_Setting_SoundEffects, true);
        SaveDoubleToUD(kUDK_BestScore, 0);
    }
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    GameScene *pScene = GameScene::scene();

    // run
    pDirector->runWithScene(pScene);
    
    MobClickCpp::startWithAppkey(kUmeng_AppKey, kUmeng_AppChannel_Wandoujia);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();
    
    MobClickCpp::applicationDidEnterBackground();
    GameControl::pauseGame();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();
    
    MobClickCpp::applicationWillEnterForeground();
    GameControl::resumeGame();
}
