//
//  ACPCore_iOS.h
//  Adobe Experience Platform -- iOS Framework
//
//  Copyright 1996-2018. Adobe. All Rights Reserved

#import <UIKit/UIKit.h>

//! Project version number for AdobeMobileMarketingCore_iOS.
FOUNDATION_EXPORT double AdobeMobileMarketingCore_iOSVersionNumber;

//! Project version string for AdobeMobileMarketingCore_iOS.
FOUNDATION_EXPORT const unsigned char AdobeMobileMarketingCore_iOSVersionString[];

// import platform core public headers
#import <ACPCore_iOS/ACPExtension.h>
#import <ACPCore_iOS/ACPExtensionApi.h>
#import <ACPCore_iOS/ACPExtensionError.h>
#import <ACPCore_iOS/ACPExtensionEvent.h>
#import <ACPCore_iOS/ACPExtensionListener.h>
#import <ACPCore_iOS/ACPCore.h>
#import <ACPCore_iOS/ACPMobileVisitorId.h>
// TODO: need to rename these classes with the correct prefix and include them in umbrella header
// ...cascading effect to all extensions
//#import <ACPCore_iOS/MobileMarketingCoreBridge.h>
//#import <ACPCore_iOS/TypeBridge.h>
