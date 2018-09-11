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
