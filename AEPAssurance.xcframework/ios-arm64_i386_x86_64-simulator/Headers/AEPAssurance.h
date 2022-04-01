//
//  AEPAssurance.h
//  Adobe Experience Platform -- iOS Framework
//
//  Copyright 1996-2020. Adobe. All Rights Reserved
//
//  AEPAssurance Version: 1.1.4

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface AEPAssurance : NSObject

    /**
     * @brief Registers the AEPAssurance extension with the Core Event Hub.
    */
+ (bool) registerExtension;

/**
 * @brief Provides the current version of AEPAssurance SDK.
 *
 * @return a string representing the version of AEPAssurance SDK
*/
+ (nonnull NSString*) extensionVersion;

/**
 * @brief Starts an AEPAssurance session.
 *
 * Calling this method when a session has already been started results in a no-op, otherwise it attempts to initiate a new AEPAssurance session.
 *
 * @param url a valid AEPAssurance URL to start a session
 */
+ (void) startSession: (NSURL* _Nonnull) url;


@end

NS_ASSUME_NONNULL_END
