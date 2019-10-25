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

#ifndef ADOBEMOBILE_CONFIGURATION_CONFIGURATIONLISTENERREQUESTIDENTITY_H
#define ADOBEMOBILE_CONFIGURATION_CONFIGURATIONLISTENERREQUESTIDENTITY_H

#include "Configuration.h"
#include "Event.h"
#include "ModuleEventListener.h"

namespace AdobeMarketingMobile {
    /**
     * @class ConfigurationListenerRequestIdentity
     * Listener for Configuration Request Identity events.
     */
    class ConfigurationListenerRequestIdentity : public ModuleEventListener<Configuration> {
    public:
        /**
         * Callback for Configuration Request Identity events.
         *
         * @param event Configuration Request Identity event.
         */
        void Hear(const std::shared_ptr<Event>& event) override;
    };
}


#endif /* ADOBEMOBILE_CONFIGURATION_CONFIGURATIONLISTENERREQUESTIDENTITY_H */
