/*
Copyright 2020 Adobe. All rights reserved.
This file is licensed to you under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License. You may obtain a copy
of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS
OF ANY KIND, either express or implied. See the License for the specific language
governing permissions and limitations under the License.
*/

#import <Foundation/Foundation.h>

/**
 * ACPHttpConnection to be used when overriding the network stack in place of internal network connection implementation. Represents the response to an Http request. Has NSURLResponse response, and NSData data as properties
 */
@interface ACPHttpConnection : NSObject
    /**
     * Constructor for ACPHttpConnection
     * @param response NSURLResponse for the http connection
     * @param data the http message body as NSData
     */
- (instancetype _Nullable) initWithResponse: (NSHTTPURLResponse* _Nullable) response data: (NSData* _Nullable) data;

@property(nonatomic, readonly, nullable) NSHTTPURLResponse* response;
@property(nonatomic, readonly, nullable) NSData* data;

@end

NS_ASSUME_NONNULL_BEGIN
/**
 * Protocol for network overrides
 * To be implemented by anyone who wishes to override the SDK's default network stack
 * Implementer is responsible for updating the @code {shouldOverride} method to let the sdk know if the default network stack should be overriden or not.
 */
@protocol ACPHttpConnectionPerformer <NSObject>
/**
 * Determines if the provided url & method should be overriden by this instance. Used to determine if the network stack should be overriden
 *
 * @param url NSString url for the request
 *
 * @param method NSString method for the request e.g. "POST"
 */
- (BOOL) shouldOverride: (NSURL*) url method: (NSString*) method;

/**
 * URL request override with a completion block
 *
 * @param url NSString containing the full url for the connection
 * @param command NSString representation of the request method, for example "POST", "GET"
 * @param payload NSString representation of Http body to be sent in the request
 * @param requestProperty NSDictionary<NSString*, NSString*>* representation of the header fields to be sent in the request
 * @param connectTimeout NSTimeInterval indicating the connection timeout
 * @param readTimeout NSTimeInterval indicating the timeout that will be used to wait for a read to finish after a successful connect
 * @param completion A completion block which takes the ACPHttpConnectionOverride as a parameter
 * In the case of a Network Error, or timeout, the ACPHttpConnection* connection is expected to be nil
 */
- (void) requestUrl: (NSURL*) url httpCommand: (NSString*) command connectPayload: (NSString*) payload requestPropertyDict: (NSDictionary<NSString*, NSString*>*) requestProperty connectTimeout: (NSTimeInterval) connectTimeout readTimeout: (NSTimeInterval) readTimeout completion: (void (^) (ACPHttpConnection* _Nullable  connection)) completion;
@end

/**
 * Interface to set the ACPHttpConnectionPerformer instance being used to override the network stack. Must set the performer here in order to override the network stack.
 */
@interface ACPNetworkServiceOverrider : NSObject
    /**
     * Sets a new ACPHttpConnectionPerformer to override default network activity. If nil, the default network stack will be used.
     * @param performer ACPHttpConnectionPerformer new performer to be used in place of default network stack. If it is nil, default network stack will be used
     */
+ (void) setHttpConnectionPerformer: (id<ACPHttpConnectionPerformer> _Nullable) performer;
@end

NS_ASSUME_NONNULL_END
