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

#ifndef ADOBEMOBILE_EXTERNALMODULE_EXTERNALMODULEPROCESSORINTERFACE_H
#define ADOBEMOBILE_EXTERNALMODULE_EXTERNALMODULEPROCESSORINTERFACE_H

#include "Object.h"
#include "Event.h"

namespace AdobeMarketingMobile {

    /**
     * @brief Wrapper used to call the ADBModuleProcessorInterface provided by the external module
     *
     */
    class ExternalModuleProcessorInterface : public virtual ObjectInterface {
    public:
        virtual void OnRegistered() = 0;
        virtual std::shared_ptr<Event> Process(const std::shared_ptr<Event>& event) = 0;
        virtual void OnUnregistered() = 0;
    };

} // AdobeMarketingMobile namespace

#endif /* ADOBEMOBILE_EXTERNALMODULE_EXTERNALMODULEPROCESSORINTERFACE_H */
