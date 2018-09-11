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

#ifndef ADOBEMOBILE_CONFIGURATION_CONFIGURATIONDISPATCHERCONFIGURATIONREQUESTCONTENT_H
#define ADOBEMOBILE_CONFIGURATION_CONFIGURATIONDISPATCHERCONFIGURATIONREQUESTCONTENT_H

#include "Configuration.h"
#include "ModuleEventDispatcher.h"

namespace AdobeMarketingMobile {

    /**
     * @class ConfigurationEventDispather
     * Event dispatcher for the Configuration module.
     */
    class ConfigurationDispatcherConfigurationRequestContent : public ModuleEventDispatcher<Configuration> {

    public:

        /**
         * Dispatch Configuration request using App ID. Called internally by the Configuration Module.
         *
         * @param app_id App ID used for configuration
         */
        virtual void DispatchInternalConfigureWithAppIdEvent(const std::string& app_id);
    };
}

#endif /* ADOBEMOBILE_CONFIGURATION_CONFIGURATIONDISPATCHERCONFIGURATIONREQUESTCONTENT_H */

