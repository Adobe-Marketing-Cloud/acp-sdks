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

#ifndef ADOBEMOBILE_LIFECYCLE_LIFECYCLELISTENERHUBSHAREDSTATE_H
#define ADOBEMOBILE_LIFECYCLE_LIFECYCLELISTENERHUBSHAREDSTATE_H

#include "Lifecycle.h"
#import <AdobeMarketingMobileCore/AdobeMarketingMobileCore.h>


namespace AdobeMarketingMobile {
    /**
     * @class LifecycleListenerSharedStateUpdate
     * Listener for EventHub Shared State events
     */
    class LifecycleListenerSharedStateUpdate: public ModuleEventListener<Lifecycle> {
    public:
        /**
         * Callback for EventHub Shared State events
         *
         * @param event EventHub Shared State event
         */
        void Hear(const std::shared_ptr<Event>& event) override;
    };

}

#endif /* ADOBEMOBILE_LIFECYCLE_LIFECYCLELISTENERHUBSHAREDSTATE_H */
