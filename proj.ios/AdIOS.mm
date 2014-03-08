//
//  AdIOS.mm
//  jumperX
//
//  Created by Declan on 14-3-4.
//
//

#include "AdIOS.h"
#include "RootViewController.h"

void AdIOS::showMyAd()
{
    [[RootViewController sharedInstance] showMyAd];
}

void AdIOS::hideMyAd()
{
    [[RootViewController sharedInstance] hideMyAd];
}
