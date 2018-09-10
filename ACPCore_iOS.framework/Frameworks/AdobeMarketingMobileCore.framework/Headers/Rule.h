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

#ifndef ADOBEMOBILE_RULESENGINE_RULE_H
#define ADOBEMOBILE_RULESENGINE_RULE_H

#include <map>
#include <string>
#include <vector>
#include "Common.h"
#include "Object.h"

namespace AdobeMarketingMobile {
    class RuleCondition;
    class RuleTokenParser;
    class Event;

    /**
     * @class Rule
     *
     * This class is the concrete rule implementation that encapsulates the rule conditions and consequences for each rule.
     *
     * This class holds all the necessary component instances to represent a rule in memory.
     */
    class Rule : public Object {

    public:

        /**
         * Creates an instance of a Rule.
         *
         * @param condition a RuleCondition object describing the conditional requirements of this rule.
         * @param consequenceEvents a vector of Event objects to be published when the rule conditions are met.
         */
        explicit Rule(const std::shared_ptr<RuleCondition>& condition,
                      const std::vector<std::shared_ptr<Event>>& consequenceEvents);

        /**
         * Evaluate the rule based on the condition data input.
         *
         * For example, consider the rule is configured with a matcher ("key1 = value1").
         * In this case, if the condition data contains a KV pair {"key", "value1"}, then this
         * function will evaluate to true.
         *
         * @param rule_token_parser RuleTokenParser will be run through the evaluation matchers.
         * @param event Event to be evaluated with the rule
         * @return True, if the KV pairs contain data that match the rule matchers as configured.
         */
        ADOBE_VIRTUAL_FOR_TESTS
        bool EvaluateCondition(const std::shared_ptr<RuleTokenParser>& rule_token_parser,
                               const std::shared_ptr<Event>& event) const;

        /**
         * Get all consequence events associated for the rule.
         * @returns a vector of Event objects for this rule.
         */
        ADOBE_VIRTUAL_FOR_TESTS
        const std::vector<std::shared_ptr<Event>>& GetConsequenceEvents() const;

        /**
         * @see ObjectInterface::ToStringImpl()
         */
        std::string ToStringImpl(const ToStringOptions& options) const override;

    protected:
        Rule() {}; // for mocking :(

    private:

        static const std::string RULE_JSON_CONDITIONS_KEY;
        static const std::string RULE_JSON_CONSEQUENCES_KEY;

        std::vector<std::shared_ptr<Event>> consequenceEvents_; ///< Events to publish when this rule evaluates to true
        std::shared_ptr<RuleCondition> condition_; ///< the conditions which this rule applies (non-null)

    };
}

#endif /* ADOBEMOBILE_RULESENGINE_RULE_H */
