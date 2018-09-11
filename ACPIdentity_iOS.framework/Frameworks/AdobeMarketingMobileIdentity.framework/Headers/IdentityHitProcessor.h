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

#ifndef ADOBEMOBILE_IDENTITY_IDENTITY_HIT_PROCESSOR_H
#define ADOBEMOBILE_IDENTITY_IDENTITY_HIT_PROCESSOR_H

#include <string>
#include "Identity.h"
#include "IdentityDatabaseHit.h"

namespace AdobeMarketingMobile {
    class Identity;
    class NetworkServiceInterface;
    class JsonUtilityServiceInterface;
    class JsonObject;
    class SystemInfoServiceInterface;


    class IdentityHitProcessor : public HitProcessor<IdentityDatabaseHit> {

    public:
        explicit IdentityHitProcessor(const std::shared_ptr<NetworkServiceInterface>& network_service,
                                      const std::shared_ptr<SystemInfoServiceInterface>& system_info_service,
                                      const std::shared_ptr<JsonUtilityServiceInterface>& json_util_service,
                                      const std::shared_ptr<Identity>& parent_module);


        RetryType Process(const std::shared_ptr<IdentityDatabaseHit>& hit) override;
        std::shared_ptr<IdentityObject> CreateIdentityObjectFromResponseJsonObject(const std::shared_ptr<JsonObject>&
                json_object) const;
        std::map<std::string, std::string> BuildIdentityRequestPropertyMap(const bool ssl);

    protected:
        IdentityHitProcessor() : HitProcessor() {}


    private:

        std::shared_ptr<NetworkServiceInterface> network_service_;
        std::shared_ptr<JsonUtilityServiceInterface> json_util_service_;
        std::shared_ptr<SystemInfoServiceInterface> system_info_service_;

        std::shared_ptr<Identity> parent_module_;
    };
}

#endif /* ADOBEMOBILE_IDENTITY_IDENTITY_HIT_PROCESSOR_H */
