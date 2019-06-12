//
//  ACPAnalytics.h
//  Adobe Digital Marketing Suite -- iOS Application Measurement Library
//
//  Copyright 1996-2019. Adobe, Inc. All Rights Reserved
//
//  Analytics Version: 2.1.1

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

/**
 *  @brief Retrieves the visitor identifier.
 *
 *  @param callback invoked with the visitor identifier value
 */
+ (void) getVisitorIdentifier: (nonnull void (^) (NSString* __nullable visitorIdentifier)) callback;

/**
 *  @brief Sets the visitor identifier.
 *
 *  @param visitorIdentifier the new value for visitor identifier
 */
+ (void) setVisitorIdentifier: (nonnull NSString*) visitorIdentifier;

@end
