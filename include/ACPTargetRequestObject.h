/* ************************************************************************
 * ADOBE CONFIDENTIAL
 * ___________________
 *
 * Copyright 2017 Adobe
 * All Rights Reserved.
 *
 * NOTICE: All information contained herein is, and remains
 * the property of Adobe and its suppliers, if any. The intellectual
 * and technical concepts contained herein are proprietary to Adobe
 * and its suppliers and are protected by all applicable intellectual
 * property laws, including trade secret and copyright laws.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Adobe.
 **************************************************************************/

#import <Foundation/Foundation.h>
#import "ACPTargetPrefetchObject.h"

@interface ACPTargetRequestObject()

    /**
     * @brief Create an instance of a Target request object.
     *
     * Creates an instance of a Target request object which may be used to make batch requests to the configured
     * Target server for content for mbox locations.
     *
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
                                      callback: (nullable void (^) (NSString* __nullable content)) callback;

@end

