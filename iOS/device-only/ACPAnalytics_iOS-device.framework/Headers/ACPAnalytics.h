//
//  ACPAnalytics.h
//  Adobe Digital Marketing Suite -- iOS Application Measurement Library
//
//  Copyright 1996-2018. Adobe, Inc. All Rights Reserved
//
//  Analytics Version: 1.1.0

#import <Foundation/Foundation.h>

@interface ACPAnalytics : NSObject {}

/**
 *  @brief Clears all hits from the tracking queue and removes them from the database.
 *  @warning Use caution when clearing the queue manually. This process cannot be reversed.
 */
+ (void) clearQueue;

/**
 * @brief Returns the current version of the ACPAnalytics Extension.
 */
+ (nonnull NSString*) extensionVersion;

/**
 *  @brief Retrieves the number of hits currently in the tracking queue
 *
 *  @param callback invoked with the queue size value
 */
+ (void) getQueueSize: (nonnull void (^) (NSUInteger queueSize)) callback;

/**
 *  @brief Retrieves the analytics tracking identifier.
 *
 *  @param callback invoked with the analytics identifier value
 */
+ (void) getTrackingIdentifier: (nonnull void (^) (NSString* __nullable trackingIdentifier)) callback;

/**
 * @brief Registers the ACPAnalytics extension with the Core Event Hub.
 */
+ (void) registerExtension;

/**
 *  @brief Forces analytics to send all queued hits regardless of current batch options
 */
+ (void) sendQueuedHits;

@end
