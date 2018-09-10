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

#ifndef ADOBEMOBILE_TARGET_TARGETCONSTANTS_H
#define ADOBEMOBILE_TARGET_TARGETCONSTANTS_H

#include <chrono>
#include <map>
#include <string>

namespace AdobeMarketingMobile {
    /**
     * TargetConstants class holds all const values used only by the Target module
     */
    class TargetConstants {

    public:
        // general strings
        static const std::string LOG_PREFIX;

        static const std::string API_URL_HOST_BASE;
        static const std::string PREFETCH_API_URL_BASE;
        static const std::string DATASTORE_KEY;
        static const std::string A4T_ACTION_NAME;
        static const std::string SESSION_ID_HEADER;
        static const std::chrono::milliseconds TOKEN_EXPIRY_MILLIS;

        // data store
        static const std::string TNT_ID;
        static const std::string THIRD_PARTY_ID;
        static const std::string EDGE_HOST;
        static const std::string MOST_RECENT_REQUEST_TIMESTAMP;

        // target preview constants
        static const std::string PREVIEW_MESSAGE_ID;
        static const std::string PREVIEW_PARAMETERS;
        static const std::string PREVIEW_TOKEN;
        static const std::string PREVIEW_ENDPOINT;
        static const std::string DEFAULT_TARGET_PREVIEW_ENDPOINT;
        static const std::string PREVIEW_QA_MODE;
        static const std::chrono::seconds DEFAULT_CONNECTION_TIMEOUT_SEC;
        static const std::string DEEPLINK;
        static const std::string DEEPLINK_SCHEME;
        static const std::string DEEPLINK_SCHEME_PATH_CANCEL;
        static const std::string DEEPLINK_SCHEME_PATH_CONFIRM;

        class ContextDataKeys {
        public:
            static const std::string INSTALL_EVENT_KEY;
            static const std::string LAUNCH_EVENT_KEY;
            static const std::string CRASH_EVENT_KEY;
            static const std::string UPGRADE_EVENT_KEY;
            static const std::string DAILY_ENGAGED_EVENT_KEY;
            static const std::string MONTHLY_ENGAGED_EVENT_KEY;
            static const std::string INSTALL_DATE;
            static const std::string LAUNCHES;
            static const std::string PREVIOUS_SESSION_LENGTH;
            static const std::string DAYS_SINCE_FIRST_LAUNCH;
            static const std::string DAYS_SINCE_LAST_LAUNCH;
            static const std::string HOUR_OF_DAY;
            static const std::string DAY_OF_WEEK;
            static const std::string OPERATING_SYSTEM;
            static const std::string APPLICATION_IDENTIFIER;
            static const std::string DAYS_SINCE_LAST_UPGRADE;
            static const std::string LAUNCHES_SINCE_UPGRADE;
            static const std::string ADVERTISING_IDENTIFIER;
            static const std::string DEVICE_NAME;
            static const std::string DEVICE_RESOLUTION;
            static const std::string CARRIER_NAME;
            static const std::string LOCALE;
            static const std::string RUN_MODE;
            static const std::string IGNORED_SESSION_LENGTH;
            static const std::string ACTION_KEY;
            static const std::string INTERNAL_ACTION_KEY;
            static const std::string TIME_SINCE_LAUNCH_KEY;

            static const std::map<std::string, std::string> MAP_TO_CONTEXT_DATA_KEYS;

        private:
            ContextDataKeys() = delete;
        };

#pragma mark - EventDataKeys
        class EventDataKeys {
        public:
            static const std::string STATE_OWNER;

            // target keys
            class Target {
            public:
                static const std::string CLEAR_PREFETCH_CACHE;
                static const std::string LOAD_REQUESTS;
                static const std::string PREFETCH_REQUESTS;
                static const std::string PREFETCH_RESULT;
                static const std::string PREVIEW_RESTART_DEEP_LINK;
                static const std::string PROFILE_PARAMETERS;
                static const std::string RESET_EXPERIENCE;
                static const std::string SHARED_STATE_NAME;
                static const std::string TARGET_CONTENT;
                static const std::string THIRD_PARTY_ID;
                static const std::string TNT_ID;
            private:
                Target() = delete;
            };

            // analytics keys
            class Analytics {
            public:
                static const std::string CONTEXT_DATA;
                static const std::string TRACK_INTERNAL;
                static const std::string TRACK_ACTION;
            private:
                Analytics() = delete;
            };

            // audience keys
            class Audience {
            public:
                static const std::string SHARED_STATE_NAME;
                static const std::string DPID;
                static const std::string DPUUID;
                static const std::string UUID;
            private:
                Audience() = delete;
            };

            // configuration keys
            class Configuration {
            public:
                static const std::string SHARED_STATE_NAME;
                static const std::string GLOBAL_CONFIG_PRIVACY;
                static const std::string ACQUISITION_CONFIG_APPID;
                static const std::string ACQUISITION_CONFIG_SERVER;
                static const std::string IDENTITY_ADID_ENABLED;
                static const std::string IDENTITY_ADID_TIMEOUT;
                static const std::string TARGET_CLIENT_CODE;
                static const std::string TARGET_NETWORK_TIMEOUT;
                static const std::string TARGET_ENVIRONMENT_ID;
            private:
                Configuration() = delete;
            };

            // identity keys
            class Identity {
            public:
                static const std::string SHARED_STATE_NAME;
                static const std::string VISITOR_ID_MID;
                static const std::string VISITOR_ID_BLOB;
                static const std::string VISITOR_ID_LOCATION_HINT;
                static const std::string VISITOR_IDS_LIST;
                static const std::string ADVERTISING_IDENTIFIER;
            private:
                Identity() = delete;
            };

            // lifecycle keys
            class Lifecycle {
            public:
                static const std::string SHARED_STATE_NAME;
                static const std::string ADDITIONAL_CONTEXT_DATA;
                static const std::string APP_ID;
                static const std::string CARRIER_NAME;
                static const std::string CRASH_EVENT;
                static const std::string DAILY_ENGAGED_EVENT;
                static const std::string DAY_OF_WEEK;
                static const std::string DAYS_SINCE_FIRST_LAUNCH;
                static const std::string DAYS_SINCE_LAST_LAUNCH;
                static const std::string DAYS_SINCE_LAST_UPGRADE;
                static const std::string DEVICE_NAME;
                static const std::string DEVICE_RESOLUTION;
                static const std::string HOUR_OF_DAY;
                static const std::string IGNORED_SESSION_LENGTH;
                static const std::string INSTALL_DATE;
                static const std::string INSTALL_EVENT;
                static const std::string LAUNCH_EVENT;
                static const std::string LAUNCHES;
                static const std::string LAUNCHES_SINCE_UPGRADE;
                static const std::string LIFECYCLE_ACTION_KEY;
                static const std::string LIFECYCLE_CONTEXT_DATA;
                static const std::string LIFECYCLE_PAUSE;
                static const std::string LIFECYCLE_START;
                static const std::string LOCALE;
                static const std::string MAX_SESSION_LENGTH;
                static const std::string MONTHLY_ENGAGED_EVENT;
                static const std::string OPERATING_SYSTEM;
                static const std::string PREVIOUS_SESSION_LENGTH;
                static const std::string PREVIOUS_SESSION_PAUSE_TIMESTAMP;
                static const std::string PREVIOUS_SESSION_START_TIMESTAMP;
                static const std::string RUN_MODE;
                static const std::string SESSION_EVENT;
                static const std::string SESSION_START_TIMESTAMP;
                static const std::string UPGRADE_EVENT;
            private:
                Lifecycle() = delete;
            };

        private:
            EventDataKeys() = delete;
        };

    private:
        TargetConstants() = delete;    ///< TargetConstants should not be instantiated
    };
}

#endif /* ADOBEMOBILE_TARGET_TARGETCONSTANTS_H */
