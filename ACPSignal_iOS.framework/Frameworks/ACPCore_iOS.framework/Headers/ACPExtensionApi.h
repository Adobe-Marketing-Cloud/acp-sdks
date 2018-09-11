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

#ifndef ADOBEMOBILE_ADBEXTENSIONSERVICES_H
#define ADOBEMOBILE_ADBEXTENSIONSERVICES_H

#import <Foundation/Foundation.h>
#import "ACPExtensionError.h"
#import "ACPExtensionEvent.h"
#import "ACPExtensionListener.h"
#import "ACPExtensionProcessor.h"

/*
 * @brief This interface is used by extensions to call into the core event hub.
 * High level documentation for this interface is here: https://wiki.corp.adobe.com/display/ADMSMobile/V5+Extensions
 */
@interface ACPExtensionApi : NSObject {}

/*
 * @brief Called by the extension to register a processor to handle all events. When any event is fired, this interface will be called to process the event.
 * @param processor A callback interface to receive events
 * @param error An optional parameter where an NSError* will be returned if valid and NO was returned
 * @return YES if processor was added, NO otherwise. For example if processing is not allowed.
 */
- (BOOL) registerProcessor: (nonnull Class) processorClass
                     error: (NSError* _Nullable* _Nullable) error;

/*
 * @brief Called by the extension to register a listener for a specific event. When this event is fired, the listener interface will be called with details.
 * @param listener A callback interface to receive events
 * @param eventType The type of the event we are listening for. See documentation for the list of available types.
 * @param eventSource The source for the events we are listening for. See documentation for the list of available sources.
 * @param error An optional parameter where an NSError* will be returned if valid and NO was returned
 * @return YES if listener was added, NO otherwise. For example if listening to this event is not allowed or event is unknown/unsupported.
 */
- (BOOL) registerListener: (nonnull Class) listenerClass
                eventType: (nonnull NSString*) eventType
              eventSource: (nonnull NSString*) eventSource
                    error: (NSError* _Nullable* _Nullable) error;

/*
 * @brief Called by extension to dispatch an event for other extensions or the internal SDK to consume.
 * @param event Event we are dispatching
 * @param error An optional parameter where an NSError* will be returned if valid and NO was returned
 * @return YES if event was dispatched, NO otherwise. For example if this extension is not allowed to dispatch this kind of event.
 */
- (BOOL) dispatchEvent: (nonnull ACPExtensionEvent*) event
                 error: (NSError* _Nullable* _Nullable) error;

/*
 * @brief Called by extension to set a shared state for itself. Usually called from a listener during event processing.
 * @param state State data (in JSON format). Passing `nil` will remove existing state data.
 * @param event The event for which the state is being set. Passing `nil` will set default state for all events.
 * @param error An optional parameter where an NSError* will be returned if valid and NO was returned
 * @return YES if state was set, NO otherwise. For example if the JSON passed for the state data was invalid.
 */
- (BOOL) setSharedEventState: (nullable NSDictionary*) state
                       event: (nullable ACPExtensionEvent*) event
                       error: (NSError* _Nullable* _Nullable) error;

/*
 * @brief Called by extension to clear all shared state it has previously set. Usually called during OnUnregister.
 * @param error An optional parameter where an NSError* will be returned if valid and NO was returned
 * @return YES if states were cleared, NO otherwise. For example if an internal error occurred.
 */
- (BOOL) clearSharedEventStates: (NSError* _Nullable* _Nullable) error;

/*
 * @brief Called by extension from a listener to get a shared state during event processing.
 * @param name State to retrieve data for. See documentation for the list of available states.
 * @param event The event for which the state is being requested. Passing `nil` will retrieve latest state available.
 * @param error An optional parameter where an NSError* will be returned in case of failure
 * @return NULL if state does not exists or NSDictionary* containing state data at that version in JSON format
 */
- (nullable NSDictionary*) getSharedEventState: (nonnull NSString*) name
                                         event: (nullable ACPExtensionEvent*) event
                                         error: (NSError* _Nullable* _Nullable) error;

/*
 * @brief Un-register this extension. This can be called at any time after SDK initialization.
 * This will result in the ACPExtension::OnUnregister callback being called.
 */
- (void) unregisterExtension;

@end

#endif /* ADOBEMOBILE_ADBEXTENSIONSERVICES_H */
