//
//  ACPGriffonEvent.h
//  Adobe Experience Platform -- iOS Framework
//
//  Copyright 1996-2020. Adobe. All Rights Reserved
//
//  ACPGriffon Version: 1.1.0

#import <Foundation/Foundation.h>

#pragma mark - ACPGriffonEvent

@interface ACPGriffonEvent : NSObject

#pragma mark - Instance members

@property(nonatomic, readonly) NSString* _Nonnull eventID;
@property(nonatomic, strong) NSString* _Nonnull clientID;
@property(nonatomic, readonly) NSString* _Nonnull vendor;
@property(nonatomic, readonly) NSString* _Nonnull type;
@property(nonatomic, readonly) NSDictionary* _Nullable payload;
@property(nonatomic, readonly) NSString* _Nullable pairID;
@property(nonatomic, readonly) long timestamp;
@property(nonatomic, readonly) int eventNumber;

#pragma mark - Initialization methods

/**
 * @brief Creates an ACPGriffonEvent instance with the required parameters specified in a JSON Object
 *
 * @discussion
 * The following keys are required in the provided JSON:
 *      > eventID - A unique UUID string to identify the event
 *      > vendor - A vendor string
 *      > type - A string describing the type of the event
 *      > timestamp - A whole number representing milliseconds since the Unix epoch
 *      > payload (optional) - A JSON object containing the event's payload
 *      > pairID (optional) - If this event is in response to another event, pairID contains the eventID of the
 *                            original event
 *
 * This method will return nil if called under any of the following conditions:
 *      > The json parameter is nil
 *      > The provided json is not valid
 *      > The provided json is not an object at its root
 *      > Any of the required keys are missing (see above for a list of required keys)
 *      > Any of the required keys do not contain the correct type of data
 *
 * @param json NSData containing the JSON that defines the ACPGriffonEvent.
 *
 * @return ACPGriffonEvent The ACPGriffonEvent instance defined by the provided json or nil.
 */
- (instancetype _Nullable) initWithJSONData: (NSData* _Nullable) json;

/**
 * @brief Creates an ACPGriffonEvent instance with the given vendor, type and payload.
 *
 * @param vendor  NSString The Vendor string to identity the event with. The string can be a reverse domain name format
 *                to uniquely identify the vendor.
 * @param type    NSString The type of the event.
 * @param payload NSDictionary The payload to be sent wrapped in the event. This will be serialized into
 *                JSON in the transport process.
 *
 * @return ACPGriffonEvent The ACPGriffonEvent instance
 */
- (instancetype _Nonnull) initWithVendor: (NSString* _Nonnull) vendor
                                    type: (NSString* _Nonnull) type
                                 payload: (NSDictionary* _Nullable) payload;

/**
 * @brief Creates an ACPGriffonEvent instance with the given vendor, type, pairID, payload, and timestamp.
 *
 * Available starting with v1.1.0
 *
 * @param vendor    NSString The Vendor string to identity the event with. The string can be a reverse domain name
 *                  format to uniquely identify the vendor.
 * @param type      NSString The type of the event.
 * @param pairID    NSString If this event is in response to another event, pairID represents the eventID of the
 *                  original triggering event.
 * @param payload   NSDictionary The payload to be sent wrapped in the event. This will be serialized into
 *                  JSON in the transport process.
 * @param timestamp long The timestamp representing the time the original Event was created.
 *
 * @return ACPGriffonEvent The ACPGriffonEvent instance
 */
- (instancetype _Nonnull) initWithVendor: (NSString* _Nonnull) vendor
                                    type: (NSString* _Nonnull) type
                                  pairID: (NSString* _Nullable) pairID
                                 payload: (NSDictionary* _Nullable) payload
                               timestamp: (long) timestamp;

#pragma mark - Helper methods

/**
 * @brief Returns the JSON representation of the ACPGriffonEvent in binary
 *
 * @return NSData The binary JSON data
 */
- (NSData* _Nonnull) jsonRepresentation;

@end

#pragma mark - ACPGriffonEventListener

@protocol ACPGriffonEventListener

/**
 * @brief Method to be called when an ACPGriffonEventListener needs to be notified of an ACPGriffonEvent
 *
 * @param remoteEvent ACPGriffonEvent that was processed.
 */
- (void) hear: (ACPGriffonEvent* _Nonnull) remoteEvent;

@end
