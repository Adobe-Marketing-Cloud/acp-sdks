/***************************************************************************
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

#ifndef ADOBEMOBILE_ACQUISITION_ACQUISITIONCONSTANTS_H
#define ADOBEMOBILE_ACQUISITION_ACQUISITIONCONSTANTS_H

#include <string>
#include <chrono>

namespace AdobeMarketingMobile {
    class AcquisitionConstants {
    public:
        static const std::string LOG_PREFIX;

        // Acquisition out keys
        static const std::string OUT_ACQUISITION_FINGERPRINTER_ADID;
        static const std::string OUT_ACQUISITION_CONTEXT_DATA_PREFIX;

        // Acquisition data keys
        static const std::string CONTEXT_DATA_KEY;
        static const std::string ADOBE_DATA_KEY;
        static const std::string LINK_DEFERRED_KEY;
        static const std::string DEEP_LINK_ID_KEY;
        static const std::string UNIQUE_ID_KEY;
        static const std::string REFERRER_DATA_JSON_STRING;
        static const std::string ACQUISITION_REFERRER_DATA_NAMESPACE;
        static const std::string ACQUISITION_ADOBE_DATA_PREFIX;

        // Referrer keys
        static const std::string CAMPAIGN_REFERRER_SOURCE;
        static const std::string CAMPAIGN_REFERRER_MEDIUM;
        static const std::string CAMPAIGN_REFERRER_TERM;
        static const std::string CAMPAIGN_REFERRER_CONTENT;
        static const std::string CAMPAIGN_REFERRER_CAMPAIGN;
        static const std::string CAMPAIGN_REFERRER_TRACKINGCODE;

        static const std::string DATA_DEEPLINK_ID;

        // Default values
        static const std::chrono::seconds ACQUISITION_TIMEOUT_DEFAULT;

        // Deeplink keys for push messaging
        static const std::string DATA_PUSH_MESSAGE_ID;
        static const std::string DATA_LOCAL_NOTIFICATION_CLICKED;
        static const std::string DATA_LOCAL_NOTIFICATION_ID;
        static const std::string ADB_TRACK_INTERNAL_PUSH_CLICK_THROUGH;
        static const std::string ADB_TRACK_INTERNAL_ADOBE_LINK;
        static const std::string ADB_TRACK_INTERNAL_LOCAL_NOTIFICATION_CLICK_THROUGH;

        // Datastore constants
        static const std::string DATASTORE_KEY;

        // event data keys used in acquisition module
        class EventDataKeys {
        public:
            static const std::string STATE_OWNER;

            // acquisition keys
            class Acquisition {
            public:
                static const std::string SHARED_STATE_NAME;
                static const std::string ACQUISITION_ADDITIONAL_PARAMETERS;
                static const std::string ACQUISITION_TYPE_INSTALL;
                static const std::string ACQUISITION_TYPE_KEY;
                static const std::string ACQUISITION_TYPE_RETENTION;
                static const std::string APP_ID_KEY;
                static const std::string CONTEXT_DATA;
                static const std::string DEEPLINK;
                static const std::string DEFERRED_DEEPLINK_KEY;
                static const std::string LOCAL_NOTIFICATION_ID;
                static const std::string OS_REFERRER_DATA_KEY;
                static const std::string PROCESSED_DEFERRED_DEEPLINK_KEY;
                static const std::string PUSH_MESSAGE_ID;
                static const std::string REFERRER_DATA;

            private:
                Acquisition() = delete;
            };

            // analytics keys
            class Analytics {
            public:
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
                static const std::string ACQUISITION_APPID;
                static const std::string ACQUISITION_SERVER;
                static const std::string IDENTITY_ADID_ENABLED;
                static const std::string IDENTITY_ADID_TIMEOUT;

            private:
                Configuration() = delete;
            };

            // identity keys
            class Identity {
            public:
                static const std::string SHARED_STATE_NAME;
                static const std::string ADVERTISING_IDENTIFIER;

            private:
                Identity() = delete;
            };

        private:
            EventDataKeys() = delete;
        };

    private:
        AcquisitionConstants() = delete;
    };
}

#endif /* ADOBEMOBILE_ACQUISITION_ACQUISITIONCONSTANTS_H */
