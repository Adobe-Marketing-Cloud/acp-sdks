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
 ****************************************************************************/

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

} // AdobeMarketingMobile namespace

#endif /* ADOBEMOBILE_EXTERNALMODULE_EXTERNALMODULEBRIDGE_H */
