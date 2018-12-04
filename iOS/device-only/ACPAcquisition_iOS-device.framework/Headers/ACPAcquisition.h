//
//  ACPAcquisition.h
//  Adobe Digital Marketing Suite -- iOS Application Measurement Library
//
//  Copyright 1996-2018. Adobe, Inc. All Rights Reserved
//
//  Acquisition Version: 1.1.0

#import <Foundation/Foundation.h>

@class UNNotificationResponse;

@interface ACPAcquisition : NSObject {}

/**
 * @brief Returns the current version of the ACPAnalytics Extension.
 */
+ (nonnull NSString*) extensionVersion;

/**
 * @brief Registers the acquisition extension
 *
 * This method should be called before any other acquisition API is called
 */
+ (void) registerExtension;

#if TARGET_OS_IOS || TARGET_OS_WATCH
/**
 * @brief Marshalls the provided UNNotificationResponse and generates an event containing its data.
 *
 * This method should be called to process a user's response to a notification.  The SDK will determine if the
 * notification was sent via Push or Local Notification and handle it accordingly.
 *
 * In your UNUserNotificationCenterDelegate, you should call this method in the implementation of the
 * userNotificationCenter:didReceiveNotificationResponse:withCompletionHandler: delegate method.
 *
 * Though not required, it is recommended that your UIApplicationDelegate also be your UNUserNotificationCenterDelegate.
 *
 * @param response the UNNotificationResponse passed to you by the delegate method
 */
+ (void) trackNotificationResponse: (nonnull UNNotificationResponse*) response;
#endif

@end
