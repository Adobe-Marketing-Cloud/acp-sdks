//
//  ACPMobileVisitorId.h
//  Adobe Experience Platform -- iOS Framework
//
//  Copyright 1996-2018. Adobe. All Rights Reserved

#import <Foundation/Foundation.h>
#import "ACPCore.h"

@interface ACPMobileVisitorId()

- (instancetype) initWithOrigin: (NSString*) idOrigin type: (NSString*) idType id: (NSString*) identifier authentication:
    (ACPMobileVisitorAuthenticationState) authenticationState;

@end

