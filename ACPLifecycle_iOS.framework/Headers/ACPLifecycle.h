//
//  ACPLifecycle.h
//  Adobe Digital Marketing Suite -- iOS Application Measurement Library
//
//  Copyright 1996-2018. Adobe, Inc. All Rights Reserved
//
//  Target Version: 1.0

#import <Foundation/Foundation.h>


@interface ACPLifecycle : NSObject {}

#pragma mark - Lifecycle
+ (void) registerAdobeLifecycleExtension;
/**
 * @brief Pause/stop lifecycle session
 *
 * Pauses the current lifecycle session. Calling pause on an already paused session updates the paused timestamp,
 * having the effect of resetting the session timeout timer. If no lifecycle session is running, then calling
 * this method does nothing.
 *
 * A paused session is resumed if ADBMobileMarketing::lifecycleStart: is called before the session timeout. After
 * the session timeout, a paused session is closed and calling ADBMobileMarketing::lifecycleStart: will create
 * a new session. The session timeout is defined by the `lifecycle.sessionTimeout` configuration parameter.
 * If not defined, the default session timeout is five minutes.
 */
+ (void) lifecyclePause;

/**
 * @brief Start/resume lifecycle session
 *
 * Start a new lifecycle session or resume a previously paused lifecycle session. If a previously paused session
 * timed out, then a new session is created. If a current session is running, then calling this method does nothing.
 *
 * Additional context data may be passed when calling this method. Lifecycle data and any additional data are
 * sent as context data parameters to Analytics, to Target as mbox parameters, and for Audience Manager they are
 * sent as customer variables. Any additional data is also used by the Rules Engine when processing rules.
 *
 * @param additionalContextData optional additional context for this session.
 */
+ (void) lifecycleStart: (nullable NSDictionary<NSString*, NSString*>*) additionalContextData;

@end
