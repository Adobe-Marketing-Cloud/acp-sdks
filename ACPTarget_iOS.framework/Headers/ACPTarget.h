//
//  ACPTarget.h
//  Adobe Digital Marketing Suite -- iOS Application Measurement Library
//
//  Copyright 1996-2018. Adobe, Inc. All Rights Reserved
//
//  Target Version: 1.0

#import <Foundation/Foundation.h>


@class ACPTargetRequestObject, ACPTargetPrefetchObject;

@interface ACPTarget : NSObject {}

#pragma mark - Target

+ (void) registerExtension;

/**
 *  @brief Clears prefetched mboxes.
 *
 *  Clears the cached prefetched ACPTargetPrefetchObject array.
 *
 *  @see ACPTarget::prefetchContent:withProfileParameters:callback:
 */
+ (void) clearPrefetchCache;

/**
 *  @brief Gets the custom visitor ID for Target
 *  @param callback will be invoked to return the thirdPartyId value or `nil` if
 *  no third-party ID is set
 */
+ (void) getThirdPartyId: (nonnull void (^) (NSString* __nullable thirdPartyId)) callback;

/**
 *  @brief Gets the Test and Target user identifier
 *
 *  Retrieves the TnT ID returned by the Target server for this visitor. The TnT ID is set to the
 *  Mobile SDK after a successful call to prefetch content or load requests.
 *
 *  This ID is preserved between app upgrades, is saved and restored during the standard application
 *  backup process, and is removed at uninstall or when ACPTarget::resetExperience is called.
 *
 *  @param callback invoked with the current tnt id or `nil` if no tnt id is set.
 *
 *  @see ACPTarget::prefetchContent:withProfileParameters:callback:
 *  @see ACPTarget::loadRequests:withProfileParameters:
 *  @see ACPTarget::resetExperience
 */
+ (void) getTntId: (nonnull void (^) (NSString* __nullable tntId)) callback;

/**
 *  @brief Retrieves content for multiple Target mbox locations at once.
 *
 *  Executes a batch request to your configured Target server for multiple mbox locations. Any prefetched content
 *  which matches a given mbox location is returned and not included in the batch request to the Target server.
 *  Each object in the array contains a callback function, which will be invoked when content is available for
 *  its given mbox location.
 *
 *  @param requests An array of ACPTargetRequestObject objects to retrieve content
 *  @param profileParameters a dictionary of key-value pairs used as profile parameters for all locations in the requests array
 *
 *  @see ACPTargetRequestObject
 */
+ (void) loadRequests: (nonnull NSArray<ACPTargetRequestObject*>*) requests
    withProfileParameters: (nullable NSDictionary<NSString*, NSString*>*) profileParameters;

/**
 *  @brief Prefetch multiple Target mboxes simultaneously.
 *
 *  Executes a prefetch request to your configured Target server with the ACPTargetPrefetchObject list provided
 *  in the \p prefetchObjectArray parameter. This prefetch request will use the provided profileParameters for all of
 *  the prefetches made in this request. The \p callback will be executed when the prefetch has been completed, returning
 *  `YES` if the prefetch was successful.
 *  The prefetched mboxes are cached in memory for the current application session and returned when requested.
 *
 *  @param prefetchObjectArray an array of ACPTargetPrefetchObject representing the desired mboxes to prefetch
 *  @param profileParameters a dictionary of key-value pairs used as profile parameters for all prefetch requests
 *  @param callback a function pointer which will be called after the prefetch is complete.  The success parameter
 *         in the callback will be YES if the prefetch completed successfully, NO otherwise
 *
 *  @see ACPTargetPrefetchObject
 */
+ (void) prefetchContent: (nonnull NSArray<ACPTargetPrefetchObject*>*) prefetchObjectArray
    withProfileParameters: (nullable NSDictionary<NSString*, NSString*>*) profileParameters
                 callback: (nullable void (^) (BOOL success)) callback;

/**
 *  @brief Resets the user's experience
 *
 *  Resets the user's experience by removing the visitor identifiers.
 *  Removes previously set third-party and TnT IDs from persistent storage.
 */
+ (void) resetExperience;

/**
 *  @brief Sets the Target preview restart deep link
 *
 *  Set the Taget preview URL to be displayed when the preview mode is restarted.
 *
 *  @param deeplink the URL which will be set for preview restart
 */
+ (void) setPreviewRestartDeeplink: (nonnull NSURL*) deeplink;

/**
 *  @brief Sets the custom visitor ID for Target
 *
 *  Sets a custom ID to identify visitors (profiles). This ID is preserved between app upgrades,
 *  is saved and restored during the standard application backup process, and is removed at uninstall or
 *  when ACPTarget::resetExperience is called.
 *
 *  @param thirdPartyId a string pointer containing the value of the third party id (custom visitor id)
 *  @see ACPTarget::resetExperience
 */
+ (void) setThirdPartyId: (nullable NSString*) thirdPartyId;

@end

#pragma mark - Custom SDK Objects
/**
 *  @class ACPTargetPrefetchObject
 *  This class contains the name of the Target location/mbox and a dictionary of mbox parameters to be used in a prefetch
 *  @see prefetchContentForObjects:withProfileParameters:callback:
 */
@interface ACPTargetPrefetchObject : NSObject
@property(nonatomic, strong, nullable) NSString* name; ///< The name of the Target location/mbox
@property(nonatomic, strong, nullable) NSDictionary<NSString*, NSString*>* mboxParameters; ///< Dictionary containing key-value pairs of mbox parameters
@property(nonatomic, strong, nullable) NSDictionary<NSString*, NSString*>* productParameters; ///< Dictionary containing key-value pairs of product parameters
@property(nonatomic, strong, nullable) NSDictionary* orderParameters; ///< Dictionary containing key-value pairs of order parameters
@end

/**
 *  @class ACPTargetRequestObject
 *  This class extends ACPTargetPrefetchObject, adding default content and a function pointer property which will be
 *  used as a callback when requesting content from Target
 *  @see loadRequests:withProfileParameters
 */
@interface ACPTargetRequestObject : ACPTargetPrefetchObject
@property(nonatomic, strong, nonnull) NSString* defaultContent; ///< The default content that will be returned if Target servers are unreachable
@property(nonatomic, strong, nullable) void (^callback)(NSString* __nullable content); ///< Optional. When batch requesting Target locations, callback will be invoked when content is available for this location.
@end
