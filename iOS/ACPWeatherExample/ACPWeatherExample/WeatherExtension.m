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
#import "ACPExtensionEvent.h"
#import "WeatherExtension.h"
#import "WeatherExtensionInternal.h"
#import "WeatherExtensionDataObject.h"

@implementation WeatherExtension

#pragma mark - WeatherExtension Public API methods
+ (void) registerExtension {
    NSError *error = nil;
    if ([ACPCore registerExtension:[WeatherExtensionInternal class] error:&error]) {
        NSLog(@"WeatherExtension was successfully registered");
    } else {
        NSLog(@"An error occurred while attempting to register WeatherExtension: %@", [error localizedDescription]);
    }
}

+ (void) getWeatherByZipCode:(NSUInteger)zip callback:(nullable void (^) (WeatherExtensionDataObject* __nullable content))callback {
    // create the request event
    NSError *eventError = nil;
    NSDictionary *requestData = @{@"zip":@(zip)};
    ACPExtensionEvent *getWeatherEvent = [ACPExtensionEvent extensionEventWithName:@"Get Weather"
                                                                              type:@"com.acpExample.eventType.weatherExtension"
                                                                            source:@"com.acpExample.eventSource.requestContent"
                                                                              data:requestData
                                                                             error:&eventError];
    if (!getWeatherEvent) {
        NSLog(@"An error occurred constructing event '%@': %@", getWeatherEvent.eventName, eventError.localizedDescription ?: @"unknown");
    }
    
    // dispatch the event and handle the callback
    NSError *dispatchError = nil;
    if ([ACPCore dispatchEventWithResponseCallback:getWeatherEvent responseCallback:^(ACPExtensionEvent * _Nonnull responseEvent) {
        NSLog(@"In response callback for event '%@', event data returned: %@", responseEvent.eventName, responseEvent.eventData);
        NSDictionary *weather = responseEvent.eventData[@"weather"];
        double temp = [weather[@"temp"] doubleValue];
        NSString *conditions = weather[@"conditions"];
        WeatherExtensionDataObject *weatherObject = [WeatherExtensionDataObject weatherWithTemp:temp conditions:conditions];
        callback(weatherObject);
    } error:&dispatchError]) {
        NSLog(@"WeatherExtension dispatched an event '%@'", getWeatherEvent.eventName);
    } else {
        NSLog(@"An error occurred dispatching event '%@': %@", getWeatherEvent.eventName, dispatchError.localizedDescription ?: @"unknown");
    }
}

@end
