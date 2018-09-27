/****************************************************************************
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
 ****************************************************************************/

#ifndef ADOBEMOBILE_UTIL_URLBUILDER_H
#define ADOBEMOBILE_UTIL_URLBUILDER_H

#include <string>
#include <map>

namespace AdobeMarketingMobile {

    class UrlBuilder {

    public:
        enum class EncodeType : int32_t {
            NONE = 1,
            ENCODE
        };

        /**
         * constructor
         */
        UrlBuilder();

        UrlBuilder(const UrlBuilder&) = delete;

        UrlBuilder& operator=(const UrlBuilder&) = delete;

        UrlBuilder(UrlBuilder&&) = delete;

        UrlBuilder&& operator=(UrlBuilder&&) = delete;

        /**
         * set whether SSL is enabled
         * @param ssl_enabled the boolean flag to indicated whether SSL is enabled
         * @return this
         */
        UrlBuilder& EnableSsl(const bool ssl_enabled);

        /**
         * set the host after converting host name to lowercase string.
         * @param host host name
         * @return this
         */
        UrlBuilder& SetHost(const std::string& host);

        /**
         * add path to the url, should not include '/' in the string
         * @param path path string without '/'
         * @return this
         */
        UrlBuilder& AddPath(const std::string& path);

        /**
         * add multiple query parameters
         * @param query_parameters the map containing query parameters
         * @return this
         */
        UrlBuilder& AddQueryParameters(const std::map<std::string, std::string>& query_parameters);

        /**
         * add one query parameter with key/value pair, both key and value will be encoded
         * @param key the key of the query parameter
         * @param value the value of the query parameter
         * @return this
         */
        UrlBuilder& AddQueryParameter(const std::string& key, const std::string& value);

        /**
         * add a whole string as a query in the url, the string will be encoded
         * @param new_query the query string to be added to the url
         * @return this
         */
        UrlBuilder& AddQuery(const std::string& new_query);

        /**
         * add a whole string as a query in the url
         * @param new_query the query string to be added to the url
         * @param encode_type encode type to be used to encode the query
         * @return this
         */
        UrlBuilder& AddQuery(const std::string& new_query, const EncodeType encode_type);

        /**
         * build the url string based on all the data provided before
         * @return the url string
         */
        std::string Build();

    private:
        bool ssl_enabled_ = false;
        std::string path_;
        std::string host_;
        std::string query_;

        std::string url_;
        bool did_build_;

        void ThrowIfAlreadyBuilt();

    };

}

#endif /* ADOBEMOBILE_UTIL_URLBUILDER_H */
