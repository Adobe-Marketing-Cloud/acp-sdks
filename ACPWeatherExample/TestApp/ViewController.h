//
//  ViewController.h
//  Adobe Cloud Platform -- ACP SDK Extension for iOS
//
//  Copyright 1996-2018 Adobe. All Rights Reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController <UITextFieldDelegate>

@property (nonatomic, assign) IBOutlet UILabel *lblTemperature;
@property (nonatomic, assign) IBOutlet UITextField *txtZip;
@property (nonatomic, assign) IBOutlet UIButton *btnGetWeather;
@property (nonatomic, assign) IBOutlet UILabel *lblConditions;
@property (nonatomic, assign) IBOutlet UIImageView *imgConditions;


- (IBAction) getWeather:(id)sender;

@end

