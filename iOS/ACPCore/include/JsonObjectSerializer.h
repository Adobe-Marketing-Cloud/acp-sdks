/*
Copyright 2018 Adobe. All rights reserved.
This file is licensed to you under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License. You may obtain a copy
of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS
OF ANY KIND, either express or implied. See the License for the specific language
governing permissions and limitations under the License.
*/

#ifndef ADOBEMOBILE_PLATFORMSHIM_JSONOBJECTSERIALIZER_H
#define ADOBEMOBILE_PLATFORMSHIM_JSONOBJECTSERIALIZER_H

#include <memory>
#include <vector>
#include "Expected.h"
#include "SdkError.h"
#include "Variant.h"

namespace AdobeMarketingMobile {

    class JsonObject;
    class JsonUtilityServiceInterface;
    /**
     * @brief Serializer for JsonObject objects
     */
    class JsonObjectSerializer : public Object, public virtual VariantSerializerInterface<JsonObject> {
    public:
        explicit JsonObjectSerializer(const std::shared_ptr<JsonUtilityServiceInterface>& json_utility_service);

        Expected<std::shared_ptr<JsonObject>> Deserialize(const Variant& value) const override;

        std::shared_ptr<Variant> Serialize(const JsonObject& o) const override;
    private:
        std::shared_ptr<JsonUtilityServiceInterface> json_utility_service_;
    };
} // namespace
#endif /* ADOBEMOBILE_PLATFORMSHIM_JSONOBJECTSERIALIZER_H */

