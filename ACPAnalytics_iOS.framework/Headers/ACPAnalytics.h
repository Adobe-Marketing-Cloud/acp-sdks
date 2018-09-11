//
//  ACPAnalytics.h
//  Adobe Digital Marketing Suite -- iOS Application Measurement Library
//
//  Copyright 1996-2018. Adobe, Inc. All Rights Reserved
//
//  Analytics Version: 1.0

#import <Foundation/Foundation.h>

@interface ACPAnalytics : NSObject {}

+ (void) registerAdobeAnalyticsExtension;

/**
 *  @brief Clears all hits from the tracking queue and removes them from the database.
 *  @warning Use caution when clearing the queue manually. This process cannot be reversed.
 */
+ (void) analyticsClearQueue;

/**
 *  @brief Retrieves the number of hits currently in the tracking queue
 *
 *  @param callback invoked with the queue size value
 */
+ (void) analyticsGetQueueSize: (nonnull void (^) (NSUInteger queueSize)) callback;

/**
 *  @brief Retrieves the analytics tracking identifier.
 *
 *  @param callback invoked with the analytics identifier value
 */
+ (void) analyticsGetTrackingIdentifier: (nonnull void (^) (NSString* __nullable trackingIdentifier)) callback;

/**
 *  @brief Forces analytics to send all queued hits regardless of current batch options
 */
+ (void) analyticsSendQueuedHits;

/**
 *  @brief This method sends an Analytics action tracking hit with context data
 *
 *  Actions represent events that occur in your application that you want to measure; the corresponding metrics will
 *  be incremented each time the event occurs. For example, you may want to track when an user click on the login
 *  button or a certain article was viewed.
 *
 *  @note calling this API will not increment page views
 *
 *  @param action NSString containing the name of the action to track
 *  @param data NSDictionary<NSString, NSString> containing context data to attach on this hit
 */
+ (void) analyticsTrackAction: (nullable NSString*) action data: (nullable NSDictionary*) data;

/**
 *  @brief This method sends an Analytics state tracking hit with context data
 *
 *  States represent different screens or views of you application. When the user navigates between application pages,
 *  a new track call should be sent with current state name. Tracking state name is typically called from an
 *  UIViewController in the viewDidLoad method.
 *
 *  @note calling this API will increment page views
 *
 *  @param state NSString containing the name of the state to track
 *  @param data NSDictionary<NSString, NSString> containing context data to attach on this hit
 */
+ (void) analyticsTrackState: (nullable NSString*) state data: (nullable NSDictionary*) data;

@end
