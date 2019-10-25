/*
Copyright 2018 Adobe. All rights reserved.
This file is licensed to you under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License. You may obtain a copy
of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS
OF ANY KIND, either express or implied. See the License for the specific language
governing permissions and limitations under the License.
*/

#ifndef ADOBEMOBILE_CORE_CORECONSTANTS_H
#define ADOBEMOBILE_CORE_CORECONSTANTS_H

#include <string>

namespace AdobeMarketingMobile {
    class CoreConstants {
    public:
        static const std::string CORE_VERSION;
        static const std::string SUFFIX_FOR_EACH_OBJECT;

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

