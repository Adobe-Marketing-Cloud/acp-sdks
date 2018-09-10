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
 **************************************************************************/

#ifndef ADOBEMOBILE_TARGET_TARGETREQUESTBUILDER_H
#define ADOBEMOBILE_TARGET_TARGETREQUESTBUILDER_H

#include <AdobeMarketingMobileTarget/AdobeMarketingMobileTarget.h>
#include <vector>
#include <map>
#include <chrono>
#include <string>

namespace AdobeMarketingMobile {
    class TargetObject;
    class TargetPrefetch;
    class TargetPreviewManager;
    class VisitorId;

    /**
     * This class can be used to create the json body for the target requests.
     */
    class TargetRequestBuilder : public Object {

    public:
        explicit TargetRequestBuilder(const std::shared_ptr<JsonUtilityServiceInterface>& json_utility_service,
                                      const std::shared_ptr<TargetPreviewManager>& preview_manager);

        /**
         * Sets the parameters provided through shared state by the identity module
         */
        virtual void SetIdentityParameters(const std::string& marketing_cloud_id,
                                           const std::string& blob, const std::string& location,
                                           const std::vector<std::shared_ptr<VisitorId>>& customer_ids);

        /**
         * Sets the parameters provided through shared state by the audience module
         */
        virtual void SetAudienceParameters(const std::string& dpuuid, const std::string& dpid, const std::string& uuid);

        /**
         * Sets the parameters provided through shared state by the config module
         */
        virtual void SetConfigParameters(int64_t environment_id);

        /**
        * Sets the parameters provided through shared state by the lifecycle module
        */
        virtual void SetLifecycleParameters(const std::map<std::string, std::string>& lifecycle_data);

        /**
         * Sets the available internal parameters
         */
        virtual void SetTargetInternalParameters(const std::string& client_code, const std::string& tnt_id,
                const std::string& third_party_id);


        /**
         * Creates the target request json object that we have to send to target APIs
         *
         * @param prefetch_array the array of TargetPrefetch objects with mboxes that we want to prefetch
         * @param batch_requests_array the array of TargetRequest objects with mboxes that we want to load
         * @param profile_parameters parameters provided by the customer
         * @param notifications viewed mboxes that we cached
         * @return the pre-built json object for prefetch
         */
        virtual std::shared_ptr<JsonObject> GetRequestPayload(
                    const std::vector<std::shared_ptr<TargetPrefetch>>& prefetch_array,
                    const std::vector<std::shared_ptr<TargetRequest>>& batch_requests_array,
                    const std::map<std::string, std::string>& profile_parameters,
                    const std::vector<std::shared_ptr<JsonObject>>& notifications);

        /**
         * Creates the visited mbox json object based on the cached mbox json node. It will contain
         * the following params: mbox, parameters, order, product, eventTokens and timestamp. Some of them
         * might be missing if they are not in the cached mboxes.
         *
         * @param cached_mbox_json mbox node from the prefetch cache
         * @return mbox node for the notification
         */
        virtual std::shared_ptr<JsonObject> GetNotificationsJsonObject(const std::shared_ptr<JsonObject>& cached_mbox_json);

        /**
         * Creates a json array with the visitor ids list. Each of the json objects inside of this will
         * contain id, integration code and authentication state.
         */
        std::shared_ptr<JsonArray> GetCustomerIds();

        /**
         * Creates a json array of all the requested mboxes. The mboxes will be have an auto-incremental index
         *
         * @see CreateMboxJsonObject(const std::shared_ptr<TargetObject>& target_object, const long index)
         * @param batch_requests_array request objects coming from the public API
         */
        std::shared_ptr<JsonArray> GetRequestedMboxJson(
                    const std::vector<std::shared_ptr<TargetRequest>>& batch_requests_array);

        /**
         * Creates a json array of all the prefetch mboxes. The mboxes will be have an auto-incremental index
         *
         * @see CreateMboxJsonObject(const std::shared_ptr<TargetObject>& target_object, const long index)
         * @param prefetch_array prefetch objects coming from the public API
         */
        std::shared_ptr<JsonArray> GetPrefetchMboxes(
                    const std::vector<std::shared_ptr<TargetPrefetch>>& prefetch_array);

        /**
         * Creates a json node with the provided target request. This json will contain the mbox name, mbox index,
         * order parameters, product parameters, mbox parameters if they are present. This node will be added in
         * the mboxes array in target network requests.
         */
        std::shared_ptr<JsonObject> CreateMboxJsonObject(
                    const std::shared_ptr<TargetObject>& target_object, const int32_t index);

        /**
         * Creates the mbox parameters json object with the provided data and the internal target parameters
         */
        std::shared_ptr<JsonObject> GetMboxParameters(
                    const std::map<std::string, std::shared_ptr<Variant>>& mbox_params);

        /**
         * Creates the order parameters json object with the provided data
         */
        std::shared_ptr<JsonObject> GetOrderParameters(
                    const std::map<std::string, std::shared_ptr<Variant>>& order_params);

        /**
         * Creates the product parameters json object with the provided data
         */
        std::shared_ptr<JsonObject> GetProductParameters(const std::map<std::string, std::shared_ptr<Variant>>& product_params);

        /**
         * This function adds target preview parameters to the current target parameter JsonObject passed in.
         *
         * @param parameters_json The JsonObject containing the exiting target parameters.
         * @return An instance with the target preview parameters added, if they exist.
         */
        std::shared_ptr<JsonObject> AddPreviewParameters(const std::shared_ptr<JsonObject>& parameters_json);

    private:
        /**
         * @private
         * Returns a JsonObject with all parameters at default level; these ones include:
         * client code, audience parameters, identity parameters, target ids
         */
        std::shared_ptr<JsonObject> GetDefaultJsonObject();

        /**
         * JsonUtilityService - required for this builder to work
         */
        std::shared_ptr<JsonUtilityServiceInterface> json_utility_service_;

        /**
         * The target preview manager required to get the preview qa parameters
         */
        std::shared_ptr<TargetPreviewManager> preview_manager_;

        /**
         * Target properties
         */
        std::string client_code_;
        std::string third_party_id_;
        std::string tnt_id_;
        int64_t environment_id_;

        /**
         * Identity properties
         */
        std::string visitor_marketing_cloud_id_;
        std::string visitor_blob_;
        std::string visitor_location_hint_;
        std::vector<std::shared_ptr<VisitorId>> visitor_customer_ids_;

        /**
         * Lifecycle context data
         */
        std::map<std::string, std::string> lifecycle_data_;

        /**
         * Audience manager properties
         */
        std::string audience_dpuuid_;
        std::string audience_dpid_;
        std::string audience_uuid_;
    };
}

#endif /* ADOBEMOBILE_TARGET_TARGETREQUESTBUILDER_H */
