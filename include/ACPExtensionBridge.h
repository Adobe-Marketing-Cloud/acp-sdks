/* ************************************************************************
 * ADOBE CONFIDENTIAL
 * ___________________
 *
 * Copyright 2018 Adobe
 * All Rights Reserved.
 *
 * NOTICE: All information contained herein is, and remains
 * the property of Adobe and its suppliers, if any. The intellectual
 * and technical concepts contained herein are proprietary to Adobe
 * and its suppliers and are protected by all applicable intellectual
 * property laws, including trade secret and copyright laws.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Adobe.
 **************************************************************************/

#ifndef ADOBEMOBILE_EXTERNALMODULEBRIDGE_H
#define ADOBEMOBILE_EXTERNALMODULEBRIDGE_H

#import "AdobeMarketingMobileCore.h"
#import "ACPExtensionApi.h"
#import "ACPExtensionListener.h"

/**
 * @brief This header contains shared methods used for bridging extension code between C++ and Obj-C.
 */
namespace AdobeMarketingMobile {

    /**
     * @brief Private methods implemented in Objective-C layer
     */

    std::shared_ptr<Event> GetEventFromACPExtensionEvent(ACPExtensionEvent* event);
    ACPExtensionError GetACPExtensionErrorFromErrorCodes(const std::string& internal_error);

    /**
     * @brief Wrapper creation methods implemented in Objective-C layer
     */

    std::shared_ptr<ExternalModuleListenerInterface> CreateExternalModuleListenerInterface(ACPExtension* extension,
            Class listener_class);
    std::shared_ptr<ExternalModuleInterface> CreateExternalModuleInterface(Class extension_class);
    id CreateACPExtensionEventFromEvent(const std::shared_ptr<Event>& event);
    id CreateACPExtensionApiFromExternalModuleServicesInterface(ACPExtension* extension,
            const std::shared_ptr<ExternalModuleServicesInterface>& services);

} // AdobeMarketingMobile namespace

#endif /* ADOBEMOBILE_EXTERNALMODULEBRIDGE_H */
