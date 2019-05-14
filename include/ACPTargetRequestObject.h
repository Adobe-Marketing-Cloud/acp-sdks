//
//  ACPTargetRequestObject.h
//  Adobe Experience Platform -- iOS Application Measurement Library
//
//  Copyright 1996-2019. Adobe Inc. All Rights Reserved

#import <Foundation/Foundation.h>
#import "ACPTargetPrefetchObject.h"

@class ACPTargetParameters;

/**
 *  @class ACPTargetRequestObject
 *  This class extends ACPTargetPrefetchObject, adding default content and a function pointer property which will be
 *  used as a callback when requesting content from Target
 *  @see loadRequests:withProfileParameters
 */
@interface ACPTargetRequestObject : ACPTargetPrefetchObject

@property(nonatomic, strong, nonnull) NSString* defaultContent; ///< The default content that will be returned if Target servers are unreachable
@property(nonatomic, strong, nullable) void (^callback)(NSString* __nullable content); ///< Optional. When batch requesting Target locations, callback will be invoked when content is available for this location.

/**
 * @brief Create an instance of a Target request object.
 *
 * Creates an instance of a Target request object which may be used to make batch requests to the configured
 * Target server for content for mbox locations.
 *
 * @deprecated Please use @see ACPTargetRequestObject::targetRequestObjectWithName:targetParameters:defaultContent:callback: instead
 * @param name NSString value representing the name for location/mbox to retrieve
 * @param defaultContent NSString value returned by the callback if the SDK is unable to retrieve content for the given mbox/location
 * @param mboxParameters optional dictionary of key-value pairs representing mbox parameters for this request
 * @param callback method which will be invoked once content is available for requested mbox/location
 * @return a pointer to an ACPTargetRequestObject containing pre-set values provided by the parameters
 *
 * @see ADBMobileMarketing::targetRequestObjectWithName()
 * @see ADBMobileMarketing::targetLoadRequests()
 */
+ (nonnull instancetype) requestObjectWithName: (nonnull NSString*) name
                                defaultContent: (nonnull NSString*) defaultContent
                                mboxParameters: (nullable NSDictionary<NSString*, NSString*>*) mboxParameters
                                      callback: (nullable void (^) (NSString* __nullable content)) callback DEPRECATED_MSG_ATTRIBUTE ("This method is deprecated, please use requestObjectWithName:targetParameters:defaultContent:callback instead");

/**
 * @brief Create an instance of a Target request object.
 *
 * Creates an instance of a Target request object which may be used to make batch requests to the configured
 * Target server for content for mbox locations.
 *
 * @param name NSString value representing the name for location/mbox to retrieve
 * @param targetParameters parameters to be associated with mbox
 * @param defaultContent NSString value returned by the callback if the SDK is unable to retrieve content for the given mbox/location
 * @param callback method which will be invoked once content is available for requested mbox/location
 * @return a pointer to an ACPTargetRequestObject containing pre-set values provided by the parameters
 *
 * @see ADBMobileMarketing::targetRequestObjectWithName()
 * @see ADBMobileMarketing::targetLoadRequests()
 */
+ (nonnull instancetype) targetRequestObjectWithName: (nonnull NSString*) name
                                    targetParameters: (nullable ACPTargetParameters*) targetParameters
                                      defaultContent: (nonnull NSString*) defaultContent
                                            callback: (nullable void (^) (NSString* __nullable content)) callback;

@end
