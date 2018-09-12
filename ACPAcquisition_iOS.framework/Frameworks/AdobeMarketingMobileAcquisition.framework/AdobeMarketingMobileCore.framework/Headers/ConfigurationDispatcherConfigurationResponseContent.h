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

#ifndef ADOBEMOBILE_CONFIGURATION_CONFIGURATIONDISPATCHERCONFIGURATIONRESPONSECONTENT_H
#define ADOBEMOBILE_CONFIGURATION_CONFIGURATIONDISPATCHERCONFIGURATIONRESPONSECONTENT_H

#include "Configuration.h"
#include "ModuleEventDispatcher.h"

namespace AdobeMarketingMobile {
    class EventData;

    /**
     * @class ConfigurationEventDispather
     * Event dispatcher for the Configuration module.
     */
    class ConfigurationDispatcherConfigurationResponseContent : public ModuleEventDispatcher<Configuration> {

    public:

        /**
         * Dispatch Configuration response event with updated configuration data.
         *
         * @param event_data Updated configuration data as EventData
         * @param pair_id A unique pairing id for the event (optional)
         */
        virtual void DispatchConfigResponseWithEventData(const std::shared_ptr<EventData>& event_data,
                const std::string& pair_id);
    };
}

#endif /* ADOBEMOBILE_CONFIGURATION_CONFIGURATIONDISPATCHERCONFIGURATIONRESPONSECONTENT_H */
