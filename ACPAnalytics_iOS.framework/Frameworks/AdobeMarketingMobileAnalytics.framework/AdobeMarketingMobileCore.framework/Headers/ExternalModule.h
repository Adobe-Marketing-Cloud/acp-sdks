/***************************************************************************
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

#ifndef ADOBEMOBILE_EXTERNALMODULE_H
#define ADOBEMOBILE_EXTERNALMODULE_H

#include <map>
#include <set>

#include "Common.h"
#include "InternalModule.h"
#include "ExternalModuleInterface.h"

namespace AdobeMarketingMobile {
    class Event;
    class ExternalModuleServicesImpl;
    class ExternalModuleListenerInterface;
    class ExternalModuleDispatcher;

    class ExternalModule : public InternalModule {
    public:
        ExternalModule();

        explicit ExternalModule(const std::string& log_prefix, const std::shared_ptr<ExternalModuleInterface>& interface);

        std::string GetLogPrefix() {
            return log_prefix_;
        }

        ADOBE_VIRTUAL_FOR_TESTS std::string GetSharedStateName() override;

        ADOBE_VIRTUAL_FOR_TESTS void HandleUnexpectedError(SdkError& e);

        /*
         * Interface methods called by the ExternalModuleServicesImpl
         */

        ADOBE_VIRTUAL_FOR_TESTS void ExternalServices_RegisterListener(const std::shared_ptr<ExternalModuleListenerInterface>&
                event_listener,
                const std::string& event_type,
                const std::string& event_source);
        ADOBE_VIRTUAL_FOR_TESTS void ExternalServices_DispatchEvent(const std::shared_ptr<Event>& event);
        ADOBE_VIRTUAL_FOR_TESTS void ExternalServices_SetSharedEventState(const std::string& state,
                const std::shared_ptr<Event>& event);
        ADOBE_VIRTUAL_FOR_TESTS void ExternalServices_ClearSharedEventStates();
        ADOBE_VIRTUAL_FOR_TESTS std::shared_ptr<std::string> ExternalServices_GetSharedEventState(const std::string& name,
                const std::shared_ptr<Event>& event);
        ADOBE_VIRTUAL_FOR_TESTS void ExternalServices_UnregisterModule();

        /*
         * Interface methods called by the ExternalModuleListener
         */

        ADOBE_VIRTUAL_FOR_TESTS void ExternalListener_OnRegistered(const std::shared_ptr<EventType>& event_type,
                const std::shared_ptr<EventSource>& event_source);
        ADOBE_VIRTUAL_FOR_TESTS void ExternalListener_Hear(const std::shared_ptr<Event>& event);
        ADOBE_VIRTUAL_FOR_TESTS void ExternalListener_OnUnregistered(const std::shared_ptr<EventType>& event_type,
                const std::shared_ptr<EventSource>& event_source);

    protected:
        ADOBE_VIRTUAL_FOR_TESTS void OnRegistered() override;
        ADOBE_VIRTUAL_FOR_TESTS void OnUnregistered() override;

    private:
        std::shared_ptr<ExternalModuleDispatcher> GetDispatcher();

        std::shared_ptr<ExternalModuleListenerInterface> FindListener(const std::shared_ptr<EventType>& event_type,
                const std::shared_ptr<EventSource>& event_source);

        // Prefix for all logging messages
        std::string log_prefix_;

        // Used for locking access to the private members
        std::mutex mutex_;

        // The internal module uses this to call the external module
        std::shared_ptr<ExternalModuleInterface> interface_;

        // The external module uses this to call the internal module
        std::shared_ptr<ExternalModuleServicesImpl> services_;

        // The internal module uses this to dispatch events from the external module
        std::shared_ptr<ExternalModuleDispatcher> dispatcher_;

        // The internal module uses this to call the external listeners
        typedef std::pair<std::shared_ptr<EventType>, std::shared_ptr<EventSource>> ListenerKey;
        std::map<ListenerKey, std::shared_ptr<ExternalModuleListenerInterface>> listeners_;
    };

}

#endif /* ADOBEMOBILE_EXTERNALMODULE_H */

