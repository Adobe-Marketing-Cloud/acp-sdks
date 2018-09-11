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

#ifndef ADOBEMOBILE_RULESENGINE_RULECONSEQUENCE_H
#define ADOBEMOBILE_RULESENGINE_RULECONSEQUENCE_H

#include <string>
#include <map>
#include <vector>
#include "Common.h"
#include "Object.h"

namespace AdobeMarketingMobile {
    class JsonUtilityServiceInterface;
    class JsonObject;
    class EventData;
    class Variant;
    class JsonObject;
    class JsonArray;

    /**
     * @class RuleConsequence
     * This class is a base class representing a generic rule consequence.
     */
    class RuleConsequence : public Object {
    public:


        /**
         * Parse the supplied json object and instantiate the concrete consequence class.
         *
         * @param consequence_json  The json object for the consequence.
         *
         * @return A RuleConsequence instance. Could be null if the consequence type in the json is not supported, or due to a json
         * error.
         *
         * @throws when the json format is not correct.
         */
        static std::shared_ptr<RuleConsequence> ConsequenceFromJson(const std::shared_ptr<JsonObject>& consequence_json);

        /**
         * Creates an Map containing the consequence information.
         * <p>
         * The Map contains the following information about the consequence.
         * <ul>
         *     <li> The id in key EventDataKeys#RulesEngine#CONSEQUENCE_ID. </li>
         *     <li> The consequence_type in key EventDataKeys#RulesEngine#CONSEQUENCE_TYPE. </li>
         *     <li> The detail in key EventDataKeys#RulesEngine#CONSEQUENCE_DETAIL. </li>
         *     <li> The provided asset_path in key EventDataKeys#RulesEngine#CONSEQUENCE_ASSETS_PATH. </li>
         * </ul>
         *
         * @param asset_path A valid String asset path for the consequence
         * @return Map representing a consequence
         */
        std::map<std::string, std::shared_ptr<Variant>> GenerateConsequenceMap(const std::string& asset_path);

        /**
         * Returns {@link EventData} populated with the data the Consequence would like to broadcast to the Core. The data
         * should be sufficient for the Core to perform the requested consequences. Assume that core will expand
         * any tokens required.
         *
         * @return An instance of EventData.
         *
         * @see EventDataKeys.RulesEngine
         */
        ADOBE_VIRTUAL_FOR_TESTS std::shared_ptr<EventData> GenerateEventData();

        /**
         * Convert and flatten JsonObject into a Variant map
         * @param json_object The JsonObject
         * @return the Variant map
         */
        static std::map<std::string, std::shared_ptr<Variant>> ParseJsonObjectIntoMap(const std::shared_ptr<JsonObject>&
                json_object);
        /**
         * Convert and flatten JsonArray into a string map
         * @param json_array The JsonArray
         * @return the string map
         */
        static std::vector<std::shared_ptr<Variant>> ParseJsonArrayIntoList(const std::shared_ptr<JsonArray>& json_array);

        /**
         * @return the map with consequence detail
         */
        std::map<std::string, std::shared_ptr<Variant>> GetConsequenceDetail();

        /**
         * @return the string consequence id
         */
        std::string GetConsequenceId();

    private:
        std::string id_;
        std::string type_;
        std::map<std::string, std::shared_ptr<Variant>> detail_;
    };
}

#endif /* ADOBEMOBILE_RULESENGINE_RULECONSEQUENCE_H */
