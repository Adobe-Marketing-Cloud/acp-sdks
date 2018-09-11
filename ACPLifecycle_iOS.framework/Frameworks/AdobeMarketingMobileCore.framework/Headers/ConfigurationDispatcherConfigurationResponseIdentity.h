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

#ifndef ADOBEMOBILE_CONFIGURATION_CONFIGURATIONDISPATCHERCONFIGURATIONRESPONSEIDENTITY_H
#define ADOBEMOBILE_CONFIGURATION_CONFIGURATIONDISPATCHERCONFIGURATIONRESPONSEIDENTITY_H

#include "Configuration.h"
#include "ModuleEventDispatcher.h"

namespace AdobeMarketingMobile {
    /**
     * @class ConfigurationDispatcherConfigurationResponseIdentity
     * Event dispatcher for the Configuration Response Identity Events.
     */
    class ConfigurationDispatcherConfigurationResponseIdentity : public ModuleEventDispatcher<Configuration> {

    public:

        /**
         * Dispatches EventType#CONFIGURATION , EventSource#RESPONSE_IDENTITY event into the EventHub
         * with #sdk_identities_json string for the given #pair_id.
         *
         * @param sdk_identities_json A Jsonstring containing all the identities
         * @param pair_id A unique pairing id for one-time listener
         */
        virtual void DispatchAllIdentities(const std::string& sdk_identities_json, const std::string& pair_id);

    };
}


#endif /* ADOBEMOBILE_CONFIGURATION_CONFIGURATIONDISPATCHERCONFIGURATIONRESPONSEIDENTITY_H */
