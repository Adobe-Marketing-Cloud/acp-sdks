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

#ifndef ADOBEMOBILE_EXTERNALMODULE_EXTERNALMODULEDISPATCHER_H
#define ADOBEMOBILE_EXTERNALMODULE_EXTERNALMODULEDISPATCHER_H

#include "ExternalModule.h"
#include "ModuleEventDispatcher.h"

namespace AdobeMarketingMobile {

    class Event;

    /**
     * @class ExternalModuleDispatcher
     * Event dispatcher for all events from the ExternalModule module.
         *
     */
    class ExternalModuleDispatcher : public ModuleEventDispatcher<ExternalModule> {

    public:
        /**
         * Dispatches a externally generated event onto the EventHub
         * @param event The event to dispatch
         *
         */
        virtual void Dispatch(const std::shared_ptr<Event>& event);
    };
}

#endif /* ADOBEMOBILE_EXTERNALMODULE_EXTERNALMODULEDISPATCHER_H */
