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
 ****************************************************************************/

#ifndef ADOBEMOBILE_CORE_CORECONSTANTS_H
#define ADOBEMOBILE_CORE_CORECONSTANTS_H

#include <string>

namespace AdobeMarketingMobile {
    class CoreConstants {
    public:
        static const std::string CORE_VERSION;

#pragma mark - Event Data Keys
        class EventDataKeys {
        public:
            static const std::string SHARED_STATE_OWNER;

            class Configuration {
            public:
                static const std::string SHARED_STATE_NAME;
                static const std::string GLOBAL_CONFIG_PRIVACY;
                static const std::string CONFIGURATION_REQUEST_CONTENT_JSON_APP_ID;
                static const std::string CONFIGURATION_REQUEST_CONTENT_JSON_FILE_PATH;
                static const std::string CONFIGURATION_REQUEST_CONTENT_UPDATE_CONFIG;
                static const std::string CONFIGURATION_REQUEST_CONTENT_RETRIEVE_CONFIG;
                static const std::string CONFIGURATION_RESPONSE_IDENTITY_ALL_IDENTIFIERS;
            private:
                Configuration() = delete;
            };

            class Identity {
            public:
                static const std::string ADVERTISING_IDENTIFIER;
                static const std::string PUSH_IDENTIFIER;
            private:
                Identity() = delete;
            };

            class Lifecycle {
            public:
                static const std::string ADDITIONAL_CONTEXT_DATA;
                static const std::string LIFECYCLE_ACTION_KEY;
                static const std::string LIFECYCLE_PAUSE;
                static const std::string LIFECYCLE_START;
            private:
                Lifecycle() = delete;
            };

            class RulesEngine {
            public:
                static const std::string CONSEQUENCE_TRIGGERED;
                static const std::string CONSEQUENCES_LOADED;
                static const std::string CONSEQUENCE_ID;
                static const std::string CONSEQUENCE_TYPE;
                static const std::string CONSEQUENCE_DETAIL;
                static const std::string CONSEQUENCE_ASSETS_PATH;
                static const std::string RULES_REQUEST_CONTENT_DOWNLOAD_RULES;
            private:
                RulesEngine() = delete;
            };

            class Signal {
            public:
                static const std::string CONTEXT_DATA;

            private:
                Signal() = delete;
            };

        private:
            EventDataKeys() = delete;
        };


    private:
        CoreConstants() = delete;
    };
}

#endif /* ADOBEMOBILE_CORE_CORECONSTANTS_H */

