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
FOUNDATION_EXPORT double AdobeMarketingMobileAcquisitionVersionNumber;
FOUNDATION_EXPORT const unsigned char AdobeMarketingMobileAcquisitionVersionString[];
#else
extern double AdobeMarketingMobileAcquisitionVersionNumber;
extern const unsigned char AdobeMarketingMobileAcquisitionVersionString[];
#endif

// import headers from the core
#import <AdobeMarketingMobileCore/AdobeMarketingMobileCore.h>

// acquisition headers
#import <AdobeMarketingMobileAcquisition/Acquisition.h>
#import <AdobeMarketingMobileAcquisition/AcquisitionConstants.h>
#import <AdobeMarketingMobileAcquisition/AcquisitionDispatcherAcquisitionResponseContent.h>
#import <AdobeMarketingMobileAcquisition/AcquisitionDispatcherAnalyticsRequestContent.h>
#import <AdobeMarketingMobileAcquisition/AcquisitionFingerprinter.h>
#import <AdobeMarketingMobileAcquisition/AcquisitionHelper.h>
#import <AdobeMarketingMobileAcquisition/AcquisitionListenerAcquisitionOS.h>
#import <AdobeMarketingMobileAcquisition/AcquisitionListenerAcquisitionRequestContent.h>
#import <AdobeMarketingMobileAcquisition/AcquisitionListenerHubBooted.h>
#import <AdobeMarketingMobileAcquisition/AcquisitionListenerHubSharedState.h>
#import <AdobeMarketingMobileAcquisition/AcquisitionPublicApi.h>
