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
