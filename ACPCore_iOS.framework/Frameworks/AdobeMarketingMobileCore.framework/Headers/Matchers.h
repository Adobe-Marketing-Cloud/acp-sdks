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

#ifndef ADOBEMOBILE_RULESENGINE_MATCHER_H
#define ADOBEMOBILE_RULESENGINE_MATCHER_H

#include <map>
#include <vector>
#include "Object.h"

namespace AdobeMarketingMobile {
    class JsonObject;
    class Variant;

    /**
     * Base Matcher class. Matcher classes evaluate given values to values mapped to a given key. Derived Matcher
     * classes specialize in the match operation used to evaluate the values.
     */
    class Matcher : public Object {
        friend class RuleConditionMatcher;
    public:

        std::string key; ///< the key to which this Matcher evaluates values against
        std::vector<std::shared_ptr<Variant>> values; ///< the values for this Matcher which will evaluate to true

        /**
         * Creates a Matcher instance based on the given JSON Object.
         * Searches the JSON object for a matcher operator, key, and values and returns a Matcher instance
         * populated with those values. Returns `nullptr` if an error occurs creating the Matcher instance.
         *
         * @param dictionary a JSON object containing the definition for a Matcher instance
         * @returns a new Matcher instance, or `nullptr` if a Matcher could not be created.
         */
        static std::shared_ptr<Matcher> MatcherWithJsonObject(const std::shared_ptr<JsonObject>& dictionary);

    protected:

        /**
         * ctor.
         */
        Matcher() = default;

        /**
         * Searches the JSON object for matcher values and adds them to the given Matcher object.
         * Logs a warning if no values are found.
         *
         * @param dictionary the JSON object containing a matcher values array
         * @param matcher the Matcher instance to add the found values
         * @throws ErrorCodes::JSON_KEY_NOT_FOUND if key is not present.
         */
        static void SetMatcherValuesFromJson(const std::shared_ptr<JsonObject>& dictionary,
                                             const std::shared_ptr<Matcher>& matcher);

        /**
         * Searches the JSON object for a matcher key and adds it to the given Matcher object.
         * Logs a warning if the key is not found or if a JSON error occurs.
         *
         * @param dictionary the JSON object containing the matcher key
         * @param matcher the Matcher instance to add the found key
         */
        static void SetMatcherKeyFromJson(const std::shared_ptr<JsonObject>& dictionary,
                                          const std::shared_ptr<Matcher>& matcher);

        /**
         * Evaluates the given \p value against this Matcher's values for this Matcher type's operation.
         *
         * @param value the value to match
         * @returns true if the value matches against this Matcher's values, false otherwise.
         */
        virtual bool Matches(const std::shared_ptr<Variant>& value) const;

        /**
         * Compares two values as doubles. The given Variant values are converted to doubles before being passed
         * to the given comparison function. Converting the values to doubles allows for comparision between different
         * numeric types and strings.
         *
         * @param value the value to compare
         * @param match the Matcher's value to compare
         * @param compare_func the comparison function
         * @returns true if both values are able to be converted to double types and \p compare_func evaluates to true,
         * false otherwise.
         */
        static bool CompareAsDoubles(const std::shared_ptr<Variant>& value, const std::shared_ptr<Variant>& match,
                                     std::function<bool(const double, const double)> compare_func);

        /**
         * @see ObjectInterface::ToStringImpl()
         */
        std::string ToStringImpl(const ToStringOptions& options) const override;

        /**
         * Helper class to perform common ToString formatting.
         *
         * @param options ToStringOptions used in formatting the result string
         * @param description a simple description for this Matcher
         * @returns a formatted string describing this Matcher
         */
        std::string ToStringImplHelper(const ToStringOptions& options, const std::string& description) const;

    private:

        /**
         * Gets a new Matcher instance of type represented by the given \p type string.
         *
         * @param type a string representation of a Matcher class
         * @returns new Matcher instance of type defined by \p type, or `nullptr` if \p type does not define
         * a valid Matcher class.
         */
        static std::shared_ptr<Matcher> InitializeMatcherTypeDictionary(const std::string& type);

    };

    class MatcherContains : public Matcher {
    public:
        /**
         * @see ObjectInterface::ToStringImpl()
         */
        std::string ToStringImpl(const ToStringOptions& options) const override;
    protected:
        /**
         * Verifies if the given value is contained within any of this Matcher's values.
         * @param value the value to evaluate
         * @returns true if the value is contained within any of this Matcher's values, false otherwise
         */
        bool Matches(const std::shared_ptr<Variant>& value) const override;
    };

    class MatcherEndsWith : public Matcher {
    public:
        /**
         * @see ObjectInterface::ToStringImpl()
         */
        std::string ToStringImpl(const ToStringOptions& options) const override;
    protected:
        /**
         * Verifies if the given value ends with any of this Matcher's \p values.
         * @param value the value to evaluate
         * @returns true if the value ends with any of this Matcher's \p values, false otherwise
         */
        bool Matches(const std::shared_ptr<Variant>& value) const override;
    };

    class MatcherEquals : public Matcher {
    public:
        /**
         * @see ObjectInterface::ToStringImpl()
         */
        std::string ToStringImpl(const ToStringOptions& options) const override;
    protected:
        /**
         * Verifies if the given value is equal to any of this Matcher's \p values.
         * @param value the value to evaluate
         * @returns true if the value is equal to any of this Matcher's \p values, false otherwise
         */
        bool Matches(const std::shared_ptr<Variant>& value) const override;
    };

    class MatcherExists : public Matcher {
    public:
        /**
         * @see ObjectInterface::ToStringImpl()
         */
        std::string ToStringImpl(const ToStringOptions& options) const override;
    protected:
        /**
         * Verifies if this Matcher's \p key exists in any of the given \p maps.
         * @param value the value to evaluate
         * @returns true if this Matcher's \p key exists in any of the given \p maps, false otherwise.
         */
        bool Matches(const std::shared_ptr<Variant>& value) const override;

    };

    class MatcherGreaterThan : public Matcher {
    public:
        /**
         * @see ObjectInterface::ToStringImpl()
         */
        std::string ToStringImpl(const ToStringOptions& options) const override;
    protected:
        /**
         * Verifies if the given value is greater than any of this Matcher's \p values.
         * @param value the value to evaluate
         * @returns true if the value is greater than any of this Matcher's \p values, false otherwise
         */
        bool Matches(const std::shared_ptr<Variant>& value) const override;

    };

    class MatcherGreaterThanOrEqual : public Matcher {
    public:
        /**
         * @see ObjectInterface::ToStringImpl()
         */
        std::string ToStringImpl(const ToStringOptions& options) const override;
    protected:
        /**
         * Verifies if the given value is greater than or equal to any of this Matcher's \p values.
         * @param value the value to evaluate
         * @returns true if the value is greater than or equal to any of this Matcher's \p values, false otherwise
         */
        bool Matches(const std::shared_ptr<Variant>& value) const override;
    };

    class MatcherLessThan : public Matcher {
    public:
        /**
         * @see ObjectInterface::ToStringImpl()
         */
        std::string ToStringImpl(const ToStringOptions& options) const override;
    protected:
        /**
         * Verifies if the given value is less than any of this Matcher's \p values.
         * @param value the value to evaluate
         * @returns true if the value is less than any of this Matcher's \p values, false otherwise
         */
        bool Matches(const std::shared_ptr<Variant>& value) const override;
    };

    class MatcherLessThanOrEqual : public Matcher {
    public:
        /**
         * @see ObjectInterface::ToStringImpl()
         */
        std::string ToStringImpl(const ToStringOptions& options) const override;
    protected:
        /**
         * Verifies if the given value is less than or equal to any of this Matcher's \p values.
         * @param value the value to evaluate
         * @returns true if the value is less than or equal to any of this Matcher's \p values, false otherwise
         */
        bool Matches(const std::shared_ptr<Variant>& value) const override;
    };

    class MatcherNotContains : public MatcherContains {
    public:
        /**
         * @see ObjectInterface::ToStringImpl()
         */
        std::string ToStringImpl(const ToStringOptions& options) const override;
    protected:
        /**
         * Verifies if the given value is not contained within any of this Matcher's \p values.
         * @param value the value to evaluate
         * @returns true if the value is not contained within any of this Matcher's \p values, false otherwise
         */
        bool Matches(const std::shared_ptr<Variant>& value) const override;
    };

    class MatcherNotEquals : public MatcherEquals {
    public:
        /**
         * @see ObjectInterface::ToStringImpl()
         */
        std::string ToStringImpl(const ToStringOptions& options) const override;
    protected:
        /**
         * Verifies if the given value does not equal any of this Matcher's \p values.
         * @param value the value to evaluate
         * @returns true if the value does not equal any of this Matcher's \p values, false otherwise
         */
        bool Matches(const std::shared_ptr<Variant>& value) const override;
    };

    class MatcherNotExists : public MatcherExists {
    public:
        /**
         * @see ObjectInterface::ToStringImpl()
         */
        std::string ToStringImpl(const ToStringOptions& options) const override;
    protected:
        /**
         * Verifies if this Matcher's \p key exists in any of the given \p maps.
         * @param value the value to evaluate
         * @returns true if this Matcher's \p key exists in any of the given \p maps, false otherwise.
         */
        bool Matches(const std::shared_ptr<Variant>& value) const override;
    };

    class MatcherStartsWith : public Matcher {
    public:
        /**
         * @see ObjectInterface::ToStringImpl()
         */
        std::string ToStringImpl(const ToStringOptions& options) const override;
    protected:
        /**
         * Verifies if the given value starts with any of the Matcher's string \p values.
         * @param value the value to evaluate
         * @returns true if the value starts with any of this Matcher's string \p values, false otherwise
         */
        bool Matches(const std::shared_ptr<Variant>& value) const override;
    };

}

#endif /* ADOBEMOBILE_RULESENGINE_MATCHER_H */
