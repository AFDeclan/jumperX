//
//  SocialControl.cpp
//  jumperX
//
//  Created by Declan on 14-3-7.
//
//

#include "SocialControl.h"

#include "platform/CCPlatformConfig.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "JniHelper.h"

static const char* kActivityName = "com/Declan/jumper/jumperX";
#include "cocos2d.h"

using namespace cocos2d;

#else

#include "SocialIOS.h"

#endif


void SocialControl::showSocial(const char * text)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //call java static method using jni
    JniMethodInfo t;
    if( JniHelper::getStaticMethodInfo(t
                                       , kActivityName
                                       , "openShareBoard"
                                       , "(Ljava/lang/String;)V"))
    {
        jstring jText = t.env->NewStringUTF(text);
        t.env->CallStaticVoidMethod(t.classID, t.methodID, jText);
        t.env->DeleteLocalRef(jText);
    }
#else
    SocialIOS::showSocial(text);
#endif
}