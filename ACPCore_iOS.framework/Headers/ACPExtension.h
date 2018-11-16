//
//  ACPExtension.h
//  Adobe Experience Platform -- iOS Framework
//
//  Copyright 1996-2018. Adobe. All Rights Reserved

#ifndef ADOBEMOBILE_ADBEXTENSIONINTERFACE_H
#define ADOBEMOBILE_ADBEXTENSIONINTERFACE_H

#import <Foundation/Foundation.h>
#import "ACPExtensionApi.h"

@interface ACPExtension : NSObject {}

/*
 * @brief Initialize a new extension instance.
 * Implementers can override this and call into the core via `self.api` e.g. to set listeners.
 * The `api` method returns a valid interface even during `init`, since it will be created prior to `init` being called.
 * @return Valid instance of the extension
 *
 */
- (nonnull instancetype) init;

/*
 * @brief Get extension name for use by the event hub to managing shared state and for logging.
 * This MUST be overridden by the extension.
 * This will be called at least once before {@code init}. Use a static initializer, don't wait for `init` method.
 * If `nil` is returned, the extension will not be registered.
 *
 * @return NSString containing the extensions name
 *
 */
- (nullable NSString*) name;

/*
 * @brief Get extension version as a string for use by the event hub for logging.
 * This should be overridden by the extension.
 * If it is not overridden, `nil` will be returned and logged for the extension.
 *
 * @return NSString containing the extensions version
 *
 */
- (nullable NSString*) version;

/*
 * @brief Called when an unexpected error related to this extension has occurred during SDK processing.
 * Implementers should override this to see what errors are occurring and handle them as needed.
 * This should be called very infrequently for a well written extension implementation.
 * @return
 *
 */
- (void) unexpectedError: (nonnull NSError*) error;

/*
 * @brief Called when the extension is unregistered by the core.
 * Implementers can override this to clean up resources when the extension is released.
 *
 */
- (void) onUnregister;

/*
 * @brief This provides the services the extension will need.
 *
 */
@property(nonatomic, readonly) ACPExtensionApi* _Nonnull api;

@end

#endif /* ADOBEMOBILE_ADBEXTENSIONINTERFACE_H */
