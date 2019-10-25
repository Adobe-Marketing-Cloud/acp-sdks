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
