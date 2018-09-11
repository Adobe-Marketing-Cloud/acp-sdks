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

#ifndef ADOBEMOBILE_CORE_TIMER_H
#define ADOBEMOBILE_CORE_TIMER_H

#include <chrono>
#include <map>
#include "Common.h"
#include "Object.h"
#include "TaskExecutor.h"

namespace AdobeMarketingMobile {

    /**
     * @class TimerTask
     *
     * This class represents a timed task and is stored in the task queue.
     *
     */
    class TimerTask {
    public:
        static constexpr const std::chrono::milliseconds DO_NOT_REPEAT{-1};

        /**
         * Construct a TimerTask. A negative period indicates a task that does not repeat.
         *
         */
        TimerTask(const std::function<void()>& task, std::chrono::milliseconds period = DO_NOT_REPEAT) :
            task_callback_(task), period_(period) {}

    public:
        std::function<void()> task_callback_;
        std::chrono::milliseconds period_;
    };

    /**
     * @class Timer
     *
     * This is a timed task executor that leverages the TaskExecutor class. It is designed to cover roughly
     * the same use cases that the Java Timer and TimerTask classes cover. All tasks scheduled on the same Timer will
     * execute in serial, according to the start time specified.
     *
     * Questions
     * ====================
     * How should Timer handle repeating tasks that fail? Currently Timer ignores failures. Tasks must handle errors.
     *
     */
    class Timer : public Object {
    public:
        static constexpr const std::chrono::milliseconds TIMER_SHUTDOWN_MAX_WAIT{100};
        static constexpr const std::chrono::milliseconds TIMER_RUNNING_MAX_WAIT{1000};

        /**
         * Construct a Timer.
         *
         * Examples:
         *
         *      std::shared_ptr<Timer> timer = Timer::Create();
         *
         */
        static std::shared_ptr<Timer> Create();
        static std::shared_ptr<Timer> Create(const std::string& name,
                                             const std::shared_ptr<PlatformServicesInterface>& platform_services);
        static std::shared_ptr<Timer> Create(const std::string& name,
                                             const std::shared_ptr<SystemInfoServiceInterface>& system_info_service);

        /**
         * Destructor
         *
         */
        ~Timer();

        /**
         * Terminates this timer, discarding any currently scheduled tasks.
         * Will wait a maximum of `wait_time` milliseconds.
         *
         * Examples:
         *
         *      std::shared_ptr<Timer> timer = std::make_shared<Timer>();
         *      timer->Schedule([](){...}, std::chrono::seconds(10000));
         *      ...
         *      timer->Cancel();
         *
         * @param wait_time - the time to wait for tasks to complete
         * @return true if tasks completed before wait time, false otherwise
         */
        ADOBE_VIRTUAL_FOR_TESTS bool Cancel(std::chrono::milliseconds wait_time = TIMER_SHUTDOWN_MAX_WAIT);

        /**
         * Schedules the specified task for execution at the specified time.
         *
         * Examples:
         *
         *      std::shared_ptr<Timer> timer = std::make_shared<Timer>();
         *      timer->Schedule([](){...}, std::chrono::now() + std::chrono::seconds(10000));
         *
         * @param task - a callable to execute at the appropriate time
         * @param start_time - the time to execute the task
         * @return true if task was scheduled, false if Timer::Cancel() was already called
         */
        ADOBE_VIRTUAL_FOR_TESTS bool Schedule(const std::function<void()>& task,
                                              std::chrono::system_clock::time_point start_time);

        /**
         * Schedules the specified task for repeated fixed-rate execution, beginning at the specified time.
         *
         * Example:
         *
         *      std::shared_ptr<Timer> timer = std::make_shared<Timer>();
         *      timer->ScheduleAtFixedRate([](){...},
         *                                 std::chrono::now() + std::chrono::seconds(100),
         *                                 std::chrono::seconds(60));
         *
         * @param task - a callable to execute at the appropriate time
         * @param start_time - the time to execute the task
         * @param period - the period at which the task will be repeated once the loop is started
         * @return true if task was scheduled, false if Timer::Cancel() was already called
         */
        ADOBE_VIRTUAL_FOR_TESTS bool ScheduleAtFixedRate(const std::function<void()>& task,
                std::chrono::system_clock::time_point start_time,
                std::chrono::milliseconds period);

    protected:
        /**
         * @protected
         * Called by Create(). This is not exposed because we don't want these to be created on the stack.
         */
        Timer(const std::string& name,
              const std::shared_ptr<SystemInfoServiceInterface>& system_info_service);

        /**
         * @private
         * Second half of two-phase Timer construction
         */
        ADOBE_VIRTUAL_FOR_TESTS void StartTimerThread();

    private:

        /**
         * @private
         * Mutex used to synchronize Timer with its task thread.
         */
        std::mutex mutex_;

        /**
         * @private
         * Condition variable used to signal when new tasks are added or Cancel is called.
         */
        std::condition_variable condition_;

        // TODO: (AMSDK-5892) Consider using atomic for cancel_called_
        /**
         * @private
         * Flag to signal to task thread that Cancel was called.
         */
        bool cancel_called_;

        /**
         * @private
         * Thread pool.
         */
        std::shared_ptr<TaskExecutor> executor_;

        /**
         * @private
         * The queue of scheduled tasks.
         */
        std::multimap<std::chrono::system_clock::time_point, TimerTask> tasks_;

        std::string name_;

        std::shared_ptr<SystemInfoServiceInterface> system_info_service_;

        bool flag_task_added;
    };

}

/////////////////////////////////////////
// template and inline implementations //
/////////////////////////////////////////

namespace AdobeMarketingMobile {
    /* Templated version of Schedule() for convenience */
    template<typename Clock>
    bool Schedule(const std::function<void()>& task, std::chrono::time_point<Clock> start_time) {
        auto start_time_system_clock = std::chrono::time_point_cast<std::chrono::system_clock::time_point>(start_time);
        return Schedule(task, start_time_system_clock);
    }

    /* Templated version of ScheduleAtFixedRate() for convenience */
    template<typename Clock, typename Period>
    bool ScheduleAtFixedRate(const std::function<void()>& task,
                             std::chrono::time_point<Clock> start_time,
                             std::chrono::duration<Period> period) {
        auto start_time_system_clock = std::chrono::time_point_cast<std::chrono::system_clock::time_point>(start_time);
        auto period_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(period);
        return ScheduleAtFixedRate(task, start_time_system_clock, period_milliseconds);
    }


} // end of namespace AdobeMarketingMobile

#endif //ADOBEMOBILE_CORE_TIMER_H
