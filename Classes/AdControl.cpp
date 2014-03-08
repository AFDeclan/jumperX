//
//  AdControl.mm
//  jumperX
//
//  Created by Declan on 14-3-4.
//
//

#include "AdControl.h"
#include "platform/CCPlatformConfig.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "JniHelper.h"

static const char* kActivityName = "com/Declan/jumper/jumperX";
#include "cocos2d.h"
using namespace cocos2d;

#else

#include "AdIOS.h"

#endif

void AdControl::showAd()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //call java static method using jni
    JniMethodInfo t;
    if( JniHelper::getStaticMethodInfo(t
                                       , kActivityName
                                       , "showMyAd"
                                       , "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
    }
#else
    //call RootViewController to control ad
    AdIOS::showMyAd();
#endif
}

void AdControl::hideAd()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    if( JniHelper::getStaticMethodInfo(t
                                       , kActivityName
                                       , "hideMyAd"
                                       , "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
    }
#else
    AdIOS::hideMyAd();
#endif
}