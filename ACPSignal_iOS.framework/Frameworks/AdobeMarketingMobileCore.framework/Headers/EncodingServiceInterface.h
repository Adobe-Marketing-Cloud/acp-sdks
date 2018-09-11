/***************************************************************************
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

#ifndef ADOBEMOBILE_PLATFORMSHIM_ENCODINGSERVICEINTERFACE_H
#define ADOBEMOBILE_PLATFORMSHIM_ENCODINGSERVICEINTERFACE_H

#include "ObjectInterface.h"

namespace AdobeMarketingMobile {
    class EncodingServiceInterface : public virtual ObjectInterface {
    public:
        virtual std::string Base64Decode(const std::string& encoded_string) const = 0;
    };
}

#endif /* ADOBEMOBILE_PLATFORMSHIM_ENCODINGSERVICEINTERFACE_H */
