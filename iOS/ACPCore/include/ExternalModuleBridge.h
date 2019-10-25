/*
Copyright 2018 Adobe. All rights reserved.
This file is licensed to you under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License. You may obtain a copy
of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS
OF ANY KIND, either express or implied. See the License for the specific language
governing permissions and limitations under the License.
*/

#ifndef ADOBEMOBILE_EXTERNALMODULE_EXTERNALMODULEBRIDGE_H
#define ADOBEMOBILE_EXTERNALMODULE_EXTERNALMODULEBRIDGE_H

/**
 * @brief This header contains shared methods used for bridging module code between C++ and Obj-C.
 *
 */
namespace AdobeMarketingMobile {

    class Event;
    class JsonUtilityServiceInterface;

    /*
     * @brief This is a list of the errors returned to external modules from the core code.
     */
    namespace ErrorCodes {
        constexpr static const char* EXT_MODULE_UNEXPECTED_ERROR = "external_module.unexpected";
        constexpr static const char* EXT_MODULE_BAD_NAME = "external_module.bad_module_name";
        constexpr static const char* EXT_MODULE_DUP_NAME = "external_module.dup_module_name";
        constexpr static const char* EXT_MODULE_EVENT_TYPE_NOT_SUPPORTED = "external_module.event_type_not_supported";
        constexpr static const char* EXT_MODULE_EVENT_SOURCE_NOT_SUPPORTED = "external_module.event_source_not_supported";
        constexpr static const char* EXT_MODULE_EVENT_DATA_NOT_SUPPORTED = "external_module.event_data_not_supported";
        constexpr static const char* EXT_MODULE_EVENT_NULL = "external_module.event_was_null";
    }

    std::shared_ptr<Event> CreateBroadcastEvent(const std::shared_ptr<JsonUtilityServiceInterface> json_utility_service,
            const std::string& event_name,
            const std::string& event_type,
            const std::string& event_source,
            const std::string& event_data);

    std::string GetEventTypeAsString(const std::shared_ptr<Event>& event);

    std::string GetEventSourceAsString(const std::shared_ptr<Event>& event);

    std::string GetEventDataAsString(const std::shared_ptr<Event>& event,
                                     const std::shared_ptr<JsonUtilityServiceInterface> json_utility_service);

    std::string GetEventUniqueIdentifierAsString(const std::shared_ptr<Event>& event);

} // AdobeMarketingMobile namespace

#endif /* ADOBEMOBILE_EXTERNALMODULE_EXTERNALMODULEBRIDGE_H */
