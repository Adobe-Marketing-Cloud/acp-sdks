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

#ifndef ADOBEMOBILE_UTIL_HTTPCONNECTIONCONSTANTS_H
#define ADOBEMOBILE_UTIL_HTTPCONNECTIONCONSTANTS_H

#include <cstdint>
#include <string>

namespace AdobeMarketingMobile {

    class HttpConnectionConstants {

    public:
        /**
         * http status code 200: ok
         */
        static const int32_t HTTP_OK;

        /**
         * http status code 404: not found
         */
        static const int32_t HTTP_NOT_FOUND;

        /**
         * http status code 408: request timeout.
         */
        static const int32_t HTTP_CLIENT_TIMEOUT;

        /**
         * http status code 416: range not satisfiable.
         */
        static const int32_t HTTP_REQUESTED_RANGE_NOT_SATISFIABLE;

        /**
         * http status code 504: gateway timeout.
         */
        static const int32_t HTTP_GATEWAY_TIMEOUT;

        /**
         * http status code 503: service unavailable.
         */
        static const int32_t HTTP_UNAVAILABLE;


    private:
        HttpConnectionConstants() = delete;

    };

    class HttpConnectionHeaderConstants {

    public:
        /**
         * Content-Type header is used to indicate the media type of the resource.
         */
        static const std::string HTTP_HEADER_KEY_CONTENT_TYPE;

        /**
         *  HTTP header advertises which languages the client is able to understand, and which locale variant is preferred.
         */
        static const std::string HTTP_HEADER_KEY_ACCEPT_LANGUAGE;

        /**
         * The Accept request HTTP header advertises which content types, expressed as MIME types, the client is able
         * understand.
         */
        static const std::string HTTP_HEADER_KEY_ACCEPT;

        /**
         * The MIME media type for JSON text. The default encoding is UTF-8
         */
        static const std::string HTTP_HEADER_CONTENT_TYPE_JSON_APPLICATION;

        /**
         * Headers for HTTP POST request. Here the body of the HTTP message sent to the server is essentially one giant
         * query string -- name/value pairs are separated by the ampersand (&), and names are separated from values by the
         * equals symbol (=)
         */
        static const std::string HTTP_HEADER_CONTENT_TYPE_WWW_FORM_URLENCODED;

        /**
         * Indicates you would only get HTML as a valid responses
         */
        static const std::string HTTP_HEADER_ACCEPT_TEXT_HTML;


    private:
        HttpConnectionHeaderConstants() = delete;
    };

}

#endif /* ADOBEMOBILE_UTIL_HTTPCONNECTIONCONSTANTS_H */
