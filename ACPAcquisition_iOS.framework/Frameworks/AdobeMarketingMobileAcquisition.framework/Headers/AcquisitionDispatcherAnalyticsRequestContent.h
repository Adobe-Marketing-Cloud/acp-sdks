/***************************************************************************
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

#ifndef ADOBEMOBILE_ACQUISITION_ACQUISITIONDISPATCHERANALYTICSREQUESTCONTENT_H
#define ADOBEMOBILE_ACQUISITION_ACQUISITIONDISPATCHERANALYTICSREQUESTCONTENT_H

#include <AdobeMarketingMobileCore/ModuleEventDispatcher.h>
#include "Acquisition.h"

namespace AdobeMarketingMobile {
    /**
     * @class AcquisitionDispatcherAnalyticsRequestContent
     * Event dispatcher for Analytics REQUEST_CONTENT events
     */
    class AcquisitionDispatcherAnalyticsRequestContent : public ModuleEventDispatcher<Acquisition> {
    public:
        /**
         * Dispatch Analytics track event
         *
         * @param action the name of action. if it is empty, no event will be dispatched
         * @param data context data map
         */
        ADOBE_VIRTUAL_FOR_TESTS void DispatchAnalyticsTrackEvent(const std::string& action,
                const std::map<std::string, std::string>& data);
    };
}

#endif /* ADOBEMOBILE_ACQUISITION_ACQUISITIONDISPATCHERANALYTICSREQUESTCONTENT_H */
