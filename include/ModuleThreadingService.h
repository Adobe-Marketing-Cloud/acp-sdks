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

#ifndef ADOBEMOBILE_CORE_MODULETHREADINGSERVICE_H
#define ADOBEMOBILE_CORE_MODULETHREADINGSERVICE_H

#include "ThreadingServiceInterface.h"

namespace AdobeMarketingMobile {
    class Module;

    /**
     * A ModuleThreadingServiceInterface is the ThreadingServiceInterface passed to Modules.
     *
     * CreateSequentialTaskExecutor and CreateParallelTaskExecutor return proxy task executors
     * that schedule jobs into the master task executor. This allows our modules to share a common
     * thread pool.
     *
     * All task executors created by this will be disposed upon disposal or destruction.
     */
    class ModuleThreadingServiceInterface : public virtual ThreadingServiceInterface {
    public:
        /**
         * @param module - the Module this platform services is associated with
         * @param master_task_executor - the master task executor
         * @return a new ModuleThreadingServiceInterface instance
         */
        static std::shared_ptr<ModuleThreadingServiceInterface> Create(const std::shared_ptr<Module>& module,
                const std::shared_ptr<TaskExecutorInterface>& master_task_executor);

        /**
         * Cleans up resources used by this.
         */
        virtual bool Dispose(std::chrono::milliseconds max_wait_duration) = 0;
    };
}

#endif
