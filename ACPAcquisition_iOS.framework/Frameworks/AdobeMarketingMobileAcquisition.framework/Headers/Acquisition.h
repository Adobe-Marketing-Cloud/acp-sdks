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

#ifndef ADOBEMOBILE_ACQUISITION_ACQUISITION_H
#define ADOBEMOBILE_ACQUISITION_ACQUISITION_H

#include <deque>
#include <AdobeMarketingMobileCore/Common.h>
#include <AdobeMarketingMobileCore/InternalModule.h>

namespace AdobeMarketingMobile {
    class AcquisitionDispatcherAcquisitionResponseContent;
    class AcquisitionDispatcherAnalyticsRequestContent;
    class AcquisitionFingerprinter;
    class DataStoreInterface;
    class Event;
    class NetworkServiceInterface;
    class URLServiceInterface;

    /**
     * @class Acquisition
     *
     * The Acquisition module is responsible for receiving data for various points of user entry, parsing that data,
     * and forwarding the data for attribution as is determined necessary by other listening modules.
     *
     * The Acquisition module handles the following use cases:
     *   1. Acquisition data via communication with the fingerprinter server
     *   2. Handling click-throughs of local and remote notifications (push messages)
     *   3. Handling app launches that occurred due to the user clicking a deeplink
     *
     * The Acquisition module listens for the following events:
     *   1. Acquisition Request Content
     *   2. Acquisition OS
     *   3. Hub Shared State
     *   4. Hub Booted
     *
     * The Acquisition module dispatches the following events:
     *   1. Analytics Request Content
     *   2. Acquisition Response Content
     *
     * The Acquisition module has dependencies on the following Platform Services:
     *   1. DataStoreInterface
     *   2. JsonUtilityService
     *   3. NetworkServiceInterface
     */
    class Acquisition : public InternalModule {
    public:

        /**
         * Creates a new instance of an Acquisition module.
         */
        Acquisition();

        /**
         * Create a new instance of an Acquisition module.
         *
         * @param log_prefix an identifier for this module used in log messages.
         */
        explicit Acquisition(const std::string& log_prefix);

        /**
         * Updates acquisition shared state with the stored referrer data.
         */
        ADOBE_VIRTUAL_FOR_TESTS void EventHubBooted(const std::shared_ptr<Event>& event);

        /**
         * Retrieves the DataStore for Acquisition.  May return nullptr if plaform services
         * or local storage are unavailable or empty.
         */
        ADOBE_VIRTUAL_FOR_TESTS std::shared_ptr<DataStoreInterface> GetDataStore();

        /**
         * Returns the Acquisition event queue that holds the pending Acquisition events.
         */
        ADOBE_VIRTUAL_FOR_TESTS const std::deque<std::shared_ptr<Event>>& GetEventQueue();

        /**
         * Retrieves the NetworkService that can be used for network connections.  May return
         * nullptr if platform services are unavailable or null.
         */
        ADOBE_VIRTUAL_FOR_TESTS std::shared_ptr<NetworkServiceInterface> GetNetworkService();

        /**
         * Retrieves the URLService that can be used to extract query parameters from deeplink URL.
         * May return nullptr if plaform services are unavailable.
         */
        ADOBE_VIRTUAL_FOR_TESTS std::shared_ptr<URLServiceInterface> GetURLService();

        /**
         * Parses the deferred deep link url passed through public API, dispatches an acquisition event if the data
         * is valid and also saves it into local storage.
         *
         * @param deep_link_url the deep link url passed through public API
         * @param event         source event being processed
         */
        ADOBE_VIRTUAL_FOR_TESTS void Handle3rdPartyDeferredDeepLinkRequest(const std::string& deep_link_url,
                const std::shared_ptr<Event>& event);

        /**
         * If the app is launched from a deeplink url, a push message, or a local message,
         * then we need to track the data. If deepLinkURL contains valid data then an acquisition event is dispatched.
         * If either of them is valid, dispatch an analytics event.
         *
         * @param event source event being processed containing:
         *        - the deep link url that was clicked to open the app, or
         *        - the id of push message whick was clicked to open the app, or
         *        - the id of local message which was clicked to open the app
         */
        ADOBE_VIRTUAL_FOR_TESTS void HandleLaunchAcquisition(const std::shared_ptr<Event>& event);

        /**
         * Process fingerprinter acquisition request
         *
         * @param additional_parameters    additional parameters need to be appended in the request url
         * @param event       source event being processed
         * @param identity_shared_state         shared state from Identity module
         * @param configuration_shared_state         shared state from Configuration module
         */
        ADOBE_VIRTUAL_FOR_TESTS void HandleFingerprinterAcquisition(const std::map<std::string, std::string>&
                additional_parameters,
                const std::shared_ptr<Event>& event,
                const std::shared_ptr<EventData>& identity_shared_state,
                const std::shared_ptr<EventData>& configuration_shared_state);

        /**
         * Process fingerprinter acquisition request
         * 1. Do nothing if acquisition is not configured.
         * 2. Do nothing if the SDK already has referrer data in storage.
         * 3. Send async request to fingerprinter server
         * 4. Do nothing if the response is invalid
         * 5. Persist data to local storage.
         * Dispatch new analytics event with acquisition data and trigger deep link if it is available.
         *
         * @param additional_parameters    additional parameters need to be appended in the request url
         * @param fingerprinter_acquisition    the handler for fingerprinter aquisition
         * @param event             source event being processed
         * @param identity_shared_state         shared state from Identity module
         * @param configuration_shared_state         shared state from Configuration module
         */
        ADOBE_VIRTUAL_FOR_TESTS void HandleFingerprinterAcquisition(
                    const std::map<std::string, std::string>& additional_parameters,
                    const std::shared_ptr<AcquisitionFingerprinter>& fingerprinter_acquisition,
                    const std::shared_ptr<Event>& event,
                    const std::shared_ptr<EventData>& identity_shared_state,
                    const std::shared_ptr<EventData>& configuration_shared_state);

        /**
         * Process the raw acquisition data received from platform, simply store the data to datastore and dispatch
         * an Acquisition RESPONSE_CONTENT event, no interactiong with fingerprinter server is needed in this case.
         *
         * @param event             source event being processed
         */
        ADOBE_VIRTUAL_FOR_TESTS void HandleRawAcquisitionData(const std::shared_ptr<Event>& event);


        /**
         * Loops through waiting events and processes them if possible. Acquisition events are dependent on
         * Configuration shared state in order to process.
         */
        ADOBE_VIRTUAL_FOR_TESTS void ProcessEvents();

        /**
         * Looks for required referrer data in the given event's data and either processes a Launch Acquisition
         * or queues the event to be processed later
         *
         * @param event Acquisition OS event containing data to be processed
         */
        ADOBE_VIRTUAL_FOR_TESTS void ProcessOsEvent(const std::shared_ptr<Event>& event);

        /**
         * Queues the provided Acquisition Request Content event and kicks off processing
         *
         * @param event Acquisition Request Content event to be queued and processed
         */
        ADOBE_VIRTUAL_FOR_TESTS void ProcessRequestContentEvent(const std::shared_ptr<Event>& event);

        /**
         * Checks the owner of the updated shared state starts to process events if the changed state
         * is owned by Configuration
         *
         * @param event Hub Shared State event containing a new shared state
         */
        ADOBE_VIRTUAL_FOR_TESTS void ProcessSharedStateEvent(const std::shared_ptr<Event>& event);

        /**
         * Adds an event to the waiting events queue
         * @param event event to be added to the queue
         */
        ADOBE_VIRTUAL_FOR_TESTS void QueueAcquisitionEvent(const std::shared_ptr<Event>& event);

        /**
         * Send a campaign start request to fingerprinter server.
         *
         * If application ID exists, it will start processing the optional query parameters:
         * a) If "adid" available, put it under “a_cid” parameter
         * b) If parameters.data contains other keys, add “ctx” as prefix and copy their values
         *
         * Start preparing the start campaign URL: https://${serverName}/v3/${applicationID}/start/${queryParameters}
         * Create a network call with the prepared URL
         *
         * @param server        string containing the server for the new start campaign call
         * @param dest_app_id   the application id, this is not the application id of the current app, but the
         *                      application id you want to start the campaign for
         * @param data          The data received from the public API
         * @param event         source event being processed
         * @param identity_shared_state         shared state from Identity module
         */
        ADOBE_VIRTUAL_FOR_TESTS void StartCampaign(const std::string& server,
                const std::string& dest_app_id,
                const std::map<std::string, std::string>& data,
                const std::shared_ptr<Event>& event,
                const std::shared_ptr<EventData>& identity_shared_state);

    protected:
        std::shared_ptr<AcquisitionDispatcherAnalyticsRequestContent> analytics_event_dispatcher_;
        std::shared_ptr<AcquisitionDispatcherAcquisitionResponseContent> response_content_dispatcher_;
        std::deque<std::shared_ptr<Event>> event_queue_;

        ADOBE_VIRTUAL_FOR_TESTS void OnRegistered() override;
        ADOBE_VIRTUAL_FOR_TESTS std::string GetSharedStateName() override;

    private:
        /**
         * Creates or updates acquisition shared state with given data, based on the create_shared_state parameter
         */
        void SetAcquisitionSharedState(const bool create_shared_state,
                                       const int32_t version,
                                       const std::map<std::string, std::string>& acquisition_data);

    };
}

#endif /* ADOBEMOBILE_ACQUISITION_ACQUISITION_H */
