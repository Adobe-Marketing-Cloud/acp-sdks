//
//  AEPMobileServices.h
//  Adobe Experience Platform -- iOS Framework
//
//  Copyright 1996-2021. Adobe. All Rights Reserved
//  Mobile Services Version: 3.0.2


#import <Foundation/Foundation.h>
@import AEPCore;

@interface AEPMobileServices : NSObject <AEPExtension>

    /**
     * @brief Returns the current version of the AEPMobileServices Extension.
     */
+ (nonnull NSString*) extensionVersion;

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
