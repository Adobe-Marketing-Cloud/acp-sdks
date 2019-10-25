/*
Copyright 2018 Adobe. All rights reserved.
This file is licensed to you under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License. You may obtain a copy
of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS
OF ANY KIND, either express or implied. See the License for the specific language
governing permissions and limitations under the License.
*/

#ifndef ADOBEMOBILE_CONFIGURATION_MOBILEIDENTITIES_H
#define ADOBEMOBILE_CONFIGURATION_MOBILEIDENTITIES_H

#include "Configuration.h"
#include "Event.h"

namespace AdobeMarketingMobile {

    class MobileIdentities {
    public:
        /**
         * Collects all the identities in the given string format from various modules.
         *
         * @param json_utility_service A JsonUtilityService instance from PlatformServices for creating a JSON string
         * @param event An Event generated by the GetSdkIdentities API
         * @param module An Module instance to retrieve the shared state information
         * @return A string with all available identities in json format
         */
        static std::string GetAllIdentifiers(const std::shared_ptr<JsonUtilityServiceInterface>& json_utility_service,
                                             const std::shared_ptr<Event>& event, const std::shared_ptr<Configuration>& module);

        /**
         * Verifies none of the shared states required for the GetSDKIdentities API are in PENDING State.
         * The required shared states are:
         * 1.Analytics
         * 2.Audience
         * 3.Configuration
         * 4.Identity
         * 5.Target
         *
         *Returns true, if the all the above shared state are valid.
         *Returns false, if any one of the above shared state is in EventHub#SHARED_STATE_PENDING.
         *
         * @param event An Event generated by the GetSdkIdentities API
         * @param module An Module instance to retrieve the shared state
         * @return A boolean indicating the availability of the required module shared state
         */
        static bool AreAllSharedStateReady(const std::shared_ptr<Event>& event, const std::shared_ptr<Configuration>& module);

    private:
        /**
         * Gets the required identities from Audience Module.
         * A List of map in the following format will be appended depending the availability of the Audience shared state.
         *
         * [{ "namespace" : "0", "value" : "AAM_UUID", "type" : "namespaceId" },
         * { "namespace" : "AAM_DPID", "value" : "AAM_DPUUID", "type" : "namespaceId" }]
         *
         * An empty list will be returned if the Audience shared state is invalid or null.
         *
         * @param event An Event generated by the GetSdkIdentities API
         * @param module An Module instance to retrieve the Audience shared state
         * @return List containing Audience Identities
         */
        static std::vector<std::shared_ptr<Variant>> GetAudienceIdentifiers(const std::shared_ptr<Event>& event,
                const std::shared_ptr<Configuration>& module);

        /**
         * Gets the required identities from Analytics Module.
         * A List of map in the following format will be appended depending the availability of theAnalytics} shared state.
         *
         * [ { "namespace" : "avid", "value" : "AID", "type" : "integrationCode" },
         * { "namespace" : "vid", "value" : "VID", "type" : "analytics", "rsids" : [ "rsid1", "rsid2", ... ] }]
         *
         * An empty list will be returned if the Analytics shared state is invalid or null.
         *
         * @param event An Event generated by the GetSdkIdentities API
         * @param module An Module instance to retrieve the Analytics shared state
         * @return List containing Analytics Identities
         */
        static std::vector<std::shared_ptr<Variant>> GetAnalyticsIdentifiers(const std::shared_ptr<Event>& event,
                const std::shared_ptr<Configuration>& module);

        /**
         * Gets the required identities from Identity Module.
         *
         * A List of map in the following format will be appended depending the availability of theIdentity shared state.
         * [ { "namespace" : "INTEGRATION CODE", "value" : "ID", "type" : "integrationCode" },
         *{ "namespace" : "4", "value" : "MCID", "type" : "namespaceId" },
         *{ "namespace" : "20920", "value" : "PUSHID", "type" : "integrationCode" },
         *{ "namespace" : "DSID_20915","value" : "ADID", "type" : "integrationCode" },
         * ]
         *
         * An empty list will be returned if the Identity shared state is invalid or null.
         *
         * @param event An Event generated by the GetSdkIdentities API
         * @param module An Module instance to retrieve the Identity shared state
         * @return List containing Visitor Identities
         */
        static std::vector<std::shared_ptr<Variant>> GetVisitorIdentifiers(const std::shared_ptr<Event>& event,
                const std::shared_ptr<Configuration>& module);


        /**
         * Gets the required identities from Target Module.
         *
         * A List of map in the following format will be appended depending the availability of the Target shared state.
         *
         * [{ "namespace" : "tntid", "value" : "TNTID", "type" : "target" },
         * { "namespace" : "3rdpartyid", "value" : "TNT3RDPARTYID", "type" : "target" }]
         *
         * An empty list will be returned if the Target shared state is invalid or null.
         *
         * @param event An Event generated by the GetSdkIdentities API
         * @param module An Module instance to retrieve the Target shared state
         * @return List containing Target Identities
         */
        static std::vector<std::shared_ptr<Variant>> GetTargetIdentifiers(const std::shared_ptr<Event>& event,
                const std::shared_ptr<Configuration>& module);

        /**
         * Gets the company context map in the following format.
         *
         *"companyContexts": [
         * { "namespace": "imsOrgID", "value": "ORGID" }
         *]
         *
         * Returns null if the Configuration shared state is invalid or null.
         * Returns null if the Configuration shared state is valid and marketingCloudID cannot be found
         * inConfiguration shared state.
         *
         * @param event An Event generated by the GetSdkIdentities API
         * @param module An Module instance to retrieve the Identity shared state
         * @return List representing company context
         */
        static std::vector<std::shared_ptr<Variant>> GetCompanyContext(const std::shared_ptr<Event>& event,
                const std::shared_ptr<Configuration>& module);

        /**
         * Helper method to create a userID Map.
         *
         * @param name_space A String representing namespace
         * @param value An String representing value
         * @param type An String representing type
         * @return An UserIDMap
         */
        static std::map<std::string, std::shared_ptr<Variant>> CreateUserIdMap(const std::string& name_space,
                const std::string& value,
                const std::string& type);

        /**
         * Verifies if the given shared state is valid.
         * Returns false, if the give provided sharedState is invalid or pending. True otherwise.
         *
         * @param shared_state An EventData representing a shared state
         * @return boolean value representing the validity of the shared state
         */
        static bool IsSharedStateValid(const std::shared_ptr<EventData>& shared_state);
    };
}

#endif /* ADOBEMOBILE_CONFIGURATION_MOBILEIDENTITIES_H */
