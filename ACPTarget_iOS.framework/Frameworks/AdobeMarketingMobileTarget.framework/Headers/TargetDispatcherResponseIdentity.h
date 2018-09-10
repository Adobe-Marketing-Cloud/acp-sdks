
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

#ifndef ADOBEMOBILE_TARGET_TARGETDISPATCHERRESPONSEIDENTITY_H
#define ADOBEMOBILE_TARGET_TARGETDISPATCHERRESPONSEIDENTITY_H

#include <AdobeMarketingMobileCore/AdobeMarketingMobileCore.h>
#include "Target.h"

namespace AdobeMarketingMobile {

    /**
     * @class TargetDispatcherResponseIdentity
     * Event dispatcher for Response Identity events from the Target module.
     */
    class TargetDispatcherResponseIdentity : public ModuleEventDispatcher<Target> {

    public:
        /**
         * Dispatches a response identity event onto the EventHub
         *
         * @param tnt_id the tnt id
         * @param third_party_id current third party id
         * @param pair_id A unique pairing id for the event
         */
        virtual void DispatchIdentityResponse(const std::string& tnt_id, const std::string& third_party_id,
                                              const std::string& pair_id);
    };
}


#endif /* ADOBEMOBILE_TARGET_TARGETDISPATCHERRESPONSEIDENTITY_H */
