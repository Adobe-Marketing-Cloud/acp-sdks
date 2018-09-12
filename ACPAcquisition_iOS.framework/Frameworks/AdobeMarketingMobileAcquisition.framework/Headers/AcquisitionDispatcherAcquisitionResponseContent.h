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

#ifndef ADOBEMOBILE_ACQUISITION_ACQUISITIONDISPATCHERACQUISITIONRESPONSECONTENT_H
#define ADOBEMOBILE_ACQUISITION_ACQUISITIONDISPATCHERACQUISITIONRESPONSECONTENT_H

#include <AdobeMarketingMobileCore/ModuleEventDispatcher.h>
#include "Acquisition.h"

namespace AdobeMarketingMobile {
    /**
     * @class AcquisitionDispatcherAcquisitionResponseContent
     * Event dispatcher for Acquisition RESPONSE_CONTENT events
     */
    class AcquisitionDispatcherAcquisitionResponseContent : public ModuleEventDispatcher<Acquisition> {
    public:
        /**
         * Dispatch Acquisition response event
         *
         * @param referrer_data referrer data map
         */
        ADOBE_VIRTUAL_FOR_TESTS void DispatchAcquisitionResponseEvent(const std::map<std::string, std::string>& referrer_data);
    };
}

#endif /* ADOBEMOBILE_ACQUISITION_ACQUISITIONDISPATCHERACQUISITIONRESPONSECONTENT_H */
