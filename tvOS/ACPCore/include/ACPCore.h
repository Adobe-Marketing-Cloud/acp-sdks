//
//  ACPCore.h
//  Adobe Experience Platform -- iOS Framework
//
//  Copyright 1996-2019. Adobe. All Rights Reserved
//
//  Core Version: 2.7.5

#import <Foundation/Foundation.h>

#if TARGET_OS_IOS || TARGET_OS_WATCH
@class UNNotificationResponse;
#endif
@class ACPExtension, ACPExtensionEvent, ACPMobileVisitorId;

@interface ACPCore : NSObject {}

#pragma mark - enums

/**
 * @brief An enum type representing different levels of logging used by the SDK.
 *
 * @see ACPCore::setLogLevel:
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
 * file using the parameter `global.privacy`. Use ACPCore::setPrivacyStatus: to override the
 * default privacy status.
 *
 * @see ACPCore::getPrivacyStatus:
 * @see ACPCore::setPrivacyStatus:
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
    ACPMobileVisitorAuthenticationStateUnknown = 0, /*!< Enum value ACPMobileVisitorAuthenticationStateUnknown. */
    ACPMobileVisitorAuthenticationStateAuthenticated = 1, /*!< Enum value ACPMobileVisitorAuthenticationStateAuthenticated. */
    ACPMobileVisitorAuthenticationStateLoggedOut = 2  /*!< Enum value ACPMobileVisitorAuthenticationStateLoggedOut. */
};

/**
 *  @brief An enum type representing possible wrapper states.
 *
 *  @see ACPCore::setWrapperType:
 */
typedef NS_ENUM(NSUInteger, ACPMobileWrapperType) {
    ACPMobileWrapperTypeNone = 0, /*!< Enum value ACPMobileWrapperTypeNone. */
    ACPMobileWrapperTypeReactNative = 1, /*!< Enum value ACPMobileWrapperTypeReactNative. */
    ACPMobileWrapperTypeFlutter = 2, /*!< Enum value ACPMobileWrapperTypeFlutter. */
    ACPMobileWrapperTypeCordova = 3, /*!< Enum value ACPMobileWrapperTypeCordova. */
    ACPMobileWrapperTypeUnity = 4, /*!< Enum value ACPMobileWrapperTypeUnity. */
    ACPMobileWrapperTypeXamarin = 5 /*!< Enum value ACPMobileWrapperTypeXamarin. */
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
 * ACPCore::updateConfiguration: or ACPCore::setPrivacyStatus:. Configuration updates
 * made using ACPCore::updateConfiguration:
 * and ACPCore::setPrivacyStatus: are always applied on top of configuration changes made using this API.
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
 * ACPCore::updateConfiguration: or ACPCore::setPrivacyStatus:. Configuration updates
 * made using ACPCore::updateConfiguration:
 * and ACPCore::setPrivacyStatus: are always applied on top of configuration changes made using this API.
 *
 * @param filepath absolute path to a local configuration file. A value of `nil` has no effect.
 */
+ (void) configureWithFileInPath: (NSString* __nullable) filepath;

/**
 * @brief Calls the provided callback with a JSON string containing all of the user's identities known by the SDK
 *
 * @param callback a void-returning method that has an NSString param containing a JSON string
 */
+ (void) getSdkIdentities: (nullable void (^) (NSString* __nullable content)) callback;

/**
 * @brief Get a JSON string containing all of the user's identities known by the SDK  and calls a handler upon completion.
 *
 * @param completionHandler a void-returning method that has an NSString param containing a JSON string, and an NSError param if the request failed
 */

+ (void) getSdkIdentitiesWithCompletionHandler: (nullable void (^) (NSString* __nullable content, NSError* _Nullable error)) completionHandler;

/**
 * @brief Set the provided callback with a url string and call this callback function before SDK extension open url action
 *
 * @param callback a method that has an string param containing a url, which return YES if it will handle the provided url, NO continue to open url.
 */
#if !TARGET_OS_WATCH
+ (void) registerURLHandler: (nonnull BOOL (^) (NSString* __nullable url)) callback;
#endif

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
 * @brief Get the current Adobe Mobile Privacy Status  and calls a handler upon completion.
 *
 * Gets the currently configured \ref ACPMobilePrivacyStatus and passes it as a parameter to the given void function.
 *
 * @param completionHandler method invoked with the configured privacy status as a parameter, and an NSError param if the request failed
 * @see ACPMobilePrivacyStatus
 */
+ (void) getPrivacyStatusWithCompletionHandler: (nonnull void (^) (ACPMobilePrivacyStatus status, NSError* _Nullable error)) completionHandler;

/**
 * @brief Returns the current version of the ACPCore Extension.
 */
+ (nonnull NSString*) extensionVersion;

/**
 * @brief set the app group used to sharing user defaults and files among containing app and extension apps
 * @note This *must* be called in AppDidFinishLaunching and before any other interactions with the Adobe Mobile library have happened.
 * Only the first call to this function will have any effect.
 */
+ (void) setAppGroup: (nullable NSString*) appGroup;

/**
 * @brief Set the logging level of the SDK
 *
 * @param logLevel ACPCore::ACPMobileLogLevel to be used by the SDK
 * @see ACPMobileLogLevel
 */
+ (void) setLogLevel: (ACPMobileLogLevel) logLevel;

/**
 * @brief Set the Adobe Mobile Privacy status
 *
 * Sets the \ref ACPMobilePrivacyStatus for this SDK. The set privacy status is preserved and applied over any new
 * configuration changes from calls to ACPCore::configureWithAppId: or ACPCore::configureWithFileInPath:,
 * even across application restarts.
 *
 * @param status ACPCore::ACPMobilePrivacyStatus to be set to the SDK
 * @see ACPMobilePrivacyStatus
 */
+ (void) setPrivacyStatus: (ACPMobilePrivacyStatus) status;

/*
 * @brief Start the Core processing. This should be called after the initial set of extensions have been registered.
 *
 * This call will wait for any outstanding registrations to complete and then start event processing.
 * You can use the callback to kickoff additional operations immediately after any operations kicked off during registration.
 * You shouldn't call this method more than once in your app, if so, sdk will ignore it and print error log.
 *
 * @param callback An optional method invoked after registrations are complete
 */
+ (void) start: (nullable void (^) (void)) callback;

/**
 * @brief Update specific configuration parameters
 *
 * Update the current SDK configuration with specific key/value pairs. Keys not found in the current
 * configuration are added. Configuration updates are preserved and applied over existing or new
 * configurations set by calling ACPCore::configureWithAppId: or ACPCore::configureWithFileInPath:,
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
 * the ACPCore interface except `setLogLevel`.
 *
 * @param extensionClass A class whose parent is `ACPExtension`.
 * @param error An optional parameter where an NSError* will be returned if valid and NO was returned
 * @return YES if registration params are valid, NO otherwise.
 */
+ (BOOL) registerExtension: (nonnull Class) extensionClass
                     error: (NSError* _Nullable* _Nullable) error;

#pragma mark - Generic methods
/**
 *    @brief Submits a generic PII collection request event with type `generic.pii`.
 *    @param data a dictionary containing PII data
 */
+ (void) collectPii: (nonnull NSDictionary<NSString*, NSString*>*) data;

/**
 * @brief Submits a generic event to pause lifecycle collection with event type `generic.lifecycle`.
 *
 * When using the Adobe Lifecycle extension, the following applies:
 *   - Pauses the current lifecycle session. Calling pause on an already paused session updates the paused timestamp,
 *     having the effect of resetting the session timeout timer. If no lifecycle session is running, then calling
 *     this method does nothing.
 *   - A paused session is resumed if ACPCore::lifecycleStart: is called before the session timeout. After
 *     the session timeout, a paused session is closed and calling ACPCore::lifecycleStart: will create
 *     a new session. The session timeout is defined by the `lifecycle.sessionTimeout` configuration parameter.
 *   - If not defined, the default session timeout is five minutes.
 */
+ (void) lifecyclePause;

/**
 * @brief Submits a generic event to start/resume lifecycle collection with event type `generic.lifecycle`.
 *
 * When using the Adobe Lifecycle extension, the following applies:
 *   - Start a new lifecycle session or resume a previously paused lifecycle session. If a previously paused session
 *     timed out, then a new session is created. If a current session is running, then calling this method does nothing.
 *   - Additional context data may be passed when calling this method. Lifecycle data and any additional data are
 *     sent as context data parameters to Analytics, to Target as mbox parameters, and for Audience Manager they are
 *     sent as customer variables. Any additional data is also used by the Rules Engine when processing rules.
 *
 * @param additionalContextData optional additional context for this session.
 */
+ (void) lifecycleStart: (nullable NSDictionary<NSString*, NSString*>*) additionalContextData;

/**
 * @brief Submits a generic event containing the provided IDFA with event type `generic.identity`.
 *
 * When using the Adobe Identity extension, the following applies:
 *   - If the IDFA was set in the SDK, the IDFA will be sent in lifecycle. It can also be accessed in Signals (Postbacks).
 *   - This ID is preserved between app upgrades, is saved and restored during the standard application backup process,
 *     and is removed at uninstall.
 *   - If the Mobile SDK is configured with `identity.adidEnabled` set to `false`, then the advertising identifier
 *     is not set or stored.
 *
 * @param adId the advertising idenifier string.
 */
+ (void) setAdvertisingIdentifier: (nullable NSString*) adId;

/**
 * @brief Submits a generic event containing the provided push token with event type `generic.identity`.
 *
 * When using the Adobe Identity extension, the following applies:
 *   - If the current SDK privacy status is \ref ACPMobilePrivacyStatusOptOut, then the push identifier is not set.
 *
 * @param deviceToken the device token for push notifications
 * @see ACPMobilePrivacyStatus
 */
+ (void) setPushIdentifier: (nullable NSData*) deviceToken;

/**
 *  @brief This method sends a generic Analytics action tracking hit with context data.
 *
 *  Actions represent events that occur in your application that you want to measure; the corresponding metrics will
 *  be incremented each time the event occurs. For example, you may want to track when an user click on the login
 *  button or a certain article was viewed.
 *
 *  @note when using the Adobe Analytics extension, calling this API will not increment page views
 *
 *  @param action NSString containing the name of the action to track
 *  @param data NSDictionary<NSString, NSString> containing context data to attach on this hit
 */
+ (void) trackAction: (nullable NSString*) action data: (nullable NSDictionary<NSString*, NSString*>*) data;

/**
 *  @brief This method sends a generic Analytics state tracking hit with context data.
 *
 *  States represent different screens or views of you application. When the user navigates between application pages,
 *  a new track call should be sent with current state name. Tracking state name is typically called from an
 *  UIViewController in the viewDidLoad method.
 *
 *  @note when using the Adobe Analytics extension, calling this API will increment page views
 *
 *  @param state NSString containing the name of the state to track
 *  @param data NSDictionary<NSString, NSString> containing context data to attach on this hit
 */
+ (void) trackState: (nullable NSString*) state data: (nullable NSDictionary<NSString*, NSString*>*) data;

/**
 * @brief Called by the extension public API to dispatch an event for other extensions or the internal SDK to consume.
 * Any events dispatched by this call will not be processed until after `start` has been called.
 *
 * @param event Required parameter with {@link Event} instance to be dispatched. Should not be nil
 * @param error Optional parameter where an NSError* will be returned if valid and NO was returned
 * @return YES if the the event dispatching operation succeeded
 */
+ (BOOL) dispatchEvent: (nonnull ACPExtensionEvent*) event
                 error: (NSError* _Nullable* _Nullable) error;

/**
 * @brief You should use this method when the {@code Event} being passed is a request and you expect an event in response.
 * Any events dispatched by this call will not be processed until after `start` has been called.
 *
 * @param requestEvent Required parameter with {@link Event} instance to be dispatched. Should not be nil
 * @param responseCallback Required parameter with callback called when response event is available. Should not be nil
 * @param error Optional parameter where an NSError* will be returned if valid and NO was returned
 * @return YES if the the event dispatching operation succeeded
 */
+ (BOOL) dispatchEventWithResponseCallback: (nonnull ACPExtensionEvent*) requestEvent
                          responseCallback: (nonnull void (^) (ACPExtensionEvent* _Nonnull responseEvent)) responseCallback
                                     error: (NSError* _Nullable* _Nullable) error;

/**
 * @brief Dispatches a response event for a paired event that was sent to {@code dispatchEventWithResponseCallback}
 * or received by an extension listener {@code hear} method.
 *
 * @param responseEvent Required parameter with {@link Event} instance to be dispatched. Should not be nil
 * @param requestEvent Required parameter with {@link Event} that {@code responseEvent} is responding to. Should not be nil
 * @param error Optional parameter where an NSError* will be returned if valid and NO was returned
 * @return YES if the the event dispatching operation succeeded
 */
+ (BOOL) dispatchResponseEvent: (nonnull ACPExtensionEvent*) responseEvent
                  requestEvent: (nonnull ACPExtensionEvent*) requestEvent
                         error: (NSError* _Nullable* _Nullable) error;

/**
 * @brief Provide user info to the SDK from various launch points in your application.
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
 * @param userInfo Dictionary of data relevant to the expected use case
 */
+ (void) collectLaunchInfo: (nonnull NSDictionary*) userInfo;

/**
 * @brief Provide message info to the SDK from various points in your application.
 *
 * This method should be called to support the following use cases:
 *
 *  1. Tracking remote or local notification receive
 *     - call from userNotificationCenter:willPresentNotification:withCompletionHandler:
 *
 *  2. Tracking remote or local notification click-throughs
 *     - call from userNotificationCenter:didReceiveNotificationResponse:withCompletionHandler:
 *
 * For scenarios where the app is launched as a result of notification click, use ACPCore::collectLaunchInfo:
 *
 * @param messageInfo Dictionary of data relevant to the expected use case
 */
+ (void) collectMessageInfo: (nonnull NSDictionary*) messageInfo;

#pragma mark - Rules Engine

/**
 * @brief RulesEngine API to download and refresh rules from the server.
 *
 * Forces Rules Engine to send a network request to the rules url in Configuration,
 * to refresh rules content set in the SDK.
 */

+ (void) downloadRules;

#pragma mark - Logging

/**
 * @brief Returns current logging level used by the SDK.
 *
 * @return ACPCore::ACPMobileLogLevel representing current logging level
 * @see ACPCore::setLogLevel:
 */
+ (ACPMobileLogLevel) logLevel;

/**
 * @brief Prints a log message with the provided logLevel and tag.
 *
 * @note This message is not printed if the current logging mode set using `setLogLevel`
 * is less verbose than the given logLevel
 *
 * @param logLevel the logging level for which the message should be printed
 * @param tag used to identify the source of the log message. It should not be empty
 * @param message the message to log. It should not be empty
 * @see ACPCore::setLogLevel:
 */
+ (void) log: (ACPMobileLogLevel) logLevel tag: (nonnull NSString*) tag message: (nonnull NSString*) message;

/**
 * @brief Sets the SDK's current wrapper type. This API should only be used if
 * being developed on platforms such as React Native.
 *
 * @param wrapperType the type of wrapper being used
 * @see ACPMobileWrapperType
 */
+ (void) setWrapperType: (ACPMobileWrapperType) wrapperType;

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
