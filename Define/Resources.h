//
//  Resources.h
//  jumper
//
//  Created by Declan on 14-03-02.
//  Copyright (c) 2014年 Declan. All rights reserved.
//

#ifndef jumper_Resources_h
#define jumper_Resources_h

#include "platform/CCPlatformConfig.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#define RES_BgMusic             "Audio/bg.m4r"
#define RES_JumpEffectPrefix    "Audio/jump"
#define RES_PowerEffect         "Audio/powering.m4a"
#define RES_WalkEffect          "Audio/walk.m4a"

#define RES_Blank			"bg/blank.png"
#define RES_CloudFarPrefix  "bg/cloudFar"
#define RES_CloudNearPrefix	"bg/cloudNear"

#define RES_FloorPrefix		"floor/block"
#define RES_FontNum			"fonts/num.png"
#define RES_PowerAniPrefix	"power/dot"
#define RES_WalkAniPrefix	"pm/"
#define RES_Jump            "pm/jump.png"
#define RES_Fart            "pm/fart.png"

#define RES_MenuCheck       "menu/check.png"
#define RES_MenuBlock		"menu/bgBlock.png"
#define RES_HelpBlock       "menu/help.png"
#define RES_RetryBtn        "menu/retryBtn.png"
#define RES_ShareBtn        "menu/shareBtn.png"

#else

#define RES_BgMusic             "bg.m4r"
#define RES_JumpEffectPrefix 	"jump"
#define RES_PowerEffect         "powering.m4a"
#define RES_WalkEffect          "walk.m4a"

#define RES_Blank			"blank.png"
#define RES_CloudFarPrefix  "cloudFar"
#define RES_CloudNearPrefix	"cloudNear"

#define RES_FloorPrefix		"block"
#define RES_FontNum			"num.png"
#define RES_PowerAniPrefix	"dot"
#define RES_WalkAniPrefix	""
#define RES_Jump            "jump.png"
#define RES_Fart            "fart.png"

#define RES_MenuCheck       "check.png"
#define RES_MenuBlock		"bgBlock.png"
#define RES_HelpBlock       "help.png"
#define RES_RetryBtn        "retryBtn.png"
#define RES_ShareBtn        "shareBtn.png"


#endif

#endif
