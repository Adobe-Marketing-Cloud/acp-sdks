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
