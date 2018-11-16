//
//  TypeBridge.h
//  Adobe Experience Platform -- iOS Framework
//
//  Copyright 1996-2018. Adobe. All Rights Reserved

#import <AdobeMarketingMobileCore/AdobeMarketingMobileCore.h>
#import <Foundation/Foundation.h>
#import "ACPCore.h"

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
     * Converts ACPMobilePrivacyStatus to MobilePrivacyStatus
     */
    MobilePrivacyStatus ToMobilePrivacyStatus(const ACPMobilePrivacyStatus status);

    /**
     * Converts C++ MobilePrivacyStatus to objective c ACPMobilePrivacyStatus
     */
    ACPMobilePrivacyStatus ToACPMobilePrivacyStatus(const MobilePrivacyStatus status);

    /**
     * ACPMobileLogLevel to LoggingMode
     */
    LoggingMode ToLoggingMode(const ACPMobileLogLevel logLevel);

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
     * Converts cpp VisitorId to Objective c ACPMobileVisitorId
     */
    NSArray* _Nullable ToACPMobileVisitorIdArray(const std::vector<std::shared_ptr<VisitorId>>& visitor_ids);

    /**
     * Converts objective c ACPMobileVisitorAuthenticationState to cpp VisitorIdAuthenticationState
     */
    VisitorIdAuthenticationState ToCppVisitorAuthenticationState(const ACPMobileVisitorAuthenticationState authentication);

    /**
     * Converts cpp VisitorIdAuthenticationState to objective c ACPMobileVisitorAuthenticationState
     */
    ACPMobileVisitorAuthenticationState ToObjCVisitorAuthenticationState(const VisitorIdAuthenticationState authentication);

    /**
     * Converts NSData to Hex NSString.
     */
    NSString* _Nullable ToHexFromEncodedData(NSData* _Nullable data);

}
