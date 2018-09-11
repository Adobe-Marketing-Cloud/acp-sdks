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

#ifndef ADOBEMOBILE_IDENTITY_IDENTITY_CONSTANTS_H
#define ADOBEMOBILE_IDENTITY_IDENTITY_CONSTANTS_H

#include <string>
#include "Identity.h"

namespace AdobeMarketingMobile {
    class IdentityConstants {

    public:

        static const std::string LOG_PREFIX;

        class Default {
        public:
            static const int32_t DEFAULT_TTL_VALUE;
            static const std::string SERVER;
            static const std::string CID_DELIMITER;
            static const std::chrono::seconds TIMEOUT;
            static const bool DEFAULT_SSL;
            static const bool DEFAULT_ADID_ENABLED;
            static const MobilePrivacyStatus DEFAULT_MOBILE_PRIVACY;
        private:
            Default() = delete;
        };

        class DataStoreKeys {
        public:
            static const std::string VISITOR_IDS_STRING;
            static const std::string MARKETING_CLOUD_ID;
            static const std::string MARKETING_CLOUD_ORG_ID;
            static const std::string LOCATION_HINT;
            static const std::string BLOB;
            static const std::string TTL;
            static const std::string LAST_SYNC;
            static const std::string VISITOR_ID;
            static const std::string ADVERTISING_IDENTIFIER;
            static const std::string PUSH_IDENTIFIER;
            static const std::string PUSH_ENABLED;
        private:
            DataStoreKeys() = delete;
        };

        // payload parameters
        static const std::string VISITOR_PAYLOAD_KEY;
        static const std::string VISITOR_TIMESTAMP_KEY;
        static const std::string VISITOR_PAYLOAD_MARKETING_CLOUD_ORG_ID;
        static const std::string VISITOR_PAYLOAD_MARKETING_CLOUD_ID_KEY;
        static const std::string VISITOR_PAYLOAD_ANALYTICS_ID_KEY;
        static const std::string ANALYTICS_PAYLOAD_KEY;

        static const std::string RESPONSE_KEY_MID;
        static const std::string RESPONSE_KEY_BLOB;
        static const std::string RESPONSE_KEY_HINT;
        static const std::string RESPONSE_KEY_TTL;
        static const std::string RESPONSE_KEY_ERROR;
        static const std::string RESPONSE_KEY_OPT_OUT;
        static const std::string VISITOR_ID_PARAMETER_KEY_CUSTOMER;

#pragma mark - EventDataKeys
        class EventDataKeys {
        public:
            static const std::string STATE_OWNER;

            // identity keys
            class Identity {
            public:
                static const std::string SHARED_STATE_NAME;
                static const std::string ADID_DSID;
                static const std::string ADVERTISING_IDENTIFIER;
                static const std::string AUTHENTICATION_STATE;
                static const std::string BASE_URL;
                static const std::string DPIDS;
                static const std::string EVENT_PUSH_STATUS;
                static const std::string FORCE_SYNC;
                static const std::string IDENTIFIERS;
                static const std::string IS_SYNC_EVENT;
                static const std::string MCPNS_DPID;
                static const std::string PUSH_ID_ENABLED_ACTION_NAME;
                static const std::string PUSH_IDENTIFIER;
                static const std::string UPDATED_URL;
                static const std::string USER_IDENTIFIER;
                static const std::string VISITOR_ID_BLOB;
                static const std::string VISITOR_ID_LOCATION_HINT;
                static const std::string VISITOR_ID_MID;
                static const std::string VISITOR_IDS_LAST_SYNC;
                static const std::string VISITOR_IDS_LIST;
            private:
                Identity() = delete;
            };

            // analytics keys
            class Analytics {
            public:
                static const std::string SHARED_STATE_NAME;
                static const std::string ANALYTICS_ID;
                static const std::string TRACK_INTERNAL;
                static const std::string TRACK_ACTION;
                static const std::string CONTEXT_DATA;
            private:
                Analytics() = delete;
            };

            // configuration keys
            class Configuration {
            public:
                static const std::string SHARED_STATE_NAME;
                static const std::string GLOBAL_CONFIG_SSL;
                static const std::string GLOBAL_CONFIG_PRIVACY;
                static const std::string CONFIG_MARKETING_CLOUD_ORGID_KEY;
                static const std::string CONFIG_MARKETING_CLOUD_SERVER_KEY;
                static const std::string IDENTITY_ADID_ENABLED;
                static const std::string CONFIGURATION_REQUEST_CONTENT_UPDATE_CONFIG;
            private:
                Configuration() = delete;
            };

        private:
            EventDataKeys() = delete;
        };

    private:
        IdentityConstants() = delete;
    };
}

#endif /* ADOBEMOBILE_IDENTITY_IDENTITY_CONSTANTS_H */
