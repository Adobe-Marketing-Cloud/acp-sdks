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
FOUNDATION_EXPORT double AdobeMarketingMobileTargetVersionNumber;
FOUNDATION_EXPORT const unsigned char AdobeMarketingMobileTargetVersionString[];
#else
extern double AdobeMarketingMobileTargetVersionNumber;
extern const unsigned char AdobeMarketingMobileTargetVersionString[];
#endif

// import headers from the core
#import <AdobeMarketingMobileCore/AdobeMarketingMobileCore.h>

// signal headers
#import <AdobeMarketingMobileSignal/Signal.h>
#import <AdobeMarketingMobileSignal/SignalConstants.h>
#import <AdobeMarketingMobileSignal/SignalListenerConfigurationResponseContent.h>
#import <AdobeMarketingMobileSignal/SignalListenerRulesEngineResponseContent.h>
#import <AdobeMarketingMobileSignal/SignalPublicApi.h>
#import <AdobeMarketingMobileSignal/Consequence.h>
