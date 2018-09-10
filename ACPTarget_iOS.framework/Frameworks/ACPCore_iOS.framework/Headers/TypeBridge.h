/***************************************************************************
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
 *
 **************************************************************************/

#import <AdobeMarketingMobileCore/AdobeMarketingMobileCore.h>
#import <Foundation/Foundation.h>
#import "ADBMarketingMobileCore.h"

namespace AdobeMarketingMobile {

#pragma mark - std::map, NSDictionary
    /**
     * Returns a copy of the provided dictionary, removing entries
     * for which either key or value are not of type NSString
     *
     * @param dictionary NSDictionary to clean
     * @param removed_entries contains removed entries from data
     */
    NSDictionary<NSString*, NSString*>* _Nonnull CleanDictionary(NSDictionary<NSString*, NSString*>* _Nonnull dictionary,
            NSDictionary* _Nonnull* _Nullable removed_entries);

    /**
     *  Converts NSDictionary to std::map<std::string, std::string>
     */
    std::map<std::string, std::string> ToStringMap(NSDictionary<NSString*, NSString*>* _Nonnull dictionary);

    /**
     * Converts NSDictionary to map<std::string, std::shared_ptr<Variant>>
     */
    std::map<std::string, std::shared_ptr<Variant>> ToVariantMap(NSDictionary* _Nullable dictionary);

    /**
     * Converts std::map to NSDictionary
     */
    NSDictionary* _Nonnull ToNSDictionary(const std::map<std::string, std::string>& map);

    /**
     * Converts map<string, Variant> to NSDictionary
     */
    NSDictionary* _Nonnull ToNSDictionary(const std::map<std::string, std::shared_ptr<Variant>>& map);

#pragma mark - std::vector, NSArray
    /**
     * Returns a copy of the provided array, removing elements
     * for which the value is not of type NSString
     *
     * @param array NSArray to clean
     * @param removed_elements contains removed elements from array
     */
    NSArray<NSString*>* _Nonnull CleanArray(NSArray<NSString*>* _Nonnull array,
                                            NSArray* _Nonnull* _Nullable removed_elements);

    /**
     * vector<string> to NSArray
     */
    NSArray* _Nonnull ToNSArray(const std::vector<std::string>& str_vec);

    /**
     * vector<Variant> to NSArray
     */
    NSArray* _Nonnull ToNSArray(const std::vector<std::shared_ptr<Variant>>& variant_vec);

    /**
     * Converts NSArray to vector<Variant>
     */
    std::vector<std::shared_ptr<Variant>> ToVariantVector(NSArray* _Nullable array);

    /**
     * Converts NSArray<NSString *> * to std::vector<std::string>
     */
    std::vector<std::string> ToStringVector(NSArray<NSString*>* _Nonnull array);

#pragma mark - std::string, NSString
    /**
     * Converts std::string to NSString
     */
    NSString* _Nullable ToNSString(const std::string& str);

    /**
     * Converts NSString to std::string
     */
    std::string ToCppString(NSString* _Nullable str);

#pragma mark - C++ primitives, NSNumber
    /**
     * NSNumber to double
     */
    double ToDouble(NSNumber* _Nonnull num);

    /**
     * NSNumber to float
     */
    float ToFloat(NSNumber* _Nonnull num);

    /**
     * NSNumber to bool
     */
    bool ToBool(NSNumber* _Nonnull num);

    /**
     * Converts int32_t to NSNumber
     */
    NSNumber* _Nonnull ToNSNumber(const int32_t num);

    /**
     * Converts NSNumber to int32_t
     */
    int32_t ToInt32(NSNumber* _Nonnull num);

    /**
     * double to NSNumber
     */
    NSNumber* _Nonnull ToNSNumber(const double num);

    /**
     * Converts int64_t to NSNumber
     */
    NSNumber* _Nonnull ToNSNumber(const int64_t num);

    /**
     * Converts bool to NSNumber
     */
    NSNumber* _Nonnull ToNSNumber(const bool val);

    /**
     * Converts float to NSNumber
     */
    NSNumber* _Nonnull ToNSNumber(const float num);

    /**
     * Converts NSNumber to int64_t
     */
    int64_t ToInt64(NSNumber* _Nonnull num);

    /**
     * Converts ADBMobilePrivacyStatus to MobilePrivacyStatus
     */
    MobilePrivacyStatus ToMobilePrivacyStatus(const ADBMobilePrivacyStatus status);

    /**
     * Converts C++ MobilePrivacyStatus to objective c ADBMobilePrivacyStatus
     */
    ADBMobilePrivacyStatus ToADBMobilePrivacyStatus(const MobilePrivacyStatus status);

    /**
     * ADBMobileLogLevel to LoggingMode
     */
    LoggingMode ToLoggingMode(const ADBMobileLogLevel logLevel);

    /**
     * Converts Objective-C type to a Variant
     */
    std::shared_ptr<Variant> ObjCToVariant(id _Nullable value);

    /**
     * Converts Variant to an Objective-C type
     */
    id _Nullable VariantToObjC(const std::shared_ptr<Variant>& variant);

    /**
     * Encode raw data as hex and return encoding as std::string with null termination
     */
    std::string BinToHex(const unsigned char* _Nullable bin, size_t size);

    /**
     * Decode hex encoded data and return raw data as std::vector
     */
    std::vector<unsigned char> HexToBin(const char* _Nullable hex, size_t size);

    /**
     * std::chrono::seconds to NSTimeInterval
     */
    NSTimeInterval ToNSTimeInterval(std::chrono::seconds ts);

    /**
     * Converts NSData to Hex NSString.
     */
    NSString* _Nullable ToHexFromEncodedData(NSData* _Nullable data);

}
