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

#ifndef ADOBEMOBILE_SHARED_HITPROCESSORBASE_H
#define ADOBEMOBILE_SHARED_HITPROCESSORBASE_H

#include "Object.h"

namespace AdobeMarketingMobile {
    class DatabaseHitBase;

    /**
     * RetryType is used to let the database know whether or not it should remove a database entry on a failed
     * network request.
     */
    enum class RetryType : int32_t {
        RetryTypeNo = 0,
        RetryTypeYes,
        RetryTypeBreak // do not delete the hit and do not continue procssing
    };

    class HitProcessorBase : public Object {
    public:
        /**
         * Process the hit that is retrieved from database. The return value of this method will decide whether
         * or not the hit will be removed from the database.
         *
         * @param hit the hit retrieved from the database.
         * @return a RetryType enum. Return RetryType::NO to remove the processed hit from the database.
         */
        virtual RetryType ProcessBase(const std::shared_ptr<DatabaseHitBase>& hit) = 0;

    protected:
        HitProcessorBase() {}   ///< makes mocking easier
    };
}

#endif /* ADOBEMOBILE_SHARED_HITPROCESSORBASE_H */

