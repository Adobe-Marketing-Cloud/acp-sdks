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

//  WeatherExtension Version: 1.0.0
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
 * Registers the WeatherExtension with the ACPCore in order to receive and dispatch new events
 * though the internal Event Hub. This method should be called once, when the application is initialized
 * in the AppDelegate.m class
 */
+ (void) registerExtension;

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
