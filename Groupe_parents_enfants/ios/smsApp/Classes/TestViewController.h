//
//  TestViewController.h
//
//  Copyright iOSDeveloperTips.com All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MessageUI/MFMessageComposeViewController.h>
	
@interface TestViewController : UIViewController <MFMessageComposeViewControllerDelegate>
{
	UIButton *buttonSMS;
}

@end
