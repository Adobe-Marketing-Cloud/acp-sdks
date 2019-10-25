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
