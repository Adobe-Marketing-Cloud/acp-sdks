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

#ifndef ADOBEMOBILE_EXTERNALMODULE_EXTERNALMODULESERVICES_H
#define ADOBEMOBILE_EXTERNALMODULE_EXTERNALMODULESERVICES_H

#include "Object.h"
#include "Event.h"
#include "SdkError.h"
#include "ExternalModuleListenerInterface.h"

namespace AdobeMarketingMobile {

    /**
     * @brief Interface providing access to event hub for the ADBModule.
     *
     */
    class ExternalModuleServicesInterface : public virtual ObjectInterface {
    public:
        virtual void RegisterListener(const std::shared_ptr<ExternalModuleListenerInterface>& event_listener,
                                      const std::string& event_type,
                                      const std::string& event_source) = 0;

        virtual void RegisterWildcardListener(const std::shared_ptr<ExternalModuleListenerInterface>& event_listener) = 0;

        virtual void SetSharedEventState(const std::string& state,
                                         const std::shared_ptr<Event>& event) = 0;

        virtual void ClearSharedEventStates() = 0;

        virtual std::shared_ptr<std::string> GetSharedEventState(const std::string& state_name,
                const std::shared_ptr<Event>& event) = 0;

        virtual void UnregisterModule() = 0;
    };

} // AdobeMarketingMobile namespace

#endif /* ADOBEMOBILE_EXTERNALMODULESERVICES_H */

