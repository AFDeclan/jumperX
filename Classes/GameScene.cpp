//
//  GameScene.cpp
//  jumper-x
//
//  Created by Declan on 14-2-28.
//
//

#include "GameScene.h"
#include "FloorGenerator.h"
#include "GameControl.h"
#include "GameOverLayer.h"
#include "MobClickCpp.h"
#include "GlobalDefine.h"
#include "AudioEffect.h"
#include "CCControlButton.h"
#include "MenuLayer.h"
#include "HelpLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

static GameScene *instance = NULL;

GameScene* GameScene::scene()
{
    if (!instance) {
        instance = GameScene::create();
    }
    return instance;
}

bool GameScene::init()
{
    if (!CCScene::init()) return false;
    
    FloorGenerator::reset();
    _skyFar = SkyLayerFar::create();
    this->addChild(_skyFar);
    _skyNear = SkyLayerNear::create();
    this->addChild(_skyNear);
    _jumpLayer = JumpLayer::create();
    this->addChild(_jumpLayer);
    _jumper = Jumper::theJumper();
    _jumper->jumpLayer = _jumpLayer;
    _jumper->setPosition(ccp(kDesignWidth/2, 0));
    _jumper->setLeftWalking(true);
    Floor *baseFloor = (Floor *)FloorGenerator::floors->objectAtIndex(0);
    _jumpLayer->addChild(_jumper);
    _jumper->walk(baseFloor);
    _powerLine = CCLayerColor::create(ccc4(255, 0, 0, 200), kScreenWidth, 20);
    _powerLine->setAnchorPoint(ccp(0, 1));
    _powerLine->setPosition(ccp(0, kScreenHeight-20));
    this->addChild(_powerLine);
    _label = CCLabelAtlas::create("0", RES_FontNum, 32, 38, 46);
    _label->setScale(kScaleFactorX*0.6);
    _label->setAnchorPoint(ccp(0.5, 1));
    _label->setPosition(ccp(kScreenWidth/2, kScreenHeight - 16));
    this->addChild(_label);
    
    CCControlButton *menuButton = CCControlButton::create("[ Menu ]", "Verdana-Bold", 16.0f*kScaleFactorX);
    menuButton->setAnchorPoint(ccp(1, 1));
    menuButton->setPosition(ccp(kScreenWidth-12, kScreenHeight-16));
    menuButton->addTargetWithActionForControlEvents(this, cccontrol_selector(GameScene::showMenu), CCControlEventTouchDown);
    this->addChild(menuButton);

    
    CCControlButton *helpButton = CCControlButton::create("[ Help ]", "Verdana-Bold", 16.0f*kScaleFactorX);
    helpButton->setAnchorPoint(ccp(0, 1));
    helpButton->setPosition(ccp(12, kScreenHeight-16));
    helpButton->addTargetWithActionForControlEvents(this, cccontrol_selector(GameScene::showHelp), CCControlEventTouchDown);
    this->addChild(helpButton);
    
    _baseY = 0;
    
    _skyFar->setZOrder(0);
    _skyNear->setZOrder(1);
    _jumpLayer->setZOrder(2);
    _label->setZOrder(3);
    menuButton->setZOrder(3);
    helpButton->setZOrder(3);
    _powerLine->setZOrder(4);
    _jumper->setZOrder(9);
    
    GameControl::startGame();

    return true;
}

void GameScene::reset()
{
    FloorGenerator::reset();
    _skyNear->reset();
    _skyFar->reset();
    _jumpLayer->reset();
    
    _jumper->setPosition(ccp(kDesignWidth/2, 0));
    _jumper->setLeftWalking(true);
    Floor *baseFloor = (Floor *)FloorGenerator::floors->objectAtIndex(0);
    _jumper->walk(baseFloor);

    _label->setString("0");
    _baseY = 0;
}

void GameScene::update(float delta)
{
    if (GameControl::getGameStatus() != On) return;
    
    _jumper->update(delta);
    
    CCPoint jumperPos = _jumper->getParent()->convertToWorldSpace(_jumper->getPosition());
    
    //Walk direct
    if (jumperPos.x <= 2) {
        _jumper->setLeftWalking(false);
    } else if (jumperPos.x >= kScreenWidth - _jumper->globalWidth()) {
        _jumper->setLeftWalking(true);
    }
    
    Floor *walkingFloor = _jumper->getWalkingFloor();
    //Whther start fall and adjust jumper speed
    if (_jumper->getWalkingFloor()) {
        CCPoint floorPos = walkingFloor->getParent()->convertToWorldSpace(walkingFloor->getPosition());
        if (jumperPos.x + _jumper->globalWidth() <= floorPos.x ||
            jumperPos.x >= floorPos.x + walkingFloor->globalWidth()) {
            _jumper->fall();
        }
    }
    
    //Whether stop fall
    if (walkingFloor == NULL && _jumper->getVy() <= 0) {
        CCArray *floors = FloorGenerator::floors;
        for (int i=0; i<floors->count(); i++) {
            Floor *floor = (Floor *)floors->objectAtIndex(i);
            CCPoint floorPos = floor->getParent()->convertToWorldSpace(floor->getPosition());
            if (floorPos.y < jumperPos.y - _jumper->getVy()*delta*kScaleFactorX*2 &&
                floorPos.y < jumperPos.y - 6*kScaleFactorX) continue;
            if (floorPos.y > jumperPos.y + 6*kScaleFactorX) break;
            if (floorPos.x <= jumperPos.x+_jumper->globalWidth() &&
                floorPos.x+floor->globalWidth() >= jumperPos.x) {
                _jumper->walk(floor);
            }
        }
    }
    
    //Whether Scroll
    if (jumperPos.y > kJumperMaxY) {
        float offset = jumperPos.y - kJumperMaxY;
        if (_jumpLayer->scrollDown(offset)) {
            if (_jumper->getParent() == _jumpLayer) {
                posAddY(_jumper, -kDesignHeight);
            }
        }
        _skyFar->scrollDown(offset * kSkyScrollScaleFar);
        _skyNear->scrollDown(offset * kSkyScrollScaleNear);
        _baseY += jumperPos.y - kJumperMaxY;
        char *scoreStr = new char[20];
        sprintf(scoreStr, "%.1f", _baseY * kScoreScale);
        _label->setString(scoreStr);
        delete [] scoreStr;
        CCArray *floors = FloorGenerator::floors;
        for (int i=0; i<floors->count(); i++) {
            Floor *floor = (Floor *)floors->objectAtIndex(0);
            if (!floor->getParent()) {
                floors->removeObject(floor);
            } else {
                CCPoint floorPos = floor->getParent()->convertToWorldSpace(floor->getPosition());
                if (floorPos.y < 0) {
                    floors->removeObject(floor);
                } else
                break;
            }
        }
    }
    
    //powerLine
    _powerLine->setScaleX(_jumper->getPower());
    
    //Whether Game Over
    if (!walkingFloor && jumperPos.y < - _jumper->globalHeight()) {
        this->gameOver();
    }
}

void GameScene::gameOver()
{
    GameControl::overGame();
    float score = _baseY * kScoreScale;
    float best = LoadDoubleFromUD(kUDK_BestScore);
    best = MAX(score, best);
    SaveDoubleToUD(kUDK_BestScore, best);
    GameOverLayer *overLayer = GameOverLayer::create();
    this->addChild(overLayer);
    overLayer->setZOrder(10);
    overLayer->show(score, best);
}

void GameScene::showMenu()
{
    MenuLayer *menu = MenuLayer::create();
    menu->setZOrder(10);
    this->addChild(menu);
}

void GameScene::showHelp()
{
    HelpLayer *help = HelpLayer::create();
    help->setZOrder(10);
    this->addChild(help);
}


void GameScene::hint()
{
    if (this->getChildByTag(10)) return;
    CCLayerColor * hint = CCLayerColor::create(ccc4(0, 0, 0, 0), kScreenWidth, kScreenHeight);
    this->addChild(hint);
    hint->setAnchorPoint(ccp(0.5, 0.5));
    hint->setScale(0);
    hint->setTag(10);
    hint->setZOrder(10);
    CCLabelTTF *hintLabel = CCLabelTTF::create("按久一点再松哦 ~", "Verdana-Bold", 16*kScaleFactorX);
    hint->addChild(hintLabel);
    CCLabelTTF *hintLabelEn = CCLabelTTF::create("Press for longer ~", "Verdana-Bold", 12*kScaleFactorX);
    hint->addChild(hintLabelEn);
    hintLabel->setPosition(ccp(kScreenWidth/2, kScreenHeight/2 + contentHeight(hintLabelEn)));
    hintLabelEn->setPosition(ccp(kScreenWidth/2, kScreenHeight/2 -contentHeight(hintLabelEn)));
    CCScaleTo *showAct = CCScaleTo::create(0.5, 1);
    CCDelayTime *delayAct = CCDelayTime::create(2);
    CCScaleTo *hideAct = CCScaleTo::create(0.5, 0);
    CCRemoveSelf *removeAct = CCRemoveSelf::create();
    hint->runAction(CCSequence::create(showAct, delayAct, hideAct, removeAct, NULL));
}

void GameScene::hintExit()
{
    if (this->getChildByTag(20)) return;
    CCLabelTTF *hintLabel = CCLabelTTF::create("再按一次返回键退出！", "Verdana-Bold", 12*kScaleFactorX);
    this->addChild(hintLabel);
    hintLabel->setZOrder(10);
    hintLabel->setTag(20);
    hintLabel->setScale(0);
    hintLabel->setPosition(ccp(kScreenWidth/2, 32*kScaleFactorX));
    CCScaleTo *showAct = CCScaleTo::create(0.2, 1);
    CCDelayTime *delayAct = CCDelayTime::create(1);
    CCScaleTo *hideAct = CCScaleTo::create(0.2, 0);
    CCRemoveSelf *removeAct = CCRemoveSelf::create();
    hintLabel->runAction(CCSequence::create(showAct, delayAct, hideAct, removeAct, NULL));
}

void GameScene::onEnter()
{
    CCScene::onEnter();
    CCDirector::sharedDirector()->getScheduler()->scheduleUpdateForTarget(this, 0, false);
    MobClickCpp::beginLogPageView("pageOne");
}

void GameScene::onExit()
{
    CCScene::onExit();
    MobClickCpp::endLogPageView("pageOne");
}
