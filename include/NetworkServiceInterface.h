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

        /**
         * Frees resources used by this, waiting up to `max_wait_duration` for the operation to complete.
         *
         * Calling Dispose() triggers clean up to occur immediately for synchronous session or asynchronous sessions
         *
         * After triggering the asynchronous disposal, this call will block for up to `max_wait_duration` for the
         * operation to complete.
         *
         * @param max_wait_duration - the maximum duration to block this call while waiting for cleanup to complete.
         *                            A `0` time indicates that we will return immediately.
         *
         * @return true if this was fully disposed
         */
        virtual bool Dispose(std::chrono::milliseconds max_wait_duration) = 0;


    };
} //namespace
#endif /* ADOBEMOBILE_PLATFORMSHIM_NETWORKSERVICEINTERFACE_H */
