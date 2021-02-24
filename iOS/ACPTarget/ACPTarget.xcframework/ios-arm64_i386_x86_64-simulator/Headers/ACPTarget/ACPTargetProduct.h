//
//  ACPTargetProduct.h
//  Adobe Experience Platform -- iOS Application Measurement Library
//
//  Copyright 1996-2019. Adobe Inc. All Rights Reserved

#import <Foundation/Foundation.h>

@interface ACPTargetProduct : NSObject<NSCoding, NSCopying>

@property(nonatomic, strong, nullable) NSString* productId;
@property(nonatomic, strong, nullable) NSString* categoryId;

/**
 * @brief Create an instance of a Target Product object.
 * @param productId product id associated with the product
 * @param categoryId category id associated with the product
 */
+ (nonnull instancetype) targetProductWithId: (nonnull NSString*) productId
                                  categoryId: (nullable NSString*) categoryId;

@end
