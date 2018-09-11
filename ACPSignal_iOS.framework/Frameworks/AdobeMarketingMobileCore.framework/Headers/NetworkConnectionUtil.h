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

#ifndef ADOBEMOBILE_UTIL_NETWORKCONNECTIONUTIL_H_
#define ADOBEMOBILE_UTIL_NETWORKCONNECTIONUTIL_H_

#include <locale>
#include <map>
#include <vector>
#include "HttpConnectionConstants.h"
#include "Object.h"

namespace AdobeMarketingMobile {
    class NetworkConnectionUtil : public Object {
    public:
        /**
         * Searches through RECOVERABLE_NETWORK_ERROR_CODES to find the given error_code
         *
         * @param error_code error code to check for recoverability
         * @returns true if error_code is a recoverable network error
         */
        static bool IsRecoverableNetworkError(int32_t error_code);

        /**
         * Returns the default headers for connection: Accept-Language(locale), Content-Type, User-Agent
         * @param locale active locale from platform
         * @param content_type the custom content type string
         * @return map with the specified keys and values
         */
        static std::map<std::string, std::string> GetHeaders(const std::string& locale,
                const std::string& content_type = "");
        /**
         * Get the name of the given locale in a string format suitable for HTTP's Accept-Language header.
         * The returned format is <language>-<region> where <language> is two or three lowercase characters and
         * <region> is two uppercase characters.
         *
         * Reference: https://www.w3.org/International/articles/language-tags/
         *
         * @param locale the active locale object
         * @return Locale as string
         */
        static std::string GetLocaleString(const std::locale& locale);

    protected:

        /**
         * Get the name of the given locale in a string format suitable for HTTP's Accept-Language header.
         * The returned format is <language>-<region> where <language> is two or three lowercase characters and
         * <region> is two uppercase characters.
         *
         * Reference: https://www.w3.org/International/articles/language-tags/
         *
         * @param locale as a string object
         * @return Locale as string
         */
        static std::string GetLocaleString(const std::string& locale);

    private:
        static const std::vector<int32_t> RECOVERABLE_NETWORK_ERROR_CODES;
    };
}
#endif /* ADOBEMOBILE_UTIL_NETWORKCONNECTIONUTIL_H_ */
