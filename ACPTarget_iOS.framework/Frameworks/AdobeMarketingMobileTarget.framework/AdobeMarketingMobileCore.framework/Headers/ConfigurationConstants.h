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
                static const std::string CONFIGURATION_REQUEST_CONTENT_UPDATE_CONFIG;
                static const std::string CONFIGURATION_REQUEST_CONTENT_RETRIEVE_CONFIG;

            private:
                Configuration() = delete;
            };

        private:
            EventDataKeys() = delete;
        };

    private:
        ConfigurationConstants() = delete;
    };
}

#endif /* ADOBEMOBILE_CONFIGURATION_CONFIGURATIONCONSTANTS_H */
