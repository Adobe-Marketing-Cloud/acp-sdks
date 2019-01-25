//
//  WeatherExtension.h
//  Adobe Cloud Platform -- ACP SDK Extension for iOS
//
//  Copyright 1996-2019 Adobe. All Rights Reserved.
//
//  WeatherExtension Version: 1.0.0
//
//  WeatherExtension is using the free tier of weather-related APIs available at:
//  https://openweathermap.org/
//
//  The ACPWeatherExample is being provided by Adobe to demonstrate how to make
//  custom extensions to integrate into the Adobe Cloud Platform SDK's ecosystem.

NS_ASSUME_NONNULL_BEGIN

@class WeatherExtensionDataObject;

@interface WeatherExtension : NSObject

#pragma mark - WeatherExtension Public API methods
/**
 * @brief Gets the current weather and conditions for the provided zip code
 *
 * This method results in an asynchronous network call to get the local weather.  Once the network call has received
 * a response, the WeatherExtension class will parse the results and return it via the content parameter in
 * the provided callback block.
 *
 * @param zip NSUInteger representing a US postal code
 * @param callback a void callback method which contains the current weather information
 */
+ (void) getWeatherByZipCode:(NSUInteger)zip callback:(nullable void (^) (WeatherExtensionDataObject* __nullable content))callback;

@end

NS_ASSUME_NONNULL_END
