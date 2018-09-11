/* **************************************************************************
 *
 * ADOBE CONFIDENTIAL
 * ___________________
 *
 * Copyright 2018 Adobe Systems Incorporated
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

#ifndef ADOBEMOBILE_PLATFORMSHIM_JSONARRAYSERIALIZER_H
#define ADOBEMOBILE_PLATFORMSHIM_JSONARRAYSERIALIZER_H

#include <memory>
#include <vector>
#include "Expected.h"
#include "SdkError.h"
#include "Variant.h"

namespace AdobeMarketingMobile {
    class JsonArray;
    class JsonUtilityServiceInterface;
    /**
     * @brief Serializer for JsonArray objects
     */
    class JsonArraySerializer : public Object, public virtual VariantSerializerInterface<JsonArray> {
    public:
        explicit JsonArraySerializer(const std::shared_ptr<JsonUtilityServiceInterface>& json_utility_service);

        Expected<std::shared_ptr<JsonArray>> Deserialize(const Variant& value) const override;

        std::shared_ptr<Variant> Serialize(const JsonArray& o) const override;
    private:
        std::shared_ptr<JsonUtilityServiceInterface> json_utility_service_;
    };
} // namespace
#endif /* ADOBEMOBILE_PLATFORMSHIM_JSONARRAYSERIALIZER_H */
