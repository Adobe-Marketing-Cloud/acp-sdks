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
 ****************************************************************************/

#ifndef ADOBEMOBILE_EXTERNALMODULE_EXTERNALMODULESERVICES_H
#define ADOBEMOBILE_EXTERNALMODULE_EXTERNALMODULESERVICES_H

#include "Object.h"
#include "Event.h"
#include "SdkError.h"
#include "ExternalModuleListenerInterface.h"

namespace AdobeMarketingMobile {

    /**
     * @brief Interface providing access to event hub for the ADBModule.
     *
     */
    class ExternalModuleServicesInterface : public virtual ObjectInterface {
    public:
        virtual void RegisterListener(const std::shared_ptr<ExternalModuleListenerInterface>& event_listener,
                                      const std::string& event_type,
                                      const std::string& event_source) = 0;

        virtual void RegisterWildcardListener(const std::shared_ptr<ExternalModuleListenerInterface>& event_listener) = 0;

        virtual void DispatchEvent(const std::shared_ptr<Event>& event) = 0;

        virtual void SetSharedEventState(const std::string& state,
                                         const std::shared_ptr<Event>& event) = 0;

        virtual void ClearSharedEventStates() = 0;

        virtual std::shared_ptr<std::string> GetSharedEventState(const std::string& state_name,
                const std::shared_ptr<Event>& event) = 0;

        virtual void UnregisterModule() = 0;
    };

} // AdobeMarketingMobile namespace

#endif /* ADOBEMOBILE_EXTERNALMODULESERVICES_H */

