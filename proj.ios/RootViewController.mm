#import "RootViewController.h"
#include "UMSocial.h"
#import "GlobalDefine.h"

#define kPublisherID    @"56OJzBMIuNKMujsQB1"
#define kAdPlaceID      @"16TLmTcoAp-WWNUfVixO7g6i"

#define setViewLeftUp(view, x, y) view.frame = CGRectMake(x, y, view.frame.size.width, view.frame.size.height)
#define setViewLeftDown(view, x, y) view.frame = CGRectMake(x, y-view.frame.size.height, view.frame.size.width, view.frame.size.height)

static RootViewController * instance;

@implementation RootViewController

+ (RootViewController *)sharedInstance
{
    if (!instance) {
        instance = [[self alloc] initWithNibName:nil bundle:nil];
        [instance initAdView];
    }
    return instance;
}
/*
 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        // Custom initialization
    }
    return self;
}
*/

/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
}
*/

/*
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
}
 
*/
// Override to allow orientations other than the default portrait orientation.
// This method is deprecated on ios6
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return UIInterfaceOrientationIsLandscape( interfaceOrientation );
}

// For ios6, use supportedInterfaceOrientations & shouldAutorotate instead
- (NSUInteger) supportedInterfaceOrientations{
#ifdef __IPHONE_6_0
    return UIInterfaceOrientationMaskAllButUpsideDown;
#endif
}

- (BOOL) shouldAutorotate {
    return YES;
}

//fix not hide status on ios7
- (BOOL)prefersStatusBarHidden
{
    return YES;
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc {
    [super dealloc];
}

- (void)showMyAd
{
    [self.view bringSubviewToFront:_dmAdView];
    [UIView animateWithDuration:0.5 animations:^{
        setViewLeftUp(_dmAdView, 0, 0);
    }];
}

- (void)hideMyAd
{
    [UIView animateWithDuration:0.5 animations:^{
        setViewLeftDown(_dmAdView, 0, 0);
    }completion:^(BOOL finished){
        [_dmAdView loadAd];
    }];
}

- (void)initAdView
{
    if (!_dmAdView) {
        _dmAdView = [[DMAdView alloc] initWithPublisherId:kPublisherID
                                              placementId:kAdPlaceID
                                                     size:DOMOB_AD_SIZE_320x50];
        setViewLeftDown(_dmAdView, 0, 0);
        _dmAdView.rootViewController = self;
        _dmAdView.delegate = self;
        [self.view addSubview:_dmAdView];
        [_dmAdView loadAd];
    }
}

- (void)setView:(UIView *)view
{
    [view addSubview:_dmAdView];
    [super setView:view];
}

- (void)dmAdViewFailToLoadAd:(DMAdView *)adView withError:(NSError *)error
{
    NSLog(@"AdView Fail:%@", error);
}

- (void)dmAdViewSuccessToLoadAd:(DMAdView *)adView
{
//    NSLog(@"AdView Suc!");
}

- (void)showSocial:(NSString *)text
{
    [UMSocialSnsService presentSnsIconSheetView:self
                                         appKey:@kUmeng_AppKey
                                      shareText:text
                                     shareImage:[UIImage imageNamed:@"Icon-72.png"]
                                shareToSnsNames:[NSArray arrayWithObjects:UMShareToSina,UMShareToTencent,UMShareToRenren,nil]
                                       delegate:nil];
}


@end
