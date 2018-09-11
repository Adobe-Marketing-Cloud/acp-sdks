
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

#ifndef ADOBEMOBILE_LIFECYCLE_LIFECYCLEDISPATCHERRESPONSECONTENT_H
#define ADOBEMOBILE_LIFECYCLE_LIFECYCLEDISPATCHERRESPONSECONTENT_H

#include "Lifecycle.h"
#import <AdobeMarketingMobileCore/AdobeMarketingMobileCore.h>


namespace AdobeMarketingMobile {

    /**
     * @class LifecycleDispatcherResponseContent
     * Event dispatcher for Lifecycle Response Content events from the Lifecycle module.
     */
    class LifecycleDispatcherResponseContent : public ModuleEventDispatcher<Lifecycle> {

    public:
        /**
         * Dispatches a lifecycle response event onto the EventHub containing the session info as event data
         *
         */
        virtual void DispatchSessionStart(const std::chrono::seconds start_timestamp_seconds,
                                          const std::map<std::string, std::string> context_data,
                                          const std::chrono::seconds previous_session_start_seconds,
                                          const std::chrono::seconds previous_session_pause_seconds);
    };
}


#endif /* ADOBEMOBILE_LIFECYCLE_LIFECYCLEDISPATCHERRESPONSECONTENT_H */

