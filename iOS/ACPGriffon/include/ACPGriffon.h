//
//  ACPSGriffon.h
//  Adobe Experience Platform -- iOS Framework
//
//  Copyright 1996-2020. Adobe. All Rights Reserved
//
//  ACPGriffon Version: 1.0.2

#import <Foundation/Foundation.h>

@class ACPGriffonEvent;
/*! \mainpage Project Griffon iOS SDK - Doxygen Documentation
 *
 * \section intro_sec Introduction
 *
 * This docuemntation describes the APIs for the iOS SDK.
 * The entry point for this SDK is the ACPGriffon class.
 *
 */
typedef NS_ENUM(NSUInteger, ACPGriffonUILogColor) {
    ACPGriffonUILogVisibilityLow = 0,
    ACPGriffonUILogVisibilityNormal = 1,
    ACPGriffonUILogVisibilityHigh = 2,
    ACPGriffonUILogVisibilityCritical = 3
};


@class ACPGriffonEvent;
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
 *
*/
+ (nonnull NSString*) extensionVersion;

/**
 * @brief Starts a Project Griffon session.
 *
 * If a session is already started, this will do nothing. If no session is active,
 * then it will attempt to initiate a new Project Griffon session.
 *
 * @param url A valid Project Griffon URL to start a session
 *
 */
+ (void) startSession: (NSURL* _Nonnull) url;

/**
 * @brief Ends an active Project Griffon session
 *
 */
+ (void) endSession;

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
+ (void) sendEvent: (ACPGriffonEvent* _Nonnull) event;

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
+ (void) sendBlob: (NSData* _Nonnull) blob contentType: (NSString* _Nullable) contentType completion: (void (^_Nullable) (NSString* _Nullable blobID, NSError* _Nullable error)) block;


/**
 * @brief Displays a log message in the local-client UI interface.
 * @discussion   Intended to be used for logging messages that are needed during a validation session on the client side.
 *
 * @param level ACPGriffonLogLevel used to determine the coloring/priority of the log message.
 * @param message NSString containing the log contents
*/
+ (void) logLocalUILevel: (ACPGriffonUILogColor) level message: (NSString*) message;


+ (void) registerListenerForVendor: (NSString* _Nonnull) vendor block: (void (^_Nullable) (ACPGriffonEvent* _Nonnull event)) block;



@end

NS_ASSUME_NONNULL_END
