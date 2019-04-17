//
//  ACPGriffonBridge.h
//  Adobe Experience Platform -- iOS Framework
//
//  Copyright 1996-2019. Adobe. All Rights Reserved
//
//  ACPGriffonBridge Version: 0.0.10beta

#import <Foundation/Foundation.h>

@interface ACPGriffonBridge : NSObject
/**
  * @brief Registers the ACPGriffonBridge extension with the Core Event Hub.
  */
+ (bool) registerExtension;

/*
 * @brief ACPGriffonBridge receives a deeplink url to start the SDK session
 */
+ (void) startSession: (NSURL* _Nonnull) url;

@end

