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

#ifndef ADOBEMOBILE_CONFIGURATION_CONFIGURATIONLISTENERBOOTEVENT_H
#define ADOBEMOBILE_CONFIGURATION_CONFIGURATIONLISTENERBOOTEVENT_H

#include "Configuration.h"
#include "Event.h"
#include "ModuleEventListener.h"

namespace AdobeMarketingMobile {
    /**
     * @class ConfigurationListenerBootEvent
     * Listener for EventHub BOOTED events.
     */
    class ConfigurationListenerBootEvent : public ModuleEventListener<Configuration> {
    public:
        /**
         * Callback for EventHub BOOTED events to the Configuration Module.
         *
         * @param event an EventHub BOOTED.
         */
        void Hear(const std::shared_ptr<Event>& event) override;
    };
}

#endif /* ADOBEMOBILE_CONFIGURATION_CONFIGURATIONLISTENERBOOTEVENT_H */
