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

#ifndef ADOBEMOBILE_UTIL_STRINGUTILS_H
#define ADOBEMOBILE_UTIL_STRINGUTILS_H

#include <chrono>
#include <deque>
#include <forward_list>
#include <list>
#include <locale>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <regex>
#include "Object.h"

namespace AdobeMarketingMobile {

    class ToStringOptions;

    class StringUtils {
    public:
        static const std::string LOG_PREFIX;

        // Do not reference these directly unless you need the default values.
        // Instead, use the values from an instance of ToStringOptions
        static const size_t DEFAULT_MAX_DEPTH; ///< @private the maximum nesting level of ToString
        static const size_t DEFAULT_MAX_ELEMENTS; ///< @private the maximum number of collection elements to print
        static const size_t DEFAULT_MAX_STRING_LENGTH; ///< @private the maximum number of string characters to print

        /**
         * Split string into a word vector using regex delimiter and a limit
         * This is specifically to emulate the String.Split call in Java.
         * Limit parameter can have three effects depending on value:
         *
         *   limit > 1 : The pattern will be applied at most limit-1 times and the output vector size will not be
         *               more than n. The output vectors last entry will contain all input beyond last matched pattern.
         *
         *   limit = 1 : The input string is returned.
         *
         *   limit = 0 : The pattern will be applied as many times as possible and the output vector can be of any size.
         *               Empty vector elements are discarded.
         *
         *   limit < 0 : The pattern will be applied as many times as possible and the output vector can be of any size.
         *
         * @param str string to split
         * @param regex_delim regex string delimiter used to split into words
         * @param limit the number of results to return
         * @return vector containing word strings
         */
        static std::vector<std::string> SplitWithLimit(const std::string& str,
                const std::string& regex_delim,
                size_t limit);

        /**
         * Split string into a word vector using regex delimiter
         *
         * @param str string to split
         * @param regex_delim regex string delimiter used to split into words
         * @return vector containing word strings
         */
        static std::vector<std::string> Split(const std::string& str,
                                              const std::string& regex_delim);

        /**
         * Searches through a string and replaces occurances of old_string with new_string
         *
         * @param base_string the initial string to search through
         * @param old_string the string to search for in the base_string
         * @param new_string if old_string is found, new_string will replace it
         * @return string with replaced strings
         */
        static std::string Replace(const std::string& base_string,
                                   const std::string& old_string,
                                   const std::string& new_string);


        /**
         * Check if a string ends with suffix
         *
         * @param str string to check suffix
         * @param suffix the suffix string
         * @return bool whether the string str ends with the suffix
        */
        static bool EndsWith(const std::string& str, const std::string& suffix);

        /**
         * Read contents of a file. The "file://" prefix will be removed if present
         *
         * @param filename full path to file to read
         * @return string containing the contents of the file
         * @throws STD_SYSTEM_ERROR if an error occurs reading the file
         */
        static std::string FileToString(const std::string& filename);

        /* @private
         * Not porting this method from Java. String empty check is simple enough without added method call.
         * If using std::string, know that it cannot be nullptr.
         *   std::string msg;
         *   if (msg.empty()) { ... } // true if empty
         * If using C style string (rare) check for null then check for zero terminator.
         *   char* msg;
         *   if (msg && msg[0]) { ... } // true if nullptr or empty string
         */
        //static bool IsNullOrEmpty(const char* msg);

        /**
         * Generates a locale instance with en_US.UTF-8, if it fails then return the default locale.
         *
         * @return a locale object with en_US.UTF-8 if it is valid on the platform, otherwise the default locale
         */
        static std::locale GetLocale();

        /**
         * Convert all characters in the given std::string to lowercase according to the rules defined
         * by the given std::locale.
         * Note, for unicode characters, the given std::locale must support unicode (ie en_US.UTF-8)
         *
         * @param str The std::string to convert to lowercase characters
         * @param loc The locale rules to use for lowercase conversion
         * @return std::string as lowercase
         */
        static std::string ToLower(const std::string& str, const std::locale& loc);

        /**
         * Convert all characters in the given std::wstring (wide string) to lowercase according to the rules defined
         * by the given std::locale.
         * Note, for unicode characters, the given std::locale must support unicode (ie en_US.UTF-8)
         *
         * @param str The std::wstring (wide string) to convert to lowercase characters
         * @param loc The locale rules to use for lowercase conversion
         * @return std::wstring as lowercase
         */
        static std::wstring ToLower(const std::wstring& str, const std::locale& loc);

        /**
         * Convert all characters in the given std::string to lowercase according to
         * the US English (en_US) locale. This is a convenience method for internal processing or
         * normalization of strings.
         * Do not use this method for strings returned back to the application. Instead, prefer to
         * use ToLower by passing in the application defined locale object.
         *
         * @param str The std::string to convert to lowercase characters
         * @return std::wstring as lowercase
         */
        static std::string ToLower(const std::string& str);

        /**
         * Convert all characters in the given std::string to uppercase according to the rules defined
         * by the given std::locale.
         * Note, for unicode characters, the given std::locale must support unicode (ie en_US.UTF-8)
         *
         * @param str The std::string to convert to uppercase characters
         * @param loc The locale rules to use for uppercase conversion
         * @return std::string as uppercase
         */
        static std::string ToUpper(const std::string& str, const std::locale& loc);

        /**
         * Convert all characters in the given std::wstring (wide string) to uppercase according to the rules defined
         * by the given std::locale.
         * Note, for unicode characters, the given std::locale must support unicode (ie en_US.UTF-8)
         *
         * @param str The std::wstring (wide string) to convert to uppercase characters
         * @param loc The locale rules to use for uppercase conversion
         * @return std::wstring as uppercase
         */
        static std::wstring ToUpper(const std::wstring& str, const std::locale& loc);

        /**
         * Convert all characters in the given std::string to uppercase according to
         * the US English (en_US) locale. This is a convenience method for internal processing or
         * normalization of strings.
         * Do not use this method for strings returned back to the application. Instead, prefer to
         * use ToUpper by passing in the application defined locale object.
         *
         * @param str The std::string to convert to uppercase characters
         * @return std::wstring as uppercase
         */
        static std::string ToUpper(const std::string& str);

        /**
         * Check if given string is a valid URL.
         *
         * @param url string to check
         * @return true if the string is a valid URL, false otherwise
         */
        static bool StringIsUrl(const std::string& url);

        /**
         * Replaces the tokens present in the input string with the values present in the tokens
         *
         * @param inputString the string in which the tokens has to be replaced
         * @param tokens the token map which has the values to be replaced.
         * @return final string with replaced tokens
         */
        static std::string ExpandTokens(const std::string& inputString, const std::map<std::string, std::string>& tokens);


        /**
         * find all the valid tokens contained in the string, the regex for a valid token is '\{([a-zA-Z0-9_.%])+\}'
         *
         * @param input_string the input string
         * @return the list of valid tokens contained in the input string
         */
        static std::vector<std::string> FindTokensForExpansion(const std::string& input_string);

        /**
         * Equivalent to calling `StringUtils::Quotify(s, MAX_STRING_LENGTH)`;
         */
        static std::string Quotify(const std::string& s);

        /**
         * Wraps s in quotes, escaping special characters.
         *
         * The following characters are escaped:
         * - newline as "\n"
         * - horizontal tab as "\t"
         * - vertical tab as "\v"
         * - backspace as "\b"
         * - carriage return as "\r"
         * - form feed as "\f"
         * - alert as "\a"
         * - backslash as "\\"
         * - single quote as "\'"
         * - double quote as "\""
         * - characters with ascii values < ' ', as hex prefixed by `\x`
         * - characters with ascii values > '~', as hex prefixed by `\x`
         *
         * @param s - the string to enclose in quotes
         * @param max_string_length - the maximum string length to output. `max_string_length` characters of `s` will be
         *                            included in the output. if the length of `s` exceeds `max_string_length`, the
         *                            returned string will end with `..."`. if `max_string_length` is 0, all characters
         *                            of `s` will included in the output.
         *
         * @return s surrounded by quotes, with special characters escaped.
         */
        static std::string Quotify(const std::string& s, size_t max_string_length);

        /**
         * Equivalent to `ToString(value, ToStringOptions{})`.
         */
        template<typename T>
        static std::string ToString(const T& value);

        /**
         * Converts value to a `std::string`.
         *
         * @param value - the value to convert
         * @param options - options for serialization
         *
         * @returns value, converted to a `std::string`
         *
         * Introduction
         * ------------
         *
         * This function is a better version of std::to_string and iostreams.
         *
         * It improves upon iostream in the following ways:
         * - ToString(...) supports collection types, pointers, and a few other types not supported by ostream.
         * - ToString(...) detects re-entrancy and will stop infinite recursion.
         * - ToString(...) can accept a formatting string.
         * - ToString(...) can accept a additional, custom flags, as needed.
         *
         * ToString() also allows us to maintain strict control over the behavior of ToString(...).
         *
         * ToString() is used by the logging framework. Specifically, ToString() is used by StringUtils::FormatString(),
         * which is used by the logging macros (ADOBE_LOG_DEBUG, etc).
         *
         * Example:
         *
         *     std::cout << ToString
         *
         * Supported Types
         * ---------------
         *
         * The following types for value are supported by default:
         * - Standard library collection types: `vector`, `list`, `deque`, `map`, `multimap`, `set`, `multiset`,
         *   `unordered_map`,`unordered_multimap`, `unordered_set`, `unordered_multiset`, `pair`, `tuple`
         * - Standard library smart pointers: `unique_ptr`, `shared_ptr`, `weak_ptr`
         * - Raw pointers
         * - Classes derived from `Object` or `ObjectInterface`
         * - Primitives: `bool`, `char`, `unsigned char`, `int`, `unsigned int`, `long`, `unsigned long`, `long long`,
         *   `unsigned long long`, `float`, `double`
         * - Strings: `const char*`, `string`
         * - `std::chrono::milliseconds`
         *
         * Customizing String Output for Objects
         * -------------------------------------
         *
         * To provide a custom string representation for classes that derive from `Object` or `ObjectInterface`,
         * override `ToStringImpl`.
         *
         * Example:
         *
         *     namespace AdobeMarketingMobile {
         *         class MyObject : public Object {
         *         public:
         *             void ToStringImpl(std::ostream& the_stream, const ToStringOptions& options) const override {
         *                 // the impl can be whatever string you feel is appropriate, but by convention, Objects
         *                 // use a JSON-like structure
         *                 the_stream << "MyObjectType {";
         *
         *                 // Invoke the superclass implementation.
         *                 // When invoking superclass, be sure to invoke Object::ToStringImpl directly, since
         *
         *                 the_stream << " super: ";
         *                 Object::ToStringImpl(the_stream, options);
         *
         *                 the_stream << "}";
         *             };
         *         };
         *
         * Customizing String Output for Other Types
         * -----------------------------------------
         *
         * To provide a custom string representation for other types, define an overload of `ToStringImpl`.
         *
         * The overload should belong to the `AdobeMarketingMobile` namespace and have the following signature:
         *
         *     namespace AdobeMarketingMobile {
         *         void ToStringImpl(std::ostream& the_stream, const MyType& value, const ToStringOptions& options);
         *     }
         *
         * Where `MyType` is the type you would like to serialize. The string representation of `value` should be
         * appended to `the_stream`. You may optionally choose to change the representation based on `options`.
         *
         * Example:
         *
         *     namespace AdobeMarketingMobile {
         *         class MyType {};
         *
         *         void ToStringImpl(std::ostream& the_stream, const MyType& value, const ToStringOptions& options) {
         *           the_stream << "my custom serialization";
         *         }
         *     }
         *
         */
        template<typename T>
        static std::string ToString(const T& value,
                                    const ToStringOptions& options);

        /**
         * Appends the string representation of `value` to the given `std::ostream`.
         *
         * @see ToString()
         */
        template<typename T>
        static void ToString(std::ostream& the_stream, const T& value);

        /**
         * Appends the string representation of `value` to the given `std::ostream` using the provided `options`.
         *
         * @see ToString()
         */
        template<typename T>
        static void ToString(std::ostream& the_stream, const T& value, const ToStringOptions& options);

        /**
         * @returns a formatted version of the given string.
         *
         * @see FormatString()
         */
        static std::string FormatString(const char* format);

        /**
         * @returns a formatted version of the given string.
         *
         * @see FormatString()
         */
        static std::string FormatString(const ToStringOptions& options, const char* format);

        /**
         * @returns a formatted version of the given string.
         *
         * @see FormatString()
         */
        static std::string FormatString(const std::string& format);

        /**
         * @returns a formatted version of the given string.
         *
         * @see FormatString()
         */
        static std::string FormatString(const ToStringOptions& options, const std::string& format);

        /**
         * @returns a formatted version of the given string.
         *
         * @see FormatString()
         */
        template<typename ...TArgTypes>
        static std::string FormatString(const char* format, const TArgTypes& ... args);

        /**
         * @returns a formatted version of the given string.
         *
         * @see FormatString()
         */
        template<typename ...TArgTypes>
        static std::string FormatString(const ToStringOptions& options, const char* format, const TArgTypes& ... args);

        /**
         * Returns a formatted version of the given string.
         *
         * This function is used by the `Log` functions to format the output.
         *
         * Motivation
         * ----------
         * This function was added instead of using sprintf or ostream for a few reasons:
         * - It uses the same format as Java, which eases porting.
         * - It will not causes crashes or corruption when invalid format strings are passed in.
         * - It is extensible.
         * - Under the covers, this function uses StringUtils::ToString() and gains all the benefits thereof:
         *   - Infinite recursion detection (a common string formatting error)
         *   - Support for collection types like `vector` and `map`.
         *   - Support for custom formatting options
         *   - Support for pointer types
         *   - Easy serialization of `Object` subclasses
         *
         * The Format String
         * -----------------
         * The `format` string should follow the conventions of
         * [Java's Formatter class](https://docs.oracle.com/javase/7/docs/api/java/util/Formatter.html). This is by
         * design, as it allows for easier porting of Java code. The implementation does not implement all of the
         * formatting options that are supported by the Java version, but has the capability to do so in the future.
         * If an option is not supported, the default formatting for the argument will be used. Currently, the only
         * option supported is argument indices.
         *
         * HOW CAN I CUSTOMIZE HOW MY OBJECT IS SERIALIZED?
         * ------------------------------------------------
         * @see ToString()
         *
         * @param format - the format string
         * @param args - the arguments for the foramt string
         *
         * @returns a formatted version of the given string.
         *
         * @see FormatString()
         */
        template<typename ...TArgTypes>
        static std::string FormatString(const std::string& format, const TArgTypes& ... args);

        /**
         * @returns a formatted version of the given string.
         *
         * @see FormatString()
         */
        template<typename ...TArgTypes>
        static std::string FormatString(const ToStringOptions& options, const std::string& format, const TArgTypes& ... args);

    private:
        static std::mutex current_depths_mutex; ///< @private mutex that protects current_depths, do not let this mutex escape

        static std::map<std::thread::id, size_t> current_depths;  ///< @private thread id to nesting level map

        static size_t GetCurrentDepth(); ///< @private @returns the current nesting level of ToString

        static void SetCurrentDepth(size_t depth); ///< @private sets the current nesting level of ToString

        static bool IsTokenValid(const std::string&
                                 token); ///< @private Check whether the token is valid. A valid token should only contain characters [a-zA-Z0-9_.%]
    };

    /**
     * Options for `ToString()`. `ToStringImpl` support for all options is optional.
     */
    class ToStringOptions {
    public:
        ToStringOptions() = default;
        ToStringOptions(const ToStringOptions&) = default;
        ToStringOptions& operator=(const ToStringOptions&) = default;
        ToStringOptions(ToStringOptions&&) = default;
        ToStringOptions& operator=(ToStringOptions&&) = default;

        /**
         * @returns a ToStringOptions with pretty set to true
         */
        static ToStringOptions Pretty();

        bool pretty = false; ///< if true, strings should be "pretty"
        std::string pretty_indent; ///< the indent for newlines in pretty strings, each new level should be 4 spaces
        bool quotify_strings = false; ///< if true, strings should be enclosed in quotes
        std::string format; ///< if non-empty, the format that should be used for the value
        size_t max_depth = StringUtils::DEFAULT_MAX_DEPTH; ///< the maximum nesting level of ToString
        size_t max_elements = StringUtils::DEFAULT_MAX_ELEMENTS; ///< the maximum number of collection elements to print
        size_t max_string_length = StringUtils::DEFAULT_MAX_STRING_LENGTH; ///< the maximum number of string characters to print
    };
}

/////////////////////////////////////////
// template and inline implementations //
/////////////////////////////////////////

namespace AdobeMarketingMobile {

    /**
     * @private
     *
     * `ToStringImpl` for `std::chrono::milliseconds`.
     */
    void ToStringImpl(std::ostream& the_stream, const std::chrono::milliseconds& the_duration,
                      const ToStringOptions& options);

    /**
     * @private
     *
     * `ToStringImpl` for `std::string`.
     */
    void ToStringImpl(std::ostream& the_stream, const std::string& value, const ToStringOptions& options);

    /**
     * @private
     *
     * `ToStringImpl` for `const char*`.
     */
    void ToStringImpl(std::ostream& the_stream, const char* value, const ToStringOptions& options);

    /**
     * @private
     *
     * `ToStringImpl` for `bool`.
     */
    void ToStringImpl(std::ostream& the_stream, bool value, const ToStringOptions& options);

    /**
     * @private
     *
     * `ToStringImpl` for `char`.
     */
    void ToStringImpl(std::ostream& the_stream, char value, const ToStringOptions& options);

    /**
     * @private
     *
     * `ToStringImpl` for `unsigned char` (and `uint8_t`).
     */
    void ToStringImpl(std::ostream& the_stream, unsigned char value, const ToStringOptions& options);

    /**
     * @private
     *
     * `ToStringImpl` for `int` (and `int32_t`).
     */
    void ToStringImpl(std::ostream& the_stream, int value, const ToStringOptions& options);

    /**
     * @private
     *
     * `ToStringImpl` for `unsigned int` (and `uint32_t`).
     */
    void ToStringImpl(std::ostream& the_stream, unsigned int value, const ToStringOptions& options);

    /**
     * @private
     *
     * `ToStringImpl` for `long` (and `int64_t`).
     */
    void ToStringImpl(std::ostream& the_stream, long value, const ToStringOptions& options);

    /**
     * @private
     *
     * `ToStringImpl` for `unsigned long` (and `uint64_t`).
     */
    void ToStringImpl(std::ostream& the_stream, unsigned long value, const ToStringOptions& options);

    /**
     * @private
     *
     * `ToStringImpl` for `long long`.
     */
    void ToStringImpl(std::ostream& the_stream, long long value, const ToStringOptions& options);

    /**
     * @private
     *
     * `ToStringImpl` for `unsigned long long`.
     */
    void ToStringImpl(std::ostream& the_stream, unsigned long long value, const ToStringOptions& options);

    /**
     * @private
     *
     * `ToStringImpl` for `float`.
     */
    void ToStringImpl(std::ostream& the_stream, float value, const ToStringOptions& options);

    /**
     * @private
     *
     * `ToStringImpl` for `double`.
     */
    void ToStringImpl(std::ostream& the_stream, double value, const ToStringOptions& options);

    /**
     * @private
     *
     * `ToStringImpl` for `long double`.
     */
    void ToStringImpl(std::ostream& the_stream, long double value, const ToStringOptions& options);

    /**
     * @private
     *
     * `ToStringImpl` for `uint16_t`.
     */
    void ToStringImpl(std::ostream& the_stream, uint16_t value, const ToStringOptions& options);

    /**
     * @private
     *
     * `ToStringImpl` for `int8_t`.
     */
    void ToStringImpl(std::ostream& the_stream, int8_t value, const ToStringOptions& options);

    /**
     * @private
     *
     * `ToStringImpl` for `int16_t`.
     */
    void ToStringImpl(std::ostream& the_stream, int16_t value, const ToStringOptions& options);

    /**
     * @private
     *
     * Default `ToStringImpl` for enum classes that derive from numeric types.
     */
    template<class TEnum>
    typename std::enable_if<std::is_enum<TEnum>::value, void>::type
    // ^this confusing line matches this template only for enum classes that inherit from a numeric type
    ToStringImpl(std::ostream& the_stream, TEnum value, const ToStringOptions& options) {
        typedef typename std::underlying_type<TEnum>::type EnumUnderlyingNumericType;
        ToStringImpl(the_stream, static_cast<EnumUnderlyingNumericType>(value), options);
    }

    /**
     * @private
     *
     * Default `ToStringImpl` for raw pointers.
     */
    template<typename T>
    void ToStringImpl(std::ostream& the_stream, const T* pointer, const ToStringOptions& options) {
        if (pointer == nullptr) {
            the_stream << "null";
        } else {
            // If you get an error on the following line, it means the type you passed in for value is not
            // supported. See the doxygen for ToString().
            ToStringImpl(the_stream, *pointer, options);
        }
    }

    /**
     * @private
     *
     * Default `ToStringImpl` for `shared_ptr`.
     */
    template<typename T>
    void ToStringImpl(std::ostream& the_stream, const std::shared_ptr<T>& pointer, const ToStringOptions& options) {
        // If you get an error on the following line, it means the type you passed in for value is not
        // supported. See the doxygen for ToString().
        ToStringImpl(the_stream, pointer.get(), options);
    }

    /**
     * @private
     *
     * Default `ToStringImpl` for `weak_ptr`.
     */
    template<typename T>
    void ToStringImpl(std::ostream& the_stream, const std::weak_ptr<T>& pointer, const ToStringOptions& options) {
        // If you get an error on the following line, it means the type you passed in for value is not
        // supported. See the doxygen for ToString().
        ToStringImpl(the_stream, pointer.lock(), options);
    }

    /**
     * @private
     *
     * Default `ToStringImpl` for `unique_ptr`.
     */
    template<typename T>
    void ToStringImpl(std::ostream& the_stream, const std::unique_ptr<T>& pointer, const ToStringOptions& options) {
        // If you get an error on the following line, it means the type you passed in for value is not
        // supported. See the doxygen for ToString().
        ToStringImpl(the_stream, pointer.get(), options);
    }

    /**
     * @private
     *
     * Default `ToStringImpl` for `pair`.
     */
    template<typename T1, typename T2>
    void ToStringImpl(std::ostream& the_stream, const std::pair<T1, T2>& the_pair, const ToStringOptions& options) {
        ToStringOptions element_options{options};
        element_options.quotify_strings = true; // quotify strings

        the_stream << "[ ";
        StringUtils::ToString(the_stream, the_pair.first, element_options);
        the_stream << ", ";
        StringUtils::ToString(the_stream, the_pair.second, element_options);
        the_stream << " ]";
    }

    namespace StringUtilsInternal {
        /**
         * @private
         *
         * Helper for tuple Impl. Metaprogramming construct to append tuple elements to a stream.
         * This is a very rare instance where metaprogramming is necessary.
         */
        template < typename TTuple, size_t I = std::tuple_size<TTuple>::value - 1 >
        struct AppendTupleElementsToStream {
            static void Call(std::ostream& the_stream, const TTuple& the_tuple, const ToStringOptions& element_options) {
                AppendTupleElementsToStream < TTuple, I - 1 >::Call(the_stream, the_tuple, element_options);
                the_stream << ", ";
                StringUtils::ToString(the_stream, std::get<I>(the_tuple), element_options);
            }
        };

        /**
         * @private
         *
         * Stopping condition for the above metaprogramming.
         */
        template<typename TTuple>
        struct AppendTupleElementsToStream<TTuple, 0> {
            static void Call(std::ostream& the_stream, const TTuple& the_tuple, const ToStringOptions& element_options) {
                the_stream << StringUtils::ToString(std::get<0>(the_tuple), element_options);
            }
        };
    }

    /**
     * @private
     *
     * Default `ToStringImpl` for `tuple`.
     */
    template<typename ...TTupleTypes>
    void ToStringImpl(std::ostream& the_stream, const std::tuple<TTupleTypes...>& the_tuple,
                      const ToStringOptions& options) {
        ToStringOptions element_options{options};
        element_options.quotify_strings = true; // quotify strings

        the_stream << "[ ";
        StringUtilsInternal::AppendTupleElementsToStream<std::tuple<TTupleTypes...>>::Call(the_stream, the_tuple,
                element_options);
        the_stream << " ]";
    }



    namespace StringUtilsInternal {
        /**
         * @private
         *
         * Actual implementation of `ToStringImpl` for collection types that are like arrays.
         */
        template<typename T>
        void CollectionToStringImpl(std::ostream& the_stream, const T& collection, const ToStringOptions& options) {
            ToStringOptions element_options{options};
            element_options.quotify_strings = true;

            the_stream << "[";
            size_t element_index = 0;

            for (auto& element : collection) {
                if (element_index == 0) {
                    the_stream << " ";
                } else {
                    the_stream << ", ";
                }

                if (element_index >= options.max_elements) {
                    the_stream << "...";
                    break;
                }

                the_stream << StringUtils::ToString(element, element_options);

                ++element_index;
            }

            if (element_index > 0) {
                the_stream << " ";
            }

            the_stream << "]";
        }
    }

    /**
     * @private
     *
     * `ToStringImpl` for `vector`.
     */
    template<typename ...TCollectionTypes>
    void ToStringImpl(std::ostream& the_stream, const std::vector<TCollectionTypes...>& collection,
                      const ToStringOptions& options) {
        StringUtilsInternal::CollectionToStringImpl(the_stream, collection, options);
    }

    /**
     * @private
     *
     * `ToStringImpl` for `list`.
     */
    template<typename ...TCollectionTypes>
    void ToStringImpl(std::ostream& the_stream, const std::list<TCollectionTypes...>& collection,
                      const ToStringOptions& options) {
        StringUtilsInternal::CollectionToStringImpl(the_stream, collection, options);
    }

    /**
     * @private
     *
     * `ToStringImpl` for `deque`.
     */
    template<typename ...TCollectionTypes>
    void ToStringImpl(std::ostream& the_stream, const std::deque<TCollectionTypes...>& collection,
                      const ToStringOptions& options) {
        StringUtilsInternal::CollectionToStringImpl(the_stream, collection, options);
    }

    /**
     * @private
     *
     * `ToStringImpl` for `map`.
     */
    template<typename ...TCollectionTypes>
    void ToStringImpl(std::ostream& the_stream, const std::map<TCollectionTypes...>& collection,
                      const ToStringOptions& options) {
        StringUtilsInternal::CollectionToStringImpl(the_stream, collection, options);
    }

    /**
     * @private
     *
     * `ToStringImpl` for `multimap`.
     */
    template<typename ...TCollectionTypes>
    void ToStringImpl(std::ostream& the_stream, const std::multimap<TCollectionTypes...>& collection,
                      const ToStringOptions& options) {
        StringUtilsInternal::CollectionToStringImpl(the_stream, collection, options);
    }

    /**
     * @private
     *
     * `ToStringImpl` for `multimap`.
     */
    template<typename ...TCollectionTypes>
    void ToStringImpl(std::ostream& the_stream, const std::set<TCollectionTypes...>& collection,
                      const ToStringOptions& options) {
        StringUtilsInternal::CollectionToStringImpl(the_stream, collection, options);
    }

    /**
     * @private
     *
     * `ToStringImpl` for `multiset`.
     */
    template<typename ...TCollectionTypes>
    void ToStringImpl(std::ostream& the_stream, const std::multiset<TCollectionTypes...>& collection,
                      const ToStringOptions& options) {
        StringUtilsInternal::CollectionToStringImpl(the_stream, collection, options);
    }

    /**
     * @private
     *
     * `ToStringImpl` for `unordered_map`.
     */
    template<typename ...TCollectionTypes>
    void ToStringImpl(std::ostream& the_stream, const std::unordered_map<TCollectionTypes...>& collection,
                      const ToStringOptions& options) {
        StringUtilsInternal::CollectionToStringImpl(the_stream, collection, options);
    }

    /**
     * @private
     *
     * `ToStringImpl` for `unordered_multimap`.
     */
    template<typename ...TCollectionTypes>
    void ToStringImpl(std::ostream& the_stream, const std::unordered_multimap<TCollectionTypes...>& collection,
                      const ToStringOptions& options) {
        StringUtilsInternal::CollectionToStringImpl(the_stream, collection, options);
    }

    /**
     * @private
     *
     * `ToStringImpl` for `unordered_set`.
     */
    template<typename ...TCollectionTypes>
    void ToStringImpl(std::ostream& the_stream, const std::unordered_set<TCollectionTypes...>& collection,
                      const ToStringOptions& options) {
        StringUtilsInternal::CollectionToStringImpl(the_stream, collection, options);
    }

    /**
     * @private
     *
     * `ToStringImpl` for `unordered_multiset`.
     */
    template<typename ...TCollectionTypes>
    void ToStringImpl(std::ostream& the_stream, const std::unordered_multiset<TCollectionTypes...>& collection,
                      const ToStringOptions& options) {
        StringUtilsInternal::CollectionToStringImpl(the_stream, collection, options);
    }

    template<typename T>
    std::string StringUtils::ToString(const T& value) {
        return ToString(value, ToStringOptions{});
    }

    template<typename T>
    std::string StringUtils::ToString(const T& value, const ToStringOptions& options) {
        std::ostringstream the_stream;
        ToString(the_stream, value, options);
        return the_stream.str();
    }

    template<typename T>
    void StringUtils::ToString(std::ostream& the_stream, const T& value) {
        ToString(the_stream, value, ToStringOptions{});
    }

    template<typename T>
    void StringUtils::ToString(std::ostream& the_stream, const T& value, const ToStringOptions& options) {
        size_t current_depth = GetCurrentDepth();

        if (current_depth >= options.max_depth) {
            // infinite recursion guard
            the_stream << "...";
            return;
        }

        SetCurrentDepth(++current_depth);

        try {
            // If you get an error on the following line, it means the type you passed in for value is not
            // supported. See the doxygen for ToString().
            ToStringImpl(the_stream, value, options);
        } catch (...) {
            the_stream << "ERROR";
        }

        SetCurrentDepth(--current_depth);
    }

    namespace StringUtilsInternal {

        /**
         * @private
         *
         * Helper for FormatString.
         *
         * GenericFormatArgs and PolymorphicFormatArgs are used to represent the args to FormatString in a polymorphic
         * manner. PolymorphicFormatArgs is the interface, and GenericFormatArgs is the implementation.
         *
         * See implementation of FormatString() for details.
         */
        class PolymorphicFormatArgs {
        public:
            /**
             * @private
             *
             * Destructor
             */
            virtual ~PolymorphicFormatArgs() {}

            /**
             * @private
             *
             * @return the number of arguments.
             */
            virtual size_t GetSize() const = 0;

            /**
             * @private
             *
             * Invokes ToString(...) on argument at the specified index.
             */
            virtual void CallToString(size_t index, std::ostream& the_stream, const ToStringOptions& options) const = 0;
        };

#ifndef ADOBE_DOXYGEN
        // doxygen cannot handle these templates

        /**
         * @private
         *
         * Helper for FormatString.
         *
         * GenericFormatArgs and PolymorphicFormatArgs are used to represent the args to FormatString in a polymorphic
         * manner. PolymorphicFormatArgs is the interface, and GenericFormatArgs is the implementation.
         *
         * See implementation of FormatString() for details.
         */
        template<typename TCurrentArg, typename ...TMoreArgs>
        class GenericFormatArgs : public GenericFormatArgs<TMoreArgs...> {
        public:
            typedef GenericFormatArgs<TMoreArgs...> Super;

            /**
             * @private
             *
             * Constructor
             */
            explicit GenericFormatArgs(const TCurrentArg& current_arg, const TMoreArgs& ...more_args) :
                Super{more_args...}, // template recurse, without first arg
                current_arg_{current_arg} {} // save a ref to the first arg

            /**
             * @private
             *
             * Impl of PolymorphicFormatArgs::GetSize
             */
            size_t GetSize() const override {
                // Deep C++:
                // https://stackoverflow.com/questions/12024304/c11-number-of-variadic-template-function-parameters
                return sizeof...(TMoreArgs) + 1;
            }

            /**
             * @private
             *
             * Impl of PolymorphicFormatArgs::CallToString
             */
            void CallToString(size_t index, std::ostream& the_stream, const ToStringOptions& options) const override {
                if (index == 0) {
                    // 0 always refers to current arg
                    StringUtils::ToString(the_stream, current_arg_, options);
                } else {
                    // template recursion.
                    // By subtracting 1 from index, we're basically performing a shift
                    // Stopping condition is
                    Super::CallToString(index - 1, the_stream, options);
                }
            }

        private:
            const TCurrentArg& current_arg_;
        };

        /**
         * @private
         *
         * Helper for FormatString. See implementation of FormatString() for explanation.
         */
        template<class TCurrentArg>
        class GenericFormatArgs<TCurrentArg> : public PolymorphicFormatArgs {
        public:
            /**
             * @private
             *
             * Constructor
             */
            explicit GenericFormatArgs(const TCurrentArg& current_arg) :
                current_arg_{current_arg} {} // save a ref to the first arg

            size_t GetSize() const override {
                return 1;
            }

            /**
             * @private
             *
             * Impl of PolymorphicFormatArgs::CallToString
             */
            void CallToString(size_t index, std::ostream& the_stream, const ToStringOptions& options) const override {
                // Stopping condition
                if (index == 0) {
                    // 0 always refers to current arg
                    StringUtils::ToString(the_stream, current_arg_, options);
                } else {
                    // indices beyond size are noops
                }
            }

        private:
            const TCurrentArg& current_arg_;
        };
#endif


        /**
         * @private
         *
         * Helper for FormatString. See implementation of FormatString() for explanation.
         *
         * Defined in StringUtils.cpp
         */
        std::string PolymorphicFormatString(const ToStringOptions& options, const char* format,
                                            const PolymorphicFormatArgs& args);

        /**
         * @private
         *
         * Helper for FormatString. See implementation of FormatString() for explanation.
         */
        template<typename ...TArgs>
        std::string GenericFormatString(const ToStringOptions& options, const char* format, const TArgs& ...args) {
            return PolymorphicFormatString(options, format, GenericFormatArgs<TArgs...> {args...});
        }
    }

    template<typename ...TArgs>
    std::string StringUtils::FormatString(const ToStringOptions& options, const std::string& format,
                                          const TArgs& ... args) {
        return FormatString(options, format.c_str(), args...);
    }

    template<typename ...TArgs>
    std::string StringUtils::FormatString(const std::string& format, const TArgs& ... args) {
        return FormatString(ToStringOptions{}, format.c_str(), args...);
    }

    template<typename ...TArgs>
    std::string StringUtils::FormatString(const char* format, const TArgs& ... args) {
        return FormatString(ToStringOptions{}, format, args...);
    }

    template<typename ...TArgs>
    std::string StringUtils::FormatString(const ToStringOptions& options, const char* format, const TArgs& ... args) {
        // This implementation is very confusing, but necessarily so, due to variadic templates.
        //
        // This implementation uses C++ features that are discouraged by our coding guidelines. This is OK in this case,
        // since there is no other way to implement this function, minimize unnecessary memory allocations, and
        // minimize binary size.
        //
        // To understand the C++ behind this implementation, you need to understand:
        // - Variadic Templates: http://eli.thegreenplace.net/2014/variadic-templates-in-c/
        // - Template specialization
        // - Polymorphic types vs. Generic types
        //
        // SHORT VERSION OF HOW THIS FUNCTION WORKS:
        //
        // - Through C++ magic, a call to FormatString(...) eventually becomes a call to PolymorphicFormatString(...).
        // - PolymorphicFormatString is defined in StringUtils.cpp.
        //
        // LONG VERSION OF HOW THIS FUNCTION WORKS:
        //
        // 1) For clarity, FormatString() is a wrapper around GenericFormatString().
        //
        // 2) GenericFormatString() is a generic (template) function.
        //
        // 3) We do not we do not want to duplicate code for every FormatString instantiation. To achieve this,
        //    we need to:
        //
        //    - Convert args to a polymorphic (non-template) class. That's the hard part. The polymorphic
        //      class we eventually will convert to is PolymorphicFormatArgs.
        //
        //    - Call a polymorphic function that has the real implementation and pass it the PolymorphicFormatArgs.
        //      That function is PolymorphicFormatString, which is defined in StringUtils.cpp.
        //
        // 4) GenericFormatArgList<TArgs...> is a subclass of PolymorphicFormatArgs. Basically, it is a bridge that
        //    lets us treat our template arg list polymorphically. GenericFormatList works as follows:
        //
        //    - GenericFormatArgList uses recursive templates. GenericFormatArgList<Arg1, Arg2, Arg3> is a subclass of
        //      GenericFormatArgList<Arg1, Arg2>. GenericFormatArgList<Arg1, Arg2> is a subclass of
        //      GenericFormatArgList<Arg1>. GenericFormatArgList<Arg1> is a subclass of PolymorphicFormatArgs
        //      (via template specialialization).
        //
        //    - GenericFormatArgList::CallToString accepts an index, an ostream, and options and invokes ToString for
        //      the given argument at the given index. Because of our use of recursive templates, this function is also
        //      recursive. GenericFormatArgList<> is a noop, our stopping condition.
        //
        // 5) In GenericFormatString, we instantiate a GenericFormatArgList then pass it to PolymorphicFormatString
        //    (as a PolymorphicFormatArgs).
        //
        // 6) In PolymorphicFormatString, we do the actual work of parsing the string, formatting the args, and
        //    calling ToString() (indirectly via PolymorphicFormatArgs::CallToString).
        //
        // Whew.
        return StringUtilsInternal::GenericFormatString(options, format, args...);
    }
}

#endif /* ADOBEMOBILE_UTIL_STRINGUTILS_H */
