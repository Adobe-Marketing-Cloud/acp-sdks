/*************************************************************************
 *
 * ADOBE CONFIDENTIAL
 * ___________________
 *
 *  Copyright 2017 Adobe Systems Incorporated
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Adobe Systems Incorporated and its suppliers,
 * if any.  The intellectual and technical concepts contained
 * herein are proprietary to Adobe Systems Incorporated and its
 * suppliers and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Adobe Systems Incorporated.
 *
 **************************************************************************/

#import <Foundation/Foundation.h>
#import "ACPTarget.h"

@interface ACPTargetPrefetchObject()

    /**
     * @brief Create an instance of a Target prefetch object.
     *
     * Create an instance of a Target prefetch object which may be used to make a batch request to the configured
     * Target server to prefetch content for mbox locations.
     *
     * @param name NSString value representing the name for location/mbox to prefetch
     * @param mboxParameters optional dictionary of key-value pairs representing mbox parameters for this prefetch request
     * @return a pointer to an ACPTargetPrefetchObject containing values provided by the parameters
     *
     * @see ADBMobileMarketing::targetPrefetchObjectWithName()
     * @see ADBMobileMarketing::targetPrefetchContent()
     */
+ (nonnull instancetype) prefetchObjectWithName: (nonnull NSString*) name
                                 mboxParameters: (nullable NSDictionary*) mboxParameters;

/**
 * @brief Set the order parameters.
 *
 * Set the order parameters for this Target prefetch object.
 *
 * @param orderId the order reference ID
 * @param orderTotal the order amount associated with the order.
 * @param purchasedProductIds order referenced product IDs
 */
- (void) setOrderParameters: (nonnull NSString*) orderId
                 orderTotal: (nonnull NSNumber*) orderTotal
        purchasedProductIds: (nonnull NSArray<NSString*>*) purchasedProductIds;

/**
 * @brief Set the product parameters.
 *
 * Set the product parameters for this Target prefetch object.
 *
 * @param productId the product reference ID
 * @param categoryId the product category ID
 */
- (void) setProductParameters: (nonnull NSString*) productId
                   categoryId: (nonnull NSString*) categoryId;

@end

