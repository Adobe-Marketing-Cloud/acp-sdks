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

#ifndef ADOBEMOBILE_CORE_PROXYTASKEXECUTOR_H
#define ADOBEMOBILE_CORE_PROXYTASKEXECUTOR_H

#include "TaskExecutorInterface.h"

namespace AdobeMarketingMobile {
    /**
     * A ProxyTaskExecutorInterface is a task executor that mimics a standard task executor, but
     * schedules all tasks into parent task executor.
     *
     * A ProxyTaskExecutorInterface is either sequential or parallel. A sequential task executor
     * behaves like a single threaded task executor, where tasks are guaranteed to execute sequentially
     * and non-concurrently. A parallel task executor behaves like a multi threaded task executor,
     * where tasks may execute out-of-order and concurrently.
     */
    class ProxyTaskExecutorInterface : public virtual TaskExecutorInterface {
    public:
        /**
         * @param parent_task_executor - the parent task executor where tasks will actually be executed.
         * @return a new sequential task executor
         **/
        static std::shared_ptr<ProxyTaskExecutorInterface> CreateSequential(const std::string& name,
                const std::shared_ptr<TaskExecutorInterface>& parent_task_executor);

        /**
         * @param parent_task_executor - the parent task executor where tasks will actually be executed.
         * @return a new parallel proxy task executor
         **/
        static std::shared_ptr<ProxyTaskExecutorInterface> CreateParallel(const std::string& name,
                const std::shared_ptr<TaskExecutorInterface>& parent_task_executor);
    };
} // end of namespace AdobeMarketingMobile

#endif //ADOBEMOBILE_CORE_PROXYTASKEXECUTOR_H
