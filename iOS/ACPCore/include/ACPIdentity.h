/*
Copyright 2017 Adobe. All rights reserved.
This file is licensed to you under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License. You may obtain a copy
of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS
OF ANY KIND, either express or implied. See the License for the specific language
governing permissions and limitations under the License.

Identity Version: 2.3.2
*/
#import <Foundation/Foundation.h>

@class ACPMobileVisitorId;
typedef NS_ENUM(NSUInteger, ACPMobileVisitorAuthenticationState);

@interface ACPIdentity : NSObject {}

#pragma mark - Identity

/**
 * @brief Appends visitor information to the given URL.
 *
 * If the given url is nil or empty, it is returned as is. Otherwise, the following information is added to the query section of the given URL.
 * The attribute `adobe_mc` is an URL encoded list containing the Experience Cloud ID, Experience Cloud Org ID,
 * Analytics Tracking ID if available from Analytics, and a timestamp when this request
 * was made. The attribute `adobe_aa_vid` is the URL encoded Analytics Customer Visitor ID, if previously set in
 * Analytics extension.
 *
 * @param baseUrl URL to which the visitor info needs to be appended. Returned as is if it is nil or empty.
 * @param callback method which will be invoked once the updated url is available.
 */
+ (void) appendToUrl: (nullable NSURL*) baseUrl withCallback: (nullable void (^) (NSURL* __nullable urlWithVisitorData))
    callback;

/**
* @brief Appends visitor information to the given URL or returns an error if the request fails.
*
* If the given url is nil or empty, it is returned as is. Otherwise, the following information is added to the query section of the given URL.
* The attribute `adobe_mc` is an URL encoded list containing the Experience Cloud ID, Experience Cloud Org ID,
* Analytics Tracking ID if available from Analytics, and a timestamp when this request
* was made. The attribute `adobe_aa_vid` is the URL encoded Analytics Customer Visitor ID, if previously set in
* Analytics extension.
*
* @param baseUrl URL to which the visitor info needs to be appended. Returned as is if it is nil or empty.
* @param completionHandler method which will be invoked once the updated url is available or passed an NSError if an unexpected error occurs or the request times out
*/
+ (void) appendToUrl: (nullable NSURL*) baseUrl withCompletionHandler: (nullable void (^) (NSURL* __nullable urlWithVersionData, NSError* __nullable error)) completionHandler;

/**
 * @brief Returns the current version of the ACPIdentity Extension.
 */
+ (nonnull NSString*) extensionVersion;

/**
 * @brief Returns all customer identifiers which were previously synced with the Adobe Experience Cloud.
 *
 * @param callback method which will be invoked once the customer identifiers are available.
 * @see ADBMobileMarketing::syncIdentifier:identifier:authentication:
 * @see ADBMobileMarketing::syncIdentifiers:
 */
+ (void) getIdentifiers: (nonnull void (^) (NSArray<ACPMobileVisitorId*>* __nullable visitorIDs)) callback;

/**
* @brief Returns all customer identifiers which were previously synced with the Adobe Experience Cloud or an error if the request fails.
*
* @param completionHandler method which will be invoked once the customer identifiers are available or passed an NSError if an unexpected error occurs or the request times out
* @see ADBMobileMarketing::syncIdentifier:identifier:authentication:
* @see ADBMobileMarketing::syncIdentifiers:
*/
+ (void) getIdentifiersWithCompletionHandler: (nonnull void (^) (NSArray<ACPMobileVisitorId*>* __nullable visitorIDs, NSError* __nullable error)) completionHandler;

/**
 * @brief Returns the Experience Cloud ID.
 *
 * The Experience Cloud ID is generated at initial launch and is stored and used from that point forward.
 * This ID is preserved between app upgrades, is saved and restored during the standard application backup process,
 * and is removed at uninstall.
 *
 * @param callback method which will be invoked once Experience Cloud ID is available.
 */
+ (void) getExperienceCloudId: (nonnull void (^) (NSString* __nullable experienceCloudId)) callback;

/**
* @brief Returns the Experience Cloud ID or an error if the request fails.
*
* The Experience Cloud ID is generated at initial launch and is stored and used from that point forward.
* This ID is preserved between app upgrades, is saved and restored during the standard application backup process,
* and is removed at uninstall.
*
* @param completionHandler method which will be invoked once Experience Cloud ID is available or passed an NSError if an unexpected error occurs or the request times out
*/
+ (void) getExperienceCloudIdWithCompletionHandler: (nonnull void (^) (NSString* __nullable experienceCloudId, NSError* __nullable error)) completionHandler;

/**
 * @brief Registers the ACPIdentity extension with the Core Event Hub.
 */
+ (void) registerExtension;

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
 * @param identifierType    a unique type to identify this customer ID, should be non empty and non nil value
 * @param identifier        the customer ID to set, should be non empty and non nil value
 * @param authenticationState a valid \ref ACPMobileVisitorAuthenticationState value.
 * @see ADBMobilePrivacyStatus
 */
+ (void) syncIdentifier: (nonnull NSString*) identifierType
             identifier: (nonnull NSString*) identifier
         authentication: (ACPMobileVisitorAuthenticationState) authenticationState;

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
 * @param identifiers a dictionary containing identifier type as the key and identifier as the value.
 *                    Both identifier type and identifier should be non empty and non nil values.
 * @see ADBMobilePrivacyStatus
 */
+ (void) syncIdentifiers: (nullable NSDictionary*) identifiers;

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
 * @param identifiers a dictionary containing identifier type as the key and identifier as the value.
 *                    Both identifier type and identifier should be non empty and non nil values.
 * @param authenticationState a valid \ref ACPMobileVisitorAuthenticationState value.
 * @see ADBMobilePrivacyStatus
 */
+ (void) syncIdentifiers: (nullable NSDictionary*) identifiers
          authentication: (ACPMobileVisitorAuthenticationState) authenticationState;

/**
 * @brief Gets Visitor ID Service identifiers in URL query string form for consumption in hybrid mobile apps.
 *
 * Retrieves the visitor identifiers as a URL query parameter string.
 * There will be no leading '&' or '?' punctuation, as the caller is responsible for placing the string in the correct
 * location of their resulting URL. If there is not a valid URL string to return, or if an error occurs, callback will
 * contain nil. Otherwise, the following information is added to the query section of the given URL.
 * The attribute `adobe_mc` is an URL encoded list containing the Experience Cloud ID, Experience Cloud Org ID,
 * Analytics Tracking ID if available from Analytics, and a timestamp when this request
 * was made. The attribute `adobe_aa_vid` is the URL encoded Analytics Customer Visitor ID, if previously set in
 * Analytics extension.
 *
 * @param callback a block pointer to call with an NSString value containing the visitor identifiers as a query
 * string upon completion of the service request
 */
+ (void) getUrlVariables: (nonnull void (^) (NSString* __nullable urlVariables)) callback;

/**
* @brief Gets Visitor ID Service identifiers in URL query string form for consumption in hybrid mobile apps or returns an error if the request fails.
*
* Retrieves the visitor identifiers as a URL query parameter string.
* There will be no leading '&' or '?' punctuation, as the caller is responsible for placing the string in the correct
* location of their resulting URL. If there is not a valid URL string to return, or if an error occurs, callback will
* contain nil. Otherwise, the following information is added to the query section of the given URL.
* The attribute `adobe_mc` is an URL encoded list containing the Experience Cloud ID, Experience Cloud Org ID,
* Analytics Tracking ID if available from Analytics, and a timestamp when this request
* was made. The attribute `adobe_aa_vid` is the URL encoded Analytics Customer Visitor ID, if previously set in
* Analytics extension.
*
* @param completionHandler a block pointer to call with an NSString value containing the visitor identifiers as a query
* string upon completion of the service request or passed an NSError if an unexpected error occurs or the request times out
*/
+ (void) getUrlVariablesWithCompletionHandler: (nonnull void (^) (NSString* __nullable urlVariables, NSError* __nullable error)) completionHandler;

@end
