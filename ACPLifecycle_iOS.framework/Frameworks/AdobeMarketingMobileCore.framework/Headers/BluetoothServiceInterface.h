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
 **************************************************************************/

#ifndef ADOBEMOBILE_PLATFORMSHIM_BLUETOOTHSERVICEINTERFACE_H
#define ADOBEMOBILE_PLATFORMSHIM_BLUETOOTHSERVICEINTERFACE_H

#include <string>
#include "NetworkServiceInterface.h"
#include "PeripheralServiceInterface.h"

namespace AdobeMarketingMobile {
    class BluetoothServiceInterface: public virtual ObjectInterface, public virtual PeripheralServiceInterface {
    public:
        virtual void StartScan() = 0;

        virtual void StopScan() = 0;

        virtual void RegisterForDevice(const std::string& identifier, const std::function<void()>& resultCallback) = 0;
    };
}
#endif /* ADOBEMOBILE_PLATFORMSHIM_BLUETOOTHSERVICEINTERFACE_H */
