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

#ifndef ADOBEMOBILE_TARGET_TARGET_H
#define ADOBEMOBILE_TARGET_TARGET_H

#include <AdobeMarketingMobileCore/AdobeMarketingMobileCore.h>

namespace AdobeMarketingMobile {
    class TargetRequest;
    class TargetPrefetch;
    class TargetDispatcherResponseContent;
    class TargetDispatcherResponseIdentity;
    class TargetDispatcherAnalyticsRequestContent;
    class TargetRequestBuilder;
    class TargetResponseParser;
    class TargetPreviewManager;

    class Target : public InternalModule {
        friend class TestableTarget; // for testing
    public:
        static const std::string LOG_PREFIX;

        Target();

        /**
         * Request multiple Target mboxes in a single network call.
         *
         * @param request_array an array of TargetRequestObject representing the desired mboxes to load
         * @param profile_parameters a dictionary of key-value pairs used as profile parameters for all prefetch requests
         * @param event the event object
         */
        ADOBE_VIRTUAL_FOR_TESTS void LoadRequests(const std::vector<std::shared_ptr<TargetRequest>>& request_array,
                const std::map<std::string, std::string>& profile_parameters,
                const std::shared_ptr<Event>& event);

        /**
         * Saves the thirdparty to the Target DataStore or remove its key in the dataStore if the thirdparty null
         *
         * @param third_party_id newThirdPartyID to be set
         */
        ADOBE_VIRTUAL_FOR_TESTS void SetThirdPartyId(const std::string& third_party_id);

        /**
         * Prefetch multiple Target mboxes in a single network call. The content will be cached locally
         * and returned immediately if any prefetched mbox is requested though a loadRequest call.
         *
         * @param target_prefetch_array an array of TargetPrefetch objects representing the desired mboxes to prefetch
         * @param profile_parameters a dictionary of key-value pairs used as profile parameters for all prefetch requests
         * @param event the event object
         */
        ADOBE_VIRTUAL_FOR_TESTS void HandlePrefetchContent(const std::vector<std::shared_ptr<TargetPrefetch>>&
                target_prefetch_array,
                const std::map<std::string, std::string>& profile_parameters,
                const std::shared_ptr<Event>& event);

        /**
         * processIdentityRequest is called when the Target module listens to a valid TargetRequestIdentity event.
         * This method dispatches an TargetResponseIdentity event with Target identities in the eventData
         *
         * @param response_pair_id response pairID associated with the target Identity request
         */
        ADOBE_VIRTUAL_FOR_TESTS void ProcessIdentityRequest(const std::string& response_pair_id);

        /**
         * resetIdentity is called when the Target module listens to a valid TargetRequestReset Event.
         * This method dispatches an reset request completion event with the assigned pairID
         *
         * @param response_pair_id response pairID associated with the target Identity request
         */
        ADOBE_VIRTUAL_FOR_TESTS void ResetIdentity(const std::string& response_pair_id);

        /**
         * ClearPrefetchCache is called when the Target module listens to a valid TargetResetIdentity Event.
         * This method clears all the previously prefetched and cached mbox locations
         *
         */
        ADOBE_VIRTUAL_FOR_TESTS void ClearPrefetchCache();

        /**
         * Starts preview mode if the deeplink contains the preview query parameters. It then dispatches a new event
         * to messages to create a custom full screen message for target preview
         *
         * @param event current event used for retrieving the config shared state
         * @param deep_link the deep link extracted from the acquisition OS event
         */
        ADOBE_VIRTUAL_FOR_TESTS void ProcessPreviewDeepLink(const std::shared_ptr<Event>& event,
                const std::string& deep_link);

        /**
         * Sets the preview restart url in the target preview manager.
         * @param deep_link the deep link received from the public API (SetPreviewRestartDeeplink)
         */
        ADOBE_VIRTUAL_FOR_TESTS void SetPreviewRestartDeepLink(const std::string& deep_link);

    protected:

        /**
         * Create a new instance of a Target Module.
         *
         * @param log_prefix an identifier for this moduled used in log messages.
         */
        explicit Target(const std::string& log_prefix);

        /**
         * Called when the EventHub registers this module.
         */
        void OnRegistered() override;

        /**
         * Called when the EventHub unregisters this module.
         */
        void OnUnregistered() override;

        /**
         * Retrieve the unique module name for storing shared state information.
         *
         * @return String containing the container name for shared state for this module (can be empty string)
         **/
        ADOBE_VIRTUAL_FOR_TESTS std::string GetSharedStateName() override;

        /**
         * Internal method to request multiple Target mboxes in a single network call, not depending on EventHub
         *
         * @param request_vector an array of TargetRequestObject representing the desired mboxes to load
         * @param profile_parameters a dictionary of key-value pairs used as profile parameters for all prefetch requests
         * @param config_data shared data from configuration module
         * @param lifecycle_data shared data from lifecycle module
         * @param audience_data shared data from audience module
         * @param identity_data shared data from identity module
         */
        ADOBE_VIRTUAL_FOR_TESTS void BatchRequests(const std::vector<std::shared_ptr<TargetRequest>>& request_vector,
                const std::map<std::string, std::string>& profile_parameters,
                const std::shared_ptr<EventData>& config_data,
                const std::shared_ptr<EventData>& lifecycle_data,
                const std::shared_ptr<EventData>& audience_data,
                const std::shared_ptr<EventData>& identity_data);

        /**
         * Internal method to prefetch multiple Target mboxes in a single network call, not depending on EventHub
         *
         * @param prefetch_array an array of TargetPrefetch objects representing the desired mboxes to prefetch
         * @param profile_parameters a dictionary of key-value pairs used as profile parameters for all prefetch requests
         * @param config_data shared data from configuration module
         * @param lifecycle_data shared data from lifecycle module
         * @param audience_data shared data from audience module
         * @param identity_data shared data from identity module
         * @return prefetch success or not
         */
        ADOBE_VIRTUAL_FOR_TESTS bool PrefetchContent(const std::vector<std::shared_ptr<TargetPrefetch>>& prefetch_array,
                const std::map<std::string, std::string>& profile_parameters,
                const std::shared_ptr<EventData>& config_data,
                const std::shared_ptr<EventData>& lifecycle_data,
                const std::shared_ptr<EventData>& audience_data,
                const std::shared_ptr<EventData>& identity_data);

        /**
         * Internal method to reset target ids, not depending on EventHub
         */
        ADOBE_VIRTUAL_FOR_TESTS void ResetIdentity();

        ADOBE_VIRTUAL_FOR_TESTS void SetupPreviewMode(const std::shared_ptr<Event>& event, const std::string& deep_link);

        std::shared_ptr<TargetDispatcherResponseContent> target_response_content_dispatcher_;
        std::shared_ptr<TargetDispatcherResponseIdentity> target_response_identity_dispatcher_;
        std::shared_ptr<TargetDispatcherAnalyticsRequestContent> analytics_request_content_dispatcher_;
        std::shared_ptr<TargetRequestBuilder> target_request_builder_;
        std::shared_ptr<TargetResponseParser> target_response_parser_;
        std::shared_ptr<TargetPreviewManager> target_preview_manager_;

    private:

        /**
         * Internal method to process the mbox that has already had cached response
         *
         * @param request_vector an array of TargetRequestObject representing the desired mboxes to load
         * @return the rest of the target requests that do not have cached response
         */
        ADOBE_VIRTUAL_FOR_TESTS std::vector<std::shared_ptr<TargetRequest>> ProcessCachedTargetRequest(const
                std::vector<std::shared_ptr<TargetRequest>>& request_vector);

        /**
         * Internal method to send the batch target request to server and return the repsonse
         *
         * @param batch_request_vector the vector of batch request
         * @param prefetch_request_vector  the vector of prefetch request
         * @param profile_parameters a dictionary of key-value pairs used as profile parameters for all prefetch requests
         * @param config_data shared data from configuration module
         * @param lifecycle_data shared data from lifecycle module
         * @param audience_data shared data from audience module
         * @param identity_data shared data from identity module
         * @return the response string
         */
        ADOBE_VIRTUAL_FOR_TESTS std::shared_ptr<HttpConnectionInterface> SendTargetRequest(
                    const std::vector<std::shared_ptr<TargetRequest>>& batch_request_vector,
                    const std::vector<std::shared_ptr<TargetPrefetch>>& prefetch_request_vector,
                    const std::map<std::string, std::string>& profile_parameters,
                    const std::shared_ptr<EventData>& config_data,
                    const std::shared_ptr<EventData>& lifecycle_data,
                    const std::shared_ptr<EventData>& audience_data,
                    const std::shared_ptr<EventData>& identity_data);

        /**
         * Internal method to process the response for batch request
         *
         * @param batch_request_vector the vector of batch request
         * @param connection the network connection object
         */
        ADOBE_VIRTUAL_FOR_TESTS void ProcessTargetRequestResponse(
                    const std::vector<std::shared_ptr<TargetRequest>>& batch_request_vector,
                    std::shared_ptr<HttpConnectionInterface>& connection);

        /**
         * Internal method to prepare for the target request and check if we should make target target network call
         *
         * @param config_data shared data from configuration module
         * @return is everything valid for target request
         */
        ADOBE_VIRTUAL_FOR_TESTS bool PrepareForTargetRequest(const std::shared_ptr<EventData>& config_data);

        /**
         * Internal method to generate the map for internal parameters to be used in Json
         *
         * @return internal parameters to be used in Json
         */
        std::map<std::string, std::string> GetInternalParameters();

        /**
         * Internal method to run the default callback for each of the request in the vector
         *
         * @param request_vector an array of TargetRequestObject
         */
        ADOBE_VIRTUAL_FOR_TESTS void RunDefaultCallbacks(const std::vector<std::shared_ptr<TargetRequest>>& request_vector);

        /**
         * @private
         * Saves the given tntID to local storage
         *
         * @param new_tnt_id tnt id to be saved
         */
        ADOBE_VIRTUAL_FOR_TESTS void SetTntId(const std::string& new_tnt_id);


        /**
         * @private
         * Saves the given third party id to local storage
         *
         * @param third_party_id third party id be saved
         */
        ADOBE_VIRTUAL_FOR_TESTS void SetThirdPartyIdInternal(const std::string& third_party_id);


        /**
         * @private
         * Loads the persisted data from data store
         */
        ADOBE_VIRTUAL_FOR_TESTS void LoadPersistedData();

        /**
         * @private
         * Prepares the URL for making target network call.
         *
         * @return the url for target request
         */
        ADOBE_VIRTUAL_FOR_TESTS std::string GetTargetRequestUrl();

        /**
         * @private
         * tntId is a concatenation of {tntId}.{sessionId}
         * this method compares only the tntId portion of the strings
         *
         * @param old_tnt_id the current tnt id
         * @param new_tnt_id the new tnt id
         */
        ADOBE_VIRTUAL_FOR_TESTS bool TntIdValuesAreEqual(const std::string& old_tnt_id, const std::string& new_tnt_id);

        /**
         * @private
         * Returns the target datastore
         * @return Shared pointer to target DataStore
         */
        ADOBE_VIRTUAL_FOR_TESTS std::shared_ptr<DataStoreInterface> GetDataStore();

        /**
         * @private
         * Verifies if the target module is in preview mode.
         * @return Returns true if preview mode is on, false otherwise
         */
        ADOBE_VIRTUAL_FOR_TESTS bool IsInPreviewMode();

        /**
         * @private
         * Retrieves the unique session identifier. Session ids are used in header for each Target Network call.
         *
         * If not initialized for current session, a new UUID will be generated. This method will return an empty
         * string if the CryptoServiceInterface is not available.
         * @return The session identifier
         */
        std::string GetSessionId();

        /**
         * @private
         * Returns the preview manager instance if already created or creates a new one otherwise
         */
        std::shared_ptr<TargetPreviewManager> GetPreviewManager();

        /**
         * @private
         * Returns the target response parser instance if already created or creates a new one otherwise
         */
        std::shared_ptr<TargetResponseParser> GetResponseParser();

        /**
         * @private
         * Returns the target request builder instance if already created or creates a new one otherwise
         */
        std::shared_ptr<TargetRequestBuilder> GetRequestBuilder();

        std::string client_code_; ///< @private current client code
        std::string tnt_id_; ///< @private tnt id
        std::string third_party_id_; ///< @private third party id
        std::string edge_host_; ///< @private edge host got from response
        std::string session_id_; ///< @private unique session id
        std::map<std::string, std::shared_ptr<JsonObject>> cached_mboxes_; ///< @private cached mxbx/json repsone pairs
        std::vector<std::shared_ptr<JsonObject>> notifications_; ///< @private notification
    };
}

#endif /* ADOBEMOBILE_TARGET_TARGET_H */
