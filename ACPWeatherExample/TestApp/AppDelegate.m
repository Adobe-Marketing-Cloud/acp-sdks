//
//  AppDelegate.m
//  Adobe Cloud Platform -- ACP SDK Extension for iOS
//
//  Copyright 1996-2019 Adobe. All Rights Reserved.
//

#import "AppDelegate.h"
#import "WeatherExtension.h"
#import "ACPCore.h"
#import "ACPIdentity.h"
#import "ACPSignal.h"
#import "ACPLifecycle.h"
#import "ACPAnalytics.h"

// fill in your API key here
static NSString *const ACPWeatherExampleApiKey = @"";

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    
    [ACPCore setLogLevel:ACPMobileLogLevelError];
    [ACPCore configureWithAppId:@"staging/launch-ENb44c5c8eb4ac4c5b8c89b6afffc167f7-development"];
    
    // register the weather extension
    [WeatherExtension registerExtension];
    
    // register Adobe core extensions
    [ACPIdentity registerExtension];
    [ACPSignal registerExtension];
    [ACPLifecycle registerExtension];
    [ACPAnalytics registerExtension];
    
    // after registering all the extensions, call ACPCore start to start procesing events in the Event Hub
    [ACPCore start:^{
        [ACPCore updateConfiguration:@{@"weather.apiKey":ACPWeatherExampleApiKey}];
        dispatch_async(dispatch_get_main_queue(), ^{
            if ([[UIApplication sharedApplication] applicationState] != UIApplicationStateBackground) {
                [ACPCore lifecycleStart:nil];
            }
        });
    }];
    
    return YES;
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    [ACPCore lifecyclePause];
}


- (void)applicationWillEnterForeground:(UIApplication *)application {
    [ACPCore lifecycleStart:nil];
}

@end
