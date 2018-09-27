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

#ifndef ADOBEMOBILE_CONFIGURATION_CONFIGURATIONLISTENERREQUESTIDENTITY_H
#define ADOBEMOBILE_CONFIGURATION_CONFIGURATIONLISTENERREQUESTIDENTITY_H

#include "Configuration.h"
#include "Event.h"
#include "ModuleEventListener.h"

namespace AdobeMarketingMobile {
    /**
     * @class ConfigurationListenerRequestIdentity
     * Listener for Configuration Request Identity events.
     */
    class ConfigurationListenerRequestIdentity : public ModuleEventListener<Configuration> {
    public:
        /**
         * Callback for Configuration Request Identity events.
         *
         * @param event Configuration Request Identity event.
         */
        void Hear(const std::shared_ptr<Event>& event) override;
    };
}


#endif /* ADOBEMOBILE_CONFIGURATION_CONFIGURATIONLISTENERREQUESTIDENTITY_H */
