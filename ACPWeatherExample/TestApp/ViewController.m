//
//  ViewController.m
//  Adobe Cloud Platform -- ACP SDK Extension for iOS
//
//  Copyright 1996-2019 Adobe. All Rights Reserved.
//

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
    [WeatherExtension getWeatherByZipCode:[_txtZip.text integerValue] callback:^(WeatherExtensionDataObject * _Nullable weather) {
        NSLog(@"In the response callback: %@", weather);
        dispatch_async(dispatch_get_main_queue(), ^{
            self.lblConditions.text = weather.conditions;
            self.lblTemperature.text = [NSString stringWithFormat:@"%0.0f ℉", weather.temperature];
            self.lblTemperature.textColor = weather.tempColor;
        });
    }];
}

- (IBAction) getWeatherByTriggeringRules:(id)sender {
    [self.txtZip resignFirstResponder];
    long zip = [_txtZip.text integerValue];
    NSDictionary* contextData = @{@"zip" : [NSString stringWithFormat:@"%ld", zip]};
    [ACPCore trackAction:@"getWeatherByTriggeringRules" data:contextData];
}

@end
