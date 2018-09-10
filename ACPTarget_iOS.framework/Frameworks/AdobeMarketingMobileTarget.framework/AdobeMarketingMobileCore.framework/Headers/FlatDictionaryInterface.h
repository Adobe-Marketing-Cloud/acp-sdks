/****************************************************************************
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

#ifndef ADOBEMOBILE_SHARED_FLATDICTIONARYINTERFACE_H
#define ADOBEMOBILE_SHARED_FLATDICTIONARYINTERFACE_H

#include <string>
#include <map>

#include "ObjectInterface.h"
#include "Variant.h"

namespace AdobeMarketingMobile {

    class FlatDictionaryInterface : public virtual ObjectInterface {

    public:
        /**
         * Extracts the data of the implementation class in a map of strings
         *
         * @return flattened dictionary
         */
        virtual std::map<std::string, std::shared_ptr<Variant>> GetFlatDictionary() const = 0;

    };

}

#endif /* ADOBEMOBILE_SHARED_FLATDICTIONARYINTERFACE_H */
