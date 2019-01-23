//
//  ACPIdentity.h
//  Adobe Experience Platform -- iOS Library
//
//  Copyright 1996-2019. Adobe. All Rights Reserved
//
//  Identity Version: 2.0.1

#import <Foundation/Foundation.h>

@class ACPMobileVisitorId;
typedef NS_ENUM(NSUInteger, ACPMobileVisitorAuthenticationState);

@interface ACPIdentity : NSObject {}

#pragma mark - Identity

/**
 * @brief Appends visitor information to the given URL.
 *
 * If the given url is nil or empty, it is returned as is. Otherwise, the following information is added to the query section of the given URL.
 * The attribute `adobe_mc` is an URL encoded list containing the Experience Cloud ID, Experience Cloud Org ID, and a timestamp when this request
 * was made. The attribute `adobe_aa_vid` is the URL encoded Visitor ID, however the attribute is only included
 * if the Visitor ID was previously set.
 *
 * @param baseUrl URL to which the visitor info needs to be appended. Returned as is if it is nil or empty.
 * @param callback method which will be invoked once the updated url is available.
 */
+(void) appendToUrl:(nullable NSURL*)baseUrl withCallback:(nullable void(^)(NSURL* __nullable urlWithVisitorData))
    callback;

/**
 * @brief Returns the current version of the ACPIdentity Extension.
 */
+(nonnull NSString*) extensionVersion;

/**
 * @brief Returns all customer identifiers which were previously synced with the Adobe Experience Cloud.
 *
 * @param callback method which will be invoked once the customer identifiers are available.
 * @see ADBMobileMarketing::syncIdentifier:identifier:authentication:
 * @see ADBMobileMarketing::syncIdentifiers:
 */
+(void) getIdentifiers:(nonnull void(^)(NSArray<ACPMobileVisitorId*>* __nullable visitorIDs))callback;

/**
 * @brief Returns the Experience Cloud ID.
 *
 * The Experience Cloud ID is generated at initial launch and is stored and used from that point forward.
 * This ID is preserved between app upgrades, is saved and restored during the standard application backup process,
 * and is removed at uninstall.
 *
 * @param callback method which will be invoked once Experience Cloud ID is available.
 */
+(void) getExperienceCloudId:(nonnull void(^)(NSString* __nullable experienceCloudId))callback;

/**
 * @brief Registers the ACPIdentity extension with the Core Event Hub.
 */
+(void) registerExtension;

/**
 * @brief Updates the given customer ID with the Adobe Experience Cloud ID Service.
 *
 * Synchronizes the provided customer identifier type key and value with the given
 * authentication state to the Adobe Experience Cloud ID Service.
 * If the given customer ID type already exists in the service, then
 * it is updated with the new ID and authentication state. Otherwise a new customer ID is added.
 *
 * This ID is preserved between app upgrades, is saved and restored during the standard application backup process,
 * and is removed at uninstall.
 *
 * If the current SDK privacy status is \ref ADBMobilePrivacyStatusOptOut, then this operation performs no action.
 *
 * @param identifierType    a unique type to identify this customer ID
 * @param identifier        the customer ID to set
 * @param authenticationState a valid \ref ACPMobileVisitorAuthenticationState value.
 * @see ADBMobilePrivacyStatus
 */
+(void) syncIdentifier:(nonnull NSString*)identifierType
    identifier:(nonnull NSString*)identifier
    authentication:(ACPMobileVisitorAuthenticationState)authenticationState;

/**
 * @brief Updates the given customer IDs with the Adobe Experience Cloud ID Service.
 *
 * Synchronizes the provided customer identifiers to the Adobe Experience Cloud ID Service.
 * If a customer ID type matches an existing ID type, then it is updated with the new ID value
 * and authentication state. New customer IDs are added. All given customer IDs are given the default
 * authentication state of \ref ADBMobileVisitorAuthenticationStateUnknown.
 *
 * These IDs are preserved between app upgrades, are saved and restored during the standard application backup process,
 * and are removed at uninstall.
 *
 * If the current SDK privacy status is \ref ACPMobilePrivacyStatusOptOut, then this operation performs no action.
 *
 * @param identifiers a dictionary of customer IDs
 * @see ADBMobilePrivacyStatus
 */
+(void) syncIdentifiers:(nullable NSDictionary*)identifiers;

/**
 * @brief Updates the given customer IDs with the Adobe Experience Cloud ID Service.
 *
 * Synchronizes the provided customer identifiers to the Adobe Experience Cloud ID Service.
 * If a customer ID type matches an existing ID type, then it is updated with the new customer ID value
 * and authentication state. New customer IDs are added.
 *
 * These IDs are preserved between app upgrades, are saved and restored during the standard application backup process,
 * and are removed at uninstall.
 *
 * If the current SDK privacy status is \ref ACPMobilePrivacyStatusOptOut, then this operation performs no action.
 *
 * @param identifiers a dictionary of customer IDs
 * @param authenticationState a valid \ref ACPMobileVisitorAuthenticationState value.
 * @see ADBMobilePrivacyStatus
 */
+(void) syncIdentifiers:(nullable NSDictionary*)identifiers
    authentication:(ACPMobileVisitorAuthenticationState)authenticationState;

@end
