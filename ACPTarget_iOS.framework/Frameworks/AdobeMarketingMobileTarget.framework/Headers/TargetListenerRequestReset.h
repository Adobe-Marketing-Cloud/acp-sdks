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

#ifndef ADOBEMOBILE_TARGET_TARGETLISTENERREQUESTRESET_H
#define ADOBEMOBILE_TARGET_TARGETLISTENERREQUESTRESET_H

#include <AdobeMarketingMobileCore/AdobeMarketingMobileCore.h>
#include "Target.h"

namespace AdobeMarketingMobile {
    /**
     * @class TargetListenerRequestReset
     * Listener for Target data reset requests
     */
    class TargetListenerRequestReset : public ModuleEventListener<Target> {
    public:
        void Hear(const std::shared_ptr<Event>& event) override;
    };
}

#endif /* ADOBEMOBILE_TARGET_TARGETLISTENERREQUESTRESET_H */
