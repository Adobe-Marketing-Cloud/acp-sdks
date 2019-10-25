/*
Copyright 2017 Adobe. All rights reserved.
This file is licensed to you under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License. You may obtain a copy
of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS
OF ANY KIND, either express or implied. See the License for the specific language
governing permissions and limitations under the License.
*/

#ifndef ADOBEMOBILE_CONFIGURATION_CONFIGURATION_H
#define ADOBEMOBILE_CONFIGURATION_CONFIGURATION_H

#include <mutex>
#include <string>
#include "FileSystemServiceInterface.h"
#include "InternalModule.h"
#include "JsonUtilityServiceInterface.h"
#include "LocalStorageServiceInterface.h"
#include "NetworkServiceInterface.h"
#include "RemoteFileManagerServiceInterface.h"
#include "SystemInfoServiceInterface.h"
#include "Variant.h"
#include "TaskExecutor.h"

namespace AdobeMarketingMobile {
    class ConfigurationData;
    class ConfigurationDownloader;
    class ConfigurationDispatcherConfigurationRequestContent;
    class ConfigurationDispatcherConfigurationResponseContent;
    class ConfigurationDispatcherConfigurationResponseIdentity;

    /**
     * @class Configuration
     * The responsibility of Configuration is to handle fetch, storage, ordering, and delivery of the configuration
     * of all modules within the SDK.
     *
     * Configuration can be done in multiple ways within the SDK.
     * Bundled
     * A configuration file can be bundled with the parent application prior to publishing the app.
     * This configuration and its settings has the lowest priority.
     * Remote
     * Remote will be the Adobe recommended approach. Remote configuration is stored on a server that the sdk will
     * pull from on a structured basis. Remote configuration will overwrite Bun dled configuration,
     * but has a lower priority than Programmatic.
     * Programmatic
     * Customers can programmatically override settings in configuration by passing in the settings key value pair.
     * Programmatic configuration has the highest priority of configurations
     * and will always be obeyed.
     */
    class Configuration : public InternalModule {
        friend class ConfigurationMethods; // for unit testing

    public:
        using InternalModule::GetSharedEventState; // make GetSharedEventState public
        using InternalModule::HasSharedEventState; // make HasSharedEventState public

        // Configuration storage keys
        static const std::string CONFIGURATION_URL_BASE;        ///< Base URL of remote configuration
        static const std::string
        CONFIG_BUNDLED_FILE_NAME;      ///< Filename of Adobe Mobile SDK configuration bundled with application
        static const std::string CONFIG_MANIFEST_APPID_KEY;     ///< Manifest property key for App ID from System Info Service
        static const std::string DATASTORE_KEY;                 ///< Local Storage Service Datastore key
        static const std::string
        PERSISTED_OVERRIDDEN_CONFIG;   ///< Overridden configuration key in Local Storage Service Datastore
        static const std::string PERSISTED_APPID;               ///< App ID key in Local Storage Service Datastore
        static const std::string PERSISTED_RULES_URL;           ///< Last known rules url key in Local Storage Service Datastore
        static const std::string LOG_PREFIX;                    ///< Prefix for all logging messages
        static const std::string CACHE_FOLDER;                  ///< Cache sub folder for config data
        static const std::string RULES_CACHE_FOLDER;			///< Cache sub folder for config-downloaded rules
        static const std::string RULES_JSON_KEY;				///< Root key for rules definition within JSON
        static const std::string RULES_JSON_FILE_NAME;			///< File name for rules definitions
        static const std::string RULES_JSON_CONDITION_KEY;		///< Json key for condition collection of a single rule
        static const std::string RULES_JSON_CONSEQUENCES_KEY;	///< Json key for actions array of single rule

        /**
         * Create a new instance of a Configuration Module.
         */
        Configuration();

        /**
         * Handler for all the configuration request content events
         *
         * @param event a configuration request content event.
         */
        virtual void HandleConfigurationEvent(const std::shared_ptr<Event>& event);

        /**
         * Handler for all the Lifecycle response content event
         *
         * Lifecycle start event will trigger the configuration to re-fetch the remote configuration.
         * Re-fetch happens only when the app_id exists in manifest or in persistence.
         *
         * Note: Lifecycle start will not reload the bundled configuration.
         */
        virtual void HandleLifeCycleEvent();

        /**
         * Handler for the Boot event created by EventHub.
         *
         * If AppId present, create a configureWithAppId request content event and then attempt to load configuration in the following
         * order
         * 1. CachedFile
         * 2. Bundled
         * 3. Overridden Config
         *
         * If No AppId, attempt to load the bundled/overridden configuration.
         *
         * @param event boot configuration event, which is generated when the module is initialized.
         */
        virtual void HandleBootEvent(const std::shared_ptr<Event>& event);

        /**
         * Handler for EventType#CONFIGURATION EventSource#REQUEST_IDENTITY Event.
         *
         * This event is generated when the getSDKIdentities public API is called.
         * Configuration module attempts to read all the identities known to the SDK. It then generates
         * a EventType#CONFIGURATION EventSource#RESPONSE_IDENTITY response Event with all
         * the obtained identities in a JSON String format.
         *
         * @param event An Configuration Request Identity event
         * @see MobileIdentities
         */
        ADOBE_VIRTUAL_FOR_TESTS void HandleGetSdkIdentitiesEvent(const std::shared_ptr<Event>& event);


        /**
         * Handler for EventType#HUB EventSource#SHARED_STATE Event.
         *
         * This event is generated by eventhub when there is a sharedstate change in any registered module.
         * This method is called when there is a shared state change in either of the following modules.
         * 1. Analytics
         * 2. Audience
         * 3. Target
         * 4. Identity
         * 5. Configuration
         */
        ADOBE_VIRTUAL_FOR_TESTS void HandleSharedStateChangeEvent();

        /**
         * Returns the configuration event queue that holds the pending EventType#CONFIGURATION EventSource#REQUEST_IDENTITY events.
         */
        ADOBE_VIRTUAL_FOR_TESTS const std::deque<std::shared_ptr<Event>>& GetEventQueue();

        /**
         * Helper method to queue EventType#CONFIGURATION EventSource#REQUEST_IDENTITY event into #getsdkids_event_queue_
         */
        ADOBE_VIRTUAL_FOR_TESTS void QueueGetSDKIdentitiesEvent(const std::shared_ptr<Event>& event);

    protected:

        /**
         * Create a new instance of a Configuration Module.
         *
         * @param log_prefix an identifier for this moduled used in log messages.
         */
        explicit Configuration(const std::string& log_prefix);

        /**
         * Called when the EventHub registers this module.
         * Registers new ConfigurationListenerResponseContent and new ConfigurationListenerLifecycleRequestContent.
         * Creates new ConfigurationDispatcher.
         */
        void OnRegistered() override;

        /**
         * Called when the EventHub unregisters this module.
         * This is the place where we do clean up jobs
         */
        void OnUnregistered() override;

        /**
         * Retrieve the unique module name for storing shared state information.
         *
         * @return String containing the container name for shared state for this module (can be empty string)
         **/
        ADOBE_VIRTUAL_FOR_TESTS std::string GetSharedStateName() override;

        /**
         * Reads the app_id from the manifest file.
         * Returns empty string if app_id is not found.
         *
         * @return application identifier from manifest file or empty string if could not read from manifest
         */
        std::string GetAppIdFromManifest();

        /**
         * Reads the bundled ADBMobileConfig.json file from the assets folder.
         * Returns an empty string if the bundled file is not found.
         *
         * @return bundled file content or empty string if could not retrieve bundled file
         */
        std::string GetBundledFileContent();

        /**
         * Attempts to load a configuration from the provide file path
         *
         * @param event    event which triggered the configuration request
         */
        virtual void ProcessConfigWithFilePathEvent(const std::shared_ptr<Event>& event);

        /**
         * Unpacks the update configuration request content event. The new configuration data is added over the existing
         * configuration and new configuration response event is dispatched.
         *
         * @param event an update configuration event.
         */
        virtual void ProcessUpdateConfigEvent(const std::shared_ptr<Event>& event);

        /**
         * Process the boot configuration event.
         *
         * If app_id present, attempt to load configuration in the following order, and then create a ConfigureWithAppId
         * request content event
         * 1. CachedFile
         * 2. Bundled
         * 3. Overridden Config
         *
         * If No app_id, attempt to load the bundled/overridden configuration.
         *
         * @param event boot configuration event, which is generated when the module is initialized.
         */
        virtual void ProcessBootConfigEvent(const std::shared_ptr<Event>& event);

        /**
         * Process the configuration request content events with app_id. Tries to retrieve the latest configuration
         * from the remote server.
         *
         * @param event    the set app_id event
         */
        virtual void ProcessConfigureWithAppIdEvent(const std::shared_ptr<Event>& event);

        /**
         * Retrieves current configuration through a new configuration response event.
         *
         * @param event the publish configuration event
         */
        virtual void ProcessPublishConfigurationEvent(const std::shared_ptr<Event>& event);

        /**
         * Dispatches a ConfigurationResponseContent event with the provided JSON string.
         * Overrides with the programmed configuration if they exist.
         *
         * @param json_config_string a String containing the JSON configuration
         * @param event            event which triggered the configuration request
         * @param  load_rules bool denoting if we should load the rules
         */
        virtual void ConfigureWithJsonString(const std::string& json_config_string,
                                             const std::shared_ptr<Event>& event,
                                             const bool load_rules);

        /**
         * Processes the Events generated by getSDKIdentities public API.
         *
         * Calls the callback with empty string if JsonUtilityService is not available.
         * Queues the Event in the #getsdkids_event_queue_ if the one of the requires shared state is in EventHub#SHARED_STATE_PENDING.
         * Dispatches the paired EventType#CONFIGURATION EventSource#RESPONSE_IDENTITY event into the EventHub with string identities JSON.
         */
        virtual void ProcessGetSdkIdsEvent();

        /**
         * Returns new instance of a configuration downloader for the specified url.
         *
         * @param app_id The app id required to build the url for the downloader.
         * @return configuration downloader instance, nullptr if the remote file service is not availabe
         */
        virtual std::shared_ptr<ConfigurationDownloader> GetConfigDownloader(const std::string& app_id);

        /**
         * @protected
         * The event dispatcher. Created when this module is registered in the Event Hub.
         */
        std::shared_ptr<ConfigurationDispatcherConfigurationRequestContent> dispatcher_request_content_;

        /**
         * @protected
         * The event dispatcher. Created when this module is registered in the Event Hub.
         */
        std::shared_ptr<ConfigurationDispatcherConfigurationResponseContent> dispatcher_response_content_;

        /**
         * @protected
         * The event dispatcher. Created when this module is registered in the Event Hub.
         */
        std::shared_ptr<ConfigurationDispatcherConfigurationResponseIdentity> dispatcher_response_identity_;

    private:

        /**
         * @private
         * Load the overridden configuration from memory.
         * @param lock a mutex lock to synchronize the overridden config. The lock is not released within this method.
         */
        void RetrieveOverriddenConfigFromPersistence(std::unique_lock<std::mutex>& lock);

        /**
         * @private
         * Saves the overridden configuration map in the persistence under the Configuration DataStore.
         * Used to persist the programmed Configuration between launches
         *
         * @param overridden_config new overridden config map to be saved
         */
        void SaveOverriddenConfigToPersistence(const std::shared_ptr<ConfigurationData>& overridden_config);

        /**
         * @private
         * Load the app id from memory.
         *
         * @return application identifier from persistence
         */
        std::string RetrieveAppIdFromPersistence();

        /**
         * @private
         * Saves the app id in the persistence under the Configuration DataStore.
         * Used to persist the app id between launches to load the cached configuration.
         *
         * @param app_id app id to be saved
         */
        void SaveAppIdToPersistence(const std::string& app_id);

        /**
         * @private
         * Load the last known rules url from local storage.
         *
         * @return last known rules url from persistence
         */
        std::string RetrieveLastRulesURLFromPersistence();

        /**
         * @private
         * Saves the last known rules url in the persistence under the Configuration DataStore.
         * Used to persist the rules url between launches to load the cached rules.
         *
         * @param url last known rules url
         */
        void SaveLastRulesURLToPersistence(const std::string& url);

        /**
         * @private
         * Load the cached rules using the last known rules url.
         */
        void RetrieveCachedRules();

        /**
         * @private
         * The purpose of the SetAppIDInternalEvent is to refresh the existing configurtion with the persisted appID
         * This method validates the appid for the SetAppIDInternalEvent
         * It return true, if the persisted appid is same as the internalEvent appid present in the event_data
         * It return false, if the persisted appid is different from the internalEvent appid present in the event_data
         *
         * @param event_data eventdata associated to the set internal appId event.
         * @param new_app_id app id to be fetched
         */
        bool ValidateForInternalEventAppIDChange(const std::shared_ptr<EventData>& event_data, const std::string new_app_id);


        // ================================
        // Helper methods
        // ================================

        /**
         * @private
         * Get a valid app id. Retrieves the stored app id from persistence.
         * If not found, retrieves the app id from manifest.
         *
         * @return application identifier
         */
        std::string GetValidAppID();

        /**
         * @private
         * Attempts to configure with the bundled configuration.
         *
         * @param event event which triggered the configruation request.
         *
         * @return true if the configuration is successfully loaded, false otherwise
         */
        bool LoadBundledConfig(const std::shared_ptr<Event>& event);

        /**
         * @private
         * Attempts to configure with the cached file.
         *
         * @param app_id associated app id of that cache file.
         * @param event event which triggered the configruation request.
         *
         * @return true if the cached file is successfully loaded, false otherwise
         */
        bool LoadCachedConfig(const std::string& app_id, const std::shared_ptr<Event>& event);

        /**
         * @private
         * Attempts to configure with the overridden configuration.
         *
         * @param event event which triggered the configruation request.
         *
         * @return true if succeeded, false otherwise
         */
        bool LoadOverriddenConfig(const std::shared_ptr<Event>& event);


        /**
         * @private
         * Central function to process all configuration changes.  Called by several functions in response to changes.
         *
         * @param config_data EventData object containing the configuration update to be processed
         * @param  load_rules bool denoting if we should load the rules
         */
        void ChangeConfiguration(const std::shared_ptr<Event>& trigger_event, const std::shared_ptr<EventData>& config_data,
                                 const bool load_rules);
        /**
         * @private
         * Helper to get the PlatformServices JsonUtilityService
         * @param json_utility_service The returned JsonUtilityService. May be nullptr if the PlatformServices
         *                              have gone away.
         * @return false if the PlatformServices is not available, true otherwise.
         */
        bool GetPlatformJsonUtilityService(std::shared_ptr<JsonUtilityServiceInterface>& json_utility_service);

        /**
         * @private
         * Helper to get the PlatformServices SystemInfoService
         * @param system_info_service The returned SystemInfoService. May be nullptr if the PlatformServices
         *                            have gone away.
         * @return false if the PlatformServices is not available, true otherwise.
         */
        bool GetPlatformSystemInfoService(std::shared_ptr<SystemInfoServiceInterface>& system_info_service);

        /**
         * @private
         * Helper to get the PlatformService FileSystemService
         * @param file_system_service The returned FileSystemService. May be nullptr if the PlatformServices
         *                              have gone away.
         * @return false if the PlatformService is unavailable, true otherwise.
         */
        bool GetFileSystemService(std::shared_ptr<FileSystemServiceInterface>& file_system_service);

        /**
         * @private
         * Helper to create a new EventHub::PENDING Shared State for the given event.
         *
         * @param version the shared state version to create
         */
        void CreatePendingSharedState(int32_t version);

        /**
         * @private
         * Helper to update previous EventHub::PENDING shared states to
         * EventHub::PREV Configuration state. Call this method to "roll-back"
         * to previous config shared state when failure occurs attempting to
         * load new config.
         *
         * @param version the shared state version to create
         */
        void UpdateSharedStateToPreviousConfig(int32_t version);

        /**
         * @private
         * Attempts to download and register rules from remote server described in config_data.
         *
         * @param config_data the EventData object containing all configuration settings.
         */
        void DownloadRules(const std::shared_ptr<EventData>& config_data);

        /**
         * @private
         * Called after rules are downloaded (by DownloadRules) to uncompress and register the rules.
         *
         * @param cached_file the Path to the downloaded rules.
         * @param url the URL that was downloaded.
         */
        void OnRulesDownloaded(const std::string& cached_file, const std::string& url);

        /**
         * @private
         * Loads rules from the given directory.  Called by OnRulesDownloaded.
         *
         * @param directory_path string containing the path to the directory containing the rules definitions (rules.json).
         *
         * @return vector of Rule objects that were parsed from the directory.
         */
        std::vector<std::shared_ptr<Rule>> LoadRulesFromDirectory(const std::string& directory_path);

        /**
        * @private
        * Parses rules from the standard rules json format into a list of Rule objects.  Called by LoadRulesFromDirectory.
        *
        * @param json_object JsonObject containing the rules to parse.
        *
        * @return vector of rule objects parsed from the json object.
        */
        std::vector<std::shared_ptr<Rule>> ParseRulesFromJsonObject(const std::shared_ptr<JsonObject>& json_object);

        /**
         * @private
         * Generates consequence Event objects from a JsonArray of rule consequences. Called by ParseRulesFromJsonObject
         *
         * @param consequences JsonArray containing a list of consequence definitions.
         *
         * @return vector of Event objects containing the parsed consequence events.
         */
        std::vector<std::shared_ptr<Event>> GenerateConsequenceEvents(const std::shared_ptr<JsonArray>& consequences);

        /**
         * @private
         * Returns the configuration datastore
         * @return Shared pointer to Configuration State DataStore
         */
        std::shared_ptr<DataStoreInterface> GetDataStore();

        /**
         * @private
         * Blocks until the network connection is active or the module is unregistered.
         * @return true if successful
         */
        bool WaitForNetworkConnection(const std::shared_ptr<SystemInfoServiceInterface>& configuration);

        /**
         * @private
         * This module's current configuration
         */
        std::shared_ptr<ConfigurationData> current_config_;

        /**
         * @private
         * Application defined configuration applied over the current_config_
         */
        std::shared_ptr<ConfigurationData> overridden_config_;

        /**
         * @private
         * For queueing the configuration request identity event.
         */
        std::deque<std::shared_ptr<Event>> getsdkids_event_queue_;

        /**
         * @private
         * @brief Generate an environment-aware version of configuration event data from a raw version
         *
         * @param config_data a raw representation of configuration, containing keys and values for all environments
         * @return a new EventData object with only key-values that are applicable in the current build environment
         */
        std::shared_ptr<EventData> GetEnvironmentAwareEventData(const std::shared_ptr<EventData>& config_data);

        /**
         * @private
         * @brief Returns the correct key from configuration json based on the build environment and base key
         *
         * For configuration, the base_key will always be the name of the production configuration value. e.g. :
         * - Production Key  -  myKeyName
         * - Staging Key     -  __stage__myKeyName
         * - Development Key -  __dev__myKeyName
         *
         * @param base_key the production key name to use as the base for the result
         * @param environment the value from build.environment in the configuration json provided by Launch
         * @return a string representing the correct key to use given the provided environment
         */
        std::string GetKeyForEnvironment(const std::string& base_key, const std::string& environment);

        /**
         * @private
         * @brief Returns a copy of raw_map with the overriding keys made environmentally correct
         *
         * For example, if the input is "analytics.rsids":"newrsids", and the value in "build.environment" is "dev",
         * the resulting map would have "__dev__analytics.rsids":"newrsids"
         *
         * Note - if an existing custom configuration matching the build environment does not exist for the
         * provided key, it be returned unchanged
         *
         * If there is no existing current configuration yet, raw_map will be returned
         *
         * @param raw_map map of configuration property key-value pairs
         * @return a new map with environment-specific keys
         */
        std::map<std::string, std::shared_ptr<Variant>> GetEnvironmentAwareOverriddenConfig(
                            const std::map<std::string, std::shared_ptr<Variant>>& raw_map);

        /**
         * @private
         * Mutex for synchronization of current_config_ and overridden_config_
         *
         * IMPORTANT: Be very very careful when calling external functions
         * while holding mutex_, especially if those functions acquire
         * mutexes. Failure to do this can result in hard-to-reproduce
         * deadlocks.
         */
        std::mutex mutex_;

        /**
         * @private
         * The executor for rules downloading, so it will not happen on the configuration module's thread
         */
        std::shared_ptr<TaskExecutorInterface>  rules_download_executor_;

    };
}

#endif /* ADOBEMOBILE_CONFIGURATION_CONFIGURATION_H */
