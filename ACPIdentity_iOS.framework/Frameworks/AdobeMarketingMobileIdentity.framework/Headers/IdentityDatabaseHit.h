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
 **************************************************************************/

#ifndef ADOBEMOBILE_IDENTITY_DATABASE_HIT_H
#define ADOBEMOBILE_IDENTITY_DATABASE_HIT_H

#include <string>
#include "Identity.h"

namespace AdobeMarketingMobile {

    class IdentityDatabaseHit : public virtual DatabaseHitBase {

    public:
        IdentityDatabaseHit();
        std::string pair_id;
        std::string url;
        int32_t event_number;
        bool config_ssl;
    private:

    };
}

#endif /* ADOBEMOBILE_IDENTITY_DATABASE_HIT_H */
