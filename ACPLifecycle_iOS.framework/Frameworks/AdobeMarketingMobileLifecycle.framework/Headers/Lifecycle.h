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
#ifndef ADOBEMOBILE_LIFECYCLE_LIFECYCLE_H
#define ADOBEMOBILE_LIFECYCLE_LIFECYCLE_H

#import <AdobeMarketingMobileCore/AdobeMarketingMobileCore.h>
#include <queue>

namespace AdobeMarketingMobile {
    class LifecycleDispatcherResponseContent;
    class PlatformServicesInterface;
    class LocalStorageServiceInterface;
    class SystemInfoServiceInterface;
    class JsonUtilityServiceInterface;
    class DataStoreInterface;
    class Event;
    class EventData;
    class LifecycleSession;

    /**
     * @class Lifecycle
     *
     * The responsibility of Lifecycle is to handle the calculation and population of a base set of data within
     * the SDK. This data will consist of information about the lifecycle of the app involving launches, installs
     * and upgrades.
     */
    class Lifecycle : public InternalModule {
        friend class TestableLifecycle; // for testing
    public:

        /**
         * Create a new instance of a Lifecycle Module.
         */
        Lifecycle();

        /**
         * Handler for all the lifecycle request content events
         *
         * @param event a lifecycle request content event.
         */
        ADOBE_VIRTUAL_FOR_TESTS void QueueEvent(const std::shared_ptr<Event>& event);

        /**
         * Checks if event's state owner is Configuration, if so starts processing the events
         */
        ADOBE_VIRTUAL_FOR_TESTS void HandleSharedStateUpdateEvent(const std::shared_ptr<Event>& event);

        /**
         * Updates the lifecycle shared state when a boot event is received
         */
        ADOBE_VIRTUAL_FOR_TESTS void HandleEventHubBootEvent(const std::shared_ptr<Event>& event);

    protected:

        /**
         * Called when the EventHub registers this module.
         * Registers new LifecycleListenerRequestContent.
         */
        ADOBE_VIRTUAL_FOR_TESTS void OnRegistered() override;

        /**
         * Retrieve the unique module name for storing shared state information.
         *
         * @return String containing the container name for shared state for this module (can be empty string)
         **/
        ADOBE_VIRTUAL_FOR_TESTS std::string GetSharedStateName() override;

        /**
         * Start/resume a new lifecycle session
         *
         * @param event event containing lifecycle start data
         * @param config_shared_state configuration shared state data
         */
        ADOBE_VIRTUAL_FOR_TESTS void Start(const std::shared_ptr<Event>& event,
                                           const std::shared_ptr<EventData>& config_shared_state);

        /**
         * Pause lifecycle session
         *
         * @param event event containing lifecycle pause data
         */
        ADOBE_VIRTUAL_FOR_TESTS void Pause(const std::shared_ptr<Event>& event);

        std::shared_ptr<LifecycleDispatcherResponseContent> lifecycle_session_info_dispatcher_;

        std::shared_ptr<LifecycleSession> lifecycle_session_;

    private:
        /**
         * @private
         * Starts processing all the queued events.
         * Important, method accesses shared resource. Call in a thread-safe way.
         * @see AddTaskToQueue
         */
        ADOBE_VIRTUAL_FOR_TESTS void ProcessQueuedEvents();

        /**
         * @private
         * Gets advertising identifier from the identity shared state
         *
         * @param event current event for which we will get the identity shared state
         * @return the advertising identifier if idenity not null, empty string otherwise
         */
        std::string GetAdvertisingIdentifier(const std::shared_ptr<Event>& event);

        /**
         * @private
         * Check for application upgrade.
         */
        void CheckForApplicationUpgrade(const std::chrono::seconds timestamp);

        /**
         * @private
         * Gets lifecycle context data.
         */
        std::map<std::string, std::string> GetContextData();

        /**
         * @private
         * Gets persisted lifecycle context data from local storage.
         */
        ADOBE_VIRTUAL_FOR_TESTS std::map<std::string, std::string> GetPersistedContextData();

        /**
         * @private
         * Checks if this is a launch event (app was closed/backgrounded > lifecycle timeout)
         *
         * @param timestamp event timestamp
         * @param timeout lifecycle timeout provided by configuration or default
         * @return launch status
         */
        bool IsLaunch(std::chrono::seconds timestamp, std::chrono::seconds timeout);

        /**
         * @private
         * Checks if this launch is an install
         *
         * @return install status
         */
        bool IsInstall();

        /**
         * @private
         * Checks if this launch is an upgrade
         *
         * @return upgrade status
         */
        bool IsUpgrade();

        /**
         * Creates a new version for the lifecycle shared state with current context data
         *
         * @param event_number the shared state version
         */
        void CreateLifecycleSharedState(const int32_t event_number);

        /**
         * @private
         * Persist lifecycle context data, last used date and last version
         */
        void PersistLifecycleData(const std::chrono::seconds timestamp);

        /**
         * @private
         * Fetches the Data Store for Lifeycle from the PlatformServicesInterface
         *
         * @return @nullable DataStoreInterface for Lifecycle Data Store
         */
        std::shared_ptr<DataStoreInterface> GetDataStore();

        /**
         * @private
         * Fetches the System Info Service from PlatformServicesInterface
         *
         * @return @nullable SystemInfoServiceInterface
         */
        std::shared_ptr<SystemInfoServiceInterface> GetSystemInfoService();

        /**
         * @private
         * Fetches the Json Utility Service from PlatformServicesInterface
         *
         * @return @nullable JsonUtilityServiceInterface
         */
        ADOBE_VIRTUAL_FOR_TESTS std::shared_ptr<JsonUtilityServiceInterface> GetJsonUtilityService();

        /**
         * @private
         * Queue of events to be processed in order. Queue should only grow when we don't have configuration to process
         */
        std::queue<std::shared_ptr<Event>> events_;

        std::map<std::string, std::string> lifecycle_context_data_;

        std::map<std::string, std::string> previous_session_lifecycle_context_data_;
    };
}


#endif /* ADOBEMOBILE_LIFECYCLE_LIFECYCLE_H */
