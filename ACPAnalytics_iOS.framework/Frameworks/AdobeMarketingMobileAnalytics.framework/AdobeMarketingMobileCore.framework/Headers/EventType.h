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

#ifndef ADOBEMOBILE_CORE_EVENTTYPE_H
#define ADOBEMOBILE_CORE_EVENTTYPE_H

#include <sstream>
#include <string>
#include <map>
#include <mutex>
#include "Object.h"

namespace AdobeMarketingMobile {

    class ToStringOptions;

    /**
     * EventType encapsulates the source of an Event.
     */
    class EventType : public Object {
    public:
        static const std::shared_ptr<EventType> ACQUISITION;
        static const std::shared_ptr<EventType> ANALYTICS;
        static const std::shared_ptr<EventType> AUDIENCE_MANAGER;
        static const std::shared_ptr<EventType> CONFIGURATION;
        static const std::shared_ptr<EventType> CUSTOM;
        static const std::shared_ptr<EventType> HUB;
        static const std::shared_ptr<EventType> IDENTITY;
        static const std::shared_ptr<EventType> LIFECYCLE;
        static const std::shared_ptr<EventType> LOCATION;
        static const std::shared_ptr<EventType> PII;
        static const std::shared_ptr<EventType> PLACES;
        static const std::shared_ptr<EventType> RULES_ENGINE;
        static const std::shared_ptr<EventType> SIGNAL;
        static const std::shared_ptr<EventType> SYSTEM;
        static const std::shared_ptr<EventType> TARGET;
        static const std::shared_ptr<EventType> USER_PROFILE;
        static const std::shared_ptr<EventType> WILDCARD;

        /*
         * @return Return prefix used for all Adobe event types
         */
        static std::string GetAdobePrefix();

        /*
         * @brief Return type if found in known types, otherwise add new type to the map and return.
         * @param type_name the name of the EventType to return
         * @return an EventType from the known_types_ table
         */
        static std::shared_ptr<EventType> Get(const std::string& type_name);

        /**
         * @returns a string representation of this
         */
        const std::string& GetName();

    protected:
        explicit EventType(const std::string& type_name);

    private:
        std::string name_; ///< @private underlying string holding the name of the EventSource
    };

    /**
     * @see StringUtils::ToString()
     */
    void ToStringImpl(std::ostream& the_stream, const std::shared_ptr<EventType>& value, const ToStringOptions& options);
}

#endif //ADOBEMOBILE_CORE_EVENTTYPE_H
