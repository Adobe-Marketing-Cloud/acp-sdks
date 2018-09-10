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

namespace AdobeMarketingMobile {
    class ConfigurationData;
    class ConfigurationDownloader;
    class ConfigurationDispatcherConfigurationRequestContent;
    class ConfigurationDispatcherConfigurationResponseContent;

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
    public:

        // Configuration storage keys
        static const std::string CONFIGURATION_URL_BASE;        ///< Base URL of remote configuration
        static const std::string
        CONFIG_BUNDLED_FILE_NAME;      ///< Filename of Adobe Mobile SDK configuration bundled with application
        static const std::string CONFIG_MANIFEST_APPID_KEY;     ///< Manifest property key for App ID from System Info Service
        static const std::string DATASTORE_KEY;                 ///< Local Storage Service Datastore key
        static const std::string
        PERSISTED_OVERRIDDEN_CONFIG;   ///< Overridden configuration key in Local Storage Service Datastore
        static const std::string PERSISTED_APPID;               ///< App ID key in Local Storage Service Datastore
        static const std::string LOG_PREFIX;                    ///< Prefix for all logging messages
        static const std::string CACHE_FOLDER;                  ///< Cache sub folder for config data

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
         * @param is_update         if set to true, will try to update an existing shared state
         */
        virtual void ConfigureWithJsonString(const std::string& json_config_string,
                                             const std::shared_ptr<Event>& event,
                                             const bool is_update);

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
         * Returns the configuration datastore
         * @return Shared pointer to Configuration State DataStore
         */
        std::shared_ptr<DataStoreInterface> GetDataStore();

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
         * Mutex for synchronization of current_config_ and overridden_config_
         *
         * IMPORTANT: Be very very careful when calling external functions
         * while holding mutex_, especially if those functions acquire
         * mutexes. Failure to do this can result in hard-to-reproduce
         * deadlocks.
         */
        std::mutex mutex_;

    };
}

#endif /* ADOBEMOBILE_CONFIGURATION_CONFIGURATION_H */
