//
//  ACPTarget.h
//  Adobe Digital Marketing Suite -- iOS Application Measurement Library
//
//  Copyright 1996-2018. Adobe, Inc. All Rights Reserved
//
//  Target Version: 1.0

#import <Foundation/Foundation.h>

// audience
@interface ACPAudience : NSObject {}

#pragma mark - Audience

+ (void) registerExtension;

#pragma mark - Audience Manager

/**
 * @brief Returns the dictionary of current Data Provider ID (DPID) and the current Data Provider Unique User ID (DPUUID).
 * @discussion Data Provider ID, also referred to as Data Source ID is assigned to each data source in
 *             Audience Manager. If DPID is not set, nil is returned.
 *             Data Provider Unique User ID, also referred to as CRM ID is the data provider's unique ID
 *             for the user in their CRM system. DPUUIDs can be synced with Audience Manager UUIDs. If DPUUID
 *             is not set, nil is returned.

 * @param callback void method invoked with the dataProviderIDs dictionary as a parameter
 */
+ (void) getDpidAndDpuuid: (nonnull void (^) (NSDictionary* __nullable dataProviderIDs)) callback;

/**
 * @brief Returns the visitor profile that was most recently obtained.
 * @discussion Visitor profile is saved in NSUserDefaults for easy access across multiple launches of your app.
 *             If no signal has been submitted, nil is returned.
 *
 * @param callback void method invoked with the visitor's profile as a parameter
 */
+ (void) getVisitorProfile: (nonnull void (^) (NSDictionary* __nullable visitorProfile)) callback;

/**
 * @brief Resets the Audience Manager UUID and purges the current visitor profile from NSUserDefaults.
 * @discussion Audience reset also clears the current in-memory DPID and DPUUID variables.
 */
+ (void) reset;

/**
 * @brief Sets the DPID and DPUUID. If DPID and DPUUID are set, they will be sent with each signal.
 * @discusssion If the DPID that is set does not match an existing data source on Audience Manager,
 *              signal call returns an error.
 *
 * @param dpid the dpid String
 * @param dpuuid the dpuuid String
 */
+ (void) setDpid: (NSString* __nullable) dpid
          dpuuid: (NSString* __nullable) dpuuid;

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
