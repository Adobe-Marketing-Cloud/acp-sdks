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

#if IDENTITY_OS_IOS
FOUNDATION_EXPORT double AdobeMarketingMobileIdentityVersionNumber;
FOUNDATION_EXPORT const unsigned char AdobeMarketingMobileIdentityVersionString[];
#else
extern double AdobeMarketingMobileIdentityVersionNumber;
extern const unsigned char AdobeMarketingMobileIdentityVersionString[];
#endif

// import headers from the core
#import <AdobeMarketingMobileCore/AdobeMarketingMobileCore.h>

// target headers
#import <AdobeMarketingMobileIdentity/ConfigurationSharedStateIdentity.h>
#import <AdobeMarketingMobileIdentity/Identity.h>
#import <AdobeMarketingMobileIdentity/IdentityConstants.h>
#import <AdobeMarketingMobileIdentity/IdentityDatabaseHit.h>
#import <AdobeMarketingMobileIdentity/IdentityDatabaseHitSchema.h>
#import <AdobeMarketingMobileIdentity/IdentityDispatcherAnalyticsRequestContent.h>
#import <AdobeMarketingMobileIdentity/IdentityDispatcherConfigurationRequestContent.h>
#import <AdobeMarketingMobileIdentity/IdentityDispatcherIdentityResponseIdentity.h>
#import <AdobeMarketingMobileIdentity/IdentityHitDatabase.h>
#import <AdobeMarketingMobileIdentity/IdentityHitProcessor.h>
#import <AdobeMarketingMobileIdentity/IdentityHitQueue.h>
#import <AdobeMarketingMobileIdentity/IdentityListenerBootedEvent.h>
#import <AdobeMarketingMobileIdentity/IdentityListenerConfigurationResponseContent.h>
#import <AdobeMarketingMobileIdentity/IdentityListenerHubSharedState.h>
#import <AdobeMarketingMobileIdentity/IdentityListenerRequestIdentity.h>
#import <AdobeMarketingMobileIdentity/IdentityObject.h>
#import <AdobeMarketingMobileIdentity/IdentityPublicApi.h>
#import <AdobeMarketingMobileIdentity/VisitorId.h>
#import <AdobeMarketingMobileIdentity/VisitorIdAuthenticationState.h>

