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
#import "WeatherExtensionApiHandler.h"
#import "WeatherExtensionDataObject.h"

@implementation WeatherExtensionApiHandler

static NSString* WEATHER_TEMPERATURE_KEY = @"temp";
static NSString* WEATHER_CONDITIONS_KEY = @"conditions";

- (void) getWeatherForZip:(NSUInteger)zip callback:(nullable void (^) (NSDictionary* __nullable content))callback {
    NSString *urlString = [NSString stringWithFormat:@"https://api.openweathermap.org/data/2.5/weather?zip=%lu,us&units=imperial&APPID=%@", (unsigned long)zip, _apiKey];
    NSURL *url = [NSURL URLWithString:urlString];
    NSURLSessionConfiguration *config = [NSURLSessionConfiguration defaultSessionConfiguration];
    NSURLSession *session = [NSURLSession sessionWithConfiguration:config];
    NSURLSessionTask *task = [session dataTaskWithURL:url completionHandler:^(NSData * _Nullable data, NSURLResponse * _Nullable response, NSError * _Nullable error) {
        if (error) {
            [ACPCore log:ACPMobileLogLevelError tag:@"WeatherExtensionApiHandler" message:[NSString stringWithFormat:@"There was an error making the request to openweathermap: %@", error.localizedDescription]];
            if (callback) {
                callback(nil);
            }
        }
        
        // get json from the data
        NSError *jsonError = nil;
        NSDictionary *jsonResponse = [NSJSONSerialization JSONObjectWithData:data options:NSJSONReadingMutableContainers error:&jsonError];
        if (!jsonResponse || jsonError) {
            [ACPCore log:ACPMobileLogLevelError tag:@"WeatherExtensionApiHandler" message:[NSString stringWithFormat:@"There was an error parsing the response from openweathermap: %@", jsonError.localizedDescription]];
            if (callback) {
                callback(nil);
            }
        }
        
        // do something with the dictionary and pass it back
        if (callback) {
            callback([WeatherExtensionApiHandler getWeatherForResponse:jsonResponse]);
        }
    }];
    [task resume];
}

+ (NSDictionary *) getWeatherForResponse:(NSDictionary *)response {
    NSDictionary *mainData = response[@"main"];
    NSString *temp = [NSString stringWithFormat:@"%0.0f", [mainData[@"temp"] doubleValue]];
    
    NSDictionary *conditionsData = response[@"weather"][0];
    NSString *conditions = conditionsData[@"main"];
    
    return @{WEATHER_TEMPERATURE_KEY:temp ?: @"unknown",
             WEATHER_CONDITIONS_KEY:conditions ?: @"unknown"
             };
}

@end
