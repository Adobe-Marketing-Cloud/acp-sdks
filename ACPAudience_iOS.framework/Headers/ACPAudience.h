/***************************************************************************
 *
 * ADOBE CONFIDENTIAL
 * ___________________
 *
 * Copyright 2018 Adobe Systems Incorporated
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Adobe Systems Incorporated and its suppliers,
 * if any.  The intellectual and technical concepts contained
 * herein are proprietary to Adobe Systems Incorporated and its
 * suppliers and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Adobe Systems Incorporated.
 *
 **************************************************************************/
//  Audience Version: 1.0.0

#import <Foundation/Foundation.h>

@interface ACPAudience : NSObject {}

/**
 * @brief Returns the current version of the ACPAudience Extension.
 */
+ (nonnull NSString*) extensionVersion;

/**
 * @brief Returns the visitor profile that was most recently obtained.
 * @discussion Visitor profile is saved in NSUserDefaults for easy access across multiple launches of your app.
 *             If no signal has been submitted, nil is returned.
 *
 * @param callback void method invoked with the visitor's profile as a parameter
 */
+ (void) getVisitorProfile: (nonnull void (^) (NSDictionary* __nullable visitorProfile)) callback;

/**
 * @brief Registers the ACPAudience extension with the Core Event Hub.
 */
+ (void) registerExtension;

/**
 * @brief Resets the Audience Manager UUID and purges the current visitor profile from NSUserDefaults.
 * @discussion Audience reset also clears the current in-memory DPID and DPUUID variables.
 */
+ (void) reset;

/**
 * @brief Sends Audience Manager a signal with traits and returns the matching segments for the visitor in a callback.
 * @discussion Audience manager sends AAM UUID in response in initial signal call. AAM UUID is persisted in
 *             NSUserDefaults and sent by SDK in all subsequent signal requests. If available, Experience Cloud ID (MID) is
 *             also sent in each signal request along with DPID and DPUUID. The visitor profile that AAM returns is
 *             saved in NSUserDefaults and updated with every signal call.
 *
 * @param data Traits data for the current visitor
 * @param callback void method invoked with the visitor's profile as a parameter
 */
+ (void) signalWithData: (NSDictionary<NSString*, NSString*>* __nullable) data
               callback: (nullable void (^) (NSDictionary* __nullable visitorProfile)) callback;


@end
