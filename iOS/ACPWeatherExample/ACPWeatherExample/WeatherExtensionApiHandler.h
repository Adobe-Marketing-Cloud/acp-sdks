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

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class WeatherExtensionDataObject;

@interface WeatherExtensionApiHandler : NSObject

@property (nonatomic, strong) NSString *apiKey;

/**
 * Makes a network call and returns a dictionary with the temperature and conditions for the provided zip code
 * in the following format:
 * {
 *  "temp" : 47.1,
 *  "conditions" : "Clear"
 * }
 */
- (void) getWeatherForZip:(NSUInteger)zip callback:(nullable void (^) (NSDictionary* __nullable content))callback;

@end

NS_ASSUME_NONNULL_END
