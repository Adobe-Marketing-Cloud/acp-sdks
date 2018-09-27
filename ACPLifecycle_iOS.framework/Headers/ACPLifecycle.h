//
//  ACPLifecycle.h
//  Adobe Digital Marketing Suite -- iOS Application Measurement Library
//
//  Copyright 1996-2018. Adobe, Inc. All Rights Reserved
//
//  Lifecycle Version: 1.0.0

#import <Foundation/Foundation.h>

@interface ACPLifecycle : NSObject {}

/**
 * @brief Returns the current version of the ACPLifecycle Extension.
 */
+ (nonnull NSString*) extensionVersion;

/**
 * @brief Registers the ACPLifecycle extension with the Core Event Hub.
 */
+ (void) registerExtension;

@end
