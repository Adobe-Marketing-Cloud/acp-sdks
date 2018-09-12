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

#ifndef ADOBEMOBILE_ACQUISITION_AcquisitionFingerprinter_H
#define ADOBEMOBILE_ACQUISITION_AcquisitionFingerprinter_H

#include <map>
#include <set>
#include <AdobeMarketingMobileCore/Common.h>
#include <AdobeMarketingMobileCore/Object.h>

namespace AdobeMarketingMobile {
    class JsonObject;
    class JsonUtilityServiceInterface;

    /**
     * @class AcquisitionFingerprinter
     *
     * This class is meant to handle all interactions for fingerprinter
     *
     * It is responsible for:
     * - Generating requests for the fingerprinter
     * - Handling responses from the fingerprinter via the JsonUtilityService
     *
     */
    class AcquisitionFingerprinter : public Object {
        friend class MockAcquisitionFingerprinter; // for testing

    public:
        explicit AcquisitionFingerprinter(const std::shared_ptr<JsonUtilityServiceInterface>& json_service);

        /**
         * generate the end acquisition request url following the format
         * {@literal https://server/v3/appid/end?&a_cid=adid}
         *
         * @param server   the server endpoint used for acquisition
         * @param app_id    the unique id given to represent this application
         * @param adid     optional string representation of advertising identifier for this device/app combination
         * @param additional_parameters    additional parameters need to be appended in the request url
         *
         * @return end acquisition request url
         */
        ADOBE_VIRTUAL_FOR_TESTS std::string GenerateUrl(const std::string& server,
                const std::string& app_id,
                const std::string& adid,
                const std::map<std::string, std::string>& additional_parameters);

        /**
         * a. adobeData. Data in the field 'adobeData' except "link_deferred", "unique_id" and "deeplinkid".
         * Add the prefix "a.acquisition.custom." to all the entries which do not have it.
         * b. contextData. All the data in "contextData" field.
         * acquisitionData is the combination of adobeData and contextData.
         *
         * @return acquisitionData which is the combination of adobeData and contextData
         */
        ADOBE_VIRTUAL_FOR_TESTS std::map<std::string, std::string> GetAcquisitionData();

        /**
         * the link_deferred value in the adobe data object
         *
         * @return deferred deep link url
         */
        ADOBE_VIRTUAL_FOR_TESTS std::string GetDeepLinkUrl();

        /**
         * a. adobeData. Data in the field 'adobeData' except "link_deferred", "unique_id" and "deeplinkid".
         * Add the prefix "a.acquisition.custom." to all the entries which do not have it.
         * b. referrerData. The data in contextData dictionary with keys "a.referrer.campaign
         * .source/medium/term/content/name/trackingcode"
         * persistData is the combination of adobeData and referrerData.
         *
         * @return persistData which is the combination of adobeData and referrerData
         */
        ADOBE_VIRTUAL_FOR_TESTS std::map<std::string, std::string> GetPersistData();

        /**
         * check if the response is valid
         *
         * @return true if contextData contains a valid string for key a.referrer.campaign.name, otherwise false
         */
        ADOBE_VIRTUAL_FOR_TESTS bool IsResponseValid();

        /**
         * process the server response returned from network service
         *
         * @param server_response the response string
         */
        ADOBE_VIRTUAL_FOR_TESTS void ProcessServerResponse(const std::string& server_response);

    private:
        std::shared_ptr<JsonUtilityServiceInterface> json_service_;
        std::shared_ptr<JsonObject> json_object_;

        static const std::set<std::string> BLACKLISTED_KEYS;  ///< A collection of reserved acquisition string keys
        static const std::set<std::string> REFERRER_CAMPAIGN_KEYS;  ///< A collection of reserved referrer string keys

        /**
         * Takes a map of key-value pairs and removes any that are in the internal list of BLACKLISTED_KEYS
         *
         * @param adobe_data source map of key-value pairs to be filtered
         * @return a new map with all blacklisted keys filtered out
         */
        std::map<std::string, std::string> FilterForBlacklistedKeys(const std::map<std::string, std::string>& adobe_data);

        /**
         * adobeData is the data in the field 'adobeData' except "link_deferred", "unique_id" and "deeplinkid".
         * Add the prefix "a.acquisition.custom." to all the entries which do not have it.
         *
         * @return adobe data
         */
        std::map<std::string, std::string> GetAdobeData();

        /**
         * Extracts context data out of the internal json_object_ and returns to the caller
         *
         * @return a map representing the context data in the internal json_object_
         */
        std::map<std::string, std::string> GetContextData();

        /**
         * referrerData is the data in contextData dictionary with keys "a.referrer.campaign
         * .source/medium/term/content/name/trackingcode"
         *
         * @param context_data the original context data map
         *
         * @return referrer data  which only contains a.referrer.campaign.source.* data
         */
        std::map<std::string, std::string> GetReferrerData(const std::map<std::string, std::string>& context_data);

    };
}

#endif /* ADOBEMOBILE_ACQUISITION_AcquisitionFingerprinter_H */
