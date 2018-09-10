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

#ifndef ADOBEMOBILE_CONFIGURATION_CONFIGURATIONLISTENERREQUESTCONTENT_H
#define ADOBEMOBILE_CONFIGURATION_CONFIGURATIONLISTENERREQUESTCONTENT_H

#include "Configuration.h"
#include "Event.h"
#include "ModuleEventListener.h"

namespace AdobeMarketingMobile {
    /**
     * @class ConfigurationListenerRequestContent
     * Listener for Configuration update events.
     */
    class ConfigurationListenerRequestContent : public ModuleEventListener<Configuration> {
    public:
        /**
         * Callback for Configuration update request events.
         *
         * @param event Configuration request content event.
         */
        void Hear(const std::shared_ptr<Event>& event) override;
    };
}

#endif /* ADOBEMOBILE_CONFIGURATION_CONFIGURATIONLISTENERREQUESTCONTENT_H */
