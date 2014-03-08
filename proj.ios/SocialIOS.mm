//
//  SocialIOS.mm
//  jumperX
//
//  Created by Declan on 14-3-7.
//
//

#include "SocialIOS.h"
#include "RootViewController.h"

void SocialIOS::showSocial(const char * text)
{
    NSString *textStr = [NSString stringWithUTF8String:text];
    [[RootViewController sharedInstance] showSocial:textStr];
}