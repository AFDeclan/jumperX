//
//  Umeng.h
//  jumper
//
//  Created by Declan on 14-2-28.
//  Copyright (c) 2014年 Declan. All rights reserved.
//

#ifndef jumper_Umeng_h
#define jumper_Umeng_h

#include "platform/CCPlatformConfig.h"

#define kUmeng_AppKey_IOS   "530e988c56240bc073075e38"
#define kUmeng_AppKey_Android "5313f30356240b622d002bd5"

#define kUmeng_AppChannel_91        "91"
#define kUmeng_AppChannel_XiaoMi    "Xiao Mi"
#define kUmeng_AppChannel_Wandoujia "Wandoujia"
#define kUmeng_AppChannel_360       "360"
#define kUmeng_AppChannel_Anzhi     "Anzhi"
#define kUmeng_AppChannel_AppStore  "App Store"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define kUmeng_AppKey   kUmeng_AppKey_Android
//！！发布前注意修改！！ --- Android
#define kUmeng_AppChannel  kUmeng_AppChannel_Wandoujia
#else
#define kUmeng_AppKey   kUmeng_AppKey_IOS
//！！发布前注意修改！！ --- IOS
#define kUmeng_AppChannel  kUmeng_AppChannel_91
#endif


#define kUmeng_Event_GameStart      "GameStart"
#define kUmeng_Event_GameOver       "GameOver"

#endif
