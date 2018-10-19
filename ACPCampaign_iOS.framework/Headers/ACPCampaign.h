//
//  ACPCampaign.h
//  Adobe Cloud Platform -- iOS Framework
//
//  Copyright 1996-2018, Adobe. All Rights Reserved.
//
//  Campaign Version: 1.0.2

#import <Foundation/Foundation.h>

@interface ACPCampaign : NSObject {}

/**
 * @brief Returns the current version of the ACPCampaign extension.
 */
+ (nonnull NSString*) extensionVersion;

/**
 * @brief Registers the ACPCampaign extension with the Core Event Hub.
 */
+ (void) registerExtension;

@end
