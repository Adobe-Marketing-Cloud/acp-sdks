//
//  ACPLifecycle.h
//  Adobe Experience Platform -- iOS Library
//
//  Copyright 1996-2019. Adobe. All Rights Reserved
//
//  Lifecycle Version: 2.0.2

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
