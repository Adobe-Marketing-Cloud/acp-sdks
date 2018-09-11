//
//  ACPSignal.h
//  Adobe Digital Marketing Suite -- iOS Application Measurement Library
//
//  Copyright 1996-2018. Adobe, Inc. All Rights Reserved
//
//  Signal Version: 1.0

#import <Foundation/Foundation.h>


@interface ACPSignal : NSObject {}

#pragma mark - Signal

+ (void) registerAdobeSignalExtension;

/**
 *    @brief Submits a PII collection request
 *    @param data a dictionary containing PII data
 */
+ (void) collectPii: (nonnull NSDictionary<NSString*, NSString*>*) data;

@end
