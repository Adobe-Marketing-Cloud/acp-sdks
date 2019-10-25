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

#ifndef ADOBEMOBILE_EXTERNALMODULE_EXTERNALMODULEINTERFACE_H
#define ADOBEMOBILE_EXTERNALMODULE_EXTERNALMODULEINTERFACE_H

#include "Object.h"
#include "ExternalModuleServicesInterface.h"

namespace AdobeMarketingMobile {

    /**
     * @brief Interface providing access to ADBModule for the event hub.
     *
     */
    class ExternalModuleInterface : public virtual ObjectInterface {
    public:
        virtual std::string GetModuleName() = 0;
        virtual std::string GetModuleVersion() = 0;
        virtual void OnRegister(const std::shared_ptr<ExternalModuleServicesInterface>& services) = 0;
        virtual void OnUnexpectedError(SdkError& e) = 0;
        virtual void OnUnregister() = 0;
    };

} // AdobeMarketingMobile namespace

#endif /* ADOBEMOBILE_EXTERNALMODULE_EXTERNALMODULEINTERFACE_H */
