//
//  ACPGriffonEvent.h
//  Adobe Experience Platform -- iOS Framework
//
//  Copyright 1996-2019. Adobe. All Rights Reserved
//
//  ACPGriffon Version: 1.0.0

#import <Foundation/Foundation.h>

@interface ACPGriffonEvent : NSObject

@property(nonatomic, readonly) NSString* eventID;
@property(nonatomic, readonly) NSString* vendor;
@property(nonatomic, readonly) NSString* type;
@property(nonatomic, readonly) NSDictionary* payload;
@property(nonatomic, readonly) NSString* pairID;

/**
 * @brief Creates an ACPGriffonEvent instance with the given vendor, type and payload.
 *
 * @param vendor NSString The Vendor string to identity the event with. The string can be a reverse domain name format to uniquely identify the vendor.
 * @param type  NSString The type of the event.
 * @param payload NSDictionary The payload to be sent wrapped in the event. This will be serialized into Json in the transport process.
 * @return ACPGriffonEvent The ACPGriffonEvent instance
 */
- (instancetype) initWithVendor: (NSString*) vendor type: (NSString*) type payload: (NSDictionary*) payload;
/**
 * @brief Creates an ACPGriffonEvent instance with the required parameters specified in a JSON Object
 *
 * @discussion The Json keys required are:
 *
 * eventID - Required - A unique UUID string to identify the event
 *
 * vendor - Required - A vendor string
 *
 * type - Required - A type string for the event
 *
 * payload - Optional - A JSON Object for the payload
 *
 * pairID - Optional - The eventID of the event this is a response for
 *
 * @return ACPGriffonEvent The ACPGriffonEvent instance. Will return nil if any the required parameters are not present in the JSON supplied.
 */
- (instancetype) initWithJSONData: (NSData*) json;
/**
 * @brief Returns the Json representation of the Event in binary
 * @return NSData The binary json data
 */
- (NSData*) jsonRepresentation;
/**
 * @brief Creates a response event with the supplied payload as the response
 * @return ACPGriffonEvent A response event
 */
- (instancetype) createResponseEventWithPayload: (NSDictionary*) payload;
- (NSString*) description;

@end

@protocol ACPGriffonEventListener

- (void) hear: (ACPGriffonEvent*) remoteEvent;

@end
