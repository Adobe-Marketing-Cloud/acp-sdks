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

#ifndef ADOBEMOBILE_ADBEXTENSIONPROCESSOR_H
#define ADOBEMOBILE_ADBEXTENSIONPROCESSOR_H

#import <Foundation/Foundation.h>

@class ADBExtension;
@class ADBExtensionEvent;

@interface ADBExtensionProcessor : NSObject {}

/*
 * @brief Initialize new processor
 * Implementers can access the extension via `self.extension` as needed.
 * This method must be fast (<100ms) or the processor may be unregistered. Avoid file and/or network operations.
 * The `extension` method returns a valid reference even during `init`, since it will be set prior to `init` being called.
 * @return ADBExtensionProcessor* or nil
 *
 */
- (nullable instancetype) init;

/*
 * @brief Reference to the extension that registered this processor
 *
 */
@property(nonatomic, readonly) ADBExtension* _Nonnull extension;

/**
 * @brief Called when any event is fired.
 * This method decides how to handle each event as it comes through. It must be fast (<100ms) else event processing WILL be blocked.
 * Be aware that this method will typically be called from a different thread than listener was registered on.
 * There are three potential outcomes:
 *   1) Ignore this event and pass through unchanged. This is the most common case. Return the event passed in unchanged for this outcome.
 *   2) Block this event. Return NULL for this outcome.
 *   3) Add/Remove/Modify event details and pass through. Return a copy of the event with member data added/removed/modified as needed for this outcome.
 * @param event The event to be processed
 * @return one of the three choices above
 */
- (nullable ADBExtensionEvent*) process: (nonnull ADBExtensionEvent*) event;

@end

#endif /* ADOBEMOBILE_ADBEXTENSIONPROCESSOR_H */
