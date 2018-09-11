/* **************************************************************************
 *
 * ADOBE CONFIDENTIAL
 * ___________________
 *
 * Copyright 2017 Adobe Systems Incorporated
 * All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Adobe Systems Incorporated and its suppliers,
 * if any.  The intellectual and technical concepts contained
 * herein are proprietary to Adobe Systems Incorporated and its
 * suppliers and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Adobe Systems Incorporated.
 **************************************************************************/

#ifndef ADOBEMOBILE_CORE_TASKEXECUTORINTERFACE_H
#define ADOBEMOBILE_CORE_TASKEXECUTORINTERFACE_H

#include <string>
#include <thread>
#include <chrono>
#include "ObjectInterface.h"

namespace AdobeMarketingMobile {

    class SdkError;

    /**
     * @class TaskExecutorInterface
     *
     * A TaskExecutorInterface is a standard thread pool + task queue. See https://en.wikipedia.org/wiki/Thread_pool.
     *
     * A TaskExecutorInterface manages a set of zero or more workers and a task queue. AddTask() adds tasks to the back
     * of the queue. Workers remove tasks from the queue (in FIFO order) and execute them. If a TaskExecutor has a
     * single worker, tasks must be executed in the same order in which AddTask() was called. When a TaskExecutor
     * has multiple workers, there are no ordering guarantees between tasks.
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
         * @brief Cleans up resources associated with this.
         *
         * Equivalent to:
         *
         *     Dispose(DEFAULT_DISPOSE_WAIT);
         *
         * Example:
         *
         *      std::shared_ptr<TaskExecutor> pool = TaskExecutor::Create(4);
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
         *      std::shared_ptr<TaskExecutorInterface> pool = TaskExecutor::Create(4);
         *      ...
         *      // shutdown and wait up to 1s for threads to terminate
         *
         *      pool->Dispose(std::chrono::milliseconds(1000));
         *
         * Example #2:
         *
         *      std::shared_ptr<TaskExecutorInterface> pool = TaskExecutor::Create(4);
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
         *      std::shared_ptr<TaskExecutorInterface> pool = TaskExecutor::Create(4);
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
         *      std::shared_ptr<TaskExecutorInterface> pool = TaskExecutor::Create(4);
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
         *      std::shared_ptr<TaskExecutor> pool = TaskExecutor::Create(4);
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
    };

} // end of namespace AdobeMarketingMobile

#endif //ADOBEMOBILE_CORE_TASKEXECUTORINTERFACE_H
