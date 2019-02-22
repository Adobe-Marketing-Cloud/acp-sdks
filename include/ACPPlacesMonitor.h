//
//  ACPPlacesMonitor.h
//  Adobe Experience Platform -- iOS Library
//
//  Copyright 1996-2019. Adobe. All Rights Reserved
//
//  Places Monitor Version: 0.0.1

#import <Foundation/Foundation.h>

@interface ACPPlacesMonitor : NSObject {}

/**
 * @brief Enable or disable logging from the ACPPlacesMonitor Extension
 *
 * @param loggingEnabled set to YES if you want the ACPPlacesMonitor to log to the console
 */
+ (void) setLoggingEnabled: (BOOL) loggingEnabled;

/**
 * @brief Returns the current version of the ACPPlacesMonitor Extension
 */
+ (nonnull NSString*) extensionVersion;

/**
 * @brief Registers the ACPPlacesMonitor extension with the Core Event Hub
 */
+ (void) registerExtension;

/**
 * @brief Start tracking the device's location and monitoring their nearby Places
 *
 * @discussion Use this method to start monitoring the user's GPS location.  Location monitoring can be done with
 * one of two strategies:
 *  - continuous - the monitor will receive and process location updates once per second.  Using this monitoring
 *    strategy consumes a lot power. For more information, see:
 *    https://developer.apple.com/documentation/corelocation/cllocationmanager/1423750-startupdatinglocation
 *  - significant changes - the monitor will only receive and process location updates when the device has
 *    moved a significant distance from the last time its location was processed.  Using this monitoring strategy
 *    consumes far less power than continuous monitoring.  For more information, see:
 *    https://developer.apple.com/documentation/corelocation/cllocationmanager/1423531-startmonitoringsignificantlocati
 *
 * Set the continuousMonitoring parameter to YES to use continuous monitoring, or NO to monitor for significant changes
 *
 * @param continuousMonitoring determines whether continuous monitoring will be enabled
 */
+ (void) startWithContinuousMonitoring: (BOOL) continuousMonitoring;

/**
 * @brief Stop tracking the device's location
 */
+ (void) stop;

/**
 * @brief Immediately gets an update for the device's location
 */
+ (void) updateLocationNow;

@end
