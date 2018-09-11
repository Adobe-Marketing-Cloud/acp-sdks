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

#ifndef SIGNAL_SIGNALCONSTANTS_H
#define SIGNAL_SIGNALCONSTANTS_H

#include <chrono>
#include <string>

namespace AdobeMarketingMobile {
    class SignalConstants {
    public:
        // general strings
        static const std::string LOG_PREFIX;

        static const std::string TEMPLATE_CALLBACK_URL;
        static const std::string TEMPLATE_CALLBACK_BODY;
        static const std::string TEMPLATE_CALLBACK_CONTENT_TYPE;
        static const std::string TEMPLATE_CALLBACK_TIMEOUT;
        static const std::chrono::seconds TEMPLATE_TIMEOUT_DEFAULT;

#pragma mark - EventDataKeys
        class EventDataKeys {
        public:

            // signal constants
            class Signal {
            public:
                static const std::string SHARED_STATE_NAME;
                static const std::string RULES_CONSEQUENCE_TYPE_POSTBACKS;
                static const std::string RULES_CONSEQUENCE_TYPE_PII;
                static const std::string RULES_CONSEQUENCE_TYPE_OPEN_URL;
                static const std::string OPENURL_URL;
                static const std::string CONTEXT_DATA;

            private:
                Signal() = delete;
            };

            // configuration keys
            class Configuration {

            public:
                static const std::string SHARED_STATE_NAME;
                static const std::string GLOBAL_CONFIG_PRIVACY;

            private:
                Configuration() = delete;
            };

            // rules constants
            class RulesEngine {
            public:
                static const std::string CONSEQUENCE_TRIGGERED;
            private:
                RulesEngine() = delete;

            };

        private:
            EventDataKeys() = delete;
        };

    private:
        SignalConstants() = delete;
    };
}

#endif /* SIGNAL_SIGNALCONSTANTS_H */
