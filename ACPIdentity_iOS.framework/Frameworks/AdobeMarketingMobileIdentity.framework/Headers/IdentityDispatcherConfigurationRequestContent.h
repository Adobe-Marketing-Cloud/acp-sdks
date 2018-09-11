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

#ifndef ADOBEMOBILE_IDENTITY_DISPATCHER_CONFIGURATION_REQUEST_CONTENT_H
#define ADOBEMOBILE_IDENTITY_DISPATCHER_CONFIGURATION_REQUEST_CONTENT_H

#include "Identity.h"

namespace AdobeMarketingMobile {

    /**
     * @class IdentityEventDispatcher
     * Identity Response Event dispatcher for the Identity module.
     */
    class IdentityDispatcherConfigurationRequestContent : public ModuleEventDispatcher<Identity> {

    public:
        /**
         * Dispatch Identity event for Configuration Update.
         *
         * @param event_data event data for Configuration module to update configruation.
         */
        virtual void DispatchConfigUpdateRequest(const std::shared_ptr<EventData>& event_data);
    };
}

#endif /* ADOBEMOBILE_IDENTITY_DISPATCHER_CONFIGURATION_REQUEST_CONTENT_H */
