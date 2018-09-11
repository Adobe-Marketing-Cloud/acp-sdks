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

#ifndef ADOBEMOBILE_CONFIGURATION_CONFIGURATIONLISTENERHUBSHAREDSTATE_H
#define ADOBEMOBILE_CONFIGURATION_CONFIGURATIONLISTENERHUBSHAREDSTATE_H

#include "Configuration.h"
#include "Event.h"
#include "ModuleEventListener.h"


namespace AdobeMarketingMobile {
    /**
     * @class ConfigurationListenerHubSharedState
     * Listener for shared state change events.
     */
    class ConfigurationListenerHubSharedState : public ModuleEventListener<Configuration> {
    public:
        /**
         * Callback for shared state change events.
         *
         * @param event HUB SHARED_STATE event.
         */
        void Hear(const std::shared_ptr<Event>& event) override;
    };
}

#endif /* ADOBEMOBILE_CONFIGURATION_CONFIGURATIONLISTENERHUBSHAREDSTATE_H */
