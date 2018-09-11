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

#ifndef ADOBEMOBILE_IDENTITY_LISTENER_REQUEST_IDENTITY_H
#define ADOBEMOBILE_IDENTITY_LISTENER_REQUEST_IDENTITY_H

#include "Identity.h"

namespace AdobeMarketingMobile {
    /**
     * @class IdentityListenerRequestIdentity
     * Listener for Identity REQUEST_IDENTITY events
     */
    class IdentityListenerRequestIdentity: public ModuleEventListener<Identity> {
    public:
        /**
         * Callback for Identity REQUEST_IDENTITY events
         *
         * @param event Identity REQUEST_IDENTITY event
         */
        void Hear(const std::shared_ptr<Event>& event) override;
    };

}


#endif /* ADOBEMOBILE_IDENTITY_LISTENER_REQUEST_IDENTITY_H */
