
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

#ifndef ADOBEMOBILE_TARGET_TARGETDISPATCHEANALYTICSREQUESTCONTENT_H
#define ADOBEMOBILE_TARGET_TARGETDISPATCHEANALYTICSREQUESTCONTENT_H

#include <AdobeMarketingMobileCore/AdobeMarketingMobileCore.h>
#include "Target.h"

namespace AdobeMarketingMobile {

    /**
     * @class TargetDispatcherAnalyticsRequestContent
     * Event dispatcher for Analytics Request Content events from the Target module.
     */
    class TargetDispatcherAnalyticsRequestContent : public ModuleEventDispatcher<Target> {

    public:
        /**
         * Dispatches a analytics request event onto the EventHub for the A4T content received from the target request
         *
         * @param payload analytics context data
         */
        virtual void DispatchAnalyticsRequest(const std::map<std::string, std::string>& payload);
    };
}


#endif /* ADOBEMOBILE_TARGET_TARGETDISPATCHEANALYTICSREQUESTCONTENT_H */
