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

#ifndef ADOBEMOBILE_EXTERNALMODULE_EXTERNALMODULELISTENERINTERFACE_H
#define ADOBEMOBILE_EXTERNALMODULE_EXTERNALMODULELISTENERINTERFACE_H

#include "Object.h"
#include "Event.h"

namespace AdobeMarketingMobile {

    /**
     * @brief Wrapper used to call the ADBModuleListenerInterface provided by the external module
     *
     */
    class ExternalModuleListenerInterface : public virtual ObjectInterface {
    public:
        virtual void OnRegistered() = 0;
        virtual void Hear(const std::shared_ptr<Event>& event) = 0;
        virtual void OnUnregistered() = 0;
    };

} // AdobeMarketingMobile namespace

#endif /* ADOBEMOBILE_EXTERNALMODULE_EXTERNALMODULELISTENERINTERFACE_H */
