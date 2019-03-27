/*
 ADOBE CONFIDENTIAL
 
 Copyright 2019 Adobe
 All Rights Reserved.
 
 NOTICE: Adobe permits you to use, modify, and distribute this file in
 accordance with the terms of the Adobe license agreement accompanying
 it. If you have received this file from a source other than Adobe,
 then your use, modification, or distribution of it requires the prior
 written permission of Adobe.
 */

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController <UITextFieldDelegate>

@property (nonatomic, assign) IBOutlet UILabel *lblTemperature;
@property (nonatomic, assign) IBOutlet UITextField *txtZip;
@property (nonatomic, assign) IBOutlet UIButton *btnGetWeather;
@property (nonatomic, assign) IBOutlet UILabel *lblConditions;

- (IBAction) getWeather:(id)sender;

@end

