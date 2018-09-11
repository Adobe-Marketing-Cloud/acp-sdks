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
 **************************************************************************/

#ifndef ADOBEMOBILE_RULESENGINE_RULETOKENPARSER_H
#define ADOBEMOBILE_RULESENGINE_RULETOKENPARSER_H

#include <string>
#include <vector>
#include "Object.h"

namespace AdobeMarketingMobile {
    class EventHub;
    class RulesEngine;
    class PlatformServicesInterface;
    class Event;
    class Variant;
    /**
     * @class RuleTokenParser
     *
     * The V5 SDK should support token expansions on the static endpoint, to allow for injection of properties, prefixes replacement.
     *
     */

    class RuleTokenParser : public Object {
        friend class EventHub;
    public:

        // ========================================================
        // Constructor
        // ========================================================

        /**
         * RuleTokenParser Constructor
         *
         * @param parent_hub parent  EventHub module instance
         */
        explicit RuleTokenParser(const std::shared_ptr<EventHub>& parent_hub,
                                 const std::shared_ptr<PlatformServicesInterface>& platform_services);

        /**
         * Sets triggering Event instance to be used by this RuleTokenParser.
         *
         * @param event triggering  Event instance
         */
        void SetEvent(const std::shared_ptr<Event>& event);

        /**
         * Returns the value for the key provided as input.
         * <p>
         * If the key is a special key recognized by SDK, the value is determined based on incoming Event,
         * or EventHub#ModuleSharedStates data. Otherwise the key is searched in the current Event's Eventdata
         * and the corresponding value is returned.
         *
         * @param key std::string containing the key whose value needs to be determined
         * @param event triggering Event instance
         *
         * @return Variant containing value to be substituted for the key
         */
        std::shared_ptr<Variant> ExpandKey(const std::string& key, const std::shared_ptr<Event>& event);

        /**
         * Finds and expands the tokens in the sourceString.
         * <p>
         * The token format is as follows {@literal {%key%}}, valid characters for key include [a-zA-Z0-9~_.]
         * <p>
         * If the token contains special key recognized by SDK, the value is determined based on incoming  Event,
         * or  EventHub#ModuleSharedStates data. Otherwise the key contained in the token is searched in the current Event's
         * data and the corresponding value is used.
         *
         * @param source_string input  std::string containing tokens to be replaced
         * @param event triggering  Event instance
         *
         * @return std::string containing source_string with the valid tokens replaced with the corresponding values
         */
        std::string ExpandTokensForString(const std::string& source_string, const std::shared_ptr<Event>& event);

    private:
        // ========================================================
        // private methods
        // ========================================================

        /**
         * Returns the value for shared state key specified by the key.
         * <p>
         * The key is provided in the format {@literal ~state.valid_shared_state_name/key}
         * For example: {@literal ~state.com.adobe.marketing.mobile.Identity/mid}
         *
         * @param key  std::string containing the key to search for in  EventHub#ModuleSharedStates
         *
         * @return Variant containing the value for the shared state key if valid, null otherwise
         */
        std::shared_ptr<Variant> GetSharedStateKey(const std::string& key);

        /**
         * Extracts the key from passed token.
         * <p>
         * For example, key extracted from a token of the given format {@literal {%myKey%}} shall be myKey
         *
         * @param token  std::string containing the token
         * @param url_encode true if token requires url_encode
         *
         * @return std::string containing the key in the passed token
         */
        std::string GetKeyFromToken(const std::string& token, bool url_encode = false);


        /**
         * Finds and returns all the valid tokens in the provided input.
         * <p>
         * A valid token follows the regex {@literal {%[a-zA-Z0-9_~.]*?%}}
         *
         * @param input the input  String containing tokens to be parsed
         *
         * @return std::vector<std::string> of valid tokens contained in the input string
         */
        std::vector<std::string> FindTokens(const std::string& input);

        // ========================================================
        // package-protected methods
        // ========================================================

        /**
         * Returns the event type from the triggering event.
         *
         * @return  std::string containing the event type name
         * @see EventType
         */
        std::string GetEventType() const;

        /**
         * Returns the event source from the triggering event.
         *
         * @return  std::string containing the event source name
         * @see EventSource
         */
        std::string GetEventSource() const;

        /**
         * Returns the current device time in epoch format (seconds since epoch).
         *
         * @return  std::string value of the number of seconds since epoch
         * @see TimeUtil#getUnixTime()
         */
        std::string GetTimestamp();

        /**
         * Returns the current SDK version string.
         *
         * @return  std::string indicating the current version of SDK
         * @see SystemInfoService#getSdkVersion()
         */
        std::string GetSdkVersion();

        /**
         * Generates and returns a random number to be used for cache-busting purposes.
         *
         * @return  std::string value of the random number
         */
        std::string GetCachebust();

        /**
         * Returns a std::string containing all data in the triggering Event object encoded in url format.
         *
         * @return  std::string containing url encoded key-value pairs in  Event data
         */
        std::string GetAllUrl();

        /**
         * Returns a std::string containing all data in the triggering Event object encoded in json format.
         *
         * @return  std::string containing json data
         */
        std::string GetAllJson();

        /**
         * Returns value for the key stored in module shared state with name sharedStateName.
         * <p>
         * This method invokes  Module#GetSharedEventState(std::string, Event) to get the shared state key.
         *
         * @param shared_state_name std::string containing name of the module shared state
         * @param key std::string containing name of the key in the module shared state
         *
         * @return Variant containing the value for given shared state key
         */
        std::shared_ptr<Variant> GetSharedStateKey(const std::string& shared_state_name, const std::string& key);

    private:
        /**
         * @brief Variant containing a mapping of rule condition special key types to their getter
         */
        std::shared_ptr<Variant> ReturnKeyType(const std::string& key);

        /**
         * Find all the occurrance of a string pattern inside of the input string and replace them in place.
         *
         * @param data the input std::string containing keywords
         * @param to_search the search pattern
         * @param replace_str the replacement to the matched pattern
         */
        void FindAndReplaceAll(std::string& data, const std::string& to_search, const std::string& replace_str);

    private:
        static const int32_t RANDOM_INT_BOUNDARY;
        static const std::string KEY_PREFIX;
        static const std::string SHARED_STATE_KEY_DELIMITER;
        static const int32_t MIN_TOKEN_LEN;
        static const std::string KEY_EVENT_TYPE;
        static const std::string KEY_EVENT_SOURCE;
        static const std::string KEY_TIMESTAMP_UNIX;
        static const std::string KEY_SDK_VERSION;
        static const std::string KEY_CACHEBUST;
        static const std::string KEY_ALL_URL;
        static const std::string KEY_ALL_JSON;
        static const std::string KEY_SHARED_STATE;
        static const std::string KEY_URL_ENCODE;
        static const std::string KEY_URL_ENCODE_PREFIX;
        static const std::string KEY_URL_ENCODE_SUFFIX;
        static const unsigned long MIN_URL_ENC_TOKEN_LEN;

        std::weak_ptr<EventHub> parent_hub_;    ///< parent module to get shared event data
        std::weak_ptr<PlatformServicesInterface> platform_services_;  ///< platform services provide access to sdk version
        std::shared_ptr<Event> event_;  ///< event associated with the rule token parser

    };
}

#endif /* ADOBEMOBILE_RULESENGINE_RULETOKENPARSER_H */
