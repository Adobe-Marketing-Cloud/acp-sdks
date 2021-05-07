/*
Copyright 2018 Adobe. All rights reserved.
This file is licensed to you under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License. You may obtain a copy
of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS
OF ANY KIND, either express or implied. See the License for the specific language
governing permissions and limitations under the License.

Analytics Version: 2.5.0
*/

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
 *  @brief Retrieves the number of hits currently in the tracking queue
 *
 *  @param completionHandler method which is invoked with the queue size or an NSError if an unexpected error occurs or the request times out
 */
+ (void) getQueueSizeWithCompletionHandler: (nonnull void (^) (NSUInteger queueSize, NSError* __nullable error)) completionHandler;

/**
 *  @brief Retrieves the analytics tracking identifier.
 *
 *  @param callback invoked with the analytics identifier value
 */
+ (void) getTrackingIdentifier: (nonnull void (^) (NSString* __nullable trackingIdentifier)) callback;

/**
 *  @brief Retrieves the analytics tracking identifier.
 *
 *  @param completionHandler method which is invoked with the  analytics identifier or an NSError if an unexpected error occurs or the request times out
 */
+ (void) getTrackingIdentifierWithCompletionHandler: (nonnull void (^) (NSString* __nullable trackingIdentifier, NSError* __nullable error)) completionHandler;

/**
 *  @brief Registers the ACPAnalytics extension with the Core Event Hub.
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
 *  @brief Retrieves the visitor identifier.
 *
 *  @param completionHandler method which is invoked with the visitor identifier or an NSError if an unexpected error occurs or the request times out
 */
+ (void) getVisitorIdentifierWithCompletionHandler: (nonnull void (^) (NSString* __nullable visitorIdentifier, NSError* __nullable error)) completionHandler;

/**
 *  @brief Sets the visitor identifier.
 *
 *  @param visitorIdentifier the new value for visitor identifier
 */
+ (void) setVisitorIdentifier: (nonnull NSString*) visitorIdentifier;

@end
