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
FOUNDATION_EXPORT double AdobeMarketingMobileAnalyticsVersionNumber;
FOUNDATION_EXPORT const unsigned char AdobeMarketingMobileAnalyticsVersionString[];
#else
extern double AdobeMarketingMobileAnalyticsVersionNumber;
extern const unsigned char AdobeMarketingMobileAnalyticsVersionString[];
#endif

// analytics headers
#import <AdobeMarketingMobileAnalytics/Analytics.h>
#import <AdobeMarketingMobileCore/VisitorId.h>
#import <AdobeMarketingMobileCore/VisitorIdAuthenticationState.h>
#import <AdobeMarketingMobileAnalytics/AnalyticsPublicApi.h>


