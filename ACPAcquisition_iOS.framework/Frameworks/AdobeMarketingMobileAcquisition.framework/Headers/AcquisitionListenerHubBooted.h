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

#ifndef ADOBEMOBILE_ACQUISITION_ACQUISITIONLISTENERHUBBOOTED_H
#define ADOBEMOBILE_ACQUISITION_ACQUISITIONLISTENERHUBBOOTED_H

#include <AdobeMarketingMobileCore/ModuleEventListener.h>
#include "Acquisition.h"

namespace AdobeMarketingMobile {
    /**
     * @class AcquisitionListenerHubBooted
     * Listener for EventHub's BOOTED event
     */
    class AcquisitionListenerHubBooted : public ModuleEventListener<Acquisition> {
    public:
        /**
         * Callback for EVENTHUB BOOTED events
         *
         * @param event EVENTHUB BOOTED event
         */
        void Hear(const std::shared_ptr<Event>& event) override;
    };
}

#endif /* ADOBEMOBILE_ACQUISITION_ACQUISITIONLISTENERHUBBOOTED_H */
