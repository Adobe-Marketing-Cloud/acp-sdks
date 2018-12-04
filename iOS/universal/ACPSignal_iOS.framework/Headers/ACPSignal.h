//
//  ACPSignal.h
//  Adobe Digital Marketing Suite -- iOS Application Measurement Library
//
//  Copyright 1996-2018. Adobe, Inc. All Rights Reserved
//
//  Signal Version: 1.1.0

#import <Foundation/Foundation.h>


@interface ACPSignal : NSObject {}

#pragma mark - Signal

/**
 * @brief Returns the current version of the ACPSignal Extension.
 */
+ (nonnull NSString*) extensionVersion;

/**
 * @brief Registers the ACPSignal extension with the Core Event Hub.
 */
+ (void) registerExtension;

@end
