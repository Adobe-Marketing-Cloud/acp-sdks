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

#ifndef ADOBEMOBILE_SHARED_HITQUEUEBASE_H
#define ADOBEMOBILE_SHARED_HITQUEUEBASE_H

#include <atomic>
#include <string>
#include "HitDatabaseBase.h"

namespace AdobeMarketingMobile {
    class DatabaseHitBase;
    class DatabaseHitSchemaBase;
    class HitProcessorBase;
    class PlatformServicesInterface;
    class SystemInfoServiceInterface;
    class TaskExecutorInterface;
    class Variant;

    /**
     * @class HitQueueBase
     *
     * You should not inherit from this class.  If you need a HitQueue in your module, add a HitQueue property.
     */
    class HitQueueBase : public HitDatabaseBase {
        friend class HitQueueBaseMethods;   ///< for testing

    public:
        /**
         * Constructor
         * ===================
         * Initialize a HitQueueBase object and set properties for the provided parameters.
         *
         * @param platform_services platform services reference, needed to access the database service.
         * @param hit_schema the hit schema defining the database object to be used.
         * @param hit_processor processor to handle the hits.
         */
        HitQueueBase(const std::shared_ptr<PlatformServicesInterface>& platform_services,
                     const std::shared_ptr<DatabaseHitSchemaBase>& hit_schema,
                     const std::shared_ptr<HitProcessorBase>& hit_processor);

        ~HitQueueBase();

        /**
         * Frees resources used by this, waiting up to `max_wait_duration` for the operation to complete.
         *
         * Calling Dispose() triggers clean up to occur asynchronously.
         *
         * After triggering the asynchronous disposal, this call will block for up to `max_wait_duration` for the
         * operation to complete.
         *
         * @param max_wait_duration - the maximum duration to block this call while waiting for cleanup to complete.
         *                            A `0` time indicates that we will return immediately.
         *
         * @return true if this was fully disposed
         */
        virtual bool Dispose(std::chrono::milliseconds max_wait_duration);

        /**
         * Indicates to the HitQueue that it should resume its background thread and process any queued hits.
         */
        virtual void BringOnline();

        /**
         * Creates the database and table based on the provided hit_schema in the constructor.
         * @returns true if successful
         */
        virtual bool InitializeDatabase() override;

        /**
         * Get the first hit that matches the provided query.
         *
         * @param query Query object defining the query that should run.
         * @returns the first hit to match the provided query.
         */
        std::shared_ptr<DatabaseHitBase> QueryHit(const std::shared_ptr<Query>& query);

        /**
         * Allows the caller to insert a DatabaseHitBase object into the database.
         *
         * @param hit database hit to queue.
         * @returns true if the hit was successfully inserted into the database.
         */
        bool Queue(const std::shared_ptr<DatabaseHitBase>& hit);

        /**
         * Get the oldest hit (according to timestamp) from the table defined in the hit_schema.
         *
         * @returns the oldest hit in the database table.
         */
        std::shared_ptr<DatabaseHitBase> SelectOldestHit();

        /**
         * Suspend the HitQueue.
         * New hit can still be queued, processing will not resume until BringOnline is called.
         */
        virtual void Suspend();

        /**
         * Update all the hits in the table with new values provided by parameters.
         *
         * @param parameters new values represented as {columnName}{value} pairs.
         * @returns true if hits are successfully updated
         */
        virtual bool UpdateAllHits(const std::map<std::string, std::shared_ptr<Variant>>& parameters);

        /**
         * Update the hit data to db. Use the identifier property of the hit as the index key.
         *
         * @param hit the hit to be updated to db.
         * @returns true if hit is successfully updated
         */
        bool UpdateHit(const std::shared_ptr<DatabaseHitBase>& hit);

    protected:
        HitQueueBase() : HitDatabaseBase(), is_suspended_{false} {}               ///< Makes mocking easier

        std::shared_ptr<TaskExecutorInterface> background_executor_; ///< Executor used to run tasks on separate threads

        std::mutex background_mutex_;                       ///< Mutex used to block access to background thread

        /**
         * @protected
         * Amount of time to wait until retry when there is a network connection failure
         */
        static const int32_t DEFAULT_NETWORK_CONNECTION_FAIL_DELAY;

        /**
         * @protected
         * DatabaseHitSchema that defines the table to be used by this hit queue
         */
        std::shared_ptr<DatabaseHitSchemaBase> hit_schema_;

        /**
         * @protected
         * HitProcessorInterface used to process a hit.
         */
        std::shared_ptr<HitProcessorBase> hit_processor_;

        bool is_suspended_;                    ///< Maintains status for hit queue suspension

        static const std::string LOG_TAG;                   ///< Tag used for logging

        std::shared_ptr<PlatformServicesInterface> platform_service_;   ///< Reference to platform services

        std::shared_ptr<SystemInfoServiceInterface> system_info_service_;   ///< Reference to system info services

        /**
         * Get the function that can be used with the TaskExecutor to do our work on a controlled background thread.
         *
         * @returns function pointer whose implementation defines the work to be done to process a database hit
         */
        std::function<void()> WorkerThread();

        /**
         * @protected
         * Check the status of is_suspended_.
         *
         * @return true is \p is_suspended is true, false otherwise.
         */
        bool IsSuspended();

    private:
        bool was_dispose_called_; ///< was Dispose() called?

        std::condition_variable worker_alarm_; ///< condition variable to wake up worker thread

        /**
         * Helper for Dispose().
         *
         * Non-virtual implementation of Dispose().
         */
        bool DisposeNonVirtualImpl(std::chrono::milliseconds max_wait_duration);

        /**
         * Helper for WorkerThread().
         *
         * Returns whether the worker thread should continue processing hits.
         *
         * Acquires background mutex during the body of this call.
         *
         * @returns whether the worker thread should continue processing hits
         */
        bool ShouldWorkerContinue();

        /**
         * Helper for WorkerThread().
         *
         * Version of ShouldWorkerContinue() that does not acquire background mutex. The caller of this function
         * should hold background mutex for the duration of this call.
         */
        bool ShouldWorkerContinueNoLock();

        /**
         * Helper for WorkerThread().
         *
         * Pauses after processing a hit fails.
         */
        void PauseBeforeRetrying();
    };
}

#endif /* ADOBEMOBILE_SHARED_HITQUEUEBASE_H */
