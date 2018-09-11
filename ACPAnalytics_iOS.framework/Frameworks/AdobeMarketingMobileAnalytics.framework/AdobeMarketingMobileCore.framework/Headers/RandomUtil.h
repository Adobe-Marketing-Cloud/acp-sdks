/***************************************************************************
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
 *
 **************************************************************************/

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
