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
         * @param platform_services_factory_function - the platform services factory function
         * @param event_hub - the event hub to use (for mocking). If `nullptr`, a new EventHub instance is created and
         *                    registers all required modules. If passing an EventHub instance, no modules are
         *                    registered.
         *
         * @note Make sure to cleanup after the returned Core by calling Dispose().
         *
         * @returns a new Core with the given platform services.
         */
        static std::shared_ptr<Core> Create(const std::function<std::shared_ptr<PlatformServicesInterface>()>&
                                            platform_services_factory_function,
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
         * @brief Start the Core processing. This should be called after extensions have been registered.
         *
         * @param completion_callback A callback called after the Core has been started.
         */
        void Start(std::function<void()> completion_callback);

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

        /**
         * @brief Clones the provided {@code event} and dispatches it through the {@code EventHub}.
         *
         * @param event provided {@link Event} from the public API
         * @param error_callback callback to return {@link SdkError} if an error occurs
         */
        void DispatchEvent(const std::shared_ptr<AdobeMarketingMobile::Event>& event,
                           std::function<void(SdkError&)> error_callback);

        /**
         * @brief This method will be used when the provided {@code Event} is used as a trigger and a response event is expected in return.
         * The returned event needs to be sent using {@code dispatchResponseEvent} method
         * <p>
         * Clones the provided {@code event}, registers an {@code OneTimeListener} for the response and dispatches it through the
         * {@code EventHub}. Returns an {@code ExtensionError} if the event is null or the response callback is null.
         *
         * @param event provided {@link Event} from the public API
         * @param response_callback If not {@code nullptr}, called with event received by the {@link OneTimeListener}
         * @param error_callback If not {@code nullptr}, called with {@link SdkError} if an error occurs
         * @see #DispatchResponseEvent
         */
        void DispatchEventWithResponseCallback(const std::shared_ptr<AdobeMarketingMobile::Event>& event,
                                               std::function<void(const std::shared_ptr<AdobeMarketingMobile::Event>&)> response_callback,
                                               std::function<void(SdkError&)> error_callback);

        /**
         * @brief Dispatches a response event for a paired event that was sent to {@code dispatchEventWithResponseCallback}
         * or received by an extension listener {@code hear} method.
         * <p>
         * Clones the provided {@code event}, registers an {@code OneTimeListener} for the response and dispatches it through the
         * {@code EventHub}. Returns an {@code ExtensionError} if the event is null or the response callback is null.
         *
         * @param response_event provided {@link Event} from the public API
         * @param response_callback If not {@code nullptr}, called with event received by the {@link OneTimeListener}
         * @param request_event The {@code Event} that this response_event is being sent in response to.
         * @see #DispatchEventWithResponseCallback
         */
        void DispatchResponseEvent(const std::shared_ptr<AdobeMarketingMobile::Event>& response_event,
                                   const std::shared_ptr<AdobeMarketingMobile::Event>& request_event,
                                   std::function<void(SdkError&)> error_callback);

        ///@}

        /**
         * @name Generic Methods
         */
        ///@{

        /**
         * @brief Create collect PII event, which is listened by Rules Engine module to determine if the data
         * matches any PII request.
         *
         * @param data the PII data to be collected, which will be used in Rules Engine comparison and request token replacement.
         */
        void CollectPii(const std::map<std::string, std::string>& data);

        /**
         * @brief Dispatches an event to pause/stop a lifecycle session
         */
        void LifecyclePause();

        /**
         * @brief Dispatches an event to resume/start a lifecycle session
         *
         * @param additional_context_data context data provided through the public API
         */
        void LifecycleStart(const std::map<std::string, std::string>& additional_context_data);

        /**
         * @brief Sets the advertising identifier in the SDK. The id will be sent in lifecycle if it has been set
         * in the SDK.
         *
         * It can also be accessed in Signals (Postbacks).
         *
         * @param ad_id the advertising idenifier string.
         */
        void SetAdvertisingIdentifier(const std::string& ad_id);

        /**
         * @brief Sets the device token for push notifications.
         *
         * @param registration_id push token that needs to be set.
         */
        void SetPushIdentifier(const std::string& registration_id);

        /**
         * @brief Initiates a track action/state request event.
         *
         * @param analytics_data EventData containing analytics track data
         */
        void Track(const std::shared_ptr<EventData>& analytics_data) const;

        /**
         * @brief Dispatches an event with generic data collected from OS level.
         *
         * @param data_map contains deepLink, push and/or local notifications information.
         */
        void CollectData(const std::map<std::string, std::shared_ptr<Variant>>& data_map) const;

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
        void Init(const std::function<std::shared_ptr<PlatformServicesInterface>()>& platform_services_factory_function,
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

