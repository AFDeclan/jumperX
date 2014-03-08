//
//  Jumper.cpp
//  jumper-x
//
//  Created by Declan on 14-2-28.
//
//

#include "Jumper.h"
#include "GlobalDefine.h"
#include "GameControl.h"
#include "AudioEffect.h"

USING_NS_CC;

#define Tag_WalkAction  1
#define Tag_PowerAction 2
#define Tag_FartAction  3

static Jumper * instance;

Jumper * Jumper::theJumper()
{
    if (!instance) {
        instance = Jumper::create();
        instance->retain();
        instance->myInit();
    }
    return instance;
}

void Jumper::onEnter()
{
    CCSprite::onEnter();
}

void Jumper::myInit()
{
    char *fileName = new char[25];
    sprintf(fileName, "%s3.png", RES_WalkAniPrefix);
    this->setDisplayFrame(CCSpriteFrame::create(fileName, CCRectMake(0, 0, 200, 249)));
    this->setAnchorPoint(ccp(0, 0));
    this->setScale(0.2);
    _vx = -kJumperWalkSpeed;
    CCArray * frames = CCArray::createWithCapacity(9);
    for (int i=0; i<9; i++) {
        sprintf(fileName, "%s%d.png", RES_WalkAniPrefix, i+1);
        CCSpriteFrame *frame = CCSpriteFrame::create(fileName, CCRectMake(0, 0, 200, 249));
        frames->addObject(frame);
    }
    _jumping = false;
    CCAnimation *anim = CCAnimation::createWithSpriteFrames(frames, 0.05);
    anim->setDelayPerUnit(0.05);
    CCAnimate *act = CCAnimate::create(anim);
    _walkAction = CCRepeatForever::create(act);
    _walkAction->setTag(Tag_WalkAction);
    _walkAction->retain();
    
    sprintf(fileName, "%s1.png", RES_PowerAniPrefix);
    _powerSprite = CCSprite::create(fileName);
    _powerSprite->setPosition(ccp(contentWidth(this)/2, contentHeight(this)/2));
    _powerSprite->setZOrder(-1);
    _powerSprite->setVisible(false);
    this->addChild(_powerSprite);
    frames = CCArray::createWithCapacity(5);
    for (int i=0; i<5; i++) {
        sprintf(fileName, "%s%d.png", RES_PowerAniPrefix, i+1);
        CCSpriteFrame * frame = CCSpriteFrame::create(fileName, CCRectMake(0, 0, 320, 320));
        frames->addObject(frame);
    }
    CCAnimation *powerAni = CCAnimation::createWithSpriteFrames(frames);
    powerAni->setDelayPerUnit(0.06);
    CCAnimate *powerAct = CCAnimate::create(powerAni);
    _powerAction = CCRepeatForever::create(powerAct);
    _powerAction->setTag(Tag_PowerAction);
    _powerAction->retain();
    
    _fartSprite = CCSprite::create(RES_Fart);
    this->addChild(_fartSprite);
    _fartSprite->setScale(0);
    _fartSprite->setZOrder(1);
    _fartSprite->setAnchorPoint(ccp(0.5, 1));
    _fartSprite->setPosition(ccp(contentWidth(this)/2, 0));
    
    delete [] fileName;
}

void Jumper::startAnimate()
{
    _fartSprite->setScale(0);
    _fartSprite->setOpacity(0);
    this->setScale(0.2);
    this->runAction(_walkAction);
    this->setLeftWalking(_leftWalking);
}

void Jumper::startAnimateJump()
{
    this->startAnimateFall();
    _fartSprite->stopActionByTag(Tag_FartAction);
    _fartSprite->setScale(0);
    _fartSprite->setOpacity(255);
    _fartSprite->setVisible(true);
    CCScaleTo *scale = CCScaleTo::create(0.3, 1);
//    CCDelayTime *delay = CCDelayTime::create(_vy / kJumperFullPowerSpeed);
    CCFadeOut *fade = CCFadeOut::create(0.3);
    CCSequence *seq = CCSequence::create(scale, fade, NULL);
    seq->setTag(Tag_FartAction);
    _fartSprite->runAction(seq);
}

void Jumper::startAnimateFall()
{
    this->adjustScale(0.2);
    this->stopAllActions();
    this->setDisplayFrame(CCSpriteFrame::create(RES_Jump, CCRectMake(0, 0, 200, 249)));
}


#pragma mark - Compute

void Jumper::update(float delta)
{
    if (GameControl::getGameStatus() != On) return;
    _vx += _ax * delta;
    _vy += _ay * delta;
    posAddX(this, _vx*delta);
    posAddY(this, _vy*delta);
    if (_powering) {
        _power += delta / kJumperPowerCicle;
        if (_power > 1) {
            _power -= 1;
            _needHint = false;
        }
    }
    if (_walkingFloor) {
        if (posY(this) < contentHeight(_walkingFloor)) {
            posSetY(this, contentHeight(_walkingFloor));
            _vy = 0;
            _ay = 0;
        }
    }
}

void Jumper::offFloor()
{
    CCPoint globalPos = _walkingFloor->convertToWorldSpace(this->getPosition());
    CCPoint nodePos = jumpLayer->convertToNodeSpace(globalPos);
    this->setPosition(nodePos);
    this->removeFromParent();
    jumpLayer->addChild(this);
    _walkingFloor = NULL;
    _powering = false;
    _power = 0;
    _ay = -kGravity;
    this->showNotPowering();
}

#pragma mark - Control

void Jumper::setLeftWalking(bool left)
{
    _leftWalking = left;
    this->setFlipX(!_leftWalking);
    _vx = _leftWalking? -ABS(_vx) : ABS(_vx);
    this->stopActionByTag(101);
    float angle = _leftWalking? -8 : 8;
    CCRotateTo *rotate = CCRotateTo::create(0.2, angle);
    rotate->setTag(101);
    CCRotateTo *rotate2 = CCRotateTo::create(0.2, 0);
    CCRepeatForever *repeat = CCRepeatForever::create(CCSequence::create(rotate, rotate2, NULL));
    repeat->setTag(101);
    if (!_walkingFloor) {
        this->runAction(rotate);
    } else {
        this->runAction(repeat);
    }
}

void Jumper::startPower()
{
    AudioEffect::playPowerEffect();
    this->showPowering();
    _needHint = true;
    _power = 0;
    _powering = true;
}

bool Jumper::jump()
{
    AudioEffect::playJumpEffect();
    if (!_powering) return false;
    bool needHint = _needHint && _power < 0.2;
    _vy = _power * kJumperFullPowerSpeed;
    this->offFloor();
    this->startAnimateJump();
    return needHint;
}

void Jumper::fall()
{
    this->offFloor();
    this->startAnimateFall();
}

void Jumper::walk(Floor *floor)
{
    AudioEffect::playWalkEffect();
    _walkingFloor = floor;
    CCPoint globalPos = jumpLayer->convertToWorldSpace(this->getPosition());
    CCPoint nodePos = _walkingFloor->convertToNodeSpace(globalPos);
    this->setPosition(nodePos);
    this->removeFromParent();
    _walkingFloor->addChild(this);
    this->startAnimate();
}

Floor * Jumper::getWalkingFloor()
{
    return _walkingFloor;
}

float Jumper::getVy()
{
    return _vy;
}

float Jumper::getPower()
{
    return _power;
}

#pragma mark - Effect

void Jumper::showPowering()
{
    _powerSprite->setVisible(true);
    _powerSprite->runAction(_powerAction);
}

void Jumper::showNotPowering()
{
    _powerSprite->stopAllActions();
    _powerSprite->setVisible(false);
}

Jumper::~Jumper()
{
    _walkAction->release();
    _powerAction->release();
    instance->release();
}
