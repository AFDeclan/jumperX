#import <UIKit/UIKit.h>
#import "DomobAdSDK/DMAdView.h"


@interface RootViewController : UIViewController <DMAdViewDelegate> {
    DMAdView * _dmAdView;
}

+ (RootViewController *)sharedInstance;

- (void)initAdView;
- (void)showMyAd;
- (void)hideMyAd;
- (void)showSocial:(NSString *)text;

@end
