/*
Copyright 2017 Adobe. All rights reserved.
This file is licensed to you under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License. You may obtain a copy
of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS
OF ANY KIND, either express or implied. See the License for the specific language
governing permissions and limitations under the License.
*/

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
