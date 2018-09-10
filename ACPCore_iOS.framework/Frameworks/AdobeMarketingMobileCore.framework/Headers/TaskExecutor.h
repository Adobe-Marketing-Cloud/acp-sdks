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

#ifndef ADOBEMOBILE_CORE_TASKEXECUTOR_H
#define ADOBEMOBILE_CORE_TASKEXECUTOR_H

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
     *
     * TaskExecutor is a standard thread pool + task queue. See https://en.wikipedia.org/wiki/Thread_pool.
     * Each TaskExecutor manages a set of worker threads and a synchronized task queue. Tasks are
     * added to the back of the queue using AddTask(). The thread workers monitor the task queue.
     * When tasks are added, all threads not currently running a task will wakeup and pull a task
     * from the front of the queue (FIFO). Tasks are simply callable objects taking no parameters
     * and returning no values. When a worker pulls a task it will immediately execute it. There
     * are currently no guarantees on task start ordering. If an exception is thrown during task
     * execution, the error callback (if any) will be called with the exception thrown and the
     * task name (if any). When the pool needs to be closed, the owner calls Dispose() which
     * flushes any remaining tasks and notifies the threads to shutdown. Each thread worker has a
     * TaskExecutor reference which it retains until it terminates.
     *
     * Requirements
     * ====================
     * - TaskExecutor must be implemented using standard C++11, nothing platform-specific.
     * - TaskExecutor must be a standalone utility class (EventHub will use TaskExecutor).
     * - TaskExecutor must have a method that cleanly shuts down all threads.
     * - TaskExecutor must capture exceptions thrown during task execution and report them.
     * - TaskExecutor must represent task as std::function to represent the callback.
     * - TaskExecutor must support multiple threads in a pool.
     * - TaskExecutor must allow multiple concurrent TaskExecutors to be instantiated.
     *
     * Future thinking
     * ====================
     * - TaskExecutor should have a way to serialize sets of tasks (e.g. virtual thread number)
     * - We might need a way to grow and shrink the pool dynamically (e.g. based on external load)
     * -- This may mean we need a bidirectional channel with individual threads
     *
     * Task ordering models
     * ====================
     * #1 Any start ordering  <== this is our MVP
     *
     * #2 Strict sequential start ordering <== this can be accomplished with #3 or #4
     *
     * #3 Strict sequential start order within a set, any start ordering between sets
     *
     * #4 Strict sequential start order between sets, any start ordering within a set
     *
     * #5 Any start ordering within a set or between sets, but sets are non-overlapping
     *
     */
    class TaskExecutor : public Object, public virtual TaskExecutorInterface {
    public:
        /**
         * Constants
         *
         */
        static constexpr const uint32_t MAX_THREADS{16};
        static constexpr const std::chrono::milliseconds MAX_NOTIFICATION_WAIT{100};

        /**
         * Instantiate a default TaskExecutor with requested number of active worker threads.
         * The TaskExecutor will begin with num_thread detached threads watching the task queue.
         *
         * Example:
         *
         *      std::shared_ptr<TaskExecutor> pool = TaskExecutor::Create(4);
         *
         * @param num_threads - number of threads in the pool must be between 1 and MAX_THREADS.
         * @return A valid TaskExecutor instance
         */
        static std::shared_ptr<TaskExecutor> Create(uint32_t num_threads);

        /**
         * Instantiate a named TaskExecutor with requested number of active worker threads.
         * The TaskExecutor will begin with num_thread detached threads watching the task queue.
         *
         * Example:
         *
         *      std::shared_ptr<TaskExecutor> pool = TaskExecutor::Create(4, "Worker");
         *
         * @param num_threads - number of threads in the pool must be between 1 and MAX_THREADS.
         * @param name - Name for threads owned by this executor. Truncated to MAX_THREAD_NAME_LENGTH chars as needed.
         * @param platform - platform-specific services used for setting thread name.
         * @return A valid TaskExecutor instance
         */
        static std::shared_ptr<TaskExecutor> Create(uint32_t num_threads,
                const std::string& name,
                const std::shared_ptr<PlatformServicesInterface>& platform);

        static std::shared_ptr<TaskExecutor> Create(uint32_t num_threads,
                const std::string& name,
                const std::shared_ptr<SystemInfoServiceInterface>& system_info);
        /**
         * Destructor
         */
        ~TaskExecutor() override;

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
