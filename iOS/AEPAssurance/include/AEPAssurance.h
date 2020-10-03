//
//  AEPAssurance.h
//  Adobe Experience Platform -- iOS Framework
//
//  Copyright 1996-2020. Adobe. All Rights Reserved
//
//  AEPAssurance Version: 1.0.0

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface AEPAssurance : NSObject

    /**
     * @brief Registers the AEPAssurance extension with the Core Event Hub.
    */
+ (bool) registerExtension;

/**
 * @brief Provides the current version of Assurace SDK.
 *
 * @return a string representing the version of Assurace SDK
*/
+ (nonnull NSString*) extensionVersion;

/**
 * @brief Starts a Assurace session.
 *
 * Calling this method when a session has already been started will result in a no-op.
 * It will attempt to initiate a new Assurace session if no session is active.
 *
 * @param url a valid Assurace URL to start a session
 */
+ (void) startSession: (NSURL* _Nonnull) url;


@end

NS_ASSUME_NONNULL_END
