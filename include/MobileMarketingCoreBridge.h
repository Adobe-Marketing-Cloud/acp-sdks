//
//  MobileMarketingCoreBridge.h
//  Adobe Experience Platform -- iOS Framework
//
//  Copyright 1996-2018. Adobe. All Rights Reserved
#ifndef ADOBEMOBILE_CORE_MOBILEMARKETINGCOREBRIDGE_H
#define ADOBEMOBILE_CORE_MOBILEMARKETINGCOREBRIDGE_H

#include "AdobeMarketingMobileCore.h"

namespace AdobeMarketingMobile {
    class Core;
    class PlatformServicesInterface;
    class SharedPlatformServicesInterface;

    class MobileMarketingCoreBridge : public Object {
    public:
        /**
         * @deprecated
         * This method can cause shutdown-related crashes. Use `GetInstance2()` instead.
         *
         * @return the bridge singleton.
         */
        ADOBE_DEPRECATED(static MobileMarketingCoreBridge* GetInstance());

        /**
         * @return the bridge singleton.
         */
        static std::shared_ptr<MobileMarketingCoreBridge> GetInstance2();

        /**
         * @return the bridge's core object
         */
        std::shared_ptr<Core> GetCore();

        /**
         * @return a platform services instance unique to the bridge.
         */
        std::shared_ptr<PlatformServicesInterface> GetPlatformServices();

        /**
         * @brief Cleans up after the current MobileMarketingCoreBridge instance.
         */
        static void ResetInstance();

    protected:
        static std::shared_ptr<MobileMarketingCoreBridge> Create();

        /**
         *  @brief Factory method for creating native SharedPlatformServicesInterface
         */
        static std::shared_ptr<SharedPlatformServicesInterface> CreateNativeSharedPlatformServices();

    private:
        MobileMarketingCoreBridge();

        std::shared_ptr<Core> core_object_;

        std::shared_ptr<SharedPlatformServicesInterface> shared_platform_services_;

        std::shared_ptr<PlatformServicesInterface> platform_services_; /// a platform services instance specific to this
    };
}

#endif

