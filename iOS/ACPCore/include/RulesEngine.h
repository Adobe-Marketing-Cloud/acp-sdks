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

#ifndef ADOBEMOBILE_RULESENGINE_RULESENGINE_H
#define ADOBEMOBILE_RULESENGINE_RULESENGINE_H

#include <locale>
#include <string>
#include <vector>
#include <map>
#include <mutex>
#include "InternalModule.h"

namespace AdobeMarketingMobile {
    class JsonUtilityServiceInterface;
    class FileSystemServiceInterface;
    class RemoteFileManagerServiceInterface;
    class CryptoServiceInterface;
    class CompressedFileServiceInterface;
    class Rule;
    class RuleConsequence;
    class RulesConfiguration;
    class RulesDownloader;
    class RulesDispatcherRulesResponseContent;
    class RulesEngineState;
    class Variant;
    class RuleTokenParser;

    /**
     * @class RulesEngine
     * RulesEngine module is responsible for evaluation of configured rules upon receiving a specific trigger event,
     * and if a rule evaluates to true, then perform the associated rule consequence.
     *
     * The module downloads, parses and stores the concrete rule implementations in-memory for evaluation when a trigger event is received.
     */
    class RulesEngine: public Object {
        friend class EventHub;
        friend class RulesEngineMethods;

    public:

        static const std::string LOG_PREFIX;
        /**
         * Create a new instance of a RulesEngine Module.
         */
        RulesEngine(const std::shared_ptr<EventHub>& parent_hub,
                    const std::function<std::shared_ptr<PlatformServicesInterface>()>& platform_services_factory_function);

        /**
         * Add a rule for the given module
         *
         * @param module module to add rule to (needed for RemoveRulesForModule to work)
         * @param rule rule object to add for the given module
         */
        ADOBE_VIRTUAL_FOR_TESTS void AddRule(const std::shared_ptr<Module>& module, const std::shared_ptr<Rule>& rule);

        /**
         * Remove all rules for the given module
         *
         * @param module module to remove all rules for
         */
        ADOBE_VIRTUAL_FOR_TESTS void RemoveRulesForModule(const std::shared_ptr<Module>& module);

        /**
         * Evaluate the current rules against the shared states the module is aware of, along with any additional data
         * that may have been provided.
         * Rules that belong to the eventType passed in along with the rules that belong to RuleEventType::ANY
         * are evaluated for matches.
         *
         * @param event triggering Event to be processed and evaluated by the rules
         */
        ADOBE_VIRTUAL_FOR_TESTS
        std::vector<std::shared_ptr<Event>> ProcessRules(const std::shared_ptr<Event>& event);

    private:

        /**
         * Returns the original map with tokens (if any) expanded with the appropriate values.
         *
         * If the map contains a map or a list then this function will recursively expand tokens within them.
         * If the map contains any other data types apart from primitive data type then it will be returned as is.
         *
         * @param map_with_tokens The map with more zero or more tokens
         * @param event The Event that will be used to expand tokens
         * @return A map with all the tokens expanded
         */
        ADOBE_VIRTUAL_FOR_TESTS std::map<std::string, std::shared_ptr<Variant>> GetTokenExpandedMap(const
                std::map<std::string, std::shared_ptr<Variant>>& map_with_tokens,
                const std::shared_ptr<Event> event);

        /**
         * Returns the original list with tokens (if any) expanded with the appropriate values.
         *
         * If the list contains a map or a list then this function will recursively expand tokens within them.
         * If the list contains any other Object apart from primitive data type containers, or collections, then it will be returned as is.
         *
         * @param list_with_tokens The list with more zero or more tokens
         * @param event The Event that will be used to expand tokens
         * @return A list with all the tokens expanded
         */
        ADOBE_VIRTUAL_FOR_TESTS std::vector<std::shared_ptr<Variant>> GetTokenExpandedList(const
                std::vector<std::shared_ptr<Variant>> list_with_tokens,
                const std::shared_ptr<Event> event);

        std::shared_ptr<RuleTokenParser> rule_token_parser_;

        // governs access to rules_module_map_
        std::mutex rules_mutex_;
        // maintains the list of rules registered, attached to the module that registered them
        std::map<std::shared_ptr<Module>, std::vector<std::shared_ptr<Rule>>> rule_module_map_;

    public:

        /**
         *
         * Set the rules for the specific module with a new set of rules. This API is meant to replace the RegisterRule, which can only
         * add rules one by one.
         *
         * @param module module to add rule to
         * @param rules_vector rules set to be used for the given module
         */
        ADOBE_VIRTUAL_FOR_TESTS void ReplaceRulesForModule(const std::shared_ptr<Module>& module,
                const std::vector<std::shared_ptr<Rule>> rules_vector);

    private:  // << new private section because newly introduced virtual methods must be declared at end of class
        /**
         * @brief Adds the eventData from the detail of consequence_event to EventData of triggering_event
         *
         * This method supports the Attach Data Consequence. By default, it will simply attach any of
         * the data from the consequence to the triggering Event's EventData. If there is a conflict in keys,
         * the value in triggering_event's EventData will have priority.
         *
         * @param consequence_event An Event that has a map<string, Variant> in its EventData that matches
         * the consequence definition for its type. See
         * https://wiki.corp.adobe.com/pages/viewpage.action?spaceKey=ADMSMobile&title=Definition+of+Rules#DefinitionofRules-ConsequenceTypes
         * for more information
         * @param triggering_event The Event for which conditions have passed, triggering the consequence_event to be processed
         */
        ADOBE_VIRTUAL_FOR_TESTS void ProcessAttachDataConsequence(const std::shared_ptr<Event>& consequence_event,
                const std::shared_ptr<Event>& triggering_event);
    };
}
#endif /* ADOBEMOBILE_RULESENGINE_RULESENGINE_H */
