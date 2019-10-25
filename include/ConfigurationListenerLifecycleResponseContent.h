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

#ifndef ADOBEMOBILE_CONFIGURATION_CONFIGURATIONLISTENERLIFECYCLERESPONSECONTENT_H
#define ADOBEMOBILE_CONFIGURATION_CONFIGURATIONLISTENERLIFECYCLERESPONSECONTENT_H

#include "Configuration.h"
#include "ModuleEventListener.h"

namespace AdobeMarketingMobile {
    /**
     * @class ConfigurationListenerLifecycleResponseContent
     * Listener for Configuration lifecycle response events.
     */
    class ConfigurationListenerLifecycleResponseContent : public ModuleEventListener<Configuration> {
    public:
        /**
         * Callback for Configuration retrieval request events.
         *
         * @param event Configuration retrieval request event.
         */
        void Hear(const std::shared_ptr<Event>& event) override;
    };
}

#endif /* ADOBEMOBILE_CONFIGURATION_CONFIGURATIONLISTENERLIFECYCLERESPONSECONTENT_H */
