/*
Copyright 2018 Adobe. All rights reserved.
This file is licensed to you under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License. You may obtain a copy
of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS
OF ANY KIND, either express or implied. See the License for the specific language
governing permissions and limitations under the License.
*/

#import <Foundation/Foundation.h>

@interface ACPDataMarshaller : NSObject {}

/**
 * @brief Verifies if the given string is null, empty or it only contains whitespaces.
 *
 * @return the evaluation result for the given string.
 */
+ (bool) isEmpty: (nullable NSString*) string;

/**
 * @brief Marshal the application context available at launch time into a generic NSDictionary.
 *
 * @param userInfo dictionary of context data available at launch time
 * @return An instance of this same marshaller, to help with chaining calls.
 */
- (nonnull ACPDataMarshaller*) marshalLaunchInfo: (nonnull NSDictionary*) userInfo;

/**
 * @brief Return the NSDictionary held by this this marshaller
 *
 * @return NSDictionary containing the processed keys from the received user info
 */
- (nonnull NSDictionary*) getLaunchData;

@end
