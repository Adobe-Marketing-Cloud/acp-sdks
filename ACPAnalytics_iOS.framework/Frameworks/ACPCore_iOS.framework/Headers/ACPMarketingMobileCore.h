//
//  ACPMarketingMobileCore.h
//  Adobe Digital Marketing Suite -- iOS Application Measurement Library
//
//  Copyright 1996-2018. Adobe, Inc. All Rights Reserved
//
//  SDK Version: 5.0.0b2

#import <Foundation/Foundation.h>

#if TARGET_OS_IOS || TARGET_OS_WATCH
@class UNNotificationResponse;
#endif
@class ACPExtension, ACPMobileVisitorId;

@interface ACPMarketingMobileCore : NSObject {}

#pragma mark - enums

/**
 * @brief An enum type representing different levels of logging used by the SDK.
 *
 * @see ACPMarketingMobileCore::setLogLevel:
 */
typedef NS_ENUM(NSUInteger, ACPMobileLogLevel) {
    ACPMobileLogLevelError = 0,
    ACPMobileLogLevelWarning = 1,
    ACPMobileLogLevelDebug = 2,
    ACPMobileLogLevelVerbose = 3
};

/**
 * @brief An enum type representing the possible Opt-Out and Privacy settings.
 *
 * The possible values for the Adobe Mobile Privacy Status. The privacy status controls whether
 * specific activity is allowed on the device. The default privacy status is set in any ADBMobile JSON configuration
 * file using the parameter `global.privacy`. Use ACPMarketingMobileCore::setPrivacyStatus: to override the
 * default privacy status.
 *
 * @see ACPMarketingMobileCore::getPrivacyStatus:
 * @see ACPMarketingMobileCore::setPrivacyStatus:
 */
typedef NS_ENUM(NSInteger, ACPMobilePrivacyStatus) {
    ACPMobilePrivacyStatusOptIn,    ///< Adobe Mobile Privacy Status opted-in
    ACPMobilePrivacyStatusOptOut,   ///< Adobe Mobile Privacy Status opted-out
    ACPMobilePrivacyStatusUnknown   ///< Adobe Mobile Privacy Status is unknown
};

/**
 *  @brief An enum type representing possible authentication states for Experience Cloud visitors.
 *
 *  @see syncIdentifier
 */
typedef NS_ENUM(NSUInteger, ACPMobileVisitorAuthenticationState) {
    ACPMobileVisitorAuthenticationStateUnknown            = 0, /*!< Enum value ACPMobileVisitorAuthenticationStateUnknown. */
    ACPMobileVisitorAuthenticationStateAuthenticated    = 1, /*!< Enum value ACPMobileVisitorAuthenticationStateAuthenticated. */
    ACPMobileVisitorAuthenticationStateLoggedOut        = 2  /*!< Enum value ACPMobileVisitorAuthenticationStateLoggedOut. */
};

#pragma mark - Configuration

/**
 * @brief Load remote configuration specified by the given application ID
 *
 * Configure the SDK by downloading the remote configuration file hosted on Adobe servers
 * specified by the given application ID. The configuration file is cached once downloaded
 * and used in subsequent calls to this API. If the remote file is updated after the first
 * download, the updated file is downloaded and replaces the cached file.
 *
 * The \p appid is preserved, and on application restarts, the remote configuration file specified by \p appid
 * is downloaded and applied to the SDK.
 *
 * On failure to download the remote configuration file, the SDK is configured using the cached
 * file if it exists, or if no cache file exists then the existing configuration remains unchanged.
 *
 * Calls to this API will replace any existing SDK configuration except those set using
 * ACPMarketingMobileCore::updateConfiguration: or ACPMarketingMobileCore::setPrivacyStatus:. Configuration updates
 * made using ACPMarketingMobileCore::updateConfiguration:
 * and ACPMarketingMobileCore::setPrivacyStatus: are always applied on top of configuration changes made using this API.
 *
 * @param appid a unique identifier assigned to the app instance by the Adobe Mobile Services. It is automatically
 * added to the ADBMobile JSON file when downloaded from the Adobe Mobile Services UI and can be
 * found in Manage App Settings. A value of `nil` has no effect.
 */
+ (void) configureWithAppId: (NSString* __nullable) appid;

/**
 * @brief Load configuration from local file
 *
 * Configure the SDK by reading a local file containing the JSON configuration.  On application relaunch,
 * the configuration from the file at \p filepath is not preserved and this method must be called again if desired.
 *
 * On failure to read the file or parse the JSON contents, the existing configuration remains unchanged.
 *
 * Calls to this API will replace any existing SDK configuration except those set using
 * ACPMarketingMobileCore::updateConfiguration: or ACPMarketingMobileCore::setPrivacyStatus:. Configuration updates
 * made using ACPMarketingMobileCore::updateConfiguration:
 * and ACPMarketingMobileCore::setPrivacyStatus: are always applied on top of configuration changes made using this API.
 *
 * @param filepath absolute path to a local configuration file. A value of `nil` has no effect.
 */
+ (void) configureWithFileInPath: (NSString* __nullable) filepath;

/**
 * @brief Calls the provided callback with a JSON string containing all of the User's identifiers known by the SDK
 * @param callback a void-returning method that has an NSString param containing a JSON string
 */
+ (void) getAllIdentifiers: (nullable void (^) (NSString* __nullable content)) callback;

/**
 * @brief Get the current Adobe Mobile Privacy Status
 *
 * Gets the currently configured \ref ACPMobilePrivacyStatus and passes it as a parameter to the given void function.
 *
 * @param callback method invoked with the configured privacy status as a parameter
 * @see ACPMobilePrivacyStatus
 */
+ (void) getPrivacyStatus: (nonnull void (^) (ACPMobilePrivacyStatus status)) callback;

/**
 *  @brief Gets the version.
 *
 *  @return a string pointer containing the version value.
 */
+ (nonnull NSString*) sdkVersion;

/**
 * @brief set the app group used to sharing user defaults and files among containing app and extension apps
 * @note This *must* be called in AppDidFinishLaunching and before any other interactions with the Adobe Mobile library have happened.
 * Only the first call to this function will have any effect.
 */
+ (void) setAppGroup: (nullable NSString*) appGroup;

/**
 * @brief Set the logging level of the SDK
 *
 * @param logLevel ACPMarketingMobileCore::ACPMobileLogLevel to be used by the SDK
 * @see ACPMobileLogLevel
 */
+ (void) setLogLevel: (ACPMobileLogLevel) logLevel;

/**
 * @brief Set the Adobe Mobile Privacy status
 *
 * Sets the \ref ACPMobilePrivacyStatus for this SDK. The set privacy status is preserved and applied over any new
 * configuration changes from calls to ACPMarketingMobileCore::configureWithAppId: or ACPMarketingMobileCore::configureWithFileInPath:,
 * even across application restarts.
 *
 * @param status ACPMarketingMobileCore::ACPMobilePrivacyStatus to be set to the SDK
 * @see ACPMobilePrivacyStatus
 */
+ (void) setPrivacyStatus: (ACPMobilePrivacyStatus) status;

/**
 * @brief Update specific configuration parameters
 *
 * Update the current SDK configuration with specific key/value pairs. Keys not found in the current
 * configuration are added. Configuration updates are preserved and applied over existing or new
 * configurations set by calling ACPMarketingMobileCore::configureWithAppId: or ACPMarketingMobileCore::configureWithFileInPath:,
 * even across application restarts.
 *
 * Using `nil` values is allowed and effectively removes the configuration parameter from the current configuration.
 *
 * @param config configuration key/value pairs to be updated or added. A value of `nil` has no effect.
 */
+ (void) updateConfiguration: (NSDictionary* __nullable) config;

#pragma mark - Extensions

/*
 * @brief Register an extension class derived from `ACPExtension` with a unique name.
 *
 * This call validates the parameters to ensure name is not empty, name is unique and parent class is ACPExtension.
 * If validation fails, NO is returned and if `error` is provided an NSError* is passed back with more details.
 * If validation succeeds, YES is returned and the extension will be instantiated and registered by the event hub on another thread.
 *
 * In order to ensure that the extension can see all events (including the BOOTED event), `registerExtension` should be called
 * from your AppDelegate's `application:didFinishLaunchingWithOptions` method. This call should be before any calls into
 * the AdobeMarketingMobile interface except `setLogLevel`.
 *
 * @param extensionClass A class whose parent is `ACPExtension`.
 * @param error An optional parameter where an NSError* will be returned if valid and NO was returned
 * @return YES if registration params are valid, NO otherwise.
 */
+ (BOOL) registerExtension: (nonnull Class) extensionClass
                     error: (NSError* _Nullable* _Nullable) error;

#pragma mark - Rules Engine

/**
 * RulesEngine API to download and refresh rules from the server.
 *
 * Forces Rules Engine to send a network request to the rules url in Configuration,
 * to refresh rules content set in the SDK.
 */

+ (void) downloadRules;

@end

/**
 *  @class ACPMobileVisitorId contains Visitor Id origin, identitfier type, identifier value and authentication state.
 *  @see getIdentifiers:
 */
@interface ACPMobileVisitorId : NSObject
@property(nonatomic, strong, nullable) NSString* idOrigin;
@property(nonatomic, strong, nullable) NSString* idType;
@property(nonatomic, strong, nullable) NSString* identifier;
@property(nonatomic, readwrite) ACPMobileVisitorAuthenticationState authenticationState;
@end
