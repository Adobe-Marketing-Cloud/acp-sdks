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

#ifndef ADOBEMOBILE_CONFIGURATION_CONFIGURATIONCONSTANTS_H
#define ADOBEMOBILE_CONFIGURATION_CONFIGURATIONCONSTANTS_H

#include <string>

namespace AdobeMarketingMobile {

    /**
     * @class ConfigurationConstants
     *
     * This class holds all constant values used by the Configuration module
     */
    class ConfigurationConstants {
    public:

#pragma mark - EventDataKeys
        class EventDataKeys {
        public:
            class Configuration {
            public:
                static const std::string SHARED_STATE_NAME;
                static const std::string CONFIGURATION_REQUEST_CONTENT_JSON_APP_ID;
                static const std::string CONFIGURATION_REQUEST_CONTENT_JSON_FILE_PATH;
                static const std::string CONFIGURATION_REQUEST_CONTENT_IS_INTERNAL_EVENT;
                static const std::string CONFIGURATION_REQUEST_CONTENT_UPDATE_CONFIG;
                static const std::string CONFIGURATION_REQUEST_CONTENT_RETRIEVE_CONFIG;
                static const std::string RULES_REMOTE_URL;
                static const std::string CONFIGURATION_RESPONSE_IDENTITY_ALL_IDENTIFIERS;
                static const std::string EVENT_STATE_OWNER;

            private:
                Configuration() = delete;
            };

        private:
            EventDataKeys() = delete;
        };


        class SharedStateKeys {
        public:

            // Analytics shared state keys
            class Analytics {
            public:
                static const std::string MODULE_NAME;
                static const std::string ANALYTICS_ID;
            private:
                Analytics() = delete;
            };

            // Audience shared state keys
            class Audience {
            public:
                static const std::string MODULE_NAME;
                static const std::string DPID;
                static const std::string DPUUID;
                static const std::string UUID;
            private:
                Audience() = delete;
            };


            // Identity shared state keys
            class Identity {
            public:
                static const std::string MODULE_NAME;
                static const std::string MID;
                static const std::string VISITOR_IDS_LIST;
                static const std::string ADVERTISING_IDENTIFIER;
                static const std::string PUSH_IDENTIFIER;
                static const std::string USER_IDENTIFIER;

            private:
                Identity() = delete;
            };


            // Configuration shared state keys
            class Configuration {
            public:
                static const std::string MODULE_NAME;
                static const std::string CONFIG_EXPERIENCE_CLOUD_ORGID_KEY;
                static const std::string ANALYTICS_CONFIG_REPORT_SUITES;
            private:
                Configuration() = delete;
            };


            // Target shared state keys
            class Target {
            public:
                static const std::string MODULE_NAME;
                static const std::string TNT_ID;
                static const std::string THIRD_PARTY_ID;
            private:
                Target() = delete;
            };


        private:
            SharedStateKeys() = delete;
        };

    private:
        ConfigurationConstants() = delete;
    };
}

#endif /* ADOBEMOBILE_CONFIGURATION_CONFIGURATIONCONSTANTS_H */
