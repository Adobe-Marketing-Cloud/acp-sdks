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
            private:
                Configuration() = delete;
            };

        private:
            EventDataKeys() = delete;
        };


    private:
        CoreConstants() = delete;
    };
}

#endif /* ADOBEMOBILE_CORE_CORECONSTANTS_H */

