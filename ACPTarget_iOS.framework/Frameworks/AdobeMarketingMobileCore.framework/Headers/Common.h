/* **************************************************************************
 *
 * ADOBE CONFIDENTIAL
 * ___________________
 *
 * Copyright 2017 Adobe Systems Incorporated
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

#ifndef ADOBEMOBILE_UTIL_COMMON_H
#define ADOBEMOBILE_UTIL_COMMON_H

/**
 * @file Common.h
 * Header file containing generally useful constructs.
 */

/**
 * ADOBE_DEPRECATED(void SomeFunction());
 *
 * When declaring a function, marks that function as deprecated.
 */
#ifdef __GNUC__
#define ADOBE_DEPRECATED(FUNCTION_SIGNATURE) FUNCTION_SIGNATURE __attribute__ ((deprecated))
#else
#pragma message("warning: ADOBE_DEPRECATED is not implemented for this compiler")
#define ADOBE_DEPRECATED(FUNCTION_SIGNATURE) FUNCTION_SIGNATURE
#endif

/**
 * Usage:
 *
 *     ADOBE_VIRTUAL_FOR_TESTS void Foo();
 *
 * ADOBE_VIRTUAL_FOR_TESTS should be used instead of `virtual` in cases where a function is only
 * only virtual to enable test-related functionality such as mocking and should not be overrided otherwise.
 *
 * When declaring a function, ADOBE_VIRTUAL_FOR_TESTS is currently equivalent to virtual in all builds
 * release or debug. However, non-test code should not rely upon this fact. In the future,
 * ADOBE_VIRTUAL_FOR_TESTS may or may not be equivalent to virtual for all builds.
 *
 * Functions that are intended to be overrided by non-testing related subclasses should be marked virtual.
 */
#define ADOBE_VIRTUAL_FOR_TESTS virtual

#endif //ADOBEMOBILE_UTIL_COMMON_H
