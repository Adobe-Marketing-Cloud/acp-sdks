/* **************************************************************************
 *
 * ADOBE CONFIDENTIAL
 * ___________________
 *
 * Copyright 2018 Adobe Systems Incorporated
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

#ifndef ADOBEMOBILE_IDENTITY_OBJECT_H
#define ADOBEMOBILE_IDENTITY_OBJECT_H

#include <string>
#include <vector>
#include <chrono>
#include "Identity.h"

namespace AdobeMarketingMobile {
    class IdentityObject : public Object {
    public:
        IdentityObject();
        /**
         * Set Blob from json response.
         */
        ADOBE_VIRTUAL_FOR_TESTS void SetBlob(const std::string& blob);

        /**
         * Get Blob as set by last json response.
         */
        ADOBE_VIRTUAL_FOR_TESTS const std::string& GetBlob() const;

        /**
         * Set Mid from json response.
         */
        ADOBE_VIRTUAL_FOR_TESTS void SetMid(const std::string& mid);

        /**
         * Get Mid as set by last json response.
         */
        ADOBE_VIRTUAL_FOR_TESTS const std::string& GetMid() const;

        /**
         * Set Hint from json response.
         */
        ADOBE_VIRTUAL_FOR_TESTS void SetHint(const std::string& hint);

        /**
         * Get Hint as set by last json response.
         */
        ADOBE_VIRTUAL_FOR_TESTS const std::string& GetHint() const;

        /**
         * Set Error from json response.
         */
        ADOBE_VIRTUAL_FOR_TESTS void SetError(const std::string& error);

        /**
         * Get Error as set by last json response.
         */
        ADOBE_VIRTUAL_FOR_TESTS const std::string& GetError() const;

        /**
         * Set TTL from json response.
         */
        ADOBE_VIRTUAL_FOR_TESTS void SetTtl(const std::chrono::seconds ttl);

        /**
         * Get TTL as set by last json response.
         */
        ADOBE_VIRTUAL_FOR_TESTS const std::chrono::seconds GetTtl() const;

        /**
         * Set OptOut vector from json response.
         */
        ADOBE_VIRTUAL_FOR_TESTS void SetOptOut(const std::vector<std::string>& opt_out);

        /**
         * Get OptOut vector as set by last json response.
         */
        ADOBE_VIRTUAL_FOR_TESTS const std::vector<std::string>& GetOptOut() const;

    private:

        std::string blob_;
        std::string mid_;
        std::string hint_;
        std::string error_;
        std::chrono::seconds ttl_;
        std::vector<std::string> opt_out_;
    };
}

#endif /* ADOBEMOBILE_IDENTITY_OBJECT_H */
