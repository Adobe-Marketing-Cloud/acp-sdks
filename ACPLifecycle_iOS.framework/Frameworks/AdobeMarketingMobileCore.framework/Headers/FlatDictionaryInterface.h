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

#ifndef ADOBEMOBILE_RULESENGINE_FLATDICTIONARY_H
#define ADOBEMOBILE_RULESENGINE_FLATDICTIONARY_H

#include <string>
#include "ObjectInterface.h"

namespace AdobeMarketingMobile {
    /**
     * @class FlatDictionary
     *
     * Interface used for redefining complex objects as map of {string, variants}
     */
    class FlatDictionaryInterface : public virtual ObjectInterface {
    public:
        /**
         * Returns the internal state of the class in a flat KV map.
         * The key is of string type, namespaced with periods if required,
         * and the value is a Variant, with no nesting.
         *
         * @param out the flattened dictionary result
         * @return true if a flat dictionary was correctly set to out, false if the operation failed.
         */
        virtual bool GetFlatDictionary(std::map<std::string, std::shared_ptr<Variant>>& out) const = 0;
    };
} //namespace


#endif /* ADOBEMOBILE_RULESENGINE_FLATDICTIONARY_H */
