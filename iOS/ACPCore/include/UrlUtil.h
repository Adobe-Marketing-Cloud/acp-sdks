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

#ifndef ADOBEMOBILE_UTIL_URLUTIL_H
#define ADOBEMOBILE_UTIL_URLUTIL_H

namespace AdobeMarketingMobile {
    class UrlUtil {
    public:

        /**
         * Extracts the query parameters as a map from the given deep link query. If one parameter
         * is null or empty or either key/value is empty, that parameter will be skipped
         *
         * @param deep_link_query query string extracted from the deep link/universal link
         */
        static std::map<std::string, std::string> ExtractQueryParameters(const std::string& deep_link_query);
    };
}

#endif /* ADOBEMOBILE_UTIL_URLUTIL_H */

