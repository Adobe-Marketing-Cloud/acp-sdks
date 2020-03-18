//
//  ACPCampaignClassic.h
//  Adobe Experience Platform -- iOS Application Measurement Library
//
//  Copyright 1996-2019. Adobe Inc. All Rights Reserved
//
//  Campaign Classic Version: 2.0.3

#import <Foundation/Foundation.h>

@interface ACPCampaignClassic : NSObject {}

#pragma mark - CampaignClassic

/**
 * @brief Returns the current version of the ACPCampaignClassic Extension.
 */
+ (nonnull NSString*) extensionVersion;

/**
 * @brief Registers the ACPCampaignClassic extension with the Core Event Hub.
 */
+ (void) registerExtension;

/**
 *  @brief Registers a device with the configured Adobe Campaign Classic server instance.
 *  The \p callback will be executed when the registration request is completed, returning success status of the call.
 *
 *  @param token a unique token received from the push notification service in application:didRegisterForRemoteNotificationsWithDeviceToken: callback
 *  @param userKey string containing the user identifier
 *  @param additionalParams a dictionary of custom key-value pairs to be sent in the registration call
 *  @param callback a function pointer which will be called after the device registration is complete. The success
 *  in the callback will be YES if the registration request completed successfully, NO otherwise
 */
+ (void) registerDevice: (nonnull NSData*) token userKey: (nullable NSString*) userKey additionalParams: (nullable NSDictionary*) additionalParams callback: (nullable void (^) (BOOL success)) callback;

/**
 *  @brief Sends tracking information to the configured Adobe Campaign Classic server.
 *  Use this API to send tracking info on receiving a notification (silent push).
 *
 *  @param trackInfo a dictionary containing `_dId` and `_mId` received in the push message payload, or in the
 *  launch options before opening the application
 */
+ (void) trackNotificationReceive: (nonnull NSDictionary<NSString*, NSString*>*) trackInfo;

/**
 *  @brief Sends tracking information to the configured Adobe Campaign Classic server.
 *  Use this API to send tracking info when the application is opened following a notification.
 *
 *  @param trackInfo a dictionary containing `_dId` and `_mId` received in the push message payload, or in the
 *  launch options before opening the application
 */
+ (void) trackNotificationClick: (nonnull NSDictionary<NSString*, NSString*>*) trackInfo;


@end
