/*
Copyright 2017 Adobe. All rights reserved.
This file is licensed to you under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License. You may obtain a copy
of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS
OF ANY KIND, either express or implied. See the License for the specific language
governing permissions and limitations under the License.
*/

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
