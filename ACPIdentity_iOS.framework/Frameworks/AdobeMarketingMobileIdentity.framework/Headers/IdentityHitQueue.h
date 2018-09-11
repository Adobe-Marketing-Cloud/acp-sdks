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

#ifndef ADOBEMOBILE_IDENTITY_IDENTITY_HIT_QUEUE_H
#define ADOBEMOBILE_IDENTITY_IDENTITY_HIT_QUEUE_H

#include <string>
#include "Identity.h"
#include "IdentityDatabaseHit.h"
#include "IdentityDatabaseHitSchema.h"
#include "IdentityHitProcessor.h"

namespace AdobeMarketingMobile {

    class IdentityHitQueue : public HitQueue<IdentityDatabaseHit, IdentityDatabaseHitSchema, IdentityHitProcessor> {

    public:
        IdentityHitQueue(const std::shared_ptr<PlatformServicesInterface>& platform_services,
                         const std::shared_ptr<IdentityDatabaseHitSchema>& hit_schema,
                         const std::shared_ptr<IdentityHitProcessor>& hit_processor) :
            HitQueue(platform_services, hit_schema, hit_processor) {}

    protected:
        IdentityHitQueue() : HitQueue() {}
    };
}

#endif /* ADOBEMOBILE_IDENTITY_IDENTITY_HIT_QUEUE_H */
