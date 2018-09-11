/***************************************************************************
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
 *
 **************************************************************************/

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

