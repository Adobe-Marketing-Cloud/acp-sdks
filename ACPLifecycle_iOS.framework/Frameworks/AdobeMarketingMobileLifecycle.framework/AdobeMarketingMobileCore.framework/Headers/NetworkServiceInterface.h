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

#ifndef ADOBEMOBILE_PLATFORMSHIM_NETWORKSERVICEINTERFACE_H
#define ADOBEMOBILE_PLATFORMSHIM_NETWORKSERVICEINTERFACE_H

#include <map>
#include <chrono>
#include "ObjectInterface.h"

namespace AdobeMarketingMobile {

    namespace ErrorCodes {
        // Platform shim errors
        constexpr static const char* NETWORK_UNSUPPORTED_HTTP_COMMAND_TYPE =
                    "network.unsupported_http_command_type"; ///< Unsupported http command type
    }

    /**
     * Currently supported command types are GET/POST
     **/
    enum class HttpCommandType : int32_t {
        GET,
        POST
    };

    class HttpConnectionDataInterface : public virtual ObjectInterface {
    public:
        /**
         * Returns application server response as raw data from the connection, if available
         *
         * @param bytes_to_read the number of bytes that need to be read in the buffer
         * @param output_buffer allocated buffer where the response raw data will be copied
         * @return the number of bytes that were written in the read_buffer
         */
        virtual uint64_t GetData(uint64_t bytes_to_read, uint8_t* output_buffer) const = 0;

        /**
         * Returns application server response raw data size
         *
         * @return the size to be read
         */
        virtual uint64_t GetSize() const = 0;
    };

    class HttpConnectionInterface : public virtual ObjectInterface {
    public:
        /**
         * Returns application server response as string from the connection, if available.
         *
         * @return std::string Network response
         */
        virtual std::string GetResponse() const = 0;

        /**
         * Returns application server response as HttpConnectionDataInterface from the connection
         *
         * @return HttpConnectionDataInterface containing the network response
         */
        virtual std::shared_ptr<HttpConnectionDataInterface> GetResponseRawData() const = 0;

        /**
         * Returns the connection attempt responseCode for the connection request.
         * @return int32_t The status code
         */
        virtual int32_t GetResponseCode() const = 0;

        /**
         * Returns a connection attempt response message, if available.
         * @returns std::string The status code string
         */
        virtual std::string GetResponseMessage() const = 0;

        /**
         * Returns a value for the response property key that might have been set when a connection was made to the resource pointed to by the Url.
         *
         * This is protocol specific. For example, HTTP urls could have properties like "last-modified", or "ETag" set.
         *
         * @param response_property_key Any additional property key sent in response when requesting a connection to the url. This will be dependent on the protocol used.
         * @return std::string corresponding to the response property value for the key specified, or empty string, if the key does not exist.
         */
        virtual std::string GetResponsePropertyValue(const std::string& response_property_key) const = 0;

        /**
         * Close this connection
         */
        virtual void Close() const = 0;
    };

    class NetworkServiceInterface : public virtual ObjectInterface {
    public:
        /** Connect to a url
         *
         * @param url The full url for connection
         * @param command Http command. For example "POST", "GET" etc.
         * @param connect_payload Payload to send to the server
         * @param request_property Any additional key value pairs to be used while requesting a
         *                        connection to the url. This will be dependent on the protocol used.
         * @param connect_timeout timeout value in seconds.
         * @param read_timeout The timeout that will be used to wait for a read to finish after a successful connect.
         *
         * @return A HttpConnectionInterface instance, representing a connection attempt.
         */
        virtual std::shared_ptr<HttpConnectionInterface> ConnectUrl(const std::string& url,
                const HttpCommandType& command,
                const std::string& connect_payload,
                const std::map<std::string,
                std::string>& request_property,
                const std::chrono::seconds connect_timeout,
                const std::chrono::seconds read_timeout) = 0;

        /**
         * Async variation of the ConnectUrl api, that will deliver the result through the callback.
         *
         * @param url The full url for connection
         * @param command Http command. For example "POST", "GET" etc.
         * @param connect_payload  Payload to send to the server
         * @param request_property Any additional key value pairs to be used while requesting a
         *                        connection to the url. This will be dependent on the protocol used.
         * @param connect_timeout timeout value in seconds.
         * @param read_timeout The timeout that will be used to wait for a read to finish after a successful connect.
         * @param result_callback Callback that will receive the HttpConnectionInterface instance after the connection has been made.
         *
         */
        virtual void ConnectUrlAsync(const std::string& url,
                                     const HttpCommandType& command,
                                     const std::string& connect_payload,
                                     const std::map<std::string,
                                     std::string>& request_property,
                                     const std::chrono::seconds connect_timeout,
                                     const std::chrono::seconds read_timeout,
                                     const std::function<void(const std::shared_ptr<HttpConnectionInterface>&)>&  result_callback) = 0;

    };
} //namespace
#endif /* ADOBEMOBILE_PLATFORMSHIM_NETWORKSERVICEINTERFACE_H */
