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

#import "WeatherExtensionDataObject.h"

@implementation WeatherExtensionDataObject

+ (WeatherExtensionDataObject *) weatherWithTemp:(double)temp conditions:(NSString *)conditions {
    WeatherExtensionDataObject *me = [[WeatherExtensionDataObject alloc] init];
    
    me.temperature = temp;
    me.tempColor = [WeatherExtensionDataObject colorForTemp:temp];
    me.conditions = conditions;
//    me.picture = [WeatherExtensionDataObject imageForConditions:conditions];
    
    return me;
}

+ (UIColor *) colorForTemp:(double)temp {
    if (temp <= 45.0) {
        return [UIColor blueColor];
    } else if (temp > 45.0 && temp < 80.0) {
        return [UIColor orangeColor];
    } else {
        return [UIColor redColor];
    }
}

+ (UIImage *) imageForConditions:(NSString *)conditions {
    static NSDictionary *conditionsImages;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        conditionsImages = @{
                             @"Sunny" : [UIImage imageNamed:@"sun2.jpg"],
                             @"Clear" : [UIImage imageNamed:@"Sun.png"],
                             @"rain" : [UIImage imageNamed:@"rain.png"],
                             @"cloudy" : [UIImage imageNamed:@"cloudy.png"],
                             @"lightning" : [UIImage imageNamed:@"lightning.jpg"]
                             };
    });
    
    return conditionsImages[conditions];
}

- (NSString *) description {
    return [NSString stringWithFormat:@"Temperature: %f - Conditions: %@", _temperature, _conditions];
}

@end
