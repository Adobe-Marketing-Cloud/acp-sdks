//
//  ACPMobileServices.h
//  Adobe Experience Platform -- iOS Framework
//
//  Copyright 1996-2019. Adobe. All Rights Reserved
//  Core Version: 1.0.0


#import <Foundation/Foundation.h>

@interface ACPMobileServices : NSObject {}

/**
 * @brief Returns the current version of the ACPMobileServices Extension.
 */
+ (nonnull NSString*) extensionVersion;

/**
 * @brief Registers the Mobile Services extension
 *
 * This method should be called before any other Mobile Services API is called
 */
+ (void) registerExtension;

/**
 * @brief Marshalls the provided deeplink and generates an event containing its data.
 *
 * This method should be called within the application:openURL:options: app delegate method.
 *
 * If Analytics is configured in the SDK, calling this method with a valid URL will result in an
 * Analytics request being sent.
 *
 * @param deeplink the NSURL that the application is processing
 */
+ (void) trackAdobeDeepLink: (NSURL* _Nonnull) deeplink;

@end
