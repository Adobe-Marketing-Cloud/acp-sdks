//
//  ACPExtensionListener.h
//  Adobe Experience Platform -- iOS Framework
//
//  Copyright 1996-2019. Adobe. All Rights Reserved

#ifndef ADOBEMOBILE_ADBEXTENSIONLISTENER_H
#define ADOBEMOBILE_ADBEXTENSIONLISTENER_H

#import <Foundation/Foundation.h>

@class ACPExtension;
@class ACPExtensionEvent;

@interface ACPExtensionListener : NSObject {}

/*
 * @brief Initialize new listener.
 * Implementers can access the extension via `self.extension` as needed.
 * This method must be fast (<100ms) or the listener may be unregistered. Avoid file and/or network operations.
 * The `extension` method returns a valid reference even during `init`, since it will be set prior to `init` being called.
 *
 * @return ACPExtensionListener* or nil
 */
- (nonnull instancetype) init;

/*
 * @brief Reference to the extension that registered this listener
 *
 * The `extension` is set to the listener when registered but before ACPExtensionListener::init is called. It can
 * be used for accessing methods in the parent ACPExtension or the ACPExtension::api property.
 */
@property(nonatomic, readonly) ACPExtension* _Nonnull extension;

/*
 * @brief Called when an event is fired that matches eventType and eventSource passed to
 * ACPExtensionApi::registerListener:eventType:eventSource:error
 * This method must be fast (<100ms) or the listener may be unregistered. Execute long running tasks in a separate thread,
 * if necessary. Be aware that this method will typically be called from a different thread than listener was registered.
 *
 * @param event The event fired
 */
- (void) hear: (nonnull ACPExtensionEvent*) event;

@end

#endif /* ADOBEMOBILE_ADBEXTENSIONLISTENER_H */
