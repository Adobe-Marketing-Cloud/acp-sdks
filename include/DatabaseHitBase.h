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
