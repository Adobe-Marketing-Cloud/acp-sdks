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

#ifndef ADOBEMOBILE_UTIL_NETWORKCONNECTIONUTIL_H_
#define ADOBEMOBILE_UTIL_NETWORKCONNECTIONUTIL_H_

#include <locale>
#include <map>
#include <vector>
#include "HttpConnectionConstants.h"
#include "Common.h"
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
        ADOBE_DEPRECATED(static std::string GetLocaleString(const std::locale& locale));

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
