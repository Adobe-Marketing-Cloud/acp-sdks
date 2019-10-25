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

#ifndef ADOBEMOBILE_CORE_TASKEXECUTORINTERFACE_H
#define ADOBEMOBILE_CORE_TASKEXECUTORINTERFACE_H

#include <string>
#include <thread>
#include <chrono>
#include "Object.h"
#include "ObjectInterface.h"

namespace AdobeMarketingMobile {

    class PlatformServicesInterface;
    class SdkError;
    class SystemInfoServiceInterface;

    /**
     * @class TaskExecutorInterface
     *
     * A TaskExecutorInterface is a standard thread pool and task queue.
     *
     * A TaskExecutorInterface manages a set of zero or more workers and a task queue. AddTask() adds tasks to the back
     * of the queue. Workers remove tasks from the queue (in FIFO order) and execute them. If a TaskExecutor has a
     * single worker, tasks must be executed in the same order in which AddTask() was called. When a TaskExecutor
     * has multiple workers, there are no ordering guarantees between task executions.
     *
     * TaskExecutor provides a C++11 implementation of TaskExecutorInterface that suits most needs.
     */
    class TaskExecutorInterface : public virtual ObjectInterface {
    public:
        /**
         * Constants
         *
         */
        static const char* DEFAULT_TASK_NAME;
        static const std::chrono::milliseconds NO_DISPOSE_WAIT;
        static const std::chrono::milliseconds MAX_DISPOSE_WAIT;
        static const std::chrono::milliseconds DEFAULT_DISPOSE_WAIT;

        /**
         * Argument object for TaskExecutorInterface::Create
         */
        class CreateArgs : public Object {
        public:
            /**
             * Creates a new CreateArgs.
             */
            static std::shared_ptr<CreateArgs> Create();

            /**
             * Equivalent to:
             * ```
             *     this->initial_threads = thread_count;
             *     this->minimum_threads = thread_count;
             *     this->maximum_threads = thread_count;
             * ```
             */
            void SetFixedThreadCount(uint32_t thread_count);

            /**
             * Equivalent to:
             * ```
             *    this->system_info_service = platform_services ? platform_services->GetSystemInfoService() : nullptr;
             * ```
             */
            void SetPlatformServices(const std::shared_ptr<PlatformServicesInterface>& platform_services);


            std::string name; /// the name of the task executor (defaults to empty string)
            uint32_t initial_threads; /// the initial number of threads to spawn (defaults to 1)
            uint32_t minimum_threads; /// the minimum number of threads to have alive (defaults to 1)
            uint32_t maximum_threads; /// the maximum number of threads to spawn (defaults to 1)
            std::chrono::milliseconds
            max_thread_idle_duration; /// duration a thread may be idle before garbage collecting (defaults to 15 seconds)
            std::shared_ptr<SystemInfoServiceInterface> system_info_service; /// the system info service

        private:
            CreateArgs();
        };

        /**
         * @brief Creates a new task executor.
         *
         * The executor returned by this method spawns actual threads. To maximize performance, use this method sparingly.
         *
         * If you have access to platform services, use one of the following:
         * - `ThreadingServiceInterface::CreateParallelTaskExecutor(...)`
         * - `ThreadingServiceInterface::CreateSequentialTaskExecutor(...)`
         * These methods are implemented in a way that uses less resources.
         *
         */
        static std::shared_ptr<TaskExecutorInterface> Create(const std::shared_ptr<CreateArgs>& args);

        /**
         * Equivalent to:
         * ```
         *    auto create_args = TaskExecutorInterface::CreateArgs::Create();
         *    create_args->SetFixedThreadCount(thread_count);
         *    return TaskExecutor::Create(create_args);
         * ```
         */
        static std::shared_ptr<TaskExecutorInterface> CreateFixedThreaded(uint32_t thread_count);

        /**
         * @brief Cleans up resources associated with this.
         *
         * Equivalent to:
         *
         *     Dispose(DEFAULT_DISPOSE_WAIT);
         *
         * Example:
         *
         *      std::shared_ptr<TaskExecutor> pool = TaskExecutorInterface::CreateFixedThreaded(4);
         *      ...
         *
         *      pool->Dispose();
         */
        bool Dispose();

        /**
         * @brief Cleans up resources associated with this.
         *
         * Tell all workers to stop consuming tasks. Tasks already in progress will continue
         * to run, but no new tasks will be started. All pending tasks will be dropped.
         *
         * Waits up to `wait_time` millseconds for workers to terminate cleanly. `wait_time` is capped at 10s.
         *
         * Example #1:
         *
         *      std::shared_ptr<TaskExecutorInterface> pool = TaskExecutorInterface::CreateFixedThreaded(4);
         *      ...
         *      // shutdown and wait up to 1s for threads to terminate
         *
         *      pool->Dispose(std::chrono::milliseconds(1000));
         *
         * Example #2:
         *
         *      std::shared_ptr<TaskExecutorInterface> pool = TaskExecutorInterface::CreateFixedThreaded(4);
         *      ...
         *      // shutdown and don't wait for threads to terminate
         *
         *      pool->Dispose(NO_DISPOSE_WAIT);
         *
         * @param wait_time - maximum time to wait for threads to finish (defaults to 10ms)
         * @return true if threads have actually shutdown, false otherwise
         */
        bool Dispose(std::chrono::milliseconds wait_time);

        /**
         * @brief Adds a task to the queue.
         *
         * Equivalent to:
         *
         *      AddTask(task_callback, [](std::string, SdkError&) {}, DEFAULT_TASK_NAME);
         *
         * Example:
         *
         *      std::shared_ptr<TaskExecutorInterface> pool = TaskExecutorInterface::CreateFixedThreaded(4);
         *      ...
         *      pool->AddTask([&](){
         *          // do some work here, thrown exceptions are ignored
         *      });
         *
         * @param task_callback - a callable object passed with "unique" ownership.
         * @return true if task was added, false if Dispose() was called
         */
        bool AddTask(std::function<void()> task_callback);

        /**
         * @brief Adds a task to the queue.
         *
         * Equivalent to:
         *
         *      AddTask(task_callback, error_callback, DEFAULT_TASK_NAME);
         *
         * Example:
         *
         *      std::shared_ptr<TaskExecutorInterface> pool = TaskExecutorInterface::CreateFixedThreaded(4);
         *      ...
         *      pool->AddTask([&](){
         *          // do some work here, thrown exceptions are handed to your callback
         *      }, [&](std::string name, SdkError& e){
         *          // handle the failure -  default name passed
         *      });
         *
         * @param task_callback - a callable object passed with "unique" ownership.
         * @param error_callback - a callable object passed with "unique" ownership, taking string and error parameters.
         * @return true if task was added, false if Dispose() was called
         */
        bool AddTask(std::function<void()> task_callback,
                     std::function<void(std::string, SdkError&)> error_callback);

        /**
         * @brief Add a task to the queue.
         *
         * After queuing, the task will be asynchronously executed by a worker. To execute the task, the worker
         * will invoke `task_callback()`. If an error occurs, `error_callback(task_name, error)` will be invoked where
         * `task_name` is the passed-in task name, and `error` represents the error that occurred.
         *
         * A TaskExecutorInterface with a single worker will always execute tasks in the order in which AddTask() was
         * called. A TaskExecutorInterface with multiple workers provides no such guarantee.
         *
         * Calling AddTask() after Dispose() is a noop.
         *
         * Example:
         *
         *      std::shared_ptr<TaskExecutor> pool = TaskExecutorInterface::CreateFixedThreaded(4);
         *      ...
         *      pool->AddTask([&](){
         *          // do some work here, thrown exceptions are handed to your callback
         *      }, [&](std::string name, SdkError& e){
         *          // handle the failure -  "sketchy_task" passed for name
         *      }, "sketchy_task");
         *
         * @param task_callback - a callable object passed with "unique" ownership.
         * @param error_callback - a callable object passed with "unique" ownership, taking string and error parameters.
         * @param task_name - a name to use for identifying this task. Reported to error_callback.
         * @return true if task was added, false if Dispose() was called
         */
        bool AddTask(std::function<void()> task_callback,
                     std::function<void(std::string, SdkError&)> error_callback,
                     const std::string& task_name);

    protected:
        /**
         * Actual implementation of AddTask. Subclasses should override this.
         */
        virtual bool AddTaskImpl(std::function<void()> task_callback,
                                 std::function<void(std::string, SdkError&)> error_callback,
                                 const std::string& task_name) = 0;

        /**
         * Actual implementation of AddTask. Subclasses should override this.
         */
        virtual bool DisposeImpl(std::chrono::milliseconds wait_time) = 0;

    public:
        /**
         * @return whether or not this was fully disposed. When fully disposed, a Dispose(0) call should return true.
         */
        virtual bool IsDisposed() = 0;
    };

} // end of namespace AdobeMarketingMobile

#endif //ADOBEMOBILE_CORE_TASKEXECUTORINTERFACE_H
