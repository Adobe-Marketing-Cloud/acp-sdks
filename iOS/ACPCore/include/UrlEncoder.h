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

#ifndef ADOBEMOBILE_UTIL_URLENCODER_H
#define ADOBEMOBILE_UTIL_URLENCODER_H

#include <iostream>

namespace AdobeMarketingMobile {

    class UrlEncoder {
    public:
        static std::string Encode(const std::string& raw_value);
        static std::string Decode(const std::string& encoded_value);
    private:
        static inline unsigned char HexDecode(char c) {
            if (c >= '0' && c <= '9') {
                return c - '0';
            }

            if (c >= 'a' && c <= 'f') {
                return c - 'a' + 10;
            }

            if (c >= 'A' && c <= 'F') {
                return c - 'A' + 10;
            }

            return 255;
        };
    };

}

#endif /* ADOBEMOBILE_UTIL_URLENCODER_H */
