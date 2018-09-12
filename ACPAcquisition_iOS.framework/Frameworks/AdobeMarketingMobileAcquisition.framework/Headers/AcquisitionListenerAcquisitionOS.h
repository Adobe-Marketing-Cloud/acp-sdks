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

#ifndef ADOBEMOBILE_ACQUISITION_ACQUISITIONLISTENERACQUISITIONOS_H
#define ADOBEMOBILE_ACQUISITION_ACQUISITIONLISTENERACQUISITIONOS_H

#include <AdobeMarketingMobileCore/AdobeMarketingMobileCore.h>
#include "Acquisition.h"

namespace AdobeMarketingMobile {
    /**
     * @class AcquisitionListenerAcquisitionOS
     * Listener for OS events
     */
    class AcquisitionListenerAcquisitionOS : public ModuleEventListener<Acquisition> {
    public:
        /**
         * Callback for Acquisition OS event
         *
         * @param event Acquisition OS event
         */
        void Hear(const std::shared_ptr<Event>& event) override;
    };
}

#endif /* ADOBEMOBILE_ACQUISITION_ACQUISITIONLISTENERACQUISITIONOS_H */
