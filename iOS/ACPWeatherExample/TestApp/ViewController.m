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

#import "ACPCore.h"
#import "ViewController.h"
#import "WeatherExtension.h"
#import "WeatherExtensionDataObject.h"

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.txtZip.delegate = self;
}

/**
 *  sample zip codes:
 *  -------------------
 *  Times Square, NY - 10036
 *  Lehi, UT - 84043
 *  Beverly Hills, CA - 90210
 *  Fairbanks, AK - 99703
 */
- (IBAction) getWeather:(id)sender {
    [self.txtZip resignFirstResponder];
    NSString* zipString = _txtZip.text;

    // retrieve the weather conditions for current zipcode by calling the getWeatherByZipCode public API
    [WeatherExtension getWeatherByZipCode:[zipString integerValue] callback:^(WeatherExtensionDataObject * _Nullable weather) {
        NSLog(@"Received response callback from weather extension: %@", weather);
        dispatch_async(dispatch_get_main_queue(), ^{
            self.lblConditions.text = weather.conditions ? weather.conditions : @"Unknown";
            self.lblTemperature.text = [NSString stringWithFormat:@"%0.0f ℉", weather.temperature];
            self.lblTemperature.textColor = weather.tempColor;
        });
    }];
}

- (IBAction)getWeatherByTriggeringRules:(id)sender {
    [self.txtZip resignFirstResponder];
    NSString* zipString = _txtZip.text;

    // Send an analytics track request with zip as context data. This will trigger the rule set up
    // in Launch UI for Mobile Core track action with context data key "zip" and the Weather extension
    // can process the rule consequence event
    NSDictionary* contextData = @{@"zip" : zipString};
    [ACPCore trackAction:@"getWeatherByTriggeringRules" data:contextData];
}

@end
