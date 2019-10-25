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

#ifndef ADOBEMOBILE_CORE_VARIANTSERIALIZERINTERFACE_H
#define ADOBEMOBILE_CORE_VARIANTSERIALIZERINTERFACE_H

#include "ObjectInterface.h"

/**
 * @brief Derive from VariantSerializerInterface for serializing class instances to and/from Variant
 * For each class you would like to use with the Variant::*Typed* methods,
 *  you will need to implement a template specialization. An example is provided.
 *
 * NOTE: You should *not* use this template directly for serialization - use FromTypedObject et al instead.
 *
 * Reqs:
 *  Must be feasible to implement for types we cannot change, so we can't rely on adding methods to the type
 *  Must return StdError when Variant cannot be converted to the type specified
 *
 * Questions:
 *  If Variant has extra data irrelevant to type serialization, is that ok? Assume YES
 *  If we want to have multiple serializers, what should we do? We will add another template param
 *
 * Example implementation:
 *
 * class MyObject {
 * public:
 *  const std::string& GetStrMember() { return str_member; }
 *  int GetIntMember() { return int_member; }
 * private:
 *  std::string str_member;
 *  int         int_member;
 * };
 *
 * class MyObjectSerializer : public Object, public virtual VariantSerializerInterface<MyObject> const {
 * public:
 *  Expected<std::shared_ptr<MyObject>> Deserialize(const Variant& value) {
 *      std::map<std::string, std::shared_ptr<Variant>> variant_map;
 *      if(value.GetVariantMap(variant_map)) {
 *          std::string str_member;
 *          if(variant_map("str_member") == variant_map() || !variant_map["str_member"]->GetString(str_member)) {
 *              return { SdkError(ErrorCodes::VARIANT_NOT_TYPE, "type error") };
 *          }
 *          int int_member;
 *          if(variant_map("int_member") == variant_map() || !variant_map["int_member"]->GetString(int_member)) {
 *              return { SdkError(ErrorCodes::VARIANT_NOT_TYPE, "type error") };
 *          }
 *          return { std::make_shared<MyObject>({ str_member, int_member }) };
 *      }
 *      return { SdkError(ErrorCodes::VARIANT_NOT_TYPE, "type error") };
 *  }
 *
 *  std::shared_ptr<Variant> Serialize(const MyObject& o) const {
 *      std::map<std::string, std::shared_ptr<Variant>> variant_value;
 *      variant_value.insert({ "str_member", Variant::FromString(o.GetStrMember()) });
 *      variant_value.insert({ "int_member", Variant::FromInt(o.GetIntMember()) });
 *      return Variant::FromVariantMap(variant_value);
 *  }
 *
 * };
 *
 */
namespace AdobeMarketingMobile {
    class Variant;

    template<class TObject>
    class VariantSerializerInterface : public virtual ObjectInterface {
    public:
        /* @brief Create a TObject from a Variant
         * Implementations must handle when Variant is not a serialized TObject e.g. return error or nullptr as needed.
         * @return TObject or SdkError
         */
        virtual Expected<std::shared_ptr<TObject>> Deserialize(const Variant& variant) const = 0;

        /* @brief Create a Variant from a TObject instance
         * @return heap allocated Variant
         */
        virtual std::shared_ptr<Variant> Serialize(const TObject& object) const = 0;
    };
} // namespace AdobeMarketingMobile
#endif /* ADOBEMOBILE_CORE_VARIANTSERIALIZERINTERFACE_H */
