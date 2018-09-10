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

#ifndef ADOBEMOBILE_RULESENGINE_RULECONDITION_H
#define ADOBEMOBILE_RULESENGINE_RULECONDITION_H

#include <map>
#include "Object.h"

namespace AdobeMarketingMobile {
    class JsonObject;
    class Matcher;
    class Variant;
    class Event;
    class RuleTokenParser;

    // ================================================================================
    // RuleCondition
    // ================================================================================
    /**
     * Base class for a Rule's condition, which are a set of conditions used to evaluate a rule.
     */
    class RuleCondition : public Object {
    public:
        static const std::string RULE_CONDITION_TYPE_KEY_JSON;
        static const std::string RULE_CONDITION_TYPE_GROUP_JSON;
        static const std::string RULE_CONDITION_TYPE_MATCHER_JSON;
        static const std::string RULE_CONDITION_DEFINITION_KEY_JSON;

        /**
         * Evaluate the condition and return true if the condition holds, with the data that is supplied.
         *
         * @param rule_token_parser The {@link RuleTokenParser} for token expansion.
         * @param event {@link Event} associated with the rule condition
         * @return True, if the condition holds. False otherwise.
         */
        virtual bool Evaluate(const std::shared_ptr<RuleTokenParser>& rule_token_parser,
                              const std::shared_ptr<Event>& event) const = 0;

        /**
         * Instantiate a Rule condition class. The condition types supported are "group" (Condition Group) and "matcher" (Condition Matcher).
         *
         * @param condition_json The json representing the rule condition.
         * @return A {@link RuleCondition} instance.
         *
         * @throws ErrorCodes::JSON_JSONOBJECT_IS_NULL if the JsonObject is nullptr
         * @throws ErrorCodes::JSON_KEY_NOT_FOUND if there is an error reading the json file
         */
        static std::shared_ptr<RuleCondition> RuleConditionFromJson(const std::shared_ptr<JsonObject>& condition_json);

    };

    // ================================================================================
    // RuleConditionGroup
    // ================================================================================
    /**
     * Base class for a group of rule conditions.
     */
    class RuleConditionGroup : public RuleCondition {
    public:
        static const std::string RULE_CONDITIONS_JSON_KEY;
        static const std::string RULE_CONDITION_JSON_DEFINITION_LOGIC;
        static const std::string RULE_CONDITION_JSON_DEFINITION_LOGIC_AND;
        static const std::string RULE_CONDITION_JSON_DEFINITION_LOGIC_OR;

        /**
         * Instantiate a Rule condition group.
         *
         * @param condition_json The JsonObject
         * @return RuleConditionGroup
         * @throws ErrorCodes::JSON_JSONOBJECT_IS_NULL if the JsonObject is nullptr
         * @throws ErrorCodes::JSON_KEY_NOT_FOUND if there is an error reading the json file
         **/
        static std::shared_ptr<RuleConditionGroup> RuleConditionGroupFromJson(
                    const std::shared_ptr<JsonObject>& condition_json);

        /**
         * Retrieve the rule conditions in this group.
         * @return list of RuleConditions in this group
         **/
        const std::vector<std::shared_ptr<RuleCondition>>& GetConditions() const;

    protected:
        RuleConditionGroup(const std::vector<std::shared_ptr<RuleCondition>>& conditions);

        std::vector<std::shared_ptr<RuleCondition>> conditions_;
    };


    // ================================================================================
    // RuleConditionOrGroup
    // ================================================================================
    /**
     * Concrete class for an OR group rule condition.  If any condition in this group evaluates
     * to `true`, then the entire group evaluates to `true`.
     */
    class RuleConditionOrGroup : public RuleConditionGroup {
    public:
        /**
         * Constructs a RuleConditionOrGroup instance.
         * @param conditions the conditions in this RuleConditionOrGroup
         */
        explicit RuleConditionOrGroup(const std::vector<std::shared_ptr<RuleCondition>>& conditions);

        /**
         * Evaluate the \p data against the conditions in this rule condition group.
         * @param rule_token_parser The {@link RuleTokenParser} for token expansion
         * @param event event {@link Event} to be evaluated with the rule
         * @returns true if any condition in this group evaluates to true, false otherwise.
         */
        bool Evaluate(const std::shared_ptr<RuleTokenParser>& rule_token_parser,
                      const std::shared_ptr<Event>& event) const override;

        /**
         * @see ObjectInterface::ToStringImpl()
         */
        std::string ToStringImpl(const ToStringOptions& options) const override;
    };


    // ================================================================================
    // RuleConditionAndGroup
    // ================================================================================
    /**
     * Concrete class for an AND group rule condition. If all conditions in this group evaluate
     * to `true`, then the entire group evaluates to `true`.
     */
    class RuleConditionAndGroup : public RuleConditionGroup {
    public:
        /**
         * Constructs a RuleConditionAndGroup instance.
         * @param conditions the conditions in this RuleConditionAndGroup
         */
        explicit RuleConditionAndGroup(const std::vector<std::shared_ptr<RuleCondition>>& conditions);

        /**
         * Evalute the \p data against the conditions in this rule condition group.
         * @param rule_token_parser The {@link RuleTokenParser} for token expansion.
         * @param event event {@link Event} to be evaluated with the rule
         * @returns true if all conditions in this group evaluate to true, false otherwise.
         */
        bool Evaluate(const std::shared_ptr<RuleTokenParser>& rule_token_parser,
                      const std::shared_ptr<Event>& event) const override;

        /**
         * @see ObjectInterface::ToStringImpl()
         */
        std::string ToStringImpl(const ToStringOptions& options) const override;
    };

    // ================================================================================
    // RuleConditionMatcher
    // ================================================================================
    /**
     * Rule condition matcher class which evaluates a specific rule condition.
     */
    class RuleConditionMatcher : public RuleCondition {
    public:
        /**
         * Constructs a RuleConditionMatcher instance.
         * @param matcher the condition matcher
         */
        explicit RuleConditionMatcher(const std::shared_ptr<Matcher>& matcher);

        /**
         * Create a new RuleConditionMatcher instance from a json file.
         *
         * @param condition_json the JSON file containing the definition of a RuleConditionMatcher
         * @throws ErrorCodes::JSON_JSONOBJECT_IS_NULL if the JsonObject is nullptr
         * @throws ErrorCodes::JSON_KEY_NOT_FOUND if there is an error reading the json file
         */
        static std::shared_ptr<RuleConditionMatcher> RuleConditionMatcherFromJson(const std::shared_ptr<JsonObject>&
                condition_json);

        /**
         * Evaluate \p data against that condition matcher.
         * @param rule_token_parser The {@link RuleTokenParser} for token expansion
         * @param event event {@link Event} to be evaluated with the rule
         * @returns true if \p data validates against the matcher, false otherwise.
         */
        bool Evaluate(const std::shared_ptr<RuleTokenParser>& rule_token_parser,
                      const std::shared_ptr<Event>& event) const override;

        /**
         * @see ObjectInterface::ToStringImpl()
         */
        std::string ToStringImpl(const ToStringOptions& options) const override;

    private:
        std::shared_ptr<Matcher> matcher_;
    };

}

#endif /* ADOBEMOBILE_RULESENGINE_RULECONDITION_H */
