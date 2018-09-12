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

#ifndef ADOBEMOBILE_EXTERNALMODULE_EXTERNALMODULELISTENER_H
#define ADOBEMOBILE_EXTERNALMODULE_EXTERNALMODULELISTENER_H

#include "ModuleEventListener.h"
#include "ExternalModule.h"
#include "Event.h"

namespace AdobeMarketingMobile {
    /**
     * @class ExternalModuleListener
     * Listener registered by an external module for various event types and sources
     */
    class ExternalModuleListener : public ModuleEventListener<ExternalModule> {
    public:
        void Hear(const std::shared_ptr<Event>& event) override;
    protected:
        void OnRegistered() override;
        void OnUnregistered() override;
    };
}

#endif /* ADOBEMOBILE_EXTERNALMODULE_EXTERNALMODULELISTENER_H */

