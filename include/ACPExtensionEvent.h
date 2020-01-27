//
//  ACPExtensionEvent.h
//  Adobe Experience Platform -- iOS Framework
//
//  Copyright 1996-2019. Adobe. All Rights Reserved

#ifndef ADOBEMOBILE_ADBEXTENSIONEVENT_H
#define ADOBEMOBILE_ADBEXTENSIONEVENT_H

#import <Foundation/Foundation.h>

@interface ACPExtensionEvent : NSObject {}

/**
 * @brief Create a new broadcast event.
 *
 * Creates a new ACPExtensionEvent which may be dispatched to the Mobile SDK. An ACPExtensionEvent is heard by any listeners which are registered to
 * the same EventType and EventSource as the event.
 *
 * @param name The name of the event to be dispatched.
 * @param type The type of the event to be dispatched.
 * @param source The source of the event to be dispatched.
 * @param data (Optional) Data associated with the event. The NSDictionary passed should follow NSCoding protocol.
 * @param error (Optional) NSError** where any errors constructing the event can be reported.
 * @return a new instance of ACPExtensionEvent or nil if `data` is non-nil and is not in a valid format
 *
 * @see ACPCore::dispatchEvent:error:
 * @see ACPCore::dispatchEventWithResponseCallback:responseCallback:error:
 * @see ACPCore::dispatchResponseEvent::requestEvent:error:
 */
+ (nullable instancetype) extensionEventWithName: (nonnull NSString*) name
                                            type: (nonnull NSString*) type
                                          source: (nonnull NSString*) source
                                            data: (nullable NSDictionary*) data
                                           error: (NSError* _Nullable* _Nullable) error;

/**
 * @brief The name of this ACPExtensionEvent
 *
 * The ACPExtensionEvent name is a descriptive string used for logging.
 */
@property(nonatomic, readonly) NSString* _Nonnull eventName;

/**
 * @brief The EventType of this ACPExtensionEvent
 *
 * An ACPExtensionEvent is received by listeners which register with the same EventType and EventSource as the dispatched event.
 */
@property(nonatomic, readonly) NSString* _Nonnull eventType;

/**
* @brief The EventSource of this ACPExtensionEvent
*
* An ACPExtensionEvent is received by listeners which register with the same EventType and EventSource as the dispatched event.
*/
@property(nonatomic, readonly) NSString* _Nonnull eventSource;

/**
 * @brief The EventData of this ACPExtensionEvent
 *
 * The optional EventData may contain any payload information required for this ACPExtensionEvent.
 */
@property(nonatomic, readonly) NSDictionary* _Nullable eventData;
@property(nonatomic, readonly) NSString* _Nonnull eventUniqueIdentifier;

@end

#endif /* ADOBEMOBILE_ADBEXTENSIONEVENT_H */
