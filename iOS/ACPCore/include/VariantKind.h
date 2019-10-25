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

#ifndef ADOBEMOBILE_CORE_VARIANTKIND_H
#define ADOBEMOBILE_CORE_VARIANTKIND_H

#include "StringUtils.h"

namespace AdobeMarketingMobile {

    /**
     * VariantKind indicates type of value that a variant contains. See Variant.
     */
    enum class VariantKind : int32_t {

        VARIANT_NULL,       ///< The variant contains no values

        STRING,     ///< The variant contains a std::string

        INTEGER,    ///< The variant contains an int32_t

        LONG,       ///< The variant contains an int64_t

        DOUBLE,     ///< The variant contains a double

        BOOLEAN,    ///<  The variant contains a bool

        VARIANT_VECTOR,     ///< The variant contains a std::vector<std::shared_ptr<Variant>>

        VARIANT_MAP,     ///< The variant contains a std::map<std::string, std::shared_ptr<Variant>>

    };

    /**
     * @see StringUtils::ToString()
     */
    void ToStringImpl(std::ostream& the_stream, VariantKind value, const ToStringOptions& options);
}

#endif //ADOBEMOBILE_CORE_VARIANTKIND_H
