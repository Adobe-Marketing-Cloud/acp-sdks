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

#ifndef ADOBEMOBILE_ANALYTICS_ANALYTICS_H
#define ADOBEMOBILE_ANALYTICS_ANALYTICS_H

#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <queue>

#import <AdobeMarketingMobileCore/Common.h>
#import <AdobeMarketingMobileCore/InternalModule.h>
#import <AdobeMarketingMobileCore/HitProcessor.h>

namespace AdobeMarketingMobile {
    class AnalyticsState;
    class AnalyticsHitQueue;
    class AnalyticsHitDatabase;
    class AnalyticsDatabaseHitSchema;
    class AnalyticsHitProcessor;
    class AnalyticsDispatcherAnalyticsRequestIdentity;
    class AnalyticsDispatcherAnalyticsResponseIdentity;
    class AnalyticsDispatcherAnalyticsResponseContent;
    class AnalyticsUnprocessedEvent;
    class AnalyticsRequestSerializer;
    class AnalyticsProperties;
    class NetworkServiceInterface;
    class LocalStorageServiceInterface;
    class SystemInfoServiceInterface;
    class DataStoreInterface;
    class CryptoServiceInterface;

    class Analytics: public InternalModule {
        friend class AnalyticsMethods; // for testing
        friend class AnalyticsSpy; // for testing

    public:
        static const std::string LOG_PREFIX; // prefix for all logging messages

        Analytics();

        ADOBE_VIRTUAL_FOR_TESTS void HandleAnalyticsContentRequest(const std::shared_ptr<Event>& event);

        ADOBE_VIRTUAL_FOR_TESTS void HandleAnalyticsIdentityRequest(const std::shared_ptr<Event>& event);

        ADOBE_VIRTUAL_FOR_TESTS void HandleConfigurationEvent(const std::shared_ptr<Event>& event);

        ADOBE_VIRTUAL_FOR_TESTS void HandleAcquisitionContentEvent(const std::shared_ptr<Event>& event);

        ADOBE_VIRTUAL_FOR_TESTS void HandleLifecycleContentEvent(const std::shared_ptr<Event>& event);

        ADOBE_VIRTUAL_FOR_TESTS void HandleSharedStateUpdateEvent(const std::shared_ptr<Event>& event);

        ADOBE_VIRTUAL_FOR_TESTS void HandleHubBootedEvent(const std::shared_ptr<Event>& event);

    protected:

        std::shared_ptr<EventData> analytics_shared_data_;

        std::chrono::seconds most_recent_hit_timestamp_;

        std::shared_ptr<AnalyticsDispatcherAnalyticsResponseIdentity> response_identity_dispatcher_;

        std::shared_ptr<AnalyticsDispatcherAnalyticsResponseContent> response_content_dispatcher_;

        std::shared_ptr<AnalyticsHitDatabase> hit_database_;

        std::shared_ptr<AnalyticsHitProcessor> hit_processor_;

        std::shared_ptr<AnalyticsDatabaseHitSchema> hit_schema_;

        std::shared_ptr<AnalyticsHitQueue> hit_queue_;

        std::shared_ptr<AnalyticsProperties> analytics_properties_;

        std::shared_ptr<AnalyticsRequestSerializer> analytics_request_serializer_;

        std::deque<std::shared_ptr<AnalyticsUnprocessedEvent>> analytics_unprocessed_events_;

        std::vector<std::string> analytics_hard_dependencies_;

        /**
         * Called when the module is fully registered with the event hub.
         * Used to register analytics listeners and dispatchers and other local variables
         */
        void OnRegistered() override;

        /**
         * @see Module::OnUnregistered()
         */
        void OnUnregistered() override;

        /**
         * Retrieve the unique module name for storing shared state information.
         *
         * @return String containing the analytics shared state name
         */
        ADOBE_VIRTUAL_FOR_TESTS std::string GetSharedStateName() override;

    private:
        /**
         * Track analytics requests for actions/states
         *
         * @param analytics_state   current analytics state
         * @param event_data        EventData object containing tracking data
         * @param timestamp         current event timestamp used for tracking
         */
        ADOBE_VIRTUAL_FOR_TESTS void Track(const std::shared_ptr<AnalyticsState>& analytics_state,
                                           const std::shared_ptr<EventData>& event_data,
                                           const std::chrono::seconds timestamp);

        /**
         * Processes the analytics data parameters from the given event data.
         * Analytics data contains keys internal tracking, additional context data parameters
         * referrer data if acquisition was processed and this is an install hit and lifecycle session info
         *
         * @param analytics_state   current analytics state
         * @param track_event_data  event data object do be processed
         * @return map with analytics key/values for the available data
         */
        ADOBE_VIRTUAL_FOR_TESTS std::map<std::string, std::string> ProcessAnalyticsData(
                    const std::shared_ptr<AnalyticsState>& analytics_state,
                    const std::shared_ptr<EventData>& track_event_data);

        /**
         * Processes the analytics vars from the given event data.
         * Analytics vars contains data related to the state/action tracked, current visitor ids,
         * aid and background/foreground state
         *
         * @param analytics_state   current analytics state
         * @param track_event_data  event data object to be processed
         * @param timestamp         event timestamp used for offline tracking
         */
        ADOBE_VIRTUAL_FOR_TESTS std::map<std::string, std::string> ProcessAnalyticsVars(
                    const std::shared_ptr<AnalyticsState>& analytics_state,
                    const std::shared_ptr<EventData>& track_event_data,
                    const std::chrono::seconds timestamp);

        /**
         * This method tries to send/clear all the analytics hits based on the privacy status
         * If the value is privacy opt in, then all the analytics hits will be sent
         * If the value is privacy opt out, then all the analytics hits and the unprocessed events
         * will be removed
         *
         * @param analytics_state Analytics state containing the configuration data
         * @param event_number the event number which initiated this method
         */
        ADOBE_VIRTUAL_FOR_TESTS void UpdatePrivacyStatus(const std::shared_ptr<AnalyticsState>& analytics_state,
                const int32_t event_number);

        /**
         * Clears all the queued analytics hits - removes all the hits from database and all events
         * queued in memory.
         */
        ADOBE_VIRTUAL_FOR_TESTS void ClearAllHits();

        /**
         * Clears the AID from memory and shared storage.
         */
        ADOBE_VIRTUAL_FOR_TESTS
        void PurgeAid();

        /**
         * Clears the queue of unprocessed Analytics requests.
         * An EventType::ANALYTICS EventSource::RESPONSE_IDENTITY event or an
         * Eventtype::ANALYTICS EventSource::RESPONSE_CONTENT event is dispatched for any one-time listeners
         * which may be waiting for a response.
         */
        void ClearUnprocessedEventQueue();

        /**
         * Dispatches a new analytics response event with the hits queue size plus the unprocessed
         * events number. If database can't be opened returns only the hits queued in memory.
         * The response event should have the same pairID.
         *
         * @param pair_id the id used for the response event
         */
        ADOBE_VIRTUAL_FOR_TESTS void GetTrackingQueueSize(const std::string& pair_id);

        /**
         * Returns the automatically generated visitor identifier for Analytics (AID) as an analytics response identity event.
         * This is an app-specific unique visitor id that is generated on initial launch and then stored and used from that
         * point forward. This ID is preserved between app upgrades, and is removed on uninstall.
         *
         * @param analytics_state   current analytics state
         * @param pair_id           event pair id
         * @param event_number      event number
         */
        ADOBE_VIRTUAL_FOR_TESTS void HandleAnalyticsIdRequest(const std::shared_ptr<AnalyticsState>& analytics_state,
                const std::string& pair_id,
                const int32_t event_number);

        /**
         * Computes and retrieves the URL to the analytics server for getting the identifier value.
         *
         * @param analytics_state analytics state
         * @return computed URL as String
         */
        ADOBE_VIRTUAL_FOR_TESTS std::string RetrieveAnalyticsIdUrl(const std::shared_ptr<AnalyticsState>& analytics_state);

        /**
         * Returns marketing cloud id and marketing cloud org id in a map if Identity is enabled
         */
        ADOBE_VIRTUAL_FOR_TESTS std::map<std::string, std::string> GetMarketingCloudIdQueryParameters(
                    const std::shared_ptr<AnalyticsState>& state);

        /**
         * Puts current event in the analytics_unprocessed_events_ queue associated with its hard&soft dependencies
         * The event will not be queued if it is null or if event data is null
         */
        ADOBE_VIRTUAL_FOR_TESTS void PutEvent(const std::shared_ptr<Event>& event,
                                              const std::vector<std::string>& hard_dependencies,
                                              const std::vector<std::string>& soft_dependencies);

        /**
         * Starts processing the queued events. It first checks if current event has all the dependencies resolved, if
         * this is true, it consumes the event and goes to the next one. If current event cannot be resolved, it will stop
         * processing any other events.
         */
        ADOBE_VIRTUAL_FOR_TESTS void ProcessEvents();

        /**
         * This method will process the analytics event given as parameter, using the retrieved shared states.
         * It handles the track request, track internal, track lifecycle and get aid requests
         *
         * @param event                 the analytics event to process
         * @param shared_dependencies   the states required to process this event
         */
        ADOBE_VIRTUAL_FOR_TESTS void Process(const std::shared_ptr<Event>& event,
                                             const std::map<std::string, std::shared_ptr<EventData>>& shared_dependencies);

        /**
         * Converts the lifecycle event in internal analytics action. If backdate session and offline tracking are enabled,
         * and previous session length is present in the contextData map, we send a separate hit with the previous session
         * information and the rest of the keys as a Lifecycle action hit.
         * If ignored session is present, it will be sent as part of the Lifecycle hit and no SessionInfo hit will be sent.
         *
         * @param state shared state values
         * @param event the lifecycle event to process
         */
        ADOBE_VIRTUAL_FOR_TESTS void TrackLifecycle(const std::shared_ptr<AnalyticsState>& state,
                const std::shared_ptr<Event>& event);

        /**
         * Reads the locale value from the system info service and sets it in AnalyticsProperties if it was not set before
         *
         * @return the locale value
         */
        ADOBE_VIRTUAL_FOR_TESTS std::string GetLocale();

        /**
         * Sets the most recent hit timestamp in persistance. This timestamp will be used to backdate the lifecycle session
         */
        ADOBE_VIRTUAL_FOR_TESTS void SetMostRecentHitTimestamp(const std::chrono::seconds timestamp);

        /**
         * Retrieves the most recent hit timestamp from persistance. If it was already retrieved before, it is returned from memory
         */
        ADOBE_VIRTUAL_FOR_TESTS std::chrono::seconds GetMostRecentHitTimestamp();

        /**
         * Updates the AID value in persistance
         */
        ADOBE_VIRTUAL_FOR_TESTS void UpdateAnalyticsIdInLocalStorage(const std::string& aid);

        /**
         * Parses the analytics server response and extracts the AID. If the parse step fails or if the identifier is null
         * or has a length greater than 33, it returns the randomly generated ID
         *
         * @param state             analytics state
         * @param server_response   the server response that we want to parse
         *
         * @return Analytics Identifier value; it may return nullptr if the server response is invalid and
         * Identity service is enabled
         */
        ADOBE_VIRTUAL_FOR_TESTS std::string ParseIdentifier(const std::shared_ptr<AnalyticsState>& state,
                const std::string& server_response);

        /**
         * Tries to retrieve the shared data for all the dependencies of the given event. When all the dependencies are
         * resolved, it will return the map with the shared states.
         *
         * @param event the unprocessed event for which we ask shared state
         *
         * @return a map if all dependencies are solved, nullptr otherwise
         */
        ADOBE_VIRTUAL_FOR_TESTS std::map<std::string, std::shared_ptr<EventData>> GetSharedState(const
                std::shared_ptr<AnalyticsUnprocessedEvent>& event);

        /**
         * Creates an internal analytics event with the crash session data
         */
        ADOBE_VIRTUAL_FOR_TESTS void BackdateLifecycleCrash(const std::shared_ptr<AnalyticsState>& state);

        /**
         * Creates an internal analytics event with the previous lifecycle session info
         */
        ADOBE_VIRTUAL_FOR_TESTS void BackdateLifecycleSessionInfo(const std::shared_ptr<AnalyticsState>& state,
                const std::string& previous_session_length,
                const std::chrono::seconds previous_session_pause_timestamp);

        /**
         * Returns the system info service. May return nullptr if platform services are null or system info service is
         * not available
         */
        ADOBE_VIRTUAL_FOR_TESTS std::shared_ptr<SystemInfoServiceInterface> GetSystemInfoService();

        /**
         * Returns the local storage. May return nullptr if platform services are null or local storage service is not
         * available
         */
        ADOBE_VIRTUAL_FOR_TESTS std::shared_ptr<DataStoreInterface> GetDataStore();

        /**
         * Returns the crypto service. May return nullptr if platform services are null or crypto service is not
         * available
         */
        ADOBE_VIRTUAL_FOR_TESTS std::shared_ptr<CryptoServiceInterface> GetCryptoService();

        /**
         * Returns the action key for internal or non-internal actions
         */
        ADOBE_VIRTUAL_FOR_TESTS std::string GetActionKey(const bool is_internal_action);

        /**
         * Returns the action prefix for internal or non-internal actions
         */
        ADOBE_VIRTUAL_FOR_TESTS std::string GetActionPrefix(const bool is_internal_action);

        /**
         * Tries to force kick the analytics hits from database.
         */
        ADOBE_VIRTUAL_FOR_TESTS void ForceKickEventsFromDB(const std::shared_ptr<AnalyticsState>& state);

        /**
         * Initializes the hits database if it was not initialized before and returns it
         *
         * @return analytics hit database instance
         */
        ADOBE_VIRTUAL_FOR_TESTS std::shared_ptr<AnalyticsHitDatabase> GetHitDatabase();

        ADOBE_VIRTUAL_FOR_TESTS std::shared_ptr<AnalyticsHitQueue> GetHitQueue();

        ADOBE_VIRTUAL_FOR_TESTS std::shared_ptr<AnalyticsDatabaseHitSchema> GetHitSchema();

        ADOBE_VIRTUAL_FOR_TESTS std::shared_ptr<AnalyticsHitProcessor> GetHitProcessor();

        ADOBE_VIRTUAL_FOR_TESTS std::chrono::seconds GetTimeSinceLaunch(const std::chrono::seconds
                lifecycle_session_start_timestamp);

        /**
         * Generates a random Analytics ID.
         * This method should be used if the analytics server response will be null or invalid
         *
         * @return new random AID
         */
        ADOBE_VIRTUAL_FOR_TESTS std::string GenerateAID();
    };
}

#endif /* ADOBEMOBILE_ANALYTICS_ANALYTICS_H */
