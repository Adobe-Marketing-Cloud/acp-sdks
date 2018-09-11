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

#ifndef ADOBEMOBILE_EXTERNALMODULE_EXTERNALMODULEINTERFACE_H
#define ADOBEMOBILE_EXTERNALMODULE_EXTERNALMODULEINTERFACE_H

#include "Object.h"
#include "ExternalModuleServicesInterface.h"

namespace AdobeMarketingMobile {

    /**
     * @brief Interface providing access to ADBModule for the event hub.
     *
     */
    class ExternalModuleInterface : public virtual ObjectInterface {
    public:
        virtual std::string GetModuleName() = 0;
        virtual std::string GetModuleVersion() = 0;
        virtual void OnRegister(const std::shared_ptr<ExternalModuleServicesInterface>& services) = 0;
        virtual void OnUnexpectedError(SdkError& e) = 0;
        virtual void OnUnregister() = 0;
    };

} // AdobeMarketingMobile namespace

#endif /* ADOBEMOBILE_EXTERNALMODULE_EXTERNALMODULEINTERFACE_H */
