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

#ifndef ADOBEMOBILE_PLATFORMSHIM_LOG_H
#define ADOBEMOBILE_PLATFORMSHIM_LOG_H

#include "LoggingServiceInterface.h"
#include "LoggingMode.h"
#include "StringUtils.h"

namespace AdobeMarketingMobile {

    class Log : public Object {
    public:
        /**
         * Sets the platform specific logging service to use for log output
         *
         * @param 	logging_service 	LoggingService to use for log output
         *
         * @see LoggingService
         */
        static void SetLoggingService(const std::shared_ptr<LoggingServiceInterface>& logging_service);

        /**
         * @returns the current logging service
         */
        static std::shared_ptr<LoggingServiceInterface> GetLoggingService();

        /**
         * Sets the log level to operate at
         *
         * @param logging_mode 	LoggingMode to use for log output
         *
         * @see LoggingMode
         */
        static void SetLogLevel(LoggingMode logging_mode);

        /**
         * Gets the log level that the SDK is currently operating at
         *
         * @return LoggingMode describing the current level of logging.
         */
        static LoggingMode GetLogLevel();

        /**
         * Gets the probable log level that the SDK is currently operating at,
         * this may differ from the actual log level, but this call is very fast
         * and does not acquire mutexes. To know the actual log level, call GetLogLevel().
         *
         * This call is useful for preventing expensive log-related operations, but should
         * be used sparingly. Example:
         *
         *    if(GetLogLevelHint() >= LoggingMode::DEBUG_LOG) {
         *        std::string serialization = SomeExpensiveSerializationOperation();
         *        Log::Debug("foo", "the serialization: %s", serialization);
         *    }
         *
         * @return LoggingMode describing the current level of logging.
         */
        static LoggingMode GetLogLevelHint();

        /**
         * @returns true if there is probably a logging service and the mode is probably greater than mode.
         *
         * This function is fast and does not acquire mutexes. Before logging, the actual service and mode should be
         * checked.
         */
        static bool Precheck(LoggingMode mode);

        /**
         * Used to print more verbose information. Info logging is expected to follow end-to-end every method an event hits.
         * Prints information to the console only when the SDK is in LoggingMode: VERBOSE
         *
         * @param	source	the source of the information to be logged
         * @param	format	the string to be logged, @see StringUtils::FormatString()
         * @param   args    the formatting arguments, @see StringUtils::FormatString()
         *
         * @see LoggingMode
         */
        template<typename ...TArgs>
        static void Trace(const std::string& source, const char* format, const TArgs& ... args);
        template<typename ...TArgs>
        static void Trace(const char* source, const char* format, const TArgs& ... args);

        /**
         * Information provided to the debug method should contain high-level details about the data being processed.
         * Prints information to the console only when the SDK is in LoggingMode: VERBOSE, DEBUG
         *
         * @param	source	the source of the information to be logged
         * @param	format	the string to be logged, @see StringUtils::FormatString()
         * @param   args    the formatting arguments, @see StringUtils::FormatString()
         *
         * @see LoggingMode
         */
        template<typename ...TArgs>
        static void Debug(const std::string& source, const char* format, const TArgs& ... args);
        template<typename ...TArgs>
        static void Debug(const char* source, const char* format, const TArgs& ... args);

        /**
         * Information provided to the warning method indicates that a request has been made to the SDK, but the SDK
         * will be unable to perform the requested task.  An example is catching an expected or unexpected but
         * recoverable exception.
         * Prints information to the console only when the SDK is in LoggingMode: VERBOSE, DEBUG, WARNING
         *
         * @param	source	the source of the information to be logged
         * @param	format	the string to be logged, @see StringUtils::FormatString()
         * @param   args    the formatting arguments, @see StringUtils::FormatString()
         *
         * @see LoggingMode
         */
        template<typename ...TArgs>
        static void Warning(const std::string& source, const char* format, const TArgs& ... args);
        template<typename ...TArgs>
        static void Warning(const char* source, const char* format, const TArgs& ... args);

        /**
         * Information provided to the error method indicates that there has been an unrecoverable error.
         * Prints information to the console regardless of current LoggingMode of the SDK.
         *
         * @param	source	the source of the information to be logged
         * @param	format	the string to be logged, @see StringUtils::FormatString()
         * @param   args    the formatting arguments, @see StringUtils::FormatString()
         *
         * @see LoggingMode
         */
        template<typename ...TArgs>
        static void Error(const std::string& source, const char* format, const TArgs& ... args);
        template<typename ...TArgs>
        static void Error(const char* source, const char* format, const TArgs& ... args);

    private:
        Log() {}

        static std::mutex mutex; ///< @private a mutex to protect logging vars

        static LoggingMode current_mode; ///< @private the current logging mode, synchronized on mutex

        /**
         * @private the current logging service, protected by mutex
         */
        static std::shared_ptr<LoggingServiceInterface> current_service;

        /**
         * @private
         * a hint about current_service (might be wrong in sometimes).
         * true if current_service is not nullptr.
         * accessible without mutex.
         */
        static bool hint_service;

        /**
         * @private
         * a hint about current_mode (might be wrong in sometimes).
         * accessible without mutex.
         */
        static LoggingMode hint_mode;

        /**
         * @private
         * @returns the current logging service if current_mode is >= mode. synchronized.
         */
        static std::shared_ptr<LoggingServiceInterface> GetLoggingServiceIfModeGreq(LoggingMode mode);

        /**
         * @private
         * Non-generic part of Trace() implementation.
         */
        static void TraceImpl(const char* source, const std::string& s);

        /**
         * @private
         * Non-generic part of Debug() implementation.
         */
        static void DebugImpl(const char* source, const std::string& s);

        /**
         * @private
         * Non-generic part of Warning() implementation.
         */
        static void WarningImpl(const char* source, const std::string& s);

        /**
         * @private
         * Non-generic part of Error() implementation.
         */
        static void ErrorImpl(const char* source, const std::string& s);
    };
} //namespace


/////////////////////////////////////////
// template and inline implementations //
/////////////////////////////////////////

namespace AdobeMarketingMobile {
    template<typename ...TArgs>
    void Log::Trace(const std::string& source, const char* format, const TArgs& ... args) {
        Trace(source.c_str(), format, args...);
    }

    template<typename ...TArgs>
    void Log::Trace(const char* source, const char* format, const TArgs& ... args) {
        if (Precheck(LoggingMode::VERBOSE_LOG) && source != nullptr && format != nullptr) {
            TraceImpl(source, StringUtils::FormatString(format, args...));
        }
    }

    template<typename ...TArgs>
    void Log::Debug(const std::string& source, const char* format, const TArgs& ... args) {
        Debug(source.c_str(), format, args...);
    }

    template<typename ...TArgs>
    void Log::Debug(const char* source, const char* format, const TArgs& ... args) {
        if (Precheck(LoggingMode::DEBUG_LOG) && source != nullptr && format != nullptr) {
            DebugImpl(source, StringUtils::FormatString(format, args...));
        }
    }

    template<typename ...TArgs>
    void Log::Warning(const std::string& source, const char* format, const TArgs& ... args) {
        Warning(source.c_str(), format, args...);
    }

    template<typename ...TArgs>
    void Log::Warning(const char* source, const char* format, const TArgs& ... args) {
        if (Precheck(LoggingMode::WARNING_LOG) && source != nullptr && format != nullptr) {
            WarningImpl(source, StringUtils::FormatString(format, args...));
        }
    }

    template<typename ...TArgs>
    void Log::Error(const std::string& source, const char* format, const TArgs& ... args) {
        Error(source.c_str(), format, args...);
    }

    template<typename ...TArgs>
    void Log::Error(const char* source, const char* format, const TArgs& ... args) {
        if (Precheck(LoggingMode::ERROR_LOG) && source != nullptr && format != nullptr) {
            ErrorImpl(source, StringUtils::FormatString(format, args...));
        }
    }
}

#endif /* ADOBEMOBILE_PLATFORMSHIM_LOG_H */
