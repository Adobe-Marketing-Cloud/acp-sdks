//
//  ACPTargetParameters.h
//  Adobe Experience Platform -- iOS Application Measurement Library
//
//  Copyright 1996-2019. Adobe Inc. All Rights Reserved

#import <Foundation/Foundation.h>

@class ACPTargetOrder, ACPTargetProduct;

@interface ACPTargetParameters : NSObject <NSCoding, NSCopying>

@property(nonatomic, strong, nullable) NSDictionary<NSString*, NSString*>* parameters;  //Dictionary containing key-value pairs of parameters
@property(nonatomic, strong, nullable) NSDictionary<NSString*, NSString*>* profileParameters;  //Dictionary containing key-value pairs of profile parameters
@property(nonatomic, strong, nullable) ACPTargetOrder* order;  //ACPTargetOrder object
@property(nonatomic, strong, nullable) ACPTargetProduct* product;  //ACPTargetProduct object

/**
 * @brief Create an instance of a Target Parameters object.
 *
 * @param parameters generic parameters
 * @param profileParameters profile parameters
 * @param product target product object associated with the object
 * @param order target order object associated with the object
 */
+ (nonnull instancetype) targetParametersWithParameters: (nullable NSDictionary*) parameters
                                      profileParameters: (nullable NSDictionary*) profileParameters
                                                product: (nullable ACPTargetProduct*) product
                                                  order: (nullable ACPTargetOrder*) order;

@end
