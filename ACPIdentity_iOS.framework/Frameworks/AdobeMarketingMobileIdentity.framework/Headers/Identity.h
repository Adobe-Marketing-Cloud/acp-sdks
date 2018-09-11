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

#ifndef ADOBEMOBILE_IDENTITY_IDENTITY_H
#define ADOBEMOBILE_IDENTITY_IDENTITY_H

#include <vector>
#include <AdobeMarketingMobileCore/AdobeMarketingMobileCore.h>

namespace AdobeMarketingMobile {
    class ConfigurationSharedStateIdentity;
    class DataStoreInterface;
    class Event;
    class IdentityDispatcherAnalyticsRequestContent;
    class IdentityDispatcherIdentityResponseIdentity;
    class IdentityDispatcherConfigurationRequestContent;
    class IdentityObject;
    class VisitorId;
    enum class VisitorIdAuthenticationState : int32_t;
    enum class MobilePrivacyStatus : int32_t;

    class IdentityHitDatabase;

    class Identity: public InternalModule {
        friend class TestableIdentity;
    public:
        static const std::string LOG_PREFIX;
        static const std::string IDENTITY_PROPERTIES_DATA_STORE_NAME;

        /**
         * Create a new instance of Identity Module.
         */
        Identity();

        /**
         * Processes stored events in the queue as long there's a corresponding
         * configuration state available.
         */
        virtual void ProcessEventQueue();

        /**
         * Handler for all the identity request identity events
         *
         * @param event a identity request identity event.
         */
        virtual void HandleIdentityRequest(const std::shared_ptr<Event>& event);

        /**
         * To call Process on queued events in a task thread.
         *
         */
        virtual void TryProcessEventQueue();

        /**
         * Handler for Configuration response content events.
         * Checks for and sets the MobilePrivacyStatus used by this module.
         * Checks for and sets the Experience Cloud Org ID used by this module.
         *
         * @param event the EventType::CONFIGURATION EventSource::RESPONSE_CONTENT Event object
         */
        void HandleConfigurationResponse(const std::shared_ptr<Event>& event);

        virtual void Bootup(const std::shared_ptr<Event>& boot_event);

        virtual void NetworkResponseLoaded(const std::shared_ptr<IdentityObject>& result, const std::string& pair_id,
                                           const std::int32_t state_version);

        virtual std::map<std::string, std::string> ExtractIdentifiers(const std::shared_ptr<EventData>& event_data,
                const std::shared_ptr<ConfigurationSharedStateIdentity>& config_shared_identity);

        virtual std::string GenerateURLEncodedValuesCustomerIdString(const std::vector<std::shared_ptr<VisitorId>>&
                visitor_ids);
        virtual std::vector<std::shared_ptr<VisitorId>> MergeCustomerIds(const std::vector<std::shared_ptr<VisitorId>>&
                new_visitor_ids);


        ADOBE_VIRTUAL_FOR_TESTS std::string GetSharedStateName() override;

    protected:
        std::string mid_;
        std::string location_hint_;
        std::string blob_;
        std::string advertising_identifier_;
        std::string push_identifier_;
        std::vector<std::shared_ptr<VisitorId>> customer_ids_;
        std::string vid_;
        std::chrono::milliseconds ttl_;
        std::chrono::milliseconds last_sync_;

        MobilePrivacyStatus privacy_status_;
        std::shared_ptr<ConfigurationSharedStateIdentity> latest_valid_config_;
        std::shared_ptr<IdentityDispatcherAnalyticsRequestContent> analytics_dispatcher_;
        std::shared_ptr<IdentityDispatcherConfigurationRequestContent> config_dispatcher_;
        std::shared_ptr<IdentityDispatcherIdentityResponseIdentity> dispatcher_;
        std::deque<std::shared_ptr<Event>> events_queue_;

        /**
         * Create a new instance of Identity Module.
         *
         * @param log_prefix an identifier for this module used in log messages.
         */
        explicit Identity(const std::string& log_prefix);

        /**
         * Processes individual events.
         *
         * @param event a identity request identity event.
         * @param config_shared_state config shared state corresponding to the event to be processed.
         * @return false if the event was not processed.
         */
        ADOBE_VIRTUAL_FOR_TESTS bool ProcessEvent(const std::shared_ptr<Event>& event,
                const std::shared_ptr<ConfigurationSharedStateIdentity>& config_shared_state);

        /**
         * Appends identity payload to base url, present in the event data of the event param.
         *
         * @param event event containing base url in its event data
         * @param config_shared_state config shared state corresponding to the event to be processed.
         */
        virtual void HandleAppendUrl(const std::shared_ptr<Event>& event,
                                     const std::shared_ptr<ConfigurationSharedStateIdentity>& config_shared_state);

        /**
         * Makes sync identifiers network call and update identity state.
         *
         * @param event event corresponding to sync identifiers call.
         * @param config_shared_state config shared state corresponding to the event to be processed.
         * @return false if a valid config (one with org id) is not available to process sync call.
         */
        ADOBE_VIRTUAL_FOR_TESTS bool HandleSyncIdentifiers(const std::shared_ptr<Event>& event,
                const std::shared_ptr<ConfigurationSharedStateIdentity>& config_shared_state);

        /**
         * Appends identity payload to base url, present in the event data of the event param.
         *
         * @param base_url url to which the identity payload needs to be appended to.
         * @param pair_id pair id of the incoming event which contains the base url
         * @param config_shared_state config shared state corresponding to the event to be processed.
         * @param analytics_shared_state analytics shared state corresponding to the event to be processed.
         */
        ADOBE_VIRTUAL_FOR_TESTS void AppendVisitorInfoForUrl(const std::string& base_url, const std::string& pair_id,
                const std::shared_ptr<ConfigurationSharedStateIdentity>& config_shared_state,
                const std::shared_ptr<EventData>& analytics_shared_state);

        /**
         * Handles all the events corresponding to getter API calls on identity module.
         *
         * @param event_name incoming event's event name
         * @param pair_id pair id of the incoming event which contains the base url
         */
        ADOBE_VIRTUAL_FOR_TESTS void HandleIdentifiersRequest(const std::string& event_name, const std::string& pair_id);

        /**
         * Updates local user idenitfier and persists the value.
         *
         * @param user_identifier user identifier to be set.
         */
        ADOBE_VIRTUAL_FOR_TESTS void UpdateUserIdentifier(const std::string& user_identifier);

        /**
         * Updates local push idenitfier and persists the value.
         *
         * @param push_identifier push identifier to be set.
         */
        ADOBE_VIRTUAL_FOR_TESTS void UpdatePushIdentifier(const std::string& push_identifier);

        /**
         * Updates local ad idenitfier and persists the value.
         *
         * @param ad_identifier advertising identifier to be set.
         */
        ADOBE_VIRTUAL_FOR_TESTS void UpdateAdvertisingIdentifier(const std::string& ad_identifier);

        /**
         * Save identity module properties to identity data store.
         *
         */
        ADOBE_VIRTUAL_FOR_TESTS void SavePersistently();

        /**
         * Dispatches identity response event.
         * @param event_name event name of the event to be dispatched.
         * @param event_data event data of the event to be dispatched.
         * @param pair_id pair id of the event to be dispatched.
         *
         */
        ADOBE_VIRTUAL_FOR_TESTS void HandleIdentityResponseEvent(const std::string& event_name,
                const std::shared_ptr<EventData>& event_data,
                const std::string& pair_id);

        /**
         * Packages identity module properties to be shared on the event hub.
         *
         */
        std::shared_ptr<EventData> PackageEventData();
        std::shared_ptr<DataStoreInterface> GetIdentityDataStore();
        void OnRegistered() override;
        void OnUnregistered() override;
        ADOBE_VIRTUAL_FOR_TESTS bool ProcessPushToken(const std::string& push_id);
        ADOBE_VIRTUAL_FOR_TESTS std::string GenerateMID();
        ADOBE_VIRTUAL_FOR_TESTS std::string GenerateInternalIdString(const std::map<std::string, std::string>& dpids);

    private:
        /**
         * Process a change to the global privacy status.
         * Sets this module's MobilePrivacyStatus reference. If the new status is MobilePrivacyStatus::OPT_OUT,
         * the identifiers are cleared, any queued events are clared, and any database hits are deleted.
         *
         * @param version the Event version for the Configuration change
         * @param event_data the updated Configuration EventData
         */
        ADOBE_VIRTUAL_FOR_TESTS
        void ProcessPrivacyChange(const int32_t version, const std::shared_ptr<EventData>& event_data);

        /**
         * Clears events queue of pending events which may be cleared immediately.
         * An Identiy Response event is dispatched for each cleared event.
         * Certain events, such as those requesting AppendUrl, will remain in the queue as
         * they are still allowed regardless of privacy status.
         */
        void ClearEventsQueue();

        /**
         * Attempts to set this module's MobilePrivacyStatus reference by retrieving the Configuration shared state
         * for the given `event`.
         * This method should be called during the module's boot process.
         */
        void LoadPrivacyStatus(const std::shared_ptr<Event>& event);


        bool push_enabled_;

        std::shared_ptr<IdentityHitDatabase> database_;

        void LoadDefaultValues();
        ADOBE_VIRTUAL_FOR_TESTS  void LoadVariablesFromPersistentData();
        ADOBE_VIRTUAL_FOR_TESTS  std::string ConvertVisitorIdObjectsVisitorIDsString(std::vector<std::shared_ptr<VisitorId>>&
                visitor_ids);
        ADOBE_VIRTUAL_FOR_TESTS  std::vector<std::shared_ptr<VisitorId>> ConvertVisitorIDsStringToVisitorIdObjects(
                            const std::string& ids_string);
        ADOBE_VIRTUAL_FOR_TESTS  std::string GenerateVisitorIdPayload(const std::shared_ptr<ConfigurationSharedStateIdentity>&
                config_data, const std::shared_ptr<EventData>& analytics_shared_state);
        ADOBE_VIRTUAL_FOR_TESTS  std::string AppendParameterToVisitorIdString(const std::string& original_string,
                const std::string& key,
                const std::string& value);
        ADOBE_VIRTUAL_FOR_TESTS  void HandleIdentityConfigurationUpdateEvent(const std::shared_ptr<EventData>& event_data);
        ADOBE_VIRTUAL_FOR_TESTS  std::map<std::string, std::string> ExtractDpid(const std::shared_ptr<EventData>& event_data);
        ADOBE_VIRTUAL_FOR_TESTS  bool ShouldSync(const std::map<std::string, std::string>& identifiers,
                const std::map<std::string, std::string>& dpids, const bool& force_re_sync,
                const std::shared_ptr<ConfigurationSharedStateIdentity>& config);
        ADOBE_VIRTUAL_FOR_TESTS  std::string BuildUrlString(const std::vector<std::shared_ptr<VisitorId>>& customer_ids,
                const std::map<std::string, std::string>& dpids,
                const std::shared_ptr<ConfigurationSharedStateIdentity>& config);
        ADOBE_VIRTUAL_FOR_TESTS  std::vector<std::shared_ptr<VisitorId>> GenerateCustomerIds(
                            const std::map<std::string, std::string>&
                            identifiers, const VisitorIdAuthenticationState& authentication_state);
        void ParseIDsOnjsonResponseReceivedCallback(const std::shared_ptr<IdentityObject>& json_map);
        void ChangePushStatusAndHitAnalytics(const bool new_status);
        bool SetPushEnabled(const bool enabled);
        bool IsPushEnabled();


    };
}


#endif /* ADOBEMOBILE_IDENTITY_IDENTITY_H */
