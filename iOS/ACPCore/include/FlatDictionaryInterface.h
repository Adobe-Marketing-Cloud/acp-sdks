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
