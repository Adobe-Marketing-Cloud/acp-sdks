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

#ifndef ADOBEMOBILE_PLATFORMSHIM_URLSERVICEINTERFACE_H
#define ADOBEMOBILE_PLATFORMSHIM_URLSERVICEINTERFACE_H

#include "ObjectInterface.h"

namespace AdobeMarketingMobile {
    /**
     * Interface for parsing URL strings
     */
    class URLServiceInterface : public virtual ObjectInterface {
    public:

        /**
         * Extracts the query parameters as string. Any percent-encoded characters are not unescaped.
         * If given URL does not conform to RFC standard, this method returns empty string.
         * Example: for URL http://www.example.com/index.php?key1=value1&key2=value2, the query string is key1=value1&key2=value2
         *
         * @return URL query
         */
        virtual std::string GetQuery(const std::string& url) const = 0;

        /**
         * Extracts the URL path, unescaped. If given URL does not conform to RFC standard, this method returns empty string.
         * Example: for URL http://www.example.com/index.html, the path is /index.html
         *
         * @return URL path
         */
        virtual std::string GetPath(const std::string& url) const = 0;

        /**
         * Extracts the scheme of given URL. If given URL is invalid, it returns empty string.
         * Example: for URL http://www.example.com/index.html, the scheme is http
         *
         * @return URL scheme
         */
        virtual std::string GetScheme(const std::string& url) const = 0;

        /**
         * Extracts the host of given URL. If given URL is invalid, it returns empty string.
         * Example: for URL http://www.example.com/index.html, the host is www.example.com
         *
         * @return URL host
         */
        virtual std::string GetHost(const std::string& url) const = 0;
    };

} // namespace
#endif /* ADOBEMOBILE_PLATFORMSHIM_URLSERVICEINTERFACE_H */
