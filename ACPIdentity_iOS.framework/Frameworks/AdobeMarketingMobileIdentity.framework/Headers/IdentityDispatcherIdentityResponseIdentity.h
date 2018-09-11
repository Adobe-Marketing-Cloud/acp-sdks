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

#ifndef ADOBEMOBILE_IDENTITY_DISPATCHER_IDENTITY_RESPONSE_IDENTITY_H
#define ADOBEMOBILE_IDENTITY_DISPATCHER_IDENTITY_RESPONSE_IDENTITY_H

#include "Identity.h"

namespace AdobeMarketingMobile {

    /**
     * @class IdentityEventDispatcher
     * Identity Response Event dispatcher for the Identity module.
     */
    class IdentityDispatcherIdentityResponseIdentity : public ModuleEventDispatcher<Identity> {

    public:
        /**
         * Dispatch Identity response event with updated identity data.
         * @param event_name event name for the event
         * @param event_data event data as EventData
         * @param pair_id A unique pairing id for the event (optional)
         */
        virtual void DispatchIdentityResponse(const std::string& event_name, const std::shared_ptr<EventData>& event_data,
                                              const std::string& pair_id);

    };
}

#endif /* ADOBEMOBILE_IDENTITY_DISPATCHER_IDENTITY_RESPONSE_IDENTITY_H */
