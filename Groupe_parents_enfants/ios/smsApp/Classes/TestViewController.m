//
//  TestViewController.m
//
//  Copyright iOSDeveloperTips.com All rights reserved.
//

#import "TestViewController.h"

@implementation TestViewController

/*-------------------------------------------------------------
*
*------------------------------------------------------------*/
- (void)messageComposeViewController:(MFMessageComposeViewController *)controller didFinishWithResult:(MessageComposeResult)result
{
	[self dismissModalViewControllerAnimated:YES];
  
  if (result == MessageComposeResultCancelled)
  	NSLog(@"Message cancelled");
  else if (result == MessageComposeResultSent)
  	NSLog(@"Message sent");  
  else 
  	NSLog(@"Message failed");
}

/*-------------------------------------------------------------
*
*------------------------------------------------------------*/
- (void)sendSMS:(NSString *)bodyOfMessage recipientList:(NSArray *)recipients
{
  MFMessageComposeViewController *controller = [[[MFMessageComposeViewController alloc] init] autorelease];
  if([MFMessageComposeViewController canSendText])
  {
    controller.body = bodyOfMessage;    
    controller.recipients = recipients;
    controller.messageComposeDelegate = self;
    [self presentModalViewController:controller animated:YES];
  }    
}

/*-------------------------------------------------------------
*
*------------------------------------------------------------*/
- (void)buttonPressed:(UIButton *)button
{
	if (button == buttonSMS)
  {	
		[self sendSMS:@"Body of SMS..." recipientList:[NSArray arrayWithObjects:@"0633303686", nil]];
  }
}

/*-------------------------------------------------------------
*
*------------------------------------------------------------*/
- (void)loadView 
{
  [self setView:[[[UIView alloc] initWithFrame:[[UIScreen mainScreen] applicationFrame]] autorelease]];  

  buttonSMS = [UIButton buttonWithType:UIButtonTypeRoundedRect];
  [buttonSMS setFrame:CGRectMake(0, 0, 180, 40)];
  [buttonSMS setCenter:CGPointMake(160, 208)];
  [buttonSMS setTitle:@"Send SMS" forState:UIControlStateNormal];
  [buttonSMS addTarget:self action:@selector(buttonPressed:) forControlEvents:UIControlEventTouchUpInside];
  [[self view] addSubview:buttonSMS];
}

/*-------------------------------------------------------------
*
*------------------------------------------------------------*/
- (void)dealloc 
{
	[buttonSMS release];
	[super dealloc];
}

@end
