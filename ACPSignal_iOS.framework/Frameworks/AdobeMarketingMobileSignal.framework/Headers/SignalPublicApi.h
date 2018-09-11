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

#ifndef ADOBEMOBILE_SIGNAL_SIGNALPUBLICAPI_H
#define ADOBEMOBILE_SIGNAL_SIGNALPUBLICAPI_H

#include <AdobeMarketingMobileCore/AdobeMarketingMobileCore.h>
#include <chrono>
#include <functional>
#include <map>
#include <string>
#include <vector>
#include "Signal.h"

namespace AdobeMarketingMobile {
    class SignalPublicApi : public Object {
    public:

        static std::shared_ptr<SignalPublicApi> Create(const std::shared_ptr<EventHub>& hub,
                const std::shared_ptr<PlatformServicesInterface>& services);

        SignalPublicApi();

        void RegisterSignal();

        // ------------------------------------ SIGNAL --------------------------------------

        ///@}

        /**
         * @name Signal
         */
        ///@{

        /**
         * @brief Create collect PII event, which is listened by Rules Engine module to determine if the data
         * matches any PII request.
         *
         * @param data the PII data to be collected, which will be used in Rules Engine comparison and request token replacement.
         */
        void CollectPii(const std::map<std::string, std::string>& data);

        ///@}

    private:

        std::shared_ptr<EventHub> event_hub_;

        std::shared_ptr<PlatformServicesInterface> platform_services_;
    };
}

#endif /* ADOBEMOBILE_SIGNAL_SIGNALPUBLICAPI_H */
