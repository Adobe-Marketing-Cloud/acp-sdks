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

#ifndef ADOBEMOBILE_ACQUISITION_ACQUISITIONPUBLICAPI_H
#define ADOBEMOBILE_ACQUISITION_ACQUISITIONPUBLICAPI_H

#include <AdobeMarketingMobileCore/AdobeMarketingMobileCore.h>
#include <chrono>
#include <functional>
#include <map>
#include <string>
#include <vector>
#include "Acquisition.h"

namespace AdobeMarketingMobile {
    class AcquisitionPublicApi : public Object {
    public:

        static std::shared_ptr<AcquisitionPublicApi> Create(const std::shared_ptr<EventHub>& hub,
                const std::shared_ptr<PlatformServicesInterface>& services);

        AcquisitionPublicApi();

        void RegisterAcquisition();

        // ------------------------------------ ACQUISITION --------------------------------------

        /**
         * @brief Creates an Event with {@link EventSource#OS} and {@link EventType#ACQUISITION} and
         * dispatches to the event hub.
         *
         * This eventData may contain deepLink information, messages info or referrer data
         *
         * @param marshaled_event_data An EventData ptr the containing the event data to be sent.
         */
        void CollectData(const std::shared_ptr<EventData>& marshaled_event_data);

        ///@}

        /**
         * @name Acquisition
         */
        ///@{

        /**
         * @brief Processes the acquisition campaign start event for the given application ID
         *
         * @param application_id  the application ID for that we want to track the acquisition flow
         * @param additional_data extra context data
         */
        void AcquisitionCampaignStart(const std::string& application_id,
                                      const std::map<std::string, std::string>& additional_data);

        /**
         * @brief Processes the acquisition campaign start event for the given application ID
         *
         * @param deep_link  the URL that the application is processing
         */
        void TrackAdobeDeepLink(const std::string& deep_link);

        /**
         * Returns a deferred deep link to the caller if one exists in the acquisition data
         *
         * @param callback function that will be called containing a deferred deep link, if it exists
         */
        void GetDeferredDeepLink(const std::function<void(const std::string)>& callback);

    private:

        std::shared_ptr<EventHub> event_hub_;
        std::shared_ptr<PlatformServicesInterface> platform_services_;
    };
}

#endif /* ADOBEMOBILE_ACQUISITION_ACQUISITIONPUBLICAPI_H */

