/* **************************************************************************
 *
 * ADOBE CONFIDENTIAL
 * ___________________
 *
 * Copyright 2018 Adobe Systems Incorporated
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Adobe Systems Incorporated and its suppliers,
 * if any.  The intellectual and technical concepts contained
 * herein are proprietary to Adobe Systems Incorporated and its
 * suppliers and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Adobe Systems Incorporated.
 ****************************************************************************/

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
 * @return a new instance of ACPExtensionEvent
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

@end

#endif /* ADOBEMOBILE_ADBEXTENSIONEVENT_H */
