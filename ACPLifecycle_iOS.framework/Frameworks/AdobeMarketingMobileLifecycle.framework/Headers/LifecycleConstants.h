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

#ifndef ADOBEMOBILE_LIFECYCLE_LIFECYCLECONSTANTS_H
#define ADOBEMOBILE_LIFECYCLE_LIFECYCLECONSTANTS_H

#include <string>

namespace AdobeMarketingMobile {
    /**
     * Lifecycle constants class holds all const values used only by the Lifecycle module
     */
    class LifecycleConstants {

    public:
        static const std::string    LOG_PREFIX;
        static const std::string    DATA_STORE_NAME;
        static const long           MAX_SESSION_LENGTH_SECONDS;
        static const int32_t        DEFAULT_LIFECYCLE_TIMEOUT;

        // event data values
        static const std::string CRASH_EVENT_VALUE;
        static const std::string DAILY_ENG_USER_VALUE;
        static const std::string INSTALL_EVENT_VALUE;
        static const std::string LAUNCH_EVENT_VALUE;
        static const std::string MONTHLY_ENG_USER_VALUE;
        static const std::string UPGRADE_EVENT_VALUE;


        /**
         * Module datastore keys
         */
        class DataStoreKeys {
        public:
            static const std::string LIFECYCLE_DATA;
            static const std::string START_DATE;
            static const std::string INSTALL_DATE;
            static const std::string UPGRADE_DATE;
            static const std::string LAST_USED_DATE;
            static const std::string LAUNCHES_AFTER_UPGRADE;
            static const std::string LAUNCHES;
            static const std::string LAST_VERSION;
            static const std::string PAUSE_DATE;
            static const std::string SUCCESSFUL_CLOSE;

        private:
            DataStoreKeys() = delete;
        };

#pragma mark - EventDataKeys
        class EventDataKeys {
        public:
            static const std::string STATE_OWNER;

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


            // configuration keys
            class Configuration {

            public:
                static const std::string SHARED_STATE_NAME;
                static const std::string LIFECYCLE_CONFIG_SESSION_TIMEOUT;
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
        LifecycleConstants() = delete;
    };
}

#endif /* ADOBEMOBILE_LIFECYCLE_LIFECYCLECONSTANTS_H */
