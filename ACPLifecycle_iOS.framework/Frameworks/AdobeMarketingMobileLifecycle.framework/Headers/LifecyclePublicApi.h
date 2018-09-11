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
#include "Lifecycle.h"

namespace AdobeMarketingMobile {
    class LifecyclePublicApi : public Object {
    public:

        static std::shared_ptr<LifecyclePublicApi> Create(const std::shared_ptr<EventHub>& hub,
                const std::shared_ptr<PlatformServicesInterface>& services);

        LifecyclePublicApi();

        void Register();

        // ------------------------------------ Lifecycle --------------------------------------

        /**
         * @name Lifecycle
         */
        ///@{

        /**
         * @brief Dispatches an event to resume/start a lifecycle session
         *
         * @param additional_context_data context data provided through the public API
         */
        void LifecycleStart(const std::map<std::string, std::string>& additional_context_data);

        /**
         * @brief Dispatches an event to pause/stop a lifecycle session
         */
        void LifecyclePause();

        ///@}


    private:

        std::shared_ptr<EventHub> event_hub_;

        std::shared_ptr<PlatformServicesInterface> platform_services_;

    };
}

#endif /* ADOBEMOBILE_TARGET_TARGETPUBLICAPI_H */
