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

#ifndef ADOBEMOBILE_IDENTITY_IDENTITYPUBLICAPI_H
#define ADOBEMOBILE_IDENTITY_IDENTITYPUBLICAPI_H

#include <AdobeMarketingMobileCore/AdobeMarketingMobileCore.h>
#include "Identity.h"

namespace AdobeMarketingMobile {
    class VisitorId;

    class IdentityPublicApi : public Object {
    public:

        static std::shared_ptr<IdentityPublicApi> Create(const std::shared_ptr<EventHub>& hub,
                const std::shared_ptr<PlatformServicesInterface>& services);

        IdentityPublicApi();

        void RegisterIdentity();

        /**
         * @brief Initiates an Identity Request event for fetching marketing cloud id
         *
         * @param callback AdobeCallback, the sdk would call with mid string value as the parameter.
         */
        void GetMarketingCloudId(const std::function<void(const std::string)>& callback) const;

        /**
         * @brief Initiates an Identity Request event for fetching IDs
         *
         * @param callback AdobeCallback, the sdk would call with the list of visitor id objects as the parameter.
         */
        void GetIdentifiers(const std::function<void(const std::vector<std::shared_ptr<VisitorId>>& result)>& callback) const;

        /**
         * @brief Initiates an Identity Request event for appending visitor ids to a base url.
         *
         * @param base_url  URL to which the visitor info needs to be appended to.
         * @param callback AdobeCallback, the sdk would call with the updated url string value as the parameter.
         */
        void AppendToUrl(const std::string& base_url,
                         const std::function<void(const std::string)>& callback) const;

        /**
         * @brief Initiates an Identity Request event for syncing identifierType, identifier with an
         * authentication state.
         *
         * @param identifier_type      identifier type value.
         * @param identifier          id value
         * @param authentication_state a valid VisitorIDAuthenticationState value.
         */
        void SyncIdentifier(const std::string& identifier_type, const std::string& identifier,
                            const VisitorIdAuthenticationState authentication_state);

        /**
         * @brief Initiates an Identity Request event for syncing a collection of identifers.
         *
         * @param identifiers that need to be synced where the key represents the idType and the value represents the id.
         */
        void SyncIdentifiers(const std::map<std::string, std::string>& identifiers);

        /**
         * @brief Initiates an Identity Request event for syncing Identifers with an authentication state.
         *
         * @param identifiers         that need to be synced where the key represents the idType and the value represents
         *                            the id.
         * @param authentication_state a valid VisitorIDAuthenticationState value.
         */
        void SyncIdentifiers(const std::map<std::string, std::string>& identifiers,
                             const VisitorIdAuthenticationState authentication_state);

        /**
         * @brief Sets the device token for push notifications.
         *
         * @param registration_id push token that needs to be set.
         */
        void SetPushIdentifier(const std::string& registration_id);

        /**
         * @brief Returns the push identifier.
         *
         * Returns empty string if there is no push identifier set yet.
         *
         * @param callback AdobeCallback, the sdk would call with the push identifier string value as the parameter.
         */
        void GetPushIdentifier(const std::function<void(const std::string)>& callback);

        /**
         * @brief Sets the advertising identifier in the SDK. The id will be sent in lifecycle if it has been set
         * in the SDK.
         *
         * It can also be accessed in Signals (Postbacks).
         *
         * @param ad_id the advertising idenifier string.
         */
        void SetAdvertisingIdentifier(const std::string& ad_id);

        /**
         * @brief Returns the advertising identifier.
         *
         * Returns empty if there is no advertising identifier set yet.
         *
         * @param callback AdobeCallback, the sdk would call with the advertising identifier string value as the parameter.
         */
        void GetAdvertisingIdentifier(const std::function<void(const std::string)>& callback);

        /**
         * @brief Sets the user identifier
         *
         * @param user_id user identifier that needs to be set.
         */
        void SetUserIdentifier(const std::string& user_id);

        /**
         * @brief Returns the custom user identifier if a custom identifier has been set.
         *
         * Returns empty string if a custom identifier is not set.
         *
         * @param callback AdobeCallback, the sdk would call with the user identifier string value as the parameter.
         */
        void GetUserIdentifier(const std::function<void(const std::string)>& callback);

    private:

        std::shared_ptr<Event> CreateIdentityRequestEvent(const std::shared_ptr<EventData>& event_data) const;


        void CreateIdentityRequestWithOneTimeCallbackWithVisitorIdCallbackParam(const std::string& identifier_key,
                const std::shared_ptr<EventData>& event_data,
                const std::function<void(const std::vector<std::shared_ptr<VisitorId>>& result)>& callback) const;


        void CreateIdentityRequestWithOneTimeCallbackWithStringCallbackParam(const std::string& identifier_key,
                const std::shared_ptr<EventData>& event_data,
                const std::function<void(const std::string&)>& callback) const;

        /**
         * @private
         *
         * Marshalling the eventData for the sync identifiers event.
         * Creates a request identity event with the syncIdentifier eventData and dispatches to the eventhub.
         *
         * @param identifiers that need to be synced where the key represents the idType and the value represents the id.
         * @param dpids       that need to be synced.
         * @param authentication_state   a valid VisitorIDAuthenticationState value.
         * @param is_force_sync boolean variable that determines if the force sync is required.
         */
        void DispatchIdSyncEvent(const std::map<std::string, std::string>& identifiers,
                                 const std::map<std::string, std::string>& dpids, const VisitorIdAuthenticationState authentication_state,
                                 const bool is_force_sync);


        std::shared_ptr<EventHub> event_hub_; ///< EventHub to which this Identity module is registered

        std::shared_ptr<PlatformServicesInterface> platform_services_; ///< PlatformServicesInterface for this Identity module
    };

}
#endif /* ADOBEMOBILE_IDENTITY_IDENTITYPUBLICAPI_H */
