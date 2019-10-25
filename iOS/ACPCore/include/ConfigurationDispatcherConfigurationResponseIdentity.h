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

#ifndef ADOBEMOBILE_CONFIGURATION_CONFIGURATIONDISPATCHERCONFIGURATIONRESPONSEIDENTITY_H
#define ADOBEMOBILE_CONFIGURATION_CONFIGURATIONDISPATCHERCONFIGURATIONRESPONSEIDENTITY_H

#include "Configuration.h"
#include "ModuleEventDispatcher.h"

namespace AdobeMarketingMobile {
    /**
     * @class ConfigurationDispatcherConfigurationResponseIdentity
     * Event dispatcher for the Configuration Response Identity Events.
     */
    class ConfigurationDispatcherConfigurationResponseIdentity : public ModuleEventDispatcher<Configuration> {

    public:

        /**
         * Dispatches EventType#CONFIGURATION , EventSource#RESPONSE_IDENTITY event into the EventHub
         * with #sdk_identities_json string for the given #pair_id.
         *
         * @param sdk_identities_json A Jsonstring containing all the identities
         * @param pair_id A unique pairing id for one-time listener
         */
        virtual void DispatchAllIdentities(const std::string& sdk_identities_json, const std::string& pair_id);

    };
}


#endif /* ADOBEMOBILE_CONFIGURATION_CONFIGURATIONDISPATCHERCONFIGURATIONRESPONSEIDENTITY_H */
