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

#ifndef ADOBEMOBILE_CONFIGURATION_SHARED_STATE_IDENTITY_H
#define ADOBEMOBILE_CONFIGURATION_SHARED_STATE_IDENTITY_H

#include <string>
#include "Identity.h"

namespace AdobeMarketingMobile {

    enum class MobilePrivacyStatus : int32_t;

    class ConfigurationSharedStateIdentity : public Object {

    public:
        explicit ConfigurationSharedStateIdentity(const std::shared_ptr<EventData>& shared_state);
        bool CanSyncIdentifiersWithCurrentConfiguration();
        std::string GetOrgId();
        std::string GetMarketingCloudServer();
        bool GetSSLStatus();
        bool GetAdIdEnabledStatus();
        MobilePrivacyStatus GetPrivacyStatus();
    protected:


    protected:

    private:
        std::string org_id_;
        bool ssl_;
        MobilePrivacyStatus privacy_status_;
        std::string marketing_cloud_server_;
        bool ad_id_enabled_;
    };
}

#endif /* ADOBEMOBILE_CONFIGURATION_SHARED_STATE_IDENTITY_H */
