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

#ifndef ADOBEMOBILE_UTIL_RANDOMUTIL_H
#define ADOBEMOBILE_UTIL_RANDOMUTIL_H

namespace AdobeMarketingMobile {
    class RandomUtil {
    public:

        /**
         * Produces random integer values, uniformly distributed on the closed interval [0, n], it uses
         * std::uniform_int_distribution
         *
         * @param n the upper bound for the distribution
         * @return the generated random integer as string
         */
        static std::string Rand(const uint64_t n);

        /**
         * @see RandomUtil::Rand(int64_t) Distribution used is [0, UINT64_MAX]
         */
        static std::string Rand();
    };
}

#endif /* ADOBEMOBILE_UTIL_RANDOMUTIL_H */
