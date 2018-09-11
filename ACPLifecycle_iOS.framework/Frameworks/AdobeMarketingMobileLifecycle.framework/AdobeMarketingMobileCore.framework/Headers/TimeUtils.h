/****************************************************************************
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

#ifndef ADOBEMOBILE_UTIL_TIMEUTILS_H
#define ADOBEMOBILE_UTIL_TIMEUTILS_H

#include <chrono>
#include <cstdint>
#include <string>

namespace AdobeMarketingMobile {

    class TimeUtils {

    public:
        /**
         * Get current unix timestamp
         *
         * @return current timestamp in milliseconds
         */
        static std::chrono::milliseconds GetUnixTime();

        /**
         * Get current unix timestamp
         *
         * @return current timestamp in seconds
         */
        static std::chrono::seconds GetUnixTimeInSeconds();

        /**
         * Get the timestamp from the provided time_point
         *
         * @return timestamp in milliseconds
         */
        static std::chrono::milliseconds GetTimeInMilliseconds(const std::chrono::time_point<std::chrono::system_clock>
                time_point);

        /**
         * Get the the Iso8601 formatted date string for the current date
         * @return Iso8601 formatted date string
         */
        static std::string GetIso8601Date();

        /**
         * Get the the Iso8601 formatted date string for the passed in date
         * @param date the date to generate the string for
         * @return Iso8601 formatted date string
         */
        static std::string GetIso8601Date(const std::tm* date);

    private:
        TimeUtils() = delete;

    };

}

#endif /* ADOBEMOBILE_UTIL_TIMEUTILS_H */
