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

#ifndef ADOBEMOBILE_IDENTITY_DISPATCHER_ANALYTICS_REQUEST_CONTENT_H
#define ADOBEMOBILE_IDENTITY_DISPATCHER_ANALYTICS_REQUEST_CONTENT_H

#include <string>
#include "Identity.h"

namespace AdobeMarketingMobile {

    /**
     * @class IdentityAnalyticsEventDispatcher
     * Analytics Event dispatcher for the Identity module.
     */
    class IdentityDispatcherAnalyticsRequestContent : public ModuleEventDispatcher<Identity> {

    public:
        /**
         * Dispatch Identity analytics event with updated analytics data.
         *
         * @param event_data analytics data as EventData
         */
        virtual void DispatchAnalyticsEventWithEventData(const std::shared_ptr<EventData>& event_data);
    };
}

#endif /* ADOBEMOBILE_IDENTITY_DISPATCHER_ANALYTICS_REQUEST_CONTENT_H */
