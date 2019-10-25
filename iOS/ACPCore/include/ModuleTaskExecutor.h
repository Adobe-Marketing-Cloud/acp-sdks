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

#ifndef ADOBEMOBILE_CORE_MODULETASKEXECUTOR_H
#define ADOBEMOBILE_CORE_MODULETASKEXECUTOR_H

#include "TaskExecutorInterface.h"

namespace AdobeMarketingMobile {
    class Module;

    /**
     * A ModuleTaskExecutorInterface is the task executor used by modules.
     *
     * It is a parallel task executor that proxies tasks to the master task executor,
     * adding safety precautions to the scheduled tasks to prevent common asynchronous coding errors.
     *
     * @see ModuleThreadingService
     */
    class ModuleTaskExecutorInterface : public virtual TaskExecutorInterface {
    public:
        /**
         * @param module - the Module this is associated with
         * @param master_task_executor - the master task executor
         * @return a new ModuleTaskExecutorInterface instance
         */
        static std::shared_ptr<ModuleTaskExecutorInterface> Create(const std::shared_ptr<Module>& module,
                const std::shared_ptr<TaskExecutorInterface>& master_task_executor);
    };
}

#endif
