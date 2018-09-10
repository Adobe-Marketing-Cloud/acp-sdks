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
 **************************************************************************/

#ifndef ADOBEMOBILE_TARGET_TARGETPUBLICAPI_H
#define ADOBEMOBILE_TARGET_TARGETPUBLICAPI_H

#include <AdobeMarketingMobileCore/AdobeMarketingMobileCore.h>
#include <chrono>
#include <functional>
#include <map>
#include <string>
#include <vector>
#include "Target.h"

namespace AdobeMarketingMobile {
    class TargetPublicApi : public Object {
    public:

        static std::shared_ptr<TargetPublicApi> Create(const std::shared_ptr<EventHub>& hub,
                const std::shared_ptr<PlatformServicesInterface>& services);

        TargetPublicApi();

        void RegisterTarget();

        // ------------------------------------ TARGET --------------------------------------

        ///@}

        /**
         * @name Target
         */
        ///@{

        /**
         * @brief Called from the platform to get the thirdPartyID.
         *
         * @param callback (required) method which will be called with thirdPartyID
         */
        void TargetGetThirdPartyId(const std::function<void(const std::string&)>& callback);

        /**
         * @brief Called from the platform to get the tntId.
         *
         * @param callback (required) method which will be called with tntId
         */
        void TargetGetTntId(const std::function<void(const std::string&)>& callback);

        /**
         * @brief Called from the platform to get the set the thirdPartyID.
         *
         * This method will create and dispatch a Target request identity event with thirdParty Key listened by the
         * Target module
         *
         * @param third_party_id (required) thirdPartyId value that needs to be set
         */
        void TargetSetThirdPartyId(const std::string& third_party_id);

        /**
         * @brief Clears any target cookies from your app.
         *
         * This method will create and dispatch a Target request reset event listened by the Target module
         */
        void TargetResetExperience();

        /**
         * @brief Clears all the data cached by Target Prefetch.
         *
         * This method will create and dispatch a Target request reset event listened by the Target module
         */
        void TargetClearPrefetchCache();

        /**
         * @brief Prefetch multiple Target mboxes in a single network call.
         *
         * This method will create a Target request content event containing the provided prefetch array
         */
        void TargetPrefetchContent(const std::vector<std::shared_ptr<TargetPrefetch>>& target_prefetch_array,
                                   const std::map<std::string, std::string>& profile_parameters,
                                   const std::function<void(const bool)>& result_callback);

        /**
         * @brief Load multiple Target mboxes in a single network call.
         *
         * This method will create a Target request content event containing the provided requests array
         */
        void TargetLoadRequests(const std::vector<std::shared_ptr<TargetRequest>>& target_requests_array,
                                const std::map<std::string, std::string>& profile_parameters);

        /**
         * @brief Dispatches a new target request content event with the received preview restart deep link
         */
        void TargetSetPreviewRestartDeepLink(const std::string& restart_deeplink);

    private:

        std::shared_ptr<EventHub> event_hub_;

        std::shared_ptr<PlatformServicesInterface> platform_services_;

        /**
         * @private
         *
         * This method will create and dispatch a Target request identity event listened by the Target module
         * @see CoreObject::TargetGetThirdPartyId
         * @see CoreObject::TargetGetTntId
         *
         * @param identifier_key    (required) to determine which value has to be passed to the callback
         * @param callback          (required) method which will be called with the appropriate identity
         */
        void TargetIdentityRequest(const std::string& identifier_key, const std::function<void(const std::string&)>& callback);
    };
}

#endif /* ADOBEMOBILE_TARGET_TARGETPUBLICAPI_H */
