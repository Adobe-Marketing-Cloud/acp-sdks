/*************************************************************************
 *
 * ADOBE CONFIDENTIAL
 * ___________________
 *
 *  Copyright 2017 Adobe Systems Incorporated
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Adobe Systems Incorporated and its suppliers,
 * if any.  The intellectual and technical concepts contained
 * herein are proprietary to Adobe Systems Incorporated and its
 * suppliers and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Adobe Systems Incorporated.
 *
 **************************************************************************/

#ifndef ADBMOBILEMARKETING_ACPMobileVisitorId_H
#define ADBMOBILEMARKETING_ACPMobileVisitorId_H

#import <Foundation/Foundation.h>
#import "ACPCore.h"


@interface ACPMobileVisitorId()

- (instancetype) initWithOrigin: (NSString*) idOrigin type: (NSString*) idType id: (NSString*) identifier authentication:
    (ACPMobileVisitorAuthenticationState) authenticationState;

@end
#endif /* ADBMOBILEMARKETING_ACPMobileVisitorId_H */
