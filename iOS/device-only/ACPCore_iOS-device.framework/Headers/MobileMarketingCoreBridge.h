//
//  MobileMarketingCoreBridge.h
//  Adobe Experience Platform -- iOS Framework
//
//  Copyright 1996-2018. Adobe. All Rights Reserved

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
