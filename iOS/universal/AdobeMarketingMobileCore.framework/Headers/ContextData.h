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

#ifndef ADOBEMOBILE_UTIL_CONTEXTDATA_H_
#define ADOBEMOBILE_UTIL_CONTEXTDATA_H_

#include <iostream>
#include <map>
#include <vector>

namespace AdobeMarketingMobile {

    class ContextData {

    public:
        static std::map<std::string, std::string> DecodeContextData(const std::string& context_data_string);
        static std::string EncodeContextData(const std::map<std::string, std::string>& cdata);
        static std::string CleanKey(const std::string& key);
        static std::map<std::string, std::string> CleanDictionaryKeys(const std::map<std::string, std::string>& raw_dictionary);

    private:
        std::map<std::string, ContextData> sub_items_;
        std::string value_;

        static std::vector<std::string> Split(const std::string& str, const char delim);
        static void EncodeValueIntoMap(const std::string& value, std::map<std::string, ContextData>& destination_map,
                                       const std::vector<std::string>& keys, size_t index = 0);
        static std::string SerializeToURLFormat(std::map<std::string, ContextData>& encoded_data);
        static std::string Flatten(const std::vector<std::string>& path, const std::string& end = "");
    };
}

#endif
