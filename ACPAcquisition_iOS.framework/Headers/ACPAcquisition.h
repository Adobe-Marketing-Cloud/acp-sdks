//
//  ACPAcquisition.h
//  Adobe Digital Marketing Suite -- iOS Application Measurement Library
//
//  Copyright 1996-2018. Adobe, Inc. All Rights Reserved
//
//  Acquisition Version: 1.0

#import <Foundation/Foundation.h>

@class UNNotificationResponse;
@class CLLocation;

@interface ACPAcquisition : NSObject {}

#pragma mark - Acquisition

/**
 * @brief Registers the acquisition extension
 *
 * This method should be called before any other acquisition API is called
 */
+ (void) registerExtension;

/**
 * @brief Processes the acquisition campaign start event for the given application ID
 *
 * This method is provided as a way for you to create an acquisition link ad-hoc, and is meant
 * to support app-to-app acquisition.
 *
 * The applicationId should be that of the targeted destination app.  For example, if you are calling
 * this method in app "A", and you deeplink the user into your other app, "B", then you would
 * need to use the applicationId for app "B".
 *
 * This method is helpful for creating manual acquisition links and handling the app store redirect
 * yourself (such as with an SKStoreView).
 *
 * @param applicationId the application ID for which we want to track the acquisition flow.  This value is a unique
 *        identifier assigned to your app by Adobe Mobile Services.
 * @param data key-value pairs that will be attached in the resulting acquisition link.  At a minimum, this dictionary
 *        must contain the keys `a.referrer.campaign.name` and `a.referrer.campaign.source`
 */
+ (void) campaignStart: (nonnull NSString*) applicationId
              withData: (nullable NSDictionary<NSString*, NSString*>*) data;

/**
 * @brief Provide user info to the SDK from various launch points in your application
 *
 * This method should be called to support the following use cases:
 *
 *  1. Tracking Deep Link click-throughs
 *     - call from application:didFinishLaunchingWithOptions:
 *     - extract userInfo from UIApplicationLaunchOptionsURLKey
 *
 *  2. Tracking Push Message click-throughs
 *     - call from application:didReceiveRemoteNotification:fetchCompletionHandler:
 *
 *  3. Tracking Local Notification click-throughs
 *     - from application:didFinishLaunchingWithOptions: - pass the dictionary contained in the userInfo
 *       UIApplicationLaunchOptionsLocalNotificationKey (pre iOS 10)
 *     - for iOS 10 and newer, use \ref trackNotificationResponse:
 *
 *  If Analytics is enabled in your SDK, the collection of this launch data will result in an Analytics request being sent.
 *  Other components in the SDK may use the collected data as well (e.g. - as a rule condition for an In-App Message)
 *
 * @param userInfo Dictionary of data relevant to the expected use case.
 *        For example, userInfo may contain key-value pairs identifying an opened push message.
 */
+ (void) collectLaunchInfo: (nonnull NSDictionary*) userInfo;

/**
 * @brief Provide user info and location to the SDK from various launch points in your application.
 *
 * See \ref collectLaunchInfo:
 *
 * @param userInfo Dictionary of data relevant to the expected use case.
 *        For example, userInfo may contain key-value pairs identifying an opened push message.
 * @param location A {@link CLLocation} instance.  If a location is provided, the resulting SDK event will be
 decorated with latitude and longitude.
 */
+ (void) collectLaunchInfo: (nonnull NSDictionary*) userInfo
              withLocation: (nullable CLLocation*) location;

/**
 * @brief Returns the deferred deeplink attached to the acquisition install data if it exists, otherwise return a null value
 *
 * @param callback void method invoked with the URL of the acquisition deferred deeplink
 */
+ (void) getDeferredDeeplinkUrl: (nonnull void (^) (NSURL* __nullable deferredDeeplinkUrl)) callback;

/**
 * @brief Marshalls the provided deeplink and generates an event containing its data.
 *
 * This method should be called within the application:openURL:options: app delegate method.
 *
 * If Analytics is configured in the SDK, calling this method with a valid URL will result in an
 * Analytics request being sent.
 *
 * @param deeplink the NSURL that the application is processing
 */
+ (void) trackAdobeDeeplink: (nonnull NSURL*) deeplink;

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
