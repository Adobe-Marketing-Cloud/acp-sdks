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

#ifndef ADOBEMOBILE_CORE_EVENTSOURCE_H
#define ADOBEMOBILE_CORE_EVENTSOURCE_H

#include <sstream>
#include <string>
#include <map>
#include <mutex>
#include "Object.h"

namespace AdobeMarketingMobile {

    class ToStringOptions;

    /**
     * EventSource encapsulates the source of an Event.
     */
    class EventSource : public Object {
    public:
        static const std::shared_ptr<EventSource> NONE;
        static const std::shared_ptr<EventSource> OS;
        static const std::shared_ptr<EventSource> REQUEST_CONTENT;
        static const std::shared_ptr<EventSource> REQUEST_IDENTITY;
        static const std::shared_ptr<EventSource> REQUEST_PROFILE;
        static const std::shared_ptr<EventSource> REQUEST_RESET;
        static const std::shared_ptr<EventSource> RESPONSE_CONTENT;
        static const std::shared_ptr<EventSource> RESPONSE_IDENTITY;
        static const std::shared_ptr<EventSource> RESPONSE_PROFILE;
        static const std::shared_ptr<EventSource> SHARED_STATE;
        static const std::shared_ptr<EventSource> BOOTED;
        static const std::shared_ptr<EventSource> WILDCARD;

        /*
         * @return Return prefix used for all Adobe event types
         */
        static std::string GetAdobePrefix();

        /*
         * @brief Return source if found in known sources, otherwise add new source to the map and return.
         * @param source_name the name of the EventSource to return
         * @return an EventSource from the known_sources_ table
         */
        static std::shared_ptr<EventSource> Get(const std::string& source_name);

        /**
         * @returns a string representation of this
         */
        const std::string& GetName();

    protected:
        explicit EventSource(const std::string& source_name);

    private:
        std::string name_;      ///< underlying string holding the name of the EventSource
    };

    /**
     * @see StringUtils::ToString()
     */
    void ToStringImpl(std::ostream& the_stream, const std::shared_ptr<EventSource>& value, const ToStringOptions& options);

}

#endif //ADOBEMOBILE_CORE_EVENTSOURCE_H
