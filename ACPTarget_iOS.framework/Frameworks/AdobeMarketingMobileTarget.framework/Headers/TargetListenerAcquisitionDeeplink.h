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

#ifndef ADOBEMOBILE_TARGET_TARGETLISTENERACQUISITIONDEEPLINK_H
#define ADOBEMOBILE_TARGET_TARGETLISTENERACQUISITIONDEEPLINK_H

#include <AdobeMarketingMobileCore/AdobeMarketingMobileCore.h>
#include "Target.h"

namespace AdobeMarketingMobile {
    /**
     * @class TargetListenerAcquisitionDeeplink
     * Listener for Acquisition OS or REQUEST_CONTENT events to capture the deep link information
     */
    class TargetListenerAcquisitionDeeplink : public ModuleEventListener<Target> {
    public:
        void Hear(const std::shared_ptr<Event>& event) override;
    };
}

#endif /* ADOBEMOBILE_TARGET_TARGETLISTENERACQUISITIONDEEPLINK_H */

