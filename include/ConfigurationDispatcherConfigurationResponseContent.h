/*
Copyright 2017 Adobe. All rights reserved.
This file is licensed to you under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License. You may obtain a copy
of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS
OF ANY KIND, either express or implied. See the License for the specific language
governing permissions and limitations under the License.
*/

#ifndef ADOBEMOBILE_CONFIGURATION_CONFIGURATIONDISPATCHERCONFIGURATIONRESPONSECONTENT_H
#define ADOBEMOBILE_CONFIGURATION_CONFIGURATIONDISPATCHERCONFIGURATIONRESPONSECONTENT_H

#include "Configuration.h"
#include "ModuleEventDispatcher.h"

namespace AdobeMarketingMobile {
    class EventData;

    /**
     * @class ConfigurationEventDispather
     * Event dispatcher for the Configuration module.
     */
    class ConfigurationDispatcherConfigurationResponseContent : public ModuleEventDispatcher<Configuration> {

    public:

        /**
         * Dispatch Configuration response event with updated configuration data.
         *
         * @param event_data Updated configuration data as EventData
         * @param pair_id A unique pairing id for the event (optional)
         */
        virtual void DispatchConfigResponseWithEventData(const std::shared_ptr<EventData>& event_data,
                const std::string& pair_id);
    };
}

#endif /* ADOBEMOBILE_CONFIGURATION_CONFIGURATIONDISPATCHERCONFIGURATIONRESPONSECONTENT_H */
