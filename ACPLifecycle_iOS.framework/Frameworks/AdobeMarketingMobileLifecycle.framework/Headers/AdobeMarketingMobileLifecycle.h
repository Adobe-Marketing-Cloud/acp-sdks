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
 **************************************************************************/

#if TARGET_OS_IOS
#import <UIKit/UIKit.h>
FOUNDATION_EXPORT double AdobeMarketingMobileLifecycleVersionNumber;
FOUNDATION_EXPORT const unsigned char AdobeMarketingMobileLifecycleVersionString[];
#else
extern double AdobeMarketingMobileLifecycleVersionNumber;
extern const unsigned char AdobeMarketingMobileLifecycleVersionString[];
#endif

// import headers from the core
#import <AdobeMarketingMobileCore/AdobeMarketingMobileCore.h>

// target headers
#import <AdobeMarketingMobileLifecycle/Lifecycle.h>
#import <AdobeMarketingMobileLifecycle/LifecycleConstants.h>
#import <AdobeMarketingMobileLifecycle/LifecycleDispatcherResponseContent.h>
#import <AdobeMarketingMobileLifecycle/LifecycleSession.h>
#import <AdobeMarketingMobileLifecycle/LifecycleListenerSharedStateUpdate.h>
#import <AdobeMarketingMobileLifecycle/LifecycleListenerRequestContent.h>
#import <AdobeMarketingMobileLifecycle/LifecycleListenerHubBooted.h>
#import <AdobeMarketingMobileLifecycle/LifecycleMetricsBuilder.h>
#import <AdobeMarketingMobileLifecycle/LifecyclePublicApi.h>
