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

#ifndef ADOBEMOBILE_SHARED_MOBILEPRIVACYSTATUS_H
#define ADOBEMOBILE_SHARED_MOBILEPRIVACYSTATUS_H

#include <sstream>
#include <string>

namespace AdobeMarketingMobile {

    class ToStringOptions;

    enum class MobilePrivacyStatus : int32_t {
        OPT_IN = 0,
        OPT_OUT,
        UNKNOWN
    };

    /**
     * Converts a string to its respective MobilePrivacyStatus enum representation
     *
     * If not match is found, returns MobilePrivacyStatus::UNKNOWN
     */
    MobilePrivacyStatus StringToMobilePrivacyStatus(const std::string& privacy_string);

    /**
     * Converts a MobilePrivacyStatus enum to its respective string representation
     *
     * If not match is found, returns "optunknown"
     */
    std::string MobilePrivacyStatusToString(MobilePrivacyStatus privacy_status);

    /**
     * Used for logging
     */
    void ToStringImpl(std::ostream& the_stream, MobilePrivacyStatus value, const ToStringOptions& options);
}

#endif /* ADOBEMOBILE_SHARED_MOBILEPRIVACYSTATUS_H */
