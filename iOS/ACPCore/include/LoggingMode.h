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

#ifndef ADOBEMOBILE_PLATFORMSHIM_LOGGINGMODE_H
#define ADOBEMOBILE_PLATFORMSHIM_LOGGINGMODE_H

namespace AdobeMarketingMobile {

    enum class LoggingMode : int32_t {
        ERROR_LOG = 0,
        WARNING_LOG = 1,
        DEBUG_LOG = 2,
        VERBOSE_LOG = 3,

    };
} //namespace

#endif /* ADOBEMOBILE_PLATFORMSHIM_LOGGINGMODE_H */
