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

#ifndef ADOBEMOBILETESTS_IDENTITY_MOCKIDENTITY_ANALYTICS_EVENT_DISPATCHER_H
#define ADOBEMOBILETESTS_IDENTITY_MOCKIDENTITY_ANALYTICS_EVENT_DISPATCHER_H

#include "Identity.h"
#include "IdentityDispatcherAnalyticsRequestContent.h"
#include "MockModule.h"
#include "gtest/gtest.h"

namespace AdobeMarketingMobile {

    class MockIdentityAnalyticsEventDispatcher : public IdentityDispatcherAnalyticsRequestContent {
    public:
        MockIdentityAnalyticsEventDispatcher() {}

        MOCK_METHOD1(DispatchAnalyticsEventWithEventData, void(const std::shared_ptr<EventData>& event_data));
    };

}
#endif /* ADOBEMOBILETESTS_IDENTITY_MOCKIDENTITY_ANALYTICS_EVENT_DISPATCHER_H */
