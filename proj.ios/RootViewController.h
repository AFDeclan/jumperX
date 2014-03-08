#import <UIKit/UIKit.h>
#import "DomobAdSDK/DMAdView.h"


@interface RootViewController : UIViewController {
    DMAdView * _dmAdView;
}

+ (RootViewController *)sharedInstance;

- (void)initAdView;
- (void)showMyAd;
- (void)hideMyAd;
- (void)showSocial:(NSString *)text;

@end
