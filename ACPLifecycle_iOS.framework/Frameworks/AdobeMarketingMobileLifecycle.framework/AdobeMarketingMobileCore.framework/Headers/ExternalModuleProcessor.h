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

#ifndef ADOBEMOBILE_EXTERNALMODULE_EXTERNALMODULEPROCESSOR_H
#define ADOBEMOBILE_EXTERNALMODULE_EXTERNALMODULEPROCESSOR_H

#include "ModuleEventProcessor.h"
#include "ExternalModule.h"
#include "Event.h"

namespace AdobeMarketingMobile {
    /**
     * @class ExternalModuleProcessor
     * Listener registered by an external module for various event types and sources
     */
    class ExternalModuleProcessor : public ModuleEventProcessor<ExternalModule> {
    public:
        std::shared_ptr<Event> Process(const std::shared_ptr<Event>& event) override;
    protected:
        void OnRegistered() override;
        void OnUnregistered() override;
    };
}

#endif /* ADOBEMOBILE_EXTERNALMODULE_EXTERNALMODULEPROCESSOR_H */


