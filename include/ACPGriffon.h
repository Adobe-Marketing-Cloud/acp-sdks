//
//  ACPGriffon.h
//  Adobe Experience Platform -- iOS Framework
//
//  Copyright 1996-2020. Adobe. All Rights Reserved
//
//  ACPGriffon Version: 1.2.1

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface ACPGriffon : NSObject

    /**
     * @brief Registers the ACPGriffon extension with the Core Event Hub.
    */
+ (bool) registerExtension;

/**
 * @brief Provides the current version of Griffon SDK.
 *
 * @return a string representing the version of Griffon SDK
*/
+ (nonnull NSString*) extensionVersion;

/**
 * @brief Starts a Project Griffon session.
 *
 * Calling this method when a session has already been started will result in a no-op.
 * It will attempt to initiate a new Project Griffon session if no session is active.
 *
 * @param url a valid Project Griffon URL to start a session
 */
+ (void) startSession: (NSURL* _Nonnull) url;


@end

NS_ASSUME_NONNULL_END
