//
//  WeatherExtensionApiHandler.h
//  Adobe Cloud Platform -- ACP SDK Extension for iOS
//
//  Copyright 1996-2018 Adobe. All Rights Reserved.
//

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
