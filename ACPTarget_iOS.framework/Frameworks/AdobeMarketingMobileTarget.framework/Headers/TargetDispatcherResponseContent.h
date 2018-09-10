
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

#ifndef ADOBEMOBILE_TARGET_TARGETDISPATCHERRESPONSECONTENT_H
#define ADOBEMOBILE_TARGET_TARGETDISPATCHERRESPONSECONTENT_H

#include <AdobeMarketingMobileCore/AdobeMarketingMobileCore.h>
#include "Target.h"

namespace AdobeMarketingMobile {

    /**
     * @class TargetDispatcherResponseContent
     * Event dispatcher for Response Content events from the Target module.
     */
    class TargetDispatcherResponseContent : public ModuleEventDispatcher<Target> {

    public:
        /**
         * Dispatches a response content event onto the EventHub for the given content and pairId
         *
         * @param content the content for the mbox request
         * @param pair_id A unique pairing id for the event
         */
        virtual void DispatchMboxContent(const std::string& content, const std::string& pair_id);

        /**
         * Dispatches a response content event for prefetch onto the EventHub
         *
         * @param result flag to indicate whether the prefetch was sucessful or not
         * @param pair_id A unique pairing id for the event
         */
        virtual void DispatchPrefetchResult(const bool result, const std::string& pair_id);
    };
}


#endif /* ADOBEMOBILE_TARGET_TARGETDISPATCHERRESPONSECONTENT_H */
