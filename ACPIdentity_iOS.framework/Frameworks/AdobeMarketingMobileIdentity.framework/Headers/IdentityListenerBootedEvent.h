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

#ifndef ADOBEMOBILE_IDENTITY_LISTENER_BOOTED_EVENT_H
#define ADOBEMOBILE_IDENTITY_LISTENER_BOOTED_EVENT_H

#include "Identity.h"

namespace AdobeMarketingMobile {
    /**
     * @class IdentityListenerBootedEvent
     * Listener for BOOTED event.
     */
    class IdentityListenerBootedEvent: public ModuleEventListener<Identity> {
    public:
        /**
         *
         * @param event BOOTED event
         */
        void Hear(const std::shared_ptr<Event>& event) override;
    };
}


#endif /* ADOBEMOBILE_IDENTITY_LISTENER_BOOTED_EVENT_H */
