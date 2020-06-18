//
//  ACPGriffon.h
//  Adobe Experience Platform -- iOS Framework
//
//  Copyright 1996-2020. Adobe. All Rights Reserved
//
//  ACPGriffon Version: 1.1.3

#import <Foundation/Foundation.h>

@class ACPGriffonEvent;

/*! \mainpage Project Griffon iOS SDK - Doxygen Documentation
 *
 * \section intro_sec Introduction
 *
 * This docuemntation describes the APIs for the iOS SDK.
 * The entry point for this SDK is the ACPGriffon class.
 */
typedef NS_ENUM(NSUInteger, ACPGriffonUILogColor) {
    ACPGriffonUILogVisibilityLow = 0,
    ACPGriffonUILogVisibilityNormal = 1,
    ACPGriffonUILogVisibilityHigh = 2,
    ACPGriffonUILogVisibilityCritical = 3
};

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

/**
 * @brief Ends an active Project Griffon session
 *
 * Calling this method when no session is active will result in a no-op.
 */
+ (void) endSession;

/**
 * @brief Attempts to reconnect to a Project Griffon session that is already running.
 *
 * Intended to be called on every app start to ensure that an already running session can be re-connected to.
 */
+ (void) attemptReconnect;

/**
 * @brief Send an ACPGriffonEvent to the Project Griffon Service.
 *
 * @param event the ACPGriffonEvent object to send to the Project Griffon service
 */
+ (void) sendEvent: (ACPGriffonEvent* _Nonnull) event;

/**
 * @brief Sends a binary blob of data to Project Griffon server to be recorded as an 'asset' for the current session.
 * @discussion Posts the binary blob to Project Griffon with the given contentType.  If no contentType is provided,
 *             default of 'application/octet-stream' will be used.  Expects server to respond with a JSON object
 *             containing one of the following keys:
 *               > blobID - NSString containing the asset ID of the newly stored asset
 *               > error - NSError representing the error that occurred
 *
 * @param blob NSData object containing the binary data to transmit
 * @param contentType NSString containing the MIME type of the blob.  If null will default to application/octet-stream
 * @param block completion to be executed when the upload has completed (either successfully or with an error condition)
 */
+ (void) sendBlob: (NSData* _Nonnull) blob
      contentType: (NSString* _Nullable) contentType
       completion: (void (^_Nullable) (NSString* _Nullable blobID, NSError* _Nullable error)) block;

/**
 * @brief Displays a log message in the local-client UI interface.
 * @discussion Intended to be used for logging messages that are needed during a validation session on the client side.
 *
 * @param level ACPGriffonLogLevel used to determine the priority and text color of the log message
 * @param message NSString containing the log contents
*/
+ (void) logLocalUILevel: (ACPGriffonUILogColor) level message: (NSString*) message;

/**
 * @brief Registers a callback for ACPGriffonEvents with the provided vendor.
 *
 * @param vendor NSString containing the vendor name
 * @param block completion block to be executed when the SDK processes an ACPGriffonEvent with a matching vendor
 */
+ (void) registerListenerForVendor: (NSString* _Nonnull) vendor
                             block: (void (^_Nullable) (ACPGriffonEvent* _Nonnull event)) block;

@end

NS_ASSUME_NONNULL_END
