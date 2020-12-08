//
//  ACPError.h
//  Adobe Experience Platform -- iOS Framework
//
//  Copyright 1996-2020. Adobe. All Rights Reserved

#ifndef ADOBEMOBILE_ACPERROR_H
#define ADOBEMOBILE_ACPERROR_H

#import <Foundation/Foundation.h>

extern NSString* _Nonnull const ACPErrorDomain;

/**
 * @brief Errors that can be returned by either any of the 3rd party extension APIs.
 */
typedef NS_ENUM(NSUInteger, ACPError) {
    ACPErrorUnexpected = 0,
    ACPErrorCallbackTimeout = 1,
    ACPErrorCallbackNil = 2,
    ACPErrorExtensionNotInitialized = 11,
};


#endif /* ADOBEMOBILE_ACPERROR_H */

