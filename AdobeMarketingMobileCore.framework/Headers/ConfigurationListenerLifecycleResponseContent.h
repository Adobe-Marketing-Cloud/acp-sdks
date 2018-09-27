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

#ifndef ADOBEMOBILE_CONFIGURATION_CONFIGURATIONLISTENERLIFECYCLERESPONSECONTENT_H
#define ADOBEMOBILE_CONFIGURATION_CONFIGURATIONLISTENERLIFECYCLERESPONSECONTENT_H

#include "Configuration.h"
#include "ModuleEventListener.h"

namespace AdobeMarketingMobile {
    /**
     * @class ConfigurationListenerLifecycleResponseContent
     * Listener for Configuration lifecycle response events.
     */
    class ConfigurationListenerLifecycleResponseContent : public ModuleEventListener<Configuration> {
    public:
        /**
         * Callback for Configuration retrieval request events.
         *
         * @param event Configuration retrieval request event.
         */
        void Hear(const std::shared_ptr<Event>& event) override;
    };
}

#endif /* ADOBEMOBILE_CONFIGURATION_CONFIGURATIONLISTENERLIFECYCLERESPONSECONTENT_H */
