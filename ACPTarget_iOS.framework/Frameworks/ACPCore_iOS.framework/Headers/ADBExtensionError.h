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
 ****************************************************************************/

#ifndef ADOBEMOBILE_ADBEXTENSIONERROR_H
#define ADOBEMOBILE_ADBEXTENSIONERROR_H

#import <Foundation/Foundation.h>

extern NSString* _Nonnull const ADBExtensionErrorDomain;

/**
 * @brief Errors that can be returned by either any of the 3rd party extension APIs.
 */
typedef NS_ENUM(NSUInteger, ADBExtensionError) {
    ADBUnexpectedExtensionError = 0,
    ADBBadExtensionNameExtensionError = 1,
    ADBDuplicateExtensionNameExtensionError = 2,
    ADBEventTypeNotSupportedExtensionError = 3,
    ADBEventSourceNotSupportedExtensionError = 4,
    ADBEventDataNotSupportedExtensionError = 5,
    ADBBadExtensionClassExtensionError = 6
};

#endif /* ADOBEMOBILE_ADBEXTENSIONERROR_H */

