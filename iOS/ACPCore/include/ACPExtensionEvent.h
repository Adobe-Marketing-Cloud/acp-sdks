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
 * @brief Create a new broadcast event. See TBD for a list of supported types, sources and data formats.
 * @param name The name of the event to be dispatched.
 * @param type The type of the event to be dispatched.
 * @param source The source of the event to be dispatched.
 * @param data (Optional) Data associated with the event. The NSDictionary passed should follow NSCoding protocol.
 * @param error (Optional) NSError** where any errors constructing the event can be reported.
 * @return a new instance of ACPExtensionEvent or nil if `data` is non-nil and is not in a valid format
 */
+ (nullable instancetype) extensionEventWithName: (nonnull NSString*) name
                                            type: (nonnull NSString*) type
                                          source: (nonnull NSString*) source
                                            data: (nullable NSDictionary*) data
                                           error: (NSError* _Nullable* _Nullable) error;

/**
 * @brief Event details
 */
@property(nonatomic, readonly) NSString* _Nonnull eventName;
@property(nonatomic, readonly) NSString* _Nonnull eventType;
@property(nonatomic, readonly) NSString* _Nonnull eventSource;
@property(nonatomic, readonly) NSDictionary* _Nullable eventData;
@property(nonatomic, readonly) NSString* _Nonnull eventUniqueIdentifier;

@end

#endif /* ADOBEMOBILE_ADBEXTENSIONEVENT_H */
