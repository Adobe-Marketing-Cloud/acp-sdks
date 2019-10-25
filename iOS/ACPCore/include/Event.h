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

#ifndef ADOBEMOBILE_CORE_EVENT_H
#define ADOBEMOBILE_CORE_EVENT_H

#include <chrono>
#include <string>
#include "Object.h"
#include "EventType.h"
#include "EventSource.h"

namespace AdobeMarketingMobile {
    class EventMethods;
    class EventBuilder;
    class EventData;

    /**
     * @class Event
     *
     * @brief An Event indicates that something notable happened and includes relevant information about what happened.
     *
     * Creating Events
     * ----------------
     *
     * Events are created using EventBuilder:
     *
     *     auto event = EventBuilder{"the_event_name", EventType::ANALYTICS, EventSource::REQUEST_CONTENT}.Build();
     *
     * Events can also be created via cloning using Event::Copy():
     *
     *     auto event2 = event.Copy();
     *
     * Event Properties
     * ----------------
     * Events carry the following pieces of information:
     * - _Name_ is a descriptive string for an individual event. Primarily used for logging.
     * - _Type_ is an EventType that identifies what happened.
     * - _Source_ is an EventSource that identifies the origin of the event.
     * - _Pairing ID_ is a string that, when set, uniquely identifies this event. A one-time listener can register on this
     *   pairing id for 1:1 communication.
     * - _Response Pairing ID_ is relevant for events that follow a response-request pattern. When set, identifies the
     *   pairing ID that should be used for responses to this event.
     * - _Number_ is an integer sequence number. Used primarily for debugging.
     * - _Data_ is an EventData, an associative map of string keys to values of various types. Used to convey additional
     *   information.
     * - _Timestamp_ is the time at which the event was generated.
     *
     * Dispatching, Processing, and Listening for Events
     * -------------------------------------------------
     * To dispatch events, a module will typically subclass ModuleEventDispatcher and invoke EventHub::Dispatch().
     *
     * To listen for events, a module will typically subclass ModuleEventListener.
     *
     * To process (change) events,  module will typically subclass ModuleEventProcessor.
     */
    class Event : public Object {
    public:
        friend class EventHub;
        friend class EventBuilder;
        friend class EventMethods;

        /**
         * @brief Convenience event for retrieving the oldest shared state
         **/
        static const std::shared_ptr<Event> SHARED_STATE_OLDEST;

        /**
         * @brief Convenience event for retrieving the newest shared state
         **/
        static const std::shared_ptr<Event> SHARED_STATE_NEWEST;

        /**
         * @brief Copies this event.
         * @return a copy of this event
         */
        std::shared_ptr<Event> Copy() const;

        /**
         * @brief Gets the name of this event.
         * @return the name of this event
         */
        const std::string& GetName() const;

        /**
         * @brief Gets the source of this event.
         * @return the source of this event
         */
        const std::shared_ptr<EventSource>& GetEventSource();

        /**
         * @brief Gets the type of this event.
         * @return the type of this event
         */
        const std::shared_ptr<EventType>& GetEventType();

        /**
         * @brief Gets the pairing id of this event.
         * @return the pairing id of this event, or empty string if there is no pairing id
         */
        const std::string& GetPairID() const;

        /**
         * @brief Gets the response pairing id of this event.
         * @return the response pairing id of this event, or empty string if there is no response pairing id
         */
        const std::string& GetResponsePairID() const;

        /**
         * @brief Gets the additional data for this event.
         * @return the data for this event
         */
        const std::shared_ptr<EventData>& GetData();

        /**
         * @brief Gets the timestamp of this event.
         * @return the time at which this event was generated, expressed as milliseconds since the UNIX epoch
         */
        std::chrono::milliseconds GetTimestamp() const; // ms since epoch of std::chrono::steady_clock

        /**
         * @brief Gets the number of this event.
         * @return a sequence number for the event
         */
        int32_t GetEventNumber() const;

        /**
         * @brief Sets the pairing id of this event.
         *
         * Intended for use by EventHub.
         *
         */
        void SetPairID(const std::string& pair_id);

        /**
         * @brief Gets the unique identifier for this event
         * @return the unique identifier for this event
         */
        std::string GetUniqueIdentifier();

        /**
         * @see ObjectInterface::ToStringImpl()
         */
        std::string ToStringImpl(const ToStringOptions& options) const override;

    private:
        /**
         * @private
         * Constructor. Intended for use by EventBuilder.
         */
        explicit Event(const std::string& name, const std::shared_ptr<EventType>& type,
                       const std::shared_ptr<EventSource>& source);

        /**
         * @private
         * Constructor. Only used by creating oldest and latest event constant.
         */
        explicit Event(int32_t event_number);

        /**
         * @brief Sets sequence number for the event.
         *
         * Intended for use by EventHub.
         *
         * @param number - the new event number
         */
        void SetEventNumber(int32_t number);

        std::string name_; ///< @private the name of this event
        std::shared_ptr<EventSource> source_; ///< @private the source of this event
        std::shared_ptr<EventType> type_; ///< @private the type of this event
        std::string pair_id_; ///< @private the pairing id of this event
        std::string response_pair_id_; ///< @private the response pairing id of this event
        std::shared_ptr<EventData> data_; ///< @private the additional data for this event

        /**
         * @private
         * the time at which this event was generated, expressed as milliseconds since the UNIX epoch
         */
        std::chrono::milliseconds timestamp_;

        int32_t event_number_; ///< @private sequence number for the event.

        std::string unique_identifier_; ///< @private the unique identifier for the event
    };
}

#endif //ADOBEMOBILE_CORE_EVENT_H
