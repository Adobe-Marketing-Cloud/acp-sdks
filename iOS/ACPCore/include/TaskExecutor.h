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

#ifndef ADOBEMOBILE_CORE_TASKEXECUTOR_H
#define ADOBEMOBILE_CORE_TASKEXECUTOR_H

#include "Common.h"
#include "Object.h"
#include "TaskExecutorInterface.h"

namespace AdobeMarketingMobile {

    class TaskExecutorData;
    class PlatformServicesInterface;
    class SystemInfoServiceInterface;

    /**
     * @class TaskExecutor
     *
     * TaskExecutor implements a C++11 implementation of TaskExecutorInterface.
     */
    class TaskExecutor : public Object, public virtual TaskExecutorInterface {
    public:
        friend class TaskExecutorInterface;

        static constexpr const uint32_t MAX_THREADS{16};
        static constexpr const std::chrono::milliseconds MAX_NOTIFICATION_WAIT{100};

        /**
         * Instantiate a default TaskExecutor with requested number of active worker threads.
         * The TaskExecutor will begin with num_thread detached threads watching the task queue.
         *
         * This method is deprecated.
         * - If you have access to platform services,
         *       use `ThreadingServiceInterface::CreateParallelTaskExecutor(...)` or
         *           `ThreadingServiceInterface::CreateSequentialTaskExecutor(...)`
         * - If you are testing or need dedicated threads,
         *       use `TaskExecutorInterface::Create(const std::shared_ptr<CreateArgs>&)` or
         *           `TaskExecutorInterface::CreateFixedThreaded(...)`
         *
         * Example:
         *
         *      std::shared_ptr<TaskExecutor> pool = TaskExecutor::Create(4);
         *
         * @param num_threads - number of threads in the pool must be between 1 and MAX_THREADS.
         * @return A valid TaskExecutor instance
         */
        ADOBE_DEPRECATED(static std::shared_ptr<TaskExecutor> Create(uint32_t num_threads));

        /**
         * Instantiate a named TaskExecutor with requested number of active worker threads.
         * The TaskExecutor will begin with num_thread detached threads watching the task queue.
         *
         * Example:
         *
         *      std::shared_ptr<TaskExecutor> pool = TaskExecutor::Create(4, "Worker");
         *
         * This method is deprecated.
         * - If you have access to platform services,
         *       use `ThreadingServiceInterface::CreateParallelTaskExecutor(...)` or
         *           `ThreadingServiceInterface::CreateSequentialTaskExecutor(...)`
         * - If you are testing or need dedicated threads,
         *       use `TaskExecutorInterface::Create(const std::shared_ptr<CreateArgs>&)` or
         *           `TaskExecutorInterface::CreateFixedThreaded(...)`
         *
         * @param num_threads - number of threads in the pool must be between 1 and MAX_THREADS.
         * @param name - Name for threads owned by this executor. Truncated to MAX_THREAD_NAME_LENGTH chars as needed.
         * @param platform - platform-specific services used for setting thread name.
         * @return A valid TaskExecutor instance
         */
        ADOBE_DEPRECATED(static std::shared_ptr<TaskExecutor> Create(uint32_t num_threads,
                         const std::string& name,
                         const std::shared_ptr<PlatformServicesInterface>& platform));

        /**
         * This method is deprecated.
         * - If you have access to platform services,
         *       use `ThreadingServiceInterface::CreateParallelTaskExecutor(...)` or
         *           `ThreadingServiceInterface::CreateSequentialTaskExecutor(...)`
         * - If you are testing or need dedicated threads,
         *       use `TaskExecutorInterface::Create(const std::shared_ptr<CreateArgs>&)` or
         *           `TaskExecutorInterface::CreateFixedThreaded(...)`
         */
        ADOBE_DEPRECATED(static std::shared_ptr<TaskExecutor> Create(uint32_t num_threads,
                         const std::string& name,
                         const std::shared_ptr<SystemInfoServiceInterface>& system_info));

        /**
         * Destructor
         */
        ~TaskExecutor() override;

        /**
         * @see TaskExecutorInterface
         */
        bool IsDisposed() override;

    protected:
        /**
         * @protected
         *
         * Called by Create().
         *
         */
        TaskExecutor();

        /**
         * @see TaskExecutorInterface
         */
        bool DisposeImpl(std::chrono::milliseconds wait_time) override;

        /**
         * @see TaskExecutorInterface
         */
        bool AddTaskImpl(std::function<void()> task_callback,
                         std::function<void(std::string, SdkError&)> error_callback,
                         const std::string& task_name) override;

    private:
        /**
         * Actual implementation of DisposeImpl, but non-virtual so it can be invoked from the destructor safely.
         */
        bool DisposeNonVirtualImpl(std::chrono::milliseconds wait_time);

        /**
         * @private
         *
         * Private data used by TaskExecutor and shared with worker threads.
         *
         */
        std::shared_ptr<TaskExecutorData> data_;
    };

} // end of namespace AdobeMarketingMobile

#endif //ADOBEMOBILE_CORE_TASKEXECUTOR_H
