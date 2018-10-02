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

#ifndef ADOBEMOBILE_CORE_EVENTBUILDER_H
#define ADOBEMOBILE_CORE_EVENTBUILDER_H

#include <chrono>
#include <memory>
#include <string>

namespace AdobeMarketingMobile {
    class Event;
    class EventData;
    class EventSource;
    class EventType;

    /**
     * @class EventBuilder
     *
     * @brief EventBuilder is the builder class for creating instances of Event.
     *
     * EventBuilder is a POD class and should only be created on the stack.
     *
     * Example:
     *
     *     std::shared_ptr<Event> event = EventBuilder{"the_event_name",
     *                                                 EventType::ANALYTICS,
     *                                                 EventSource::REQUEST_CONTENT}
     *         .SetPairID("1234") // methods can be chained
     *         .Build(); // when complete, call Build() to construct the Event
     */
    class EventBuilder {
    public:
        /**
         * @brief Constructs the builder for an event with the given name, type, and source.
         */
        explicit EventBuilder(const std::string& name, const std::shared_ptr<EventType>& type,
                              const std::shared_ptr<EventSource>& source);

        /* EventBuilder is not copyable or movable */
        EventBuilder(const EventBuilder&) = delete;
        EventBuilder& operator=(const EventBuilder&) = delete;
        EventBuilder(EventBuilder&&) = delete;
        EventBuilder&& operator=(EventBuilder&&) = delete;

        /**
         * @brief Sets the pair id for the event.
         */
        EventBuilder& SetPairID(const std::string& pairId);

        /**
         * @brief Sets the response pair id for the event.
         */
        EventBuilder& SetResponsePairID(const std::string& responsePairId);

        /**
         * @brief Sets the timestamp for the event.
         * If not explicitly set, the timestamp would be set to the number of milliseconds since Unix Epoch.
         */
        EventBuilder& SetTimestamp(std::chrono::milliseconds timestamp);

        /**
         * @brief Sets the data for the event.
         *
         * For efficiency reasons, the event's data will be set to the instance provided by the `data` argument.
         * Do not modify the `data` instance after passing the instance to `SetData()`
         */
        EventBuilder& SetData(const std::shared_ptr<EventData>& data);

        /**
         * @brief Sets the data for the event to a copy of the given EventData.
         */
        EventBuilder& CopyData(const std::shared_ptr<EventData>& data);

        /**
         * @brief  Sets the number of the event.
         *
         * Most users will not need to call this method directly, as the event number is typically set by the EventHub.
         */
        EventBuilder& SetEventNumber(int32_t number);

        /**
         * @brief Builds the specified event.
         *
         * Calling this method twice will result in an error.
         *
         * @returns the newly created event.
         */
        std::shared_ptr<Event> Build();

    private:
        /**
         * @private
         *
         * Throws an exception if this was already built.
         */
        void ThrowIfAlreadyBuilt();

        std::shared_ptr<Event> event_; ///< @private the underlying event

        bool did_build_; ///<  @private  true iff `Build()` was already called
    };
}

#endif //ADOBEMOBILE_CORE_EVENTBUILDER_H
