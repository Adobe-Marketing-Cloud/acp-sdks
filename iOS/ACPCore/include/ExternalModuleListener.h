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

#ifndef ADOBEMOBILE_EXTERNALMODULE_EXTERNALMODULELISTENER_H
#define ADOBEMOBILE_EXTERNALMODULE_EXTERNALMODULELISTENER_H

#include "ModuleEventListener.h"
#include "ExternalModule.h"
#include "Event.h"

namespace AdobeMarketingMobile {
    /**
     * @class ExternalModuleListener
     * Listener registered by an external module for various event types and sources
     */
    class ExternalModuleListener : public ModuleEventListener<ExternalModule> {
    public:
        void Hear(const std::shared_ptr<Event>& event) override;
    protected:
        void OnRegistered() override;
        void OnUnregistered() override;
    };
}

#endif /* ADOBEMOBILE_EXTERNALMODULE_EXTERNALMODULELISTENER_H */

