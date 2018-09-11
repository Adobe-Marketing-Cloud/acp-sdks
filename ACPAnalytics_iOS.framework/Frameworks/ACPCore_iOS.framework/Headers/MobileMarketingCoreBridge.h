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
 ****************************************************************************/

#include <AdobeMarketingMobileCore/AdobeMarketingMobileCore.h>

namespace AdobeMarketingMobile {
    class Core;
    class PlatformServicesInterface;

    class MobileMarketingCoreBridge : public Object {

    public:
        static MobileMarketingCoreBridge* GetInstance();
        std::shared_ptr<Core> GetCore();
        static void ResetInstance();

    private:
        MobileMarketingCoreBridge();

        static MobileMarketingCoreBridge* instance_;
        std::shared_ptr<Core> core_object_;
        std::shared_ptr<PlatformServicesInterface> platform_services_;
    };
}
