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
 **************************************************************************/

#ifndef ADOBEMOBILE_ACQUISITION_ACQUISITIONHELPER_H
#define ADOBEMOBILE_ACQUISITION_ACQUISITIONHELPER_H

#include <map>
#include <string>

namespace AdobeMarketingMobile {
    class URLServiceInterface;
    /**
     * @class AcquisitionHelper
     *
     * This class has static methods that are meant to help assist with Acquisition related business logic
     */
    class AcquisitionHelper {

    public:
        /**
         * Takes a of key-value pairs and a prefix and adds that prefix foreach key. If one key is already prefixed with the
         * provided key, then it will not add a new prefix for that specific key
         * e.g. Input: {"key1":"value1", "key2":"value2"}, prefix="pre" Output: {"prekey1":"value1", "prekey2":"value2"}
         * @param config map to be modified
         * @param prefix prefix string
         * @return the initial map with prefixed keys
         */
        static std::map<std::string, std::string> AddPrefixForEachKey(const std::map<std::string, std::string>& config,
                const std::string& prefix);

        /**
         * This method receives a deep link URL as string and returns a {@code Map<String, String>} with the parsed query parameters.
         * e.g.1: input: {@literal "http://someHost.xyz/somePath?key1=value1&key2=value2&a.deeplink.id=552"}
         * output: {@literal {"key1": "value1", "key2": "value2", "a.deeplink.id" : "552"}}
         * e.g.2: input: {@literal "http://someHost.xyz/somePath?key1=value1&key2=&a.deeplink.id=552"}
         * output: {@literal {"key1": "value1", "a.deeplink.id" : "552"}}
         * @param deepLink query parameters as string
         * @param url_service URLService instance
         * @return a Map of all parsable query parameters or empty map, if input is empty string or doesn't contain the key "a.deeplink.id"
         */
        static std::map<std::string, std::string> GetAdobeDeepLinkQueryParameters(const std::string& deep_link,
                const std::shared_ptr<URLServiceInterface>& url_service);

    private:
        AcquisitionHelper() = delete;
    };
}

#endif /* ADOBEMOBILE_ACQUISITION_ACQUISITIONHELPER_H */
