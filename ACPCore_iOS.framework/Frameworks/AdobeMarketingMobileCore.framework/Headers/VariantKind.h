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
