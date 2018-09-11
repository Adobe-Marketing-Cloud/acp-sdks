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

#ifndef ADOBEMOBILE_PLATFORMSHIM_PERIPHERALSERVICEINTERFACE_H
#define ADOBEMOBILE_PLATFORMSHIM_PERIPHERALSERVICEINTERFACE_H
/**
 * Peripheral Service (callback) Interface definition in C++
 * This defined a callback interface for the peripheral services
**/
namespace AdobeMarketingMobile {
    class PeripheralServiceInterface: public virtual ObjectInterface {

        //    public:
        //        enum class PeripheralType : int {
        //            BLUETOOTH,
        //        };
        //        // callback function
        //        virtual int cbCallbackFunction(int) = 0;
    };
} //namespace
#endif /* ADOBEMOBILE_PLATFORMSHIM_PERIPHERALSERVICEINTERFACE_H */
