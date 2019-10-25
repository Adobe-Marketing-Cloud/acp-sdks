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

#ifndef ADOBEMOBILE_CORE_VARIANT_H
#define ADOBEMOBILE_CORE_VARIANT_H

#include <map>
#include <vector>
#include "Object.h"
#include "Expected.h"
#include "VariantSerializerInterface.h"
#include "Common.h"

namespace AdobeMarketingMobile {
    enum class VariantKind : int32_t;

    /**
     * @class Variant
     *
     * A variant is an Object that can contain different types of data. A variant can contain
     * one of the following:
     *   - a std::string
     *   - an int32_t (referred to as an Integer)
     *   - an int64_t (referred to as a Long)
     *   - a bool
     *   - a std::map<std::string, std::shared_ptr<Variant>> (referred to as a Map or VariantMap)
     *   - a std::vector<std::shared_ptr<Variant>> (referred to as a Vector or VariantVector)
     *   - null
     *
     * CONSTRUCTING A VARIANT
     * ----------------------
     * Variant::FromXyz(...) functions can be used to construct a variant:
     *
     *    std::shared_ptr<Variant> v = Variant::FromInteger(123); // constructs a variant that contains 123
     *
     * INSPECTING A VARIANT
     * --------------------
     * Variant::GetKind(...) and Variant::GetXyz(...) can be used to get the value of a variant:
     *
     * Example:
     *
     *    std::shared_ptr<Variant> v = Variant::FromLong(123L); // constructs a variant that contains 123L
     *    v->GetKind(); // returns VariantKind::LONG
     *    int64_t aLong;
     *    v->GetLong(aLong); // returns true and sets aLong to 123L
     *    std::shared_ptr<Object> anObject;
     *    v->GetObject(anObject); // returns false
     *
     * Variant::GetXyz(...) will not perform any type conversions. For example, if an int32_t is stored in a
     * variant, calling GetLong(...) will not convert the int32_t to an int62_t.
     *
     * STORING VARIANTS IN A COLLECTION
     * --------------------------------
     * The primary use of variants is to store different types of data in a single collection:
     *
     * Example:
     *
     *    std::vector<std::shared_ptr<Variant>> aVector;
     *    aVector.push(Variant::FromString("hello"));
     *    aVector.push(Variant::FromInteger(123));
     *    aVector.push(Variant::FromObject(std::make_shared<Object>()));
     *
     * LIMITS ON VARIANT VALUES
     * --------------------------------
     * Because JSON is widely exchanged and processed on a wide range of platforms, it is practical to look at common
     * limitations to avoid overflow issues. Most JSON parser implementations use a double for holding all numeric
     * types. This leads to a range of [-(2**53)+1, (2**53)-1] for integers, since only that range can be accurately
     * represented in a double.
     * More discussion in
     *   RFC-7159: https://tools.ietf.org/html/rfc7159#section-6
     *   ECMA-262: https://tc39.github.io/ecma262/#sec-number.min_safe_integer
     */
    class Variant : public Object {
    public:
        static const int64_t MAX_SAFE_INTEGER = 9007199254740991;
        static const int64_t MIN_SAFE_INTEGER = -9007199254740991;

        // returns a new variant with no value
        static std::shared_ptr<Variant> FromNull();

        /**
         * @return a new variant with the given string as its value.
         * Objects will be stored by reference.
         */
        static std::shared_ptr<Variant> FromString(const std::string& value);

        /**
         * @return a new variant with the given int32 as its value.
         * Objects will be stored by reference.
         */
        static std::shared_ptr<Variant> FromInteger(int32_t value);

        /**
         * @return a new variant with the given int64 as its value.
         * Objects will be stored by reference.
         */
        static std::shared_ptr<Variant> FromLong(int64_t value);

        /**
         * @return a new variant with the given double as its value.
         * Objects will be stored by reference.
         */
        static std::shared_ptr<Variant> FromDouble(double value);

        /**
         * @return a new variant with the given bool as its value.
         * Objects will be stored by reference.
         */
        static std::shared_ptr<Variant> FromBoolean(bool value);

        /**
         * @return a new variant with the given map as its value.
         * Objects will be stored by reference.
         */
        static std::shared_ptr<Variant> FromVariantVector(const std::vector<std::shared_ptr<Variant>>& value);

        /**
         * @return a new variant with the given string map as its value.
         * Objects will be stored by reference.
         *
         * @note The variant will contain a COPY of the given string map.
         */
        static std::shared_ptr<Variant> FromStringMap(const std::map<std::string, std::string>& out_value);

        /**
         * @return a new variant with the given string vector as its value.
         * Objects will be stored by reference.
         *
         * @note The variant will contain a COPY of the given string map.
         */
        static std::shared_ptr<Variant> FromStringVector(const std::vector<std::string>& value);

        /**
         * @return a new variant with the given variant map as its value.
         * Objects will be stored by reference.
         *
         * @note The variant will contain a COPY of the given string map.
         */
        static std::shared_ptr<Variant> FromVariantMap(const std::map<std::string, std::shared_ptr<Variant>>& out_value);

        // returns a new variant whose value is serialized from the given typed object
        // NOTE: The variant will contain a COPY of the given object.
        template<class TObject>
        static std::shared_ptr<Variant> FromTypedObject(const TObject* val);

        // returns a new variant whose value is serialized from a vector of the given typed object and serializer
        // NOTE: The variant will contain a COPY of the given vector.
        template<class TObject>
        static std::shared_ptr<Variant> FromTypedObject(const TObject* val,
                const std::shared_ptr<VariantSerializerInterface<TObject>>& s);

        // returns a new variant whose value is serialized from a vector of the given typed object
        // NOTE: The variant will contain a COPY of the given vector.
        template<class TObject>
        static std::shared_ptr<Variant> FromTypedVector(const std::vector<std::shared_ptr<TObject>>& val);

        // returns a new variant whose value is serialized from a vector of the given typed object and serializer
        // NOTE: The variant will contain a COPY of the given vector.
        template<class TObject>
        static std::shared_ptr<Variant> FromTypedVector(const std::vector<std::shared_ptr<TObject>>& val,
                const std::shared_ptr<VariantSerializerInterface<TObject>>& s);

        // returns a new variant whose value is serialized from a map of the given typed object
        // NOTE: The variant will contain a COPY of the given map.
        template<class TObject>
        static std::shared_ptr<Variant> FromTypedMap(const std::map<std::string, std::shared_ptr<TObject>>& val);

        // returns a new variant whose value is serialized from a map of the given typed object and serializer
        // NOTE: The variant will contain a COPY of the given map.
        template<class TObject>
        static std::shared_ptr<Variant> FromTypedMap(const std::map<std::string, std::shared_ptr<TObject>>& val,
                const std::shared_ptr<VariantSerializerInterface<TObject>>& s);

        /**
         * @return true if variant is of INTEGER/LONG/DOUBLE kind
         * @param kind - VariantKind
         */
        static bool IsNumericKind(const VariantKind& kind);

        /**
         * @return the kind of value that this variant stores
         * @return VariantKind - the kind of variant
         */
        virtual VariantKind GetKind() const = 0;

        /**
         * @return if this' value is a string, returns true and sets \p out_value to the variant's value.
         * Otherwise, returns false.
         */
        virtual bool GetString(std::string& out_value) const;

        /**
         * @return if this' value is an integer, returns true and sets \p out_value to the variant's value.
         * Otherwise, returns false.
         */
        virtual bool GetInteger(int32_t& out_value) const;

        /**
         * @return if this' value is a long, returns true and sets \p out_value to the variant's value.
         * Otherwise, returns false.
         */
        virtual bool GetLong(int64_t& out_value) const;

        /**
         * @return if this' value is a double, returns true and sets \p out_value to the variant's value.
         * Otherwise, returns false.
         */
        virtual bool GetDouble(double& out_value) const;

        /**
         * @return if this' value is a boolean, returns true and sets \p out_value to the variant's value.
         * Otherwise, returns false.
         */
        virtual bool GetBoolean(bool& out_value) const;

        /**
         * @return if this' value is a variant vector, returns true and sets \p out_value to the variant's value.
         * Otherwise, returns false.
         *
         * @note This function will COPY the stored map.
         */
        virtual bool GetVariantVector(std::vector<std::shared_ptr<Variant>>& out_value) const;

        /**
         * @return if this' value is a string map, returns true and sets \p out_value to the variant's value.
         * Otherwise, returns false.
         *
         * @note This function will COPY the stored map.
         */
        bool GetStringMap(std::map<std::string, std::string>& out_value) const;

        // if this' value is a variant map, returns true and sets out_value to the variant's value.
        // otherwise, returns false.
        //
        // NOTE: This function will COPY the stored map.
        virtual bool GetVariantMap(std::map<std::string, std::shared_ptr<Variant>>& out_value) const;

        // if typed object can be created from value, return typed object. Else return StdError.
        template<class TObject>
        Expected<std::shared_ptr<TObject>> GetTypedObject() const;

        // if typed object can be created from value and given serializer, return typed object. Else return StdError.
        template<class TObject>
        Expected<std::shared_ptr<TObject>> GetTypedObject(const std::shared_ptr<VariantSerializerInterface<TObject>>& s) const;

        // if vector of typed object can be created from value, return vector of typed object. Else return StdError.
        // NOTE: This function will COPY the stored vector.
        template<class TObject>
        Expected<std::vector<std::shared_ptr<TObject>>> GetTypedVector() const;

        // if vector of typed object can be created from value and given serializer, return vector of typed object. Else return StdError.
        // NOTE: This function will COPY the stored vector.
        template<class TObject>
        Expected<std::vector<std::shared_ptr<TObject>>> GetTypedVector(const
                std::shared_ptr<VariantSerializerInterface<TObject>>& s) const;

        /**
         * @return if map of typed object can be created from value, return map of typed object. Else return StdError.
         *
         * @note This function will COPY the stored map.
         */
        template<class TObject>
        Expected<std::map<std::string, std::shared_ptr<TObject>>> GetTypedMap() const;


        /**
         * @return if map of typed object can be created from value and given serializer, return map of typed object. Else return StdError.
         *
         * @note This function will COPY the stored map.
         */
        template<class TObject>
        Expected<std::map<std::string, std::shared_ptr<TObject>>> GetTypedMap(const
                std::shared_ptr<VariantSerializerInterface<TObject>>& s) const;
        /**
         * @return a copy of this. If this' value is an object, the new variant's value will refer
         * to the same object as the old variant. Otherwise, the new variant's value will be a copy
         * of the old variant's value.
         */
        virtual std::shared_ptr<Variant> Copy() const = 0;

        // Equals is implemented by subclasses.
        // Two variants are equal if all of the following are true:
        // - They are both Variants
        // - They are both the same kind
        // - If both values are an object, the values are Equal
        // - If both values are not an object, the values are ==
        // bool Equals(const ObjectInterface& right) const override final;

        /**
         * @see ObjectInterface::ToStringImpl()
         */
        std::string ToStringImpl(const ToStringOptions& options) const override;

        /**
         * @return if this' value is a string or numeric type that can be converted to double, returns true and
         * sets \p out_value to the converted double value.
         * Otherwise, returns false.
         */
        virtual bool ConvertToDouble(double& out_value) const;

        /**
         * @return if this' value is a numeric type that can be converted to string, returns true and
         * sets \p out_value to the converted string value.
         * Otherwise, returns false.
         */
        virtual bool ConvertToString(std::string& out_value) const;

    protected:
        // Internal use only
        Variant() {};
    };



    /////////////////////////////////
    // template/inline definitions //
    /////////////////////////////////

    // Error codes specific to Variants
    namespace ErrorCodes {
        constexpr static const char* VARIANT_NOT_TYPE = "variant.not_type"; ///< Variant does not contain requested type
        constexpr static const char* VARIANT_NOT_VECTOR = "variant.not_vector"; ///< Variant does not contain a vector
        constexpr static const char* VARIANT_NOT_MAP = "variant.not_map"; ///< Variant does not contain a map
    }

    template<class TObject>
    struct GetDefaultSerializer {
        using type = typename TObject::Serializer;
    };

    template<typename TObject>
    using Serializer = typename GetDefaultSerializer<TObject>::type;

    template<class TObject>
    std::shared_ptr<Variant> Variant::FromTypedObject(const TObject* objptr) {
        return Variant::FromTypedObject<TObject>(objptr, std::make_shared<Serializer<TObject>>());
    }

    template<class TObject>
    std::shared_ptr<Variant> Variant::FromTypedObject(const TObject* objptr,
            const std::shared_ptr<VariantSerializerInterface<TObject>>& s) {
        if (objptr == nullptr) {
            return Variant::FromNull();
        }

        return s->Serialize(*objptr);
    }

    template<class TObject>
    std::shared_ptr<Variant> Variant::FromTypedVector(const std::vector<std::shared_ptr<TObject>>& typed_vector) {
        return Variant::FromTypedVector<TObject>(typed_vector, std::make_shared<Serializer<TObject>>());
    }

    template<class TObject>
    std::shared_ptr<Variant> Variant::FromTypedVector(const std::vector<std::shared_ptr<TObject>>& typed_vector,
            const std::shared_ptr<VariantSerializerInterface<TObject>>& s) {
        std::vector<std::shared_ptr<Variant>> variant_vector;

        for (auto& item : typed_vector) {
            variant_vector.push_back(FromTypedObject(item.get(), s));
        }

        return Variant::FromVariantVector(variant_vector);
    }

    template<class TObject>
    std::shared_ptr<Variant> Variant::FromTypedMap(const std::map<std::string, std::shared_ptr<TObject>>& typed_map) {
        return Variant::FromTypedMap<TObject>(typed_map, std::make_shared<Serializer<TObject>>());
    }

    template<class TObject>
    std::shared_ptr<Variant> Variant::FromTypedMap(const std::map<std::string, std::shared_ptr<TObject>>& typed_map,
            const std::shared_ptr<VariantSerializerInterface<TObject>>& s) {
        std::map<std::string, std::shared_ptr<Variant>> variant_map;

        for (auto& item : typed_map) {
            variant_map.insert({ item.first, FromTypedObject(item.second.get(), s) });
        }

        return Variant::FromVariantMap(variant_map);
    }

    template<class TObject>
    Expected<std::shared_ptr<TObject>> Variant::GetTypedObject() const {
        return GetTypedObject<TObject>(std::make_shared<Serializer<TObject>>());
    }

    template<class TObject>
    Expected<std::shared_ptr<TObject>> Variant::GetTypedObject(const std::shared_ptr<VariantSerializerInterface<TObject>>&
    s) const {
        return s->Deserialize(*this);
    }

    template<class TObject>
    Expected<std::vector<std::shared_ptr<TObject>>> Variant::GetTypedVector() const {
        return GetTypedVector<TObject>(std::make_shared<Serializer<TObject>>());
    }

    template<class TObject>
    Expected<std::vector<std::shared_ptr<TObject>>> Variant::GetTypedVector(const
            std::shared_ptr<VariantSerializerInterface<TObject>>& s) const {
        std::vector<std::shared_ptr<Variant>> variant_vector;

        if (GetVariantVector(variant_vector)) {
            std::vector<std::shared_ptr<TObject>> typed_vector;

            for (auto& variant : variant_vector) {
                Expected<std::shared_ptr<TObject>> typed_object = variant->GetTypedObject<TObject>(s);

                if (typed_object) {
                    typed_vector.push_back(typed_object.Value());
                } else {
                    return { typed_object.Error() };
                }
            }

            return { typed_vector };
        }

        return { SdkError(ErrorCodes::VARIANT_NOT_VECTOR, "type conversion error") };
    }

    template<class TObject>
    Expected<std::map<std::string, std::shared_ptr<TObject>>> Variant::GetTypedMap() const {
        return GetTypedMap<TObject>(std::make_shared<Serializer<TObject>>());
    }

    template<class TObject>
    Expected<std::map<std::string, std::shared_ptr<TObject>>> Variant::GetTypedMap(const
            std::shared_ptr<VariantSerializerInterface<TObject>>& s) const {
        std::map<std::string, std::shared_ptr<Variant>> variant_map;

        if (GetVariantMap(variant_map)) {
            std::map<std::string, std::shared_ptr<TObject>> typed_map;

            for (auto& iter : variant_map) {
                Expected<std::shared_ptr<TObject>> typed_object = (iter.second)->GetTypedObject<TObject>(s);

                if (typed_object) {
                    typed_map.insert({ iter.first, typed_object.Value() });
                } else {
                    return { typed_object.Error() };
                }
            }

            return { typed_map };
        }

        return { SdkError(ErrorCodes::VARIANT_NOT_MAP, "type conversion error") };
    }

}

#endif //ADOBEMOBILE_CORE_VARIANT_H
