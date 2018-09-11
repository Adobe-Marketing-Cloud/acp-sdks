/* ************************************************************************
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

#ifndef ADOBEMOBILE_SHARED_HITPROCESSOR_H
#define ADOBEMOBILE_SHARED_HITPROCESSOR_H

#include <string>
#include "DatabaseHitBase.h"
#include "HitProcessorBase.h"

namespace AdobeMarketingMobile {

    /*
     * @class HitProcessor
     * This class needs to be implemented and passed as a parameter to a HitQueue object.
     */
    template<class TDatabaseHit>
    class HitProcessor : public HitProcessorBase {
        // If you get an error on the following line, you need to make sure that TDatabaseHit is a type derived from DatabaseHitBase.
        static_assert(std::is_base_of<DatabaseHitBase, TDatabaseHit>::value,
                      "Type of TDatabaseHit must be derived from DatabaseHitBase.");

    public:
        /**
         * Process the hit that is retrieved from database. The return value of this method will decide whether
         * or not the hit will be removed from the database.
         *
         * @param hit the hit retrieved from the database.
         * @return a RetryType enum. Return RetryType::NO to remove the processed hit from the database.
         */
        virtual RetryType Process(const std::shared_ptr<TDatabaseHit>& hit) = 0;
        RetryType ProcessBase(const std::shared_ptr<DatabaseHitBase>& hit) override;

    protected:
        HitProcessor() : HitProcessorBase() {}      ///< makes mocking easier
    };
}

/////////////////////////////////
// template/inline definitions //
/////////////////////////////////
namespace AdobeMarketingMobile {
    template<class TDatabaseHit>
    RetryType HitProcessor<TDatabaseHit>::ProcessBase(const std::shared_ptr<DatabaseHitBase>& hit) {
        return Process(std::dynamic_pointer_cast<TDatabaseHit>(hit));
    }
}

#endif /* ADOBEMOBILE_SHARED_HITPROCESSOR_H */
