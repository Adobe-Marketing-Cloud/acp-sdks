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
