//
//  ACPExtensionError.h
//  Adobe Experience Platform -- iOS Framework
//
//  Copyright 1996-2018. Adobe. All Rights Reserved

#ifndef ADOBEMOBILE_ADBEXTENSIONERROR_H
#define ADOBEMOBILE_ADBEXTENSIONERROR_H

#import <Foundation/Foundation.h>

extern NSString* _Nonnull const ACPExtensionErrorDomain;

/**
 * @brief Errors that can be returned by either any of the 3rd party extension APIs.
 */
typedef NS_ENUM(NSUInteger, ACPExtensionError) {
    ADBUnexpectedExtensionError = 0,
    ADBBadExtensionNameExtensionError = 1,
    ADBDuplicateExtensionNameExtensionError = 2,
    ADBEventTypeNotSupportedExtensionError = 3,
    ADBEventSourceNotSupportedExtensionError = 4,
    ADBEventDataNotSupportedExtensionError = 5,
    ADBBadExtensionClassExtensionError = 6,
    ADBEventNullError = 7,
};

#endif /* ADOBEMOBILE_ADBEXTENSIONERROR_H */

