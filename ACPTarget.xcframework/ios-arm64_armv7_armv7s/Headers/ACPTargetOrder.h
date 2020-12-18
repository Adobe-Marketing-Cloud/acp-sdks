//
//  ACPTargetOrder.h
//  Adobe Experience Platform -- iOS Application Measurement Library
//
//  Copyright 1996-2019. Adobe Inc. All Rights Reserved

#import <Foundation/Foundation.h>

@interface ACPTargetOrder : NSObject <NSCoding, NSCopying>
@property(nonatomic, strong, nonnull) NSString* orderId;
@property(nonatomic, strong, nullable) NSNumber* total;
@property(nonatomic, strong, nullable) NSArray<NSString*>* purchasedProductIds;

/**
 * @brief Create an instance of a Target Order object.
 *
 * @param orderId order id associated with the order
 * @param total value of the order
 * @param purchasedProductIds an array of puchased product ids
 */
+ (nonnull instancetype) targetOrderWithId: (nonnull NSString*) orderId
                                     total: (nullable NSNumber*) total
                       purchasedProductIds: (nullable NSArray <NSString*>*) purchasedProductIds;

@end
