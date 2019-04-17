//
//  ACPGriffon.h
//  Adobe Experience Platform -- iOS Framework
//
//  Copyright 1996-2019. Adobe. All Rights Reserved
//
//  ACPGriffon Version: 0.0.9beta

#import <Foundation/Foundation.h>

/*! \mainpage Project Griffon iOS SDK - Doxygen Documentation
 *
 * \section intro_sec Introduction
 *
 * This docuemntation describes the APIs for the iOS SDK.
 * The entry point for this SDK is the ACPGriffon class.
 *
 *
 */

typedef NS_ENUM(NSUInteger, ACPGriffonLogLevel) {
    ACPGriffonLogLevelError = 0,
    ACPGriffonLogLevelWarning = 1,
    ACPGriffonLogLevelDebug = 2,
    ACPGriffonLogLevelVerbose = 3
};


NS_ASSUME_NONNULL_BEGIN

@class ACPGriffonEvent;

@interface ACPGriffon : NSObject

+ (void) registerListenerForVendor: (NSString*) vendor block: (void (^) (ACPGriffonEvent* event)) block;

/**
 * @brief Starts a Project Griffon session.
 *
 * If a session is already started, this will do nothing. If no session is active,
 * then it will attempt to initiate a new Project Griffon session.
 *
 * @param url A valid Project Griffon URL to start a session
 *
 */
+ (void) startSession: (NSURL*) url;

/**
 * @brief Attempts to reconnect to an already running Project Griffon session.
 *
 * Intended to be called on every app start to ensure that an already running session can be re-connected to.
 *
 */
+ (void) attemptReconnect;

/**
 * @brief Send a message to the Project Griffon Service
 *
 * @param event The ACPGriffonEvent object to send to the Project Griffon service
 */
+ (void) sendEvent: (ACPGriffonEvent*) event;

/**
 * @brief Sends a binary blob of data to Project Griffon server to be recorded as an 'asset' for the current session
 * @discussion  Posts the binary blob to Project Griffon with the given contentType.  If no contentType is provided, default of
 *              'application/octet-stream' will be used.  Expects server to respond with a JSON object containing at one of
 *              the following keys (both will have string values):
 *                      'blobID' - contains asset ID of the newly stored asset
 *                      'error' - description of an error that occurred
 *
 * @param blob NSData object containing the binary data to transmit.
 * @param contentType NSString containing the MIME type of the blob.  If null will default to application/octet-stream.
 * @param block completion to be executed when the upload has completed (either successfully or with an error condition).
 */
+ (void) sendBlob: (NSData* _Nonnull) blob contentType: (NSString* _Nullable) contentType completion: (void (^) (NSString* _Nullable blobID, NSError* _Nullable error)) block;

/**
 * @brief Ends an active Project Griffon session
 *
 */
+ (void) endSession;

/**
 * @brief Gets the current logging level
 *
 * @return ACPGriffonLogLevel detailing the currently set logging level.
 */
+ (ACPGriffonLogLevel) logLevel;

/**
 * @brief Sets the current logging level
 *
 * @param logLevel ACPGriffonLogLevel to filter output of logging statements.
 */
+ (void) setLogLevel: (ACPGriffonLogLevel) logLevel;

@end

NS_ASSUME_NONNULL_END
