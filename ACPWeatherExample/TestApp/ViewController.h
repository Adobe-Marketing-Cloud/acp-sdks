//
//  ViewController.h
//  Adobe Cloud Platform -- ACP SDK Extension for iOS
//
//  Copyright 1996-2019 Adobe. All Rights Reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController <UITextFieldDelegate>

@property (nonatomic, assign) IBOutlet UILabel *lblTemperature;
@property (nonatomic, assign) IBOutlet UITextField *txtZip;
@property (nonatomic, assign) IBOutlet UIButton *btnGetWeather;
@property (nonatomic, assign) IBOutlet UILabel *lblConditions;

- (IBAction) getWeather:(id)sender;

@end

