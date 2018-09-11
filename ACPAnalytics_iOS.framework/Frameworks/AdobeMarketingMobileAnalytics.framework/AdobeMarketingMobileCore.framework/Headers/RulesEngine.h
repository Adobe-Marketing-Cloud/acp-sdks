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

    public:

        static const std::string LOG_PREFIX;
        /**
         * Create a new instance of a RulesEngine Module.
         */
        RulesEngine(const std::shared_ptr<EventHub>& parent_hub,
                    const std::shared_ptr<PlatformServicesInterface>& platform_services);

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
    };
}
#endif /* ADOBEMOBILE_RULESENGINE_RULESENGINE_H */
