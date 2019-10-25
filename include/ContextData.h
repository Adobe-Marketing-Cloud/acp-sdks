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
