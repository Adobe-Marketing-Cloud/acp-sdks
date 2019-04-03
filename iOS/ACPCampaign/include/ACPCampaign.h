//
//  ACPCampaign.h
//  Adobe Experience Platform -- iOS Application Measurement Library
//
//  Copyright 1996-2019. Adobe Inc. All Rights Reserved
//
//  Campaign Version: 1.0.1

#import <Foundation/Foundation.h>

@interface ACPCampaign : NSObject {}

/**
 * @brief Returns the current version of the ACPCampaign extension.
 */
+ (nonnull NSString*) extensionVersion;

/**
 * @brief Registers the ACPCampaign extension with the Core Event Hub.
 */
+ (void) registerExtension;

/**
 * @brief Sets the Campaign linkage fields (CRM IDs) in the mobile SDK to be used for downloading personalized messages from Campaign.
 *
 * The set linkage fields are stored as base64 encoded JSON string in memory and they are sent in a custom HTTP header 'X-InApp-Auth'
 * in all future Campaign rules download requests until ACPCampaign::resetLinkageFields is invoked. These in-memory variables are also
 * lost in the wake of an Application crash event or upon graceful Application termination or when the privacy status is updated to
 * \ref ACPMobilePrivacyStatusOptOut.
 *
 * This method clears cached rules from previous download before triggering a rules download request to the configured Campaign server.
 * If the current SDK privacy status is not \ref ACPMobilePrivacyStatusOptIn, no rules download happens.
 *
 * @param linkageFields a dictionary containing linkage field key-value pairs
 * @see ACPMobilePrivacyStatus
 */
+ (void) setLinkageFields: (nonnull NSDictionary<NSString*, NSString*>*) linkageFields;

/**
 * @brief Clears previously stored linkage fields in the mobile SDK and triggers Campaign rules download request to the configured Campaign server.
 *
 * This method unregisters any previously registered rules with the Event Hub and clears cached rules from previous download.
 * If the current SDK privacy status is not \ref ACPMobilePrivacyStatusOptIn, no rules download happens.
 *
 * @see ACPMobilePrivacyStatus
 */
+ (void) resetLinkageFields;

@end
