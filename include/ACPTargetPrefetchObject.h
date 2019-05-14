//
//  ACPTargetPrefetchObject.h
//  Adobe Experience Platform -- iOS Application Measurement Library
//
//  Copyright 1996-2019. Adobe Inc. All Rights Reserved

#import <Foundation/Foundation.h>

@class ACPTargetParameters;

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
@property(nonatomic, strong, nullable) ACPTargetParameters* targetParameters; ///target parameters associated with the prefetch object. You can set all other parameters in this object

/**
 * @brief Create an instance of a Target prefetch object.
 *
 * Create an instance of a Target prefetch object which may be used to make a batch request to the configured
 * Target server to prefetch content for mbox locations.
 *
 * @deprecated Please use @see ACPTargetPrefetchObject::targetPrefetchObjectWithName:targetParameters: instead
 * @param name NSString value representing the name for location/mbox to prefetch
 * @param mboxParameters optional dictionary of key-value pairs representing mbox parameters for this prefetch request
 * @return a pointer to an ACPTargetPrefetchObject containing values provided by the parameters
 *
 * @see ADBMobileMarketing::targetPrefetchObjectWithName()
 * @see ADBMobileMarketing::targetPrefetchContent()
 */
+ (nonnull instancetype) prefetchObjectWithName: (nonnull NSString*) name
                                 mboxParameters: (nullable NSDictionary*) mboxParameters DEPRECATED_MSG_ATTRIBUTE ("This method is deprecated, please use prefetchObjectWithName:targetParameters: instead") ;;

/**
 * @brief Create an instance of a Target prefetch object.
 *
 * Create an instance of a Target prefetch object which may be used to make a batch request to the configured
 * Target server to prefetch content for mbox locations.
 *
 * @param name NSString value representing the name for location/mbox to prefetch
 * @param targetParameters parameters to be associated with mbox
 * @return a pointer to an ACPTargetPrefetchObject containing values provided by the parameters
 *
 * @see ADBMobileMarketing::targetPrefetchObjectWithName()
 * @see ADBMobileMarketing::targetPrefetchContent()
 */
+ (nonnull instancetype) targetPrefetchObjectWithName: (nonnull NSString*) name
                                     targetParameters: (nullable ACPTargetParameters*) targetParameters;

/**
 * @brief Set the order parameters.
 *
 * Set the order parameters for this Target prefetch object.
 *
 * @deprecated Please use the "order" (ACPTargetOrder) property of the "targetParameters" (ACPTargetParameters) object
 *     to modify values in the order
 * @param orderId the order reference ID
 * @param orderTotal the order amount associated with the order.
 * @param purchasedProductIds order referenced product IDs
 */
- (void) setOrderParameters: (nonnull NSString*) orderId
                 orderTotal: (nonnull NSNumber*) orderTotal
        purchasedProductIds: (nonnull NSArray<NSString*>*) purchasedProductIds DEPRECATED_MSG_ATTRIBUTE ("This method is deprecated, please use prefetchObjectWithName:targetParameters: to create instance and set order parameters as part of targetParameters") ;;

/**
 * @brief Set the product parameters.
 *
 * Set the product parameters for this Target prefetch object.
 *
 * @deprecated Please use the "product" (ACPTargetProduct) property of the "targetParameters" (ACPTargetParameters) object
 *     to modify values product values for this request
 * @param productId the product reference ID
 * @param categoryId the product category ID
 */
- (void) setProductParameters: (nonnull NSString*) productId
                   categoryId: (nonnull NSString*) categoryId DEPRECATED_MSG_ATTRIBUTE ("This method is deprecated, please use prefetchObjectWithName:targetParameters: to create instance and set product parameters as part of targetParameters") ;;

@end

