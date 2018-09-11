/* **************************************************************************
 *
 * ADOBE CONFIDENTIAL
 * ___________________
 *
 * Copyright 2018 Adobe Systems Incorporated
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
 **************************************************************************/

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
