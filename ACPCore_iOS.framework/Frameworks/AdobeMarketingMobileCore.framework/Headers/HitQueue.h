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
 ****************************************************************************/

#ifndef ADOBEMOBILE_SHARED_HITQUEUE_H
#define ADOBEMOBILE_SHARED_HITQUEUE_H

#include <string>
#include "DatabaseHitBase.h"
#include "DatabaseHitSchema.h"
#include "HitQueueBase.h"
#include "HitProcessor.h"
#include "PlatformServicesInterface.h"
#include "Query.h"
#include "Common.h"

namespace AdobeMarketingMobile {

    /**
     * @class HitQueue
     *
     * Main class to be used by a module's database class to interface with the database
     * provided by platform services.
     */
    template<class TDatabaseHit, class TDatabaseHitSchema, class THitProcessor>
    class HitQueue : public HitQueueBase {
        // If you get an error on the following line, you need to make sure that TDatabaseHit is a type derived from DatabaseHitBase.
        static_assert(std::is_base_of<DatabaseHitBase, TDatabaseHit>::value,
                      "Type of TDatabaseHit must be derived from DatabaseHitBase.");
        // If you get an error on the following line, you need to make sure that TDatabaseHitSchema is a type derived from DatabaseHitSchema.
        static_assert(std::is_base_of<DatabaseHitSchema<TDatabaseHit>, TDatabaseHitSchema>::value,
                      "Type of TDatabaseHitSchema must be derived from DatabaseHitSchema.");
        // If you get an error on the following line, you need to make sure that THitProcessor is a type derived from HitProcessor.
        static_assert(std::is_base_of<HitProcessor<TDatabaseHit>, THitProcessor>::value,
                      "Type of THitProcessor must be derived from HitProcessor.");

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
        explicit HitQueue(const std::shared_ptr<PlatformServicesInterface>& platform_services,
                          const std::shared_ptr<TDatabaseHitSchema>& hit_schema,
                          const std::shared_ptr<THitProcessor>& hit_processor);

        /**
         * Get the first hit that matches the provided query.
         *
         * Deliberately hides HitQueueBase::QueryHit()
         *
         * @param query Query object defining the query that should run.
         * @returns the first hit to match the provided query.
         */
        ADOBE_VIRTUAL_FOR_TESTS std::shared_ptr<TDatabaseHit> QueryHit(const std::shared_ptr<Query>& query);

        /**
         * Allows the caller to insert a DatabaseHitBase object into the database.
         *
         * Deliberately hides HitQueueBase::Queue()
         *
         * @param hit database hit to queue.
         * @returns true if the hit was successfully inserted into the database.
         */
        ADOBE_VIRTUAL_FOR_TESTS bool Queue(const std::shared_ptr<TDatabaseHit>& hit);

        /**
         * Get the oldest hit (according to timestamp) from the table defined in the hit_schema.
         *
         * Deliberately hides HitQueueBase::SelectOldestHit()
         *
         * @returns the oldest hit in the database table.
         */
        ADOBE_VIRTUAL_FOR_TESTS std::shared_ptr<TDatabaseHit> SelectOldestHit();

        /**
         * Update the hit data to db. Use the identifier property of the hit as the index key.
         *
         * Deliberately hides HitQueueBase::UpdateHit()
         *
         * @param hit the hit to be updated to db.
         */
        ADOBE_VIRTUAL_FOR_TESTS bool UpdateHit(const std::shared_ptr<TDatabaseHit>& hit);

    protected:
        HitQueue() : HitQueueBase() {}      ///< makes mocking easier
    };
}

/////////////////////////////////
// template/inline definitions //
/////////////////////////////////
namespace AdobeMarketingMobile {
    // ctor
    template<class TDatabaseHit, class TDatabaseHitSchema, class THitProcessor>
    HitQueue<TDatabaseHit, TDatabaseHitSchema, THitProcessor>::HitQueue(
                const std::shared_ptr<PlatformServicesInterface>& platform_services,
                const std::shared_ptr<TDatabaseHitSchema>& hit_schema,
                const std::shared_ptr<THitProcessor>& hit_processor) :
        HitQueueBase(platform_services, hit_schema, hit_processor)
    { }

    // public methods
    template<class TDatabaseHit, class TDatabaseHitSchema, class THitProcessor>
    std::shared_ptr<TDatabaseHit>
    HitQueue<TDatabaseHit, TDatabaseHitSchema, THitProcessor>::SelectOldestHit() {
        return std::dynamic_pointer_cast<TDatabaseHit>(HitQueueBase::SelectOldestHit());
    }

    template<class TDatabaseHit, class TDatabaseHitSchema, class THitProcessor>
    std::shared_ptr<TDatabaseHit>
    HitQueue<TDatabaseHit, TDatabaseHitSchema, THitProcessor>::QueryHit(const std::shared_ptr<Query>&
            query) {
        return std::dynamic_pointer_cast<TDatabaseHit>(HitQueueBase::QueryHit(query));
    }

    template<class TDatabaseHit, class TDatabaseHitSchema, class THitProcessor>
    bool HitQueue<TDatabaseHit, TDatabaseHitSchema, THitProcessor>::UpdateHit(const std::shared_ptr<TDatabaseHit>& hit) {
        return HitQueueBase::UpdateHit(hit);
    }

    template<class TDatabaseHit, class TDatabaseHitSchema, class THitProcessor>
    bool HitQueue<TDatabaseHit, TDatabaseHitSchema, THitProcessor>::Queue(const std::shared_ptr<TDatabaseHit>& hit) {
        return HitQueueBase::Queue(hit);
    }
}


#endif /* ADOBEMOBILE_SHARED_HITQUEUE_H */
