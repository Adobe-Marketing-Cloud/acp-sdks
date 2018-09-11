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
        RetryTypeYes
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

