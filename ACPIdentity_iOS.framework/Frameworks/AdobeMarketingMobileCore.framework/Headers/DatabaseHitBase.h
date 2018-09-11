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

#ifndef ADOBEMOBILE_SHARED_DATABASEHITBASE_H
#define ADOBEMOBILE_SHARED_DATABASEHITBASE_H

#include <chrono>
#include <string>
#include "Object.h"

namespace AdobeMarketingMobile {

    /**
     * DatabaseHitBase
     *
     * Abstract Base class that should be implemented by any class that represents a "Hit" which will be
     * stored in a local database
     */
    class DatabaseHitBase : public Object {
    public:

        std::string identifier;     ///< unique identifier for the database record
        std::chrono::seconds timestamp;    ///< created timestamp in seconds since jan 1, 1970
    };
}

#endif /* ADOBEMOBILE_SHARED_DATABASEHITBASE_H */
