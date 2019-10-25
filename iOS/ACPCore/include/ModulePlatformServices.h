/*
Copyright 2019 Adobe. All rights reserved.
This file is licensed to you under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License. You may obtain a copy
of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS
OF ANY KIND, either express or implied. See the License for the specific language
governing permissions and limitations under the License.
*/

#ifndef ADOBEMOBILE_CORE_MODULEPLATFORMSERVICES_H
#define ADOBEMOBILE_CORE_MODULEPLATFORMSERVICES_H

#include "PlatformServicesInterface.h"

namespace AdobeMarketingMobile {
    class Module;

    /**
     * A ModulePlatformServicesInterface is the PlatformServicesInterface passed to Modules.
     *
     * It is a wrapper around the PlatformServicesInterface passed to the EventHub.
     */
    class ModulePlatformServicesInterface : public virtual PlatformServicesInterface {
    public:
        /**
         * @param module - the Module this platform services is associated with
         * @param inner_platform_services - wrapped platform services
         * @param master_task_executor - the task executor
         * @return a new ModulePlatformServicesInterface instance
         */
        static std::shared_ptr<ModulePlatformServicesInterface> Create(const std::shared_ptr<Module>& module,
                const std::shared_ptr<PlatformServicesInterface>& inner_platform_services,
                const std::shared_ptr<TaskExecutorInterface>& master_task_executor);
    };
}

#endif
