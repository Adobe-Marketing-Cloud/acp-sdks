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

#ifndef ADOBEMOBILE_CORE_CORE_H
#define ADOBEMOBILE_CORE_CORE_H

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <map>
#include <string>
#include <vector>

#include "Common.h"
#include "Configuration.h"
#include "Core.h"
#include "CryptoServiceInterface.h"
#include "Event.h"
#include "EventBuilder.h"
#include "EventData.h"
#include "EventHub.h"
#include "EventSource.h"
#include "EventType.h"
#include "ExternalModuleInterface.h"
#include "InternalModule.h"
#include "Log.h"
#include "MobilePrivacyStatus.h"
#include "Module.h"
#include "ModuleEventDispatcher.h"
#include "ModuleEventDispatcherBase.h"
#include "ModuleEventListener.h"
#include "ModuleEventListenerBase.h"
#include "ModuleEventProcessor.h"
#include "ModuleEventProcessorBase.h"
#include "Object.h"
#include "ObjectInterface.h"
#include "OneTimeListener.h"
#include "PlatformServicesInterface.h"
#include "RandomUtil.h"
#include "SdkError.h"
#include "StringUtils.h"
#include "Variant.h"
#include "VariantKind.h"

namespace AdobeMarketingMobile {

    /**
     * @class Core
     *
     * @brief Core is the API surface used by the top-level native API.
     *
     * The native API layer instantiates and calls into the Core to implement most API functionality.
     * This design allows the native API layer implementation to mostly consist of bindings to the native language.
     *
     * Internally, the Core takes care of EventHub registration and cleanup.
     */
    class Core : public Object {
    public:
        std::shared_ptr<EventHub> event_hub; ///< the event hub instance

        std::shared_ptr<PlatformServicesInterface> platform_services; ///< the platform services instance

        /**
         * @name Creation and Disposal
         */
        ///@{

        /**
         * @brief Creates the Core.
         *
         * @param platform_services - the platform services to use
         * @param event_hub - the event hub to use (for mocking). If `nullptr`, a new EventHub instance is created and
         *                    registers all required modules. If passing an EventHub instance, no modules are
         *                    registered.
         *
         * @note Make sure to cleanup after the returned Core by calling Dispose().
         *
         * @returns a new Core with the given platform services.
         */
        static std::shared_ptr<Core> Create(const std::shared_ptr<PlatformServicesInterface>& platform_services,
                                            const std::shared_ptr<EventHub>& event_hub = nullptr);

        /**
         * @brief Destructor
         */
        ~Core();

        /**
         * @brief Cleans up after this
         *
         * Calls Dispose with a reasonable default wait time.
         *
         * @see bool Dispose(std::chrono::milliseconds max_wait_duration)
         *
         * @return true if clean up completed before the wait time elapsed.
         */
        bool Dispose();

        /**
         * @brief Cleans up after this
        *
         * Clean up is asynchronous and this call may block for up to `max_wait_duration` for the
         * operation to complete.
         *
         * @param max_wait_duration - the maximum duration to block this call while waiting for cleanup to complete.
         *                            A `0` time indicates that we will return immediately.
         *
         * @return true if clean up completed before the wait time elapsed.
         */
        bool Dispose(std::chrono::milliseconds max_wait_duration);

        ///@}

        /**
         * @name Module Registration
         */
        ///@{

        /**
         * @brief Creates and registers a module of the specified type.
         *
         * `TModule` is the module class to register, must be a subclass of `Module`.
         */
        template<class TModule>
        void RegisterModule();

        ///@}

        /**
         * @name Configuration
         */
        ///@{

        /**
         *  @brief Loads remote configuration specified by given application ID.
         *
         * Configure the SDK by downloading the remote configuration file hosted on Adobe servers
         * specified by the given application ID. The configuration file is cached once downloaded
         * and used in subsequent calls to this API. If the remote file is updated after the first
         * download, the updated file is downloaded and replaces the cached file.
         *
         * On failure to download the remote configuration file, the SDK is configured using the cached
         * file if it exists, or if no cache file exists then the existing configuration remains unchanged.
         *
         * Calls to this API will replace any existing SDK configuration except those set using
         * UpdateConfiguration() or SetPrivacyStatus(). Configuration updates made using UpdateConfiguration()
         * and SetPrivacyStatus() are always applied on top of configuration changes made using this API.
         *
         * @param app_id a unique identifier assigned to the app instance by the Adobe Mobile Services. It is automatically
         *              added to the ADBMobile JSON file when downloaded from the Adobe Mobile Services UI and can be
         *              found in Manage App Settings. A value of empty string has no effect.
         */
        void ConfigureWithAppId(const std::string& app_id) const;

        /**
         * @brief Loads configuration from local file.
         *
         * Configure the SDK by reading a local file containing the JSON configuration.
         *
         * On failure to read the file or parse the JSON contents, the existing configuration remains unchanged.
         *
         * Calls to this API will replace any existing SDK configuration except those set using
         * UpdateConfiguration() or SetPrivacyStatus(). Configuration updates made using UpdateConfiguration()
         * and SetPrivacyStatus() are always applied on top of configuration changes made using this API.
         *
         * @param file_path absolute path to a local configuration file. A value of empty string has no effect.
         */
        void ConfigureWithFileInPath(const std::string& file_path) const;

        /**
         * @brief Update specific configuration parameters.
         *
         * Update the current SDK configuration with specific key/value pairs. Keys not found in the current
         * configuration are added. Configuration updates are preserved and applied over existing or new
         * configurations set by calling ConfigureWithAppId() or ConfigureWithFileInPath().
         *
         * Using nullptr values is allowed and effectively removes the configuration parameter from the
         * current configuration.
         *
         * @param config_map configuration key/value pairs to be updated or added. A value of empty map has no effect.
         * @see EventDataKeys
         */
        void UpdateConfiguration(const std::map<std::string, std::shared_ptr<Variant>>& config_map) const;

        /**
         * @brief Set the Adobe Mobile Privacy status.
         *
         * Sets the MobilePrivacyStatus for this SDK. The set privacy status is preserved
         * and applied over any new configuration changes from calls to ConfigureWithAppId() or ConfigureWithFileInPath().
         *
         * @param privacy_status MobilePrivacyStatus to be set to the SDK
         * @see MobilePrivacyStatus
         * @see UpdateConfiguration()
         */
        void SetPrivacyStatus(MobilePrivacyStatus privacy_status) const;

        /**
         * @brief Get the current Adobe Mobile Privacy Status.
         *
         * Gets the currently configured MobilePrivacyStatus and passes it as a parameter
         * to the given void function.
         *
         * @param callback method invoked with the configured privacy status as a parameter
         * @see MobilePrivacyStatus
         */
        void GetPrivacyStatus(const std::function<void(const MobilePrivacyStatus&)>& callback) const;

        /**
         * Retrieve all identities stored by/known to the SDK in a JSONString format.
         *
         * Dispatches an EventType#CONFIGURATION - EventSource#REQUEST_IDENTITY Event.
         * Returns an empty string if the SDK is unable to retrieve any identifiers.
         *
         * @param callback method which is invoked with all the known identifier in JSONString format
         * @see AdobeCallback
         */
        void GetSDKIdentities(const std::function<void(const std::string& identities)>& callback) const;

        /**
         * @name External Module
         */
        ///@{

        /**
         * @brief Register an external module.
         *
         * @param external_module The interface to the applications external module implementation.
         * @param error_callback A callback called if errors occur during registration.
         */
        void RegisterExternalModule(const std::shared_ptr<ExternalModuleInterface>& external_module,
                                    std::function<void(SdkError&)> error_callback);

        ///@}

        /**
         * @name Rules Engine Module
         */
        ///@{

        /**
         * Called from the platform to force redownload rules.
         * <p>
         * Rules Engine attempts to redownload rules from the already defined url provided in the configuration.
         * Dispatches {@code EventType#RULES_ENGINE} - {@code EventSource.REQUEST_CONTENT} {code Event} to refresh rules.
         */
        void DownloadRules();

        ///@}

    private:
        /**
         * @private
         *
         * Default constructor, part of 2-phase initialization.
         */
        Core();

        /**
         * @private
         *
         * Initializes this, part of 2-phase initialization.
         */
        void Init(const std::shared_ptr<PlatformServicesInterface>& new_platform_services,
                  const std::shared_ptr<EventHub>& new_event_hub);
    };
}

/////////////////////////////////
// template/inline definitions //
/////////////////////////////////
namespace AdobeMarketingMobile {
    template<class TModule>
    void Core::RegisterModule() {
        if (event_hub) {
            event_hub->RegisterModule<TModule>();
        }
    }
}

#endif //ADOBEMOBILE_CORE_CORE_H

