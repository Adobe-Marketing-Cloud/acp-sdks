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

#ifndef ADOBEMOBILE_PLATFORMSHIM_THREADINGSERVICEINTERFACE_H
#define ADOBEMOBILE_PLATFORMSHIM_THREADINGSERVICEINTERFACE_H

#include <memory>
#include <string>
#include <locale>
#include <fstream>
#include "ObjectInterface.h"
#include "TaskExecutorInterface.h"

namespace AdobeMarketingMobile {
    /**
     * A ThreadingServiceInterface provides access to threading related capabilities.
     */
    class ThreadingServiceInterface : public virtual ObjectInterface {
    public:
        /**
         * Creates a task executor that sequentially executes tasks.
         *
         * @param name - the name of the task executor (used for logging and debugging)
         *
         * @return a new task executor
         */
        virtual std::shared_ptr<TaskExecutorInterface> CreateSequentialTaskExecutor(const std::string& name) = 0;

        /**
         * Creates a task executor that executes tasks in parallel.
         *
         * @param name - the name of the task executor (used for logging and debugging)
         *
         * @return a new task executor
         */
        virtual std::shared_ptr<TaskExecutorInterface> CreateParallelTaskExecutor(const std::string& name) = 0;
    };
}

#endif /* ADOBEMOBILE_PLATFORMSHIM_THREADINGSERVICEINTERFACE_H */
