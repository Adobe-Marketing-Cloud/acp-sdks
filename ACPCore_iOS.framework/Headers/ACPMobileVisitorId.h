//
//  ACPMobileVisitorId.h
//  Adobe Experience Platform -- iOS Framework
//
//  Copyright 1996-2018. Adobe. All Rights Reserved

#ifndef ADBMOBILEMARKETING_ACPMobileVisitorId_H
#define ADBMOBILEMARKETING_ACPMobileVisitorId_H

#import <Foundation/Foundation.h>
#import "ACPCore.h"


@interface ACPMobileVisitorId()

- (instancetype) initWithOrigin: (NSString*) idOrigin type: (NSString*) idType id: (NSString*) identifier authentication:
    (ACPMobileVisitorAuthenticationState) authenticationState;

@end
#endif /* ADBMOBILEMARKETING_ACPMobileVisitorId_H */
