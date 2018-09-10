/* **************************************************************************
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
 **************************************************************************/

#ifndef ADOBEMOBILE_TARGET_TARGETRESPONSEPARSER_H
#define ADOBEMOBILE_TARGET_TARGETRESPONSEPARSER_H

#include <AdobeMarketingMobileCore/AdobeMarketingMobileCore.h>
#include <vector>
#include <map>
#include <string>

namespace AdobeMarketingMobile {
    /**
     * This class can be used to parse the response from the target server.
     */
    class TargetResponseParser : public Object {

    public:
        explicit TargetResponseParser(const std::shared_ptr<JsonUtilityServiceInterface>& json_utility_service);

        /**
         * Verify if the network response is valid, and parse it to a json object if there is no error
         *
         * @param connection the network connnection object returned from server
         * @return the json object if the response is valid
         */
        virtual std::shared_ptr<JsonObject> ParseResponseToJson(const std::shared_ptr<HttpConnectionInterface>& connection);

        /**
         * Extracts the prefetched mboxes from the server response and returns them as a Map, where the mbox name is the key
         * and the json object returned is the value
         *
         * @param json the json response
         * @return all the prefetched mboxes
         */
        virtual std::map<std::string, std::shared_ptr<JsonObject>> ExtractPrefetchedMboxes(const std::shared_ptr<JsonObject>&
                json);

        /**
         * Extracts the batched mboxes from the server response and returns them as a Map, where the mbox name is the key
         * and the json object returned is the value
         *
         * @param json the json response
         * @return all the batched mboxes
         */
        virtual std::map<std::string, std::shared_ptr<JsonObject>> ExtractBatchedMBoxes(const std::shared_ptr<JsonObject>&
                json);

        /**
         * Get the tnt id from the server response
         *
         * @param json the json response
         * @return new tnt id
         */
        virtual std::string GetTntId(const std::shared_ptr<JsonObject>& json);

        /**
         * Get the edge host from the server response
         *
         * @param json the json response
         * @return new edge host
         */
        virtual std::string GetEdgeHost(const std::shared_ptr<JsonObject>& json);

        /**
         * Grabs the a4t payload from the target response and convert the keys to correct format
         *
         * @param json the json response
         * @return a4t payload
         */
        virtual std::map<std::string, std::string> GetAnalyticsForTargetPayload(const std::shared_ptr<JsonObject>& json);

        /**
         * Iterate the mboxes json response to check if there is any error, if so return the map which has mbox name as key and error type as string
         * if there is any error
         *
         * @param mboxes the mboxes json response received from server
         * @return the map which has mbox name as key and error type as string, if there is any error
         */
        virtual std::map<std::string, std::string> GetErrorTypesForMboxes(const
                std::map<std::string, std::shared_ptr<JsonObject>>& mboxes);


        /**
         * Check if the json response contains notificationErrors, if so return the list of the notifications that should retry.
         * Currently we only resend the notification if the error type is 'time_out'.
         *
         * @param json the json response
         * @return the vector of notifications that need to retry
         */
        virtual std::vector<std::shared_ptr<JsonObject>> GetNotificationsNeedRetry(const std::shared_ptr<JsonObject>& json);

    private:
        std::shared_ptr<JsonUtilityServiceInterface> json_utility_service_;

        /**
         * @Private
         * Extracts the mboxes from the server response from a certain key, used by methods ExtractPrefetchedMboxes and ExtractBatchedMBoxes
         *
         * @param json the json response
         * @param key_name under which key name should the mboxes be extracted from
         * @return all the mboxes
         */
        virtual std::map<std::string, std::shared_ptr<JsonObject>> GetMboxesFromKey(const std::shared_ptr<JsonObject>& json,
                const std::string key_name);
    };
}

#endif /* ADOBEMOBILE_TARGET_TARGETRESPONSEPARSER_H */

