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

#ifndef ADOBEMOBILE_ADBEXTENSIONLISTENER_H
#define ADOBEMOBILE_ADBEXTENSIONLISTENER_H

#import <Foundation/Foundation.h>

@class ADBExtension;
@class ADBExtensionEvent;

@interface ADBExtensionListener : NSObject {}

/*
 * @brief Initialize new listener.
 * Implementers can access the extension via `self.extension` as needed.
 * This method must be fast (<100ms) or the listener may be unregistered. Avoid file and/or network operations.
 * The `extension` method returns a valid reference even during `init`, since it will be set prior to `init` being called.
 * @return ADBExtensionListener* or nil
 *
 */
- (nullable instancetype) init;

/*
 * @brief Reference to the extension that registered this listener
 *
 */
@property(nonatomic, readonly) ADBExtension* _Nonnull extension;

/*
 * @brief Called when an event is fired that matches eventType and eventSource passed to RegisterListener.
 * Be aware that this method will typically be called from a different thread than listener was registered on.
 * @param event The event fired
 */
- (void) hear: (nonnull ADBExtensionEvent*) event;

@end

#endif /* ADOBEMOBILE_ADBEXTENSIONLISTENER_H */
