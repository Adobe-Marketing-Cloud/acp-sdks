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

#ifndef ADOBEMOBILE_CORE_SDKERROR_H
#define ADOBEMOBILE_CORE_SDKERROR_H

#include <stdexcept>
#include <string>
#include <functional>
#include "Common.h"

namespace AdobeMarketingMobile {

    class ToStringOptions;

    /**
     * A POD that encapsulates debugging information.
     */
    class DebugInfo {
    public:
        DebugInfo() = default;
        DebugInfo(const DebugInfo& right) = default;
        DebugInfo& operator=(const DebugInfo& right) = default;
        DebugInfo(DebugInfo&& right) = default;
        DebugInfo& operator=(DebugInfo&& right) = default;

        /**
         * Constructs a DebugInfo with the given field values
         */
        DebugInfo(const std::string& file,
                  int32_t line_number,
                  const std::string& stack_trace);
        /**
         * The file name where an error occurred.
         * Empty string if unavailable.
         */
        std::string file;

        /**
         * The line number where an error occurred.
         * -1 if unavailable.
         */
        int32_t line_number = -1;

        /**
         * The stack trace for the error.
         * Empty string if unavailable.
         */
        std::string stack_trace;
    };

    /**
     * @see StringUtils::ToString()
     */
    void ToStringImpl(std::ostream& the_stream, const DebugInfo& debug_info, const ToStringOptions& options);

    namespace GetCurrentDebugInfoPrivate {
        // this namespace is only intended for use by the ADOBE_GET_CURRENT_DEBUG_INFO() macro
        // it is present to prevent unintended usage of this function

        /**
         * @private
         * @return the current stack trace
         */
        std::string GetCurrentStackTrace();
    }

    /**
     * DebugInfo ADOBE_GET_CURRENT_DEBUG_INFO()
     *
     * @returns a DebugInfo object populated with the current line number and stack trace.
     */
#define ADOBE_GET_CURRENT_DEBUG_INFO() AdobeMarketingMobile::DebugInfo{ __FILE__, __LINE__, GetCurrentDebugInfoPrivate::GetCurrentStackTrace() }

    /**
     * @class SdkError
     * An SdkError represents an error signaled by the SDK. It is also the base class for all exceptions thrown from the SDK.
     *
     * Best Practices
     * --------------
     * 1) Throw SdkError to signal uncommon, fatal errors. Return `Expected<...>` if errors are common.
     *
     * 2) When throwing, code should almost always throw SdkError:
     *
     * - Internal SDK functions (accessible only within Adobe) may bubble up
     *   std::exception, but should not explicitly throw std::exception.
     *
     * - Public SDK functions (accessible to customers) should only throw/return SdkError.
     *   In this case, std::exception and other exception types should be wrapped
     *   in SdkError.
     *
     * 3) Prefer using ADOBE_THROW() to a native throw.
     *
     * 4) Prefer the TrySwallow(), TryCatch(), TryCatchFinally(), TryFinally() methods to
     *    hand-rolled try catch blocks.
     *
     * 5) Be specific with your errors. If you need a new error code, add one.
     *
     * 6) If you must write your own try-catch block, always catch by reference:
     *
     *     try {
     *       ...
     *     } catch(SdkError& e) { // <- non-const reference
     *       ...
     *     }
     *
     * Why is this class useful?
     * -------------------------
     * SdkError provides a standard way for errors to be thrown, caught, and returned in the SDK.
     * It provides an error code and stack trace to ease analysis.
     *
     * How to create and throw SdkError
     * --------------------------------
     * Use SdkErrorconstructors to create an SdkError. SdkError::From can also be used to create
     * SdkError from std::exception or std::exception_ptr. SdkError are typically created on stack
     * (do not new SdkError).
     *
     * Use ADOBE_THROW() to throw SdkError. ADOBE_THROW() will add a stack trace and line number information
     * to the SdkError (if available on the current platform).
     *
     * When an exception needs to be rethrown, use std::rethrow_exception.
     *
     * Examples:
     *
     *     void SimpleExample() {
     *       if(SomeOtherErrorCondition()) {
     *         SdkError error{ ErrorCodes::MY_ERROR_CODE, "something crazy happened" }; // constructs an exception
     *         Throw(error); // throws it, canonical form
     *       }
     *       if(SomeErrorCondition()) {
     *         Throw(ErrorCodes::MY_ERROR_CODE, "something crazy happened"); // convenience form
     *       }
     *     }
     *
     *     void RethrowExample() {
     *       TryCatch([&]{
     *         DoSomething();
     *       }, [&](SdkError& e) {
     *          if(e.GetCode() == ErrorCodes::AN_ERROR_I_CAN_RECOVER_FROM) {
     *           recover();
     *         } else {
     *           std::rethrow_exception(std::current_exception()); // <- rethrow
     *         }
     *       });
     *     }
     *
     * How to catch SdkError
     * ---------------------
     * Use TrySwallow(), TryCatch(), TryCatchFinally(), TryFinally() to catch and handle exceptions. These
     * provide a number of benefits over hand-rolled try-catch blocks:
     *
     * - Catch/Swallow functions will catch all exception types (including std::exception and unrecognized
     *   exception classes), convert exceptions to SdkError, and invoke the catch block.
     *
     * - Try functions make sure code always catches by reference (to avoid slicing of exceptions).
     *
     * - Finally functions provide java-like finally blocks.
     *
     * Examples:
     *
     *     void Example1() {
     *        TryCatch([&]{
     *          DoSomething();
     *        }, [&](SdkError& e) {
     *          if(e.CodeIs(ErrorCodes::AN_ERROR_I_CAN_RECOVER_FROM)) {
     *            DoSomethingToRecover();
     *          } else {
     *            DoSomethingOnFail();
     *          }
     *        });
     *     }
     *
     *     void Example2() {
     *       TrySwallow([&]{
     *         DoSomething();
     *       });
     *     }
     *
     *
     * Understanding error codes
     * -------------------------
     * Each SdkError has a string error code that indicates what happened. Error code values can be found in
     * the ErrorCodes namespace. The core provides a set of default error codes and modules can
     * add custom error codes.
     *
     * Use CodeIs() To check if error codes match:
     *
     *     void Example() {
     *       SdkError error1{ErrorCodes::SOME_ERROR, "some description"}; // assume SOME_ERROR is "my_module.some_error"
     *       SdkError error2{ErrorCodes::ANOTHER_ERROR, "some description"}; // assume ANOTHER_ERROR is "my_module.another_error"
     *       std::cout << error1.CodeIs(ErrorCodes::SOME_ERROR) << std::endl; // prints true
     *       std::cout << error1.CodeIs(ErrorCodes::ANOTHER_ERROR) << std::endl; // prints false
     *     }
     *
     * Error codes are hierarchical. For example, if PEAR_ERROR is "fruit.pear" and FRUIT_ERROR is
     * "fruit", a PEAR_ERROR is a FRUIT_ERROR. CodeIs() takes this into consideration:
     *
     *     void Example() {
     *       SdkError pear_error{ErrorCodes::PEAR_ERROR, "some description"}; // assume PEAR_ERROR is "fruit.pear"
     *       SdkError fruit_error{ErrorCodes::FRUIT_ERROR, "some description"}; // assume FRUIT_ERROR is "fruit"
     *       std::cout << pear_error.CodeIs(ErrorCodes::PEAR_ERROR) << std::endl; // prints true
     *       std::cout << pear_error.CodeIs(ErrorCodes::FRUIT_ERROR) << std::endl; // prints true
     *       std::cout << fruit_error.CodeIs(ErrorCodes::PEAR_ERROR) << std::endl; // prints false
     *     }
     *
     * Hierarchical error codes allow new error codes to be specialized without breaking backward compatibility.
     *
     * Defining new error codes
     * ------------------------
     * New error codes should typically be added to the ErrorCodes namespace. Error code string values should consist
     * of lowercase alphanumeric or underscore characters separated by periods.
     *
     * Module-specific error code values should typically be prefixed with a module-specific token. The identifier
     * should also be prefixed with a module-specific prefix.
     *
     * Examples:
     *
     *     namespace AdobeMarketingMobile {
     *       namespace ErrorCodes {
     *         constexpr static const char* MYMODULE_CAMERA_UNAVAILABLE = "my_module.camera_unavailable";
     *       }
     *     }
     *
     * Inner errors
     * ------------
     * An SdkError may contain a nested error for additional information. @see HasInner(), GetInner().
     */
    class SdkError {
    public:
        /**
         * Default constructor.
         *
         * The SdkError will be initialized with code ErrorCodes::NOTHING, no inner
         */
        SdkError();

        SdkError(const SdkError& right) = default;
        SdkError& operator=(const SdkError& right) = default;
        SdkError(SdkError&& right) = default;
        SdkError& operator=(SdkError&& right) = default;

        /**
         * Copies the given SdkError, replacing its debug information with the
         * given debug_info.
         *
         * @param right - the error to copy
         * @param debug_info - the new debug_info for the error
         */
        explicit SdkError(const SdkError& right,
                          const DebugInfo& debug_info);

        /**
         * Constructs an SdkError with the given error code and description.
         * @param code - the error code
         * @param message - a description of the error
         * @param debug_info - (optional) debug information for the error
         */
        explicit SdkError(const std::string& code,
                          const std::string& message,
                          const DebugInfo& debug_info = DebugInfo());

        /**
         * Constructs an SdkError with the given error code, description, and inner error.
         * @param code - the error code
         * @param message - a description of the error
         * @param inner - the inner error
         * @param debug_info - (optional) debug information for the error
         */
        explicit SdkError(const std::string& code,
                          const std::string& message,
                          const SdkError& inner,
                          const DebugInfo& debug_info = DebugInfo{});

        /**
         * Converts a std::exception to an SdkError.
         *
         * Converted exceptions will a STD_ error codes.
         *
         * @param e - the std::exception to convert
         * @param debug_info - (optional) debug information for the error
         */
        static SdkError From(const std::exception& e,
                             const DebugInfo& debug_info = DebugInfo{});

        /**
         * Converts any exception to an SdkError.
         *
         * Converted std::exceptions will a STD_ error codes.
         * Converted SdkErrors will be unchanged.
         * Other errors will be converted to UNKNOWN_EXCEPTION.
         *
         * @param e - the exception to convert
         * @param debug_info - (optional) debug information for the error
         */
        static SdkError From(const std::exception_ptr& e,
                             const DebugInfo& debug_info = DebugInfo{});

        /**
         * Compares the error code of this against another error code, factoring in hierarchical codes.
         *
         * @return true if this' error code matches error_code
         */
        bool CodeIs(const std::string& error_code) const;

        /**
         * @return the error code. Consider using CodeIs() instead of this function.
         */
        std::string GetCode() const;

        /**
         * @return true if the error has a nested error
         */
        bool HasInner() const;

        /**
         * Obtains the nested error, if there is one.
         *
         * @param value - (out) if there is a nested error, value will be set to the nested error.
         *
         * @return true if the error has a nested error, false otherwise.
         */
        bool GetInner(SdkError& value) const;

        /**
         * @return a description of the error
         */
        std::string GetMessage() const;

        /**
         * @return the stack trace for a thrown exception
         */
        const DebugInfo& GetDebugInfo() const;

        /**
         * Converts this to a string. Equivalent to calling `StringUtils::ToString(*this)`.
         *
         * @return a string representation of this
         *
         * @see StringUtils::ToString()
         */
        std::string ToString() const;

        /**
         * Converts this to a string. Equivalent to calling `StringUtils::ToString(*this, options)`.
         *
         * @return a string representation of this
         *
         * @see StringUtils::ToString()
         */
        std::string ToString(const ToStringOptions& options) const;

        /**
         * @private
         *
         * For use by AdobeMarketingMobile::ToStringImpl().
         */
        void ToStringImpl(std::ostream& the_stream, const ToStringOptions& options) const;

    private:
        std::string code_; ///<@private the error code from ErrorCodes namespace
        std::shared_ptr<const SdkError> inner_; ///<@private the inner exception, const to enable fast, shared copies
        std::string message_; ///<@private the error description
        DebugInfo debug_info_; ///<@private the stack trace
    };

    /**
     * @see StringUtils::ToString()
     */
    void ToStringImpl(std::ostream& the_stream, const SdkError& error, const ToStringOptions& options);

    /**
     * Helper to swallow and log exceptions.
     *
     * Invokes f(), catching and logging any exceptions thrown by f(). This function
     * is designed to work with C++ lambdas.
     *
     * Examples:
     *
     *   void Foo(bool try_throw) {
     *     TrySwallow([&] {
     *       std::cout << "try" << std::endl;
     *       if(try_throw) {
     *         Throw(ErrorCodes::UNEXPECTED, "try threw");
     *       }
     *       std::cout << "try complete" << std::endl;
     *     });
     *     std::cout << "foo" << std::endl;
     *   }
     *
     *   void Bar() {
     *     Foo(false); // prints "try", "try complete", then "foo"
     *     Foo(true); // prints "try", the exception, then "foo"
     *   }
     *
     * Remember that returning from a C++11 lamba only exits the lambda, not the enclosing function.
     */
    void TrySwallow(const std::function<void()>& f) noexcept;

    /**
     * Simple replacement for try-catch. Converts all exceptions to SdkError so a single catch block can be
     * used. This function is designed to work with C++ lambdas.
     *
     * Invokes try_block(), if any exceptions are thrown they are converted to SdkError
     * and catch_block() is called with the exception.
     *
     * Exceptions thrown from catch_block() are rethrown. They are not converted or translated to
     * SdkError.
     *
     * Examples:
     *
     *   void Foo(bool try_throw) {
     *     TryCatch([&] {
     *       std::cout << "try" << std::endl;
     *       if(try_throw) {
     *         Throw(ErrorCodes::UNEXPECTED, "try threw");
     *       }
     *       std::cout << "try complete" << std::endl;
     *     }, [&](SdkError& e) {
     *       std::cout << "catch" << std::endl;
     *     });
     *     std::cout << "foo" << std::endl;
     *   }
     *
     *   void Bar() {
     *     Foo(false); // prints "try", "try complete", then "foo"
     *     Foo(true); // prints "try", "catch", then "foo"
     *   }
     *
     * Remember that returning from a C++11 lamba only exits the lambda, not the enclosing function.
     */
    void TryCatch(const std::function<void()>& try_block,
                  const std::function<void(SdkError& error)>& catch_block);


    /**
     * Simple replacement for try-catch that adds a java-like finally. Converts all exceptions to
     * SdkError so a single catch block can be used. This function is designed to work with
     * C++ lambdas.
     *
     * Invokes try_block(), if any exceptions are thrown they are converted to SdkError
     * and catch_block() is called with the exception. Before returning, the function always calls
     * finally_block().
     *
     * Exceptions thrown from catch_block() or finally_block() are rethrown. They are not converted
     * to SdkErrors. If catch_block() throws an exception, finally_block() will still be invoked.
     *
     * Examples:
     *
     *   void Foo(bool try_throw) {
     *     TryCatchFinally([&] {
     *       std::cout << "try" << std::endl;
     *       if(try_throw) {
     *         Throw(SdkErrorCode::UNEXPECTED, "try threw");
     *       }
     *       std::cout << "try complete" << std::endl;
     *     }, [&](SdkError& e) {
     *       std::cout << "catch" << std::endl;
     *     }, [&]() {
     *       std::cout << "finally" << std::endl;
     *     });
     *     std::cout << "foo" << std::endl;
     *   }
     *
     *   void Bar() {
     *     Foo(false); // prints "try", "try complete", "finally", then "foo"
     *     Foo(true); // prints "try", "catch", "finally", then "foo"
     *   }
     *
     * Remember that returning from a C++11 lamba only exits the lambda, not the enclosing function.
     */
    void TryCatchFinally(const std::function<void()>& try_block,
                         const std::function<void(SdkError& error)>& catch_block,
                         const std::function<void()>& finally_block);

    /**
     * C++ version of a java-like finally. This function is designed to work with C++ lambdas.
     *
     * Invokes try_block(), if any exceptions are thrown they are bubbled up (unconverted).
     * Before exiting, the function always calls finally_block().
     *
     * Exceptions thrown from finally_block() are rethrown. They are not converted to SdkExceptions.
     *
     * Examples:
     *
     *   void Foo(bool try_throw) {
     *     TryFinally([=] {
     *       std::cout << "try" << std::endl;
     *       if(try_throw) {
     *         Throw(SdkErrorCode::UNEXPECTED, "try threw");
     *       }
     *       std::cout << "try complete" << std::endl;
     *     }, [=]() {
     *       std::cout << "finally" << std::endl;
     *     });
     *     std::cout << "foo" << std::endl;
     *   }
     *
     *   void Bar() {
     *     Foo(false); // prints "try", "try complete", "finally", then "foo"
     *     Foo(true); // prints "try", "finally", then throws
     *   }
     *
     * Remember that returning from a C++11 lamba only exits the lambda, not the enclosing function.
     */
    void TryFinally(const std::function<void()>& try_block,
                    const std::function<void()>& finally_block);

    /**
     * Throws an SdkError, setting the stack trace if available.
     *
     * Deprecated. Use ADOBE_THROW instead.
     */
    [[noreturn]]
    ADOBE_DEPRECATED(void Throw(SdkError error));

    /**
     * Creates and throws an SdkError, setting the stack trace if available.
     *
     * Deprecated. Use ADOBE_THROW instead.
     */
    [[noreturn]]
    ADOBE_DEPRECATED(void Throw(const std::string& code, const std::string& message));

    /**
     * Creates and throws an SdkError, setting the stack trace if available.
     *
     * Deprecated. Use ADOBE_THROW instead.
     */
    [[noreturn]]
    ADOBE_DEPRECATED(void Throw(const std::string& code, const std::string& message, const SdkError& inner));

    /**
     * ADOBE_THROW(const SdkError& error)
     * ADOBE_THROW(const std::string& code, const std::string& message)
     * ADOBE_THROW(const std::string& code, const std::string& message, const SdkError& inner)
     *
     * Throws an SdkError setting the stack trace and providing line number information when available.
     */
#define ADOBE_THROW(...) \
	    do { \
	        throw AdobeMarketingMobile::SdkError{__VA_ARGS__, ADOBE_GET_CURRENT_DEBUG_INFO()}; \
	    } while(false)

    /**
     * Namespace that contains SdkError codes. @see SdkError
     */
    namespace ErrorCodes {
        constexpr static const char* NOTHING = ""; ///< Special error code for default constructed SdkErrors. Do not use
        constexpr static const char* OK = "general.ok"; ///< The operation completed successfully.
        constexpr static const char* INVALID_ARGUMENT = "general.invalid_argument"; ///< A function was called with bad argument
        constexpr static const char* UNEXPECTED = "general.unexpected"; ///< An error that should never occur occurred
        constexpr static const char* UNSUPPORTED = "general.unsupported"; ///< The desired functionality is not supported
        constexpr static const char* UNKNOWN_EXCEPTION = "general.unknown_exception"; ///< An unrecognized exception was thrown

        // Standard library errors
        constexpr static const char* STD_ERROR = "std"; ///< A standard library error occurred.
        constexpr static const char* STD_LOGIC_ERROR = "std.logic_error"; ///< A std::logic_error occurred.
        constexpr static const char* STD_DOMAIN_ERROR = "std.logic_error.domain_error"; ///< A std::domain_error occurred.
        constexpr static const char* STD_INVALID_ARGUMENT =
                    "std.logic_error.invalid_argument"; ///< A std::invalid_argument occurred.
        constexpr static const char* STD_LENGTH_ERROR = "std.logic_error.length_error"; ///< A std::length_error occurred.
        constexpr static const char* STD_OUT_OF_RANGE = "std.logic_error.out_of_range"; ///< A std::out_of_range occurred.
        constexpr static const char* STD_FUTURE_ERROR = "std.logic_error.future_error"; ///< A std::future_error occurred.
        constexpr static const char* STD_RUNTIME_ERROR = "std.runtime_error"; ///< A std::runtime_error occurred.
        constexpr static const char* STD_SYSTEM_ERROR = "std.runtime_error.system_error";  ///< A std::system_error occurred.
        constexpr static const char* STD_RANGE_ERROR = "std.runtime_error.range_error"; ///< A std::range_error occurred.
        constexpr static const char* STD_OVERFLOW_ERROR =
                    "std.runtime_error.overflow_error"; ///< A std::overflow_error occurred.
        constexpr static const char* STD_UNDERFLOW_ERROR =
                    "std.runtime_error.underflow_error"; ///< A std::underflow_error occurred.
        constexpr static const char* STD_BAD_CAST = "std.bad_cast"; ///< A std::bad_cast occurred.
        constexpr static const char* STD_BAD_TYPEID = "std.bad_typeid"; ///< A std::bad_typeid occurred.
        constexpr static const char* STD_BAD_EXCEPTION = "std.bad_exception"; ///< A std::bad_exception occurred.
        constexpr static const char* STD_BAD_ALLOC = "std.bad_alloc"; ///< A std::bad_alloc occurred.
        constexpr static const char* STD_BAD_ARRAY_NEW_LENGTH =
                    "std.bad_alloc.bad_array_new_length"; ///< A std::bad_array_new_length occurred.
        constexpr static const char* STD_BAD_WEAK_PTR = "std.bad_weak_ptr"; ///< A std::bad_weak_ptr occurred.
        constexpr static const char* STD_BAD_FUNCTION_CALL =
                    "std.bad_function_call"; ///< A std::bad_function_call occurred.
    }
}

#endif //ADOBEMOBILE_CORE_SDKERROR_H
