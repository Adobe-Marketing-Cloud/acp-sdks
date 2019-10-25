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
