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

#ifndef ADOBEMOBILE_CORE_EVENTDATA_H
#define ADOBEMOBILE_CORE_EVENTDATA_H

#include <map>
#include <string>
#include <vector>
#include "Expected.h"
#include "Object.h"
#include "Variant.h"

namespace AdobeMarketingMobile {
    enum class VariantKind : int32_t;


    /**
     * @class EventData
     *
     * @brief EventData is data that can be included with events or shared states.
     *
     * At the top-level, EventData is a map of `string` keys to `Variant` values.
     *
     * @note When making changes to the interface/implementation of EventData, any information stored in EventData
     * MUST be convertible to JSON. If it can't be expressed as JSON, it shouldn't be stored in EventData.
     *
     * Constructing an EventData
     * -------------------------
     * To construct an empty EventData, use `std::make_shared`:
     *
     *     auto event_data = std::make_shared<EventData>();
     *
     * Adding key-value pairs to an EventData
     * --------------------------------------
     * The `Put` methods can be used to add/modify EventData key-value pairs:
     *
     *     auto event_data = std::make_shared<EventData>();
     *     event_data->PutString("a string", "some value");
     *     event_data->PutInteger("a number", 42);
     *
     * EventData supports storing any values that Variant supports.
     *
     * Inspecting EventData
     * --------------------
     * The `Get` methods can be used to retrieve key-value pairs:
     *
     *     std::string value;
     *     if (event_data->GetString("a string", value)) {
     *       // the value associated with "a string" will be put into value
     *     } else {
     *       // event_data does not contain "a string" or it is not convertible to std::string
     *     }
     *
     * The `Opt` methods retrieve key-value pairs, returning a default value if the key was not found:
     *
     *     auto value = event_data->OptString("a string", "value if missing");
     *
     * Additonal methods such as EventData::ContainsKey(), EventData::IsEmpty(), EventData::Size(),
     * EventData::GetKind() allow inspection of the underlying map.
     *
     * Cloning an EventData
     * --------------------
     * EventData::Copy() can be used to (deep) clone an EventData instance:
     *
     *     auto event_data_1 = std::make_shared<EventData>();
     *     event_data_1.PutString("flavor", "sour");
     *     event_data_1.PutString("color, "blue");
     *
     *     auto event_data_2 = event_data_1->Copy();
     *     event_data_2.PutString("color", "green");
     *
     *     // event_data_1 contains { "flavor" : "sour", "color" : "blue" }
     *     // event_data_2 contains { "flavor" : "sour", "color" : "green" }
     *
     * Converting an EventData to/from std::map
     * ----------------------------------------
     * Constructors exist to construct EventData from `std::map<std::string, std::string>` and
     * `std::map<std::string, std::shared_ptr<Variant>>`.
     *
     * EventData::AsMapCopy() or can be used to (deep) copy the EventData contents into a map.
     *
     */
    class EventData : public Object {
    public:
        /**
         * @brief Constructs an empty EventData
         */
        EventData();

        /**
         * @brief Constructs an EventData with the given key-value pairs
         */
        explicit EventData(const std::map<std::string, std::shared_ptr<Variant>>& map);

        /**
         * @brief Constructs an EventData with the given key-value pairs
         */
        explicit EventData(const std::map<std::string, std::string>& map);

        /**
         * @brief Deep copies this
         * @returns a deep copy of this
         */
        std::shared_ptr<EventData> Copy() const;

        /**
         * @brief Copies this to a `std::map`
         * @returns a copy of this, as a `std::map`
         */
        std::map<std::string, std::shared_ptr<Variant>> AsMapCopy() const;

        /**
         * @brief Checks if the EventData contains the given key
         * @returns true iff the EventData contains the given key
         */
        bool ContainsKey(const std::string& key);

        /**
         * @brief Checks if the EventData contains no keys
         * @returns true iff there EventData contains no keys
         */
        bool IsEmpty() const;

        /**
         * @brief Gets the number of key-value pairs in this
         * @returns the number of key-value pairs in this
         */
        size_t Size() const;

        /**
         * @brief Gets the kind of value for a given key
         * @returns the kind of value that the specific key of EventData holds. EVENT_DATA_NO_SUCH_KEY if no such key.
         */
        Expected<VariantKind> GetKind(const std::string& key) const;

        /**
         * @brief Sets the value for key to a copy of the given string.
         *
         * Equivalent to:
         *
         *     return this->PutVariant(Variant::FromString(value));
         *
         * @returns `*this`
         */
        EventData& PutString(const std::string& key, const std::string& value);

        /**
         * @brief Sets the value for key to the given `int32_t`.
         *
         * Equivalent to:
         *
         *     return this->PutVariant(Variant::FromInteger(value));
         *
         * @returns `*this`
         */
        EventData& PutInteger(const std::string& key, int32_t value);

        /**
         * @brief Sets the value for key to the given `int64_t`.
         *
         * Equivalent to:
         *
         *     return this->PutVariant(Variant::FromLong(value));
         *
         * @returns `*this`
         */
        EventData& PutLong(const std::string& key, int64_t value);

        /**
         * @brief Sets the value for key to the given `double`.
         *
         * Equivalent to:
         *
         *     return this->PutVariant(Variant::FromDouble(value));
         *
         * @returns `*this`
         */
        EventData& PutDouble(const std::string& key, double value);

        /**
         * @brief Sets the value for key to the given `bool`.
         *
         * Equivalent to:
         *
         *     return this->PutVariant(Variant::FromBoolean(value));
         *
         * @returns `*this`
         */
        EventData& PutBoolean(const std::string& key, bool value);

        /**
         * @brief Sets the value for key to the given variant.
         *
         * @returns `*this`
         */
        EventData& PutVariant(const std::string& key, const std::shared_ptr<Variant>& value);

        /**
         * @brief Sets the value for key to a copy of the given vector.
         *
         * Equivalent to:
         *
         *     return this->PutVariant(Variant::FromVariantVector(value));
         *
         * @returns `*this`
         */
        EventData& PutVariantVector(const std::string& key, const std::vector<std::shared_ptr<Variant>>& value);

        /**
         * @brief Sets the value for key to a copy of the given string map.
         *
         * Equivalent to:
         *
         *     return this->PutVariant(Variant::FromStringMap(value));
         *
         * @returns `*this`
         */
        EventData& PutStringMap(const std::string& key, const std::map<std::string, std::string>& value);

        /**
         * @brief Sets the value for key to a copy of the given map.
         *
         * Equivalent to:
         *
         *     return this->PutVariant(Variant::FromVariantMap(value));
         *
         * @returns `*this`
         */
        EventData& PutVariantMap(const std::string& key, const std::map<std::string, std::shared_ptr<Variant>>& value);

        /**
         * @brief Sets the value for key to a serialization of the given object to a variant.
         *
         * Equivalent to:
         *
         *     return this->PutVariant(Variant::FromTypedObject(value));
         *
         * @returns `*this`
         */
        template<class TObject>
        EventData& PutTypedObject(const std::string& key, const TObject* value);

        /**
         * @brief Sets the value for key to a serialization of the given object to a variant.
         *
         * Equivalent to:
         *
         *     return this->PutVariant(Variant::FromTypedObject(value, s));
         *
         * @returns `*this`
         */
        template<class TObject>
        EventData& PutTypedObject(const std::string& key, const TObject* value,
                                  const std::shared_ptr<VariantSerializerInterface<TObject>>& s);

        /**
         * @brief Sets the value for key to a serialization of the given vector to a variant vector.
         *
         * Equivalent to:
         *
         *     return this->PutVariant(Variant::FromTypedVector(value));
         *
         * @returns `*this`
         */
        template<class TObject>
        EventData& PutTypedVector(const std::string& key, std::vector<std::shared_ptr<TObject>> value);

        /**
         * @brief Sets the value for key to a serialization of the given vector to a variant vector.
         *
         * Equivalent to:
         *
         *     return this->PutVariant(Variant::FromTypedVector(value, s));
         *
         * @returns `*this`
         */
        template<class TObject>
        EventData& PutTypedVector(const std::string& key, std::vector<std::shared_ptr<TObject>> value,
                                  const std::shared_ptr<VariantSerializerInterface<TObject>>& s);

        /**
         * @brief Sets the value for key to a serialization of the given map to a variant map.
         *
         * Equivalent to:
         *
         *     return this->PutVariant(Variant::FromTypedMap(value));
         *
         * @returns `*this`
         */
        template<class TObject>
        EventData& PutTypedMap(const std::string& key, std::map<std::string, std::shared_ptr<TObject>> value);

        /**
         * @brief Sets the value for key to a serialization of the given map to a variant map.
         *
         * Equivalent to:
         *
         *     return this->PutVariant(Variant::FromTypedMap(value, s));
         *
         * @returns `*this`
         */
        template<class TObject>
        EventData& PutTypedMap(const std::string& key, std::map<std::string, std::shared_ptr<TObject>> value,
                               const std::shared_ptr<VariantSerializerInterface<TObject>>& s);

        /**
         * @brief Assigns `value` to a copy of the string value associated with `key`.
         *
         * Equivalent to:
         *
         *     std::shared_ptr<Variant> variant_value;
         *     if (this->GetVariant(key, variant_value)) {
         *       return variant_value->GetString(value);
         *     } else {
         *       return false;
         *     }
         *
         * @returns true iff the key was present and was convertible to a string
         */
        bool GetString(const std::string& key, std::string& value) const;

        /**
         * @brief Assigns `value` to the `int32_t` value associated with `key`.
         *
         * Equivalent to:
         *
         *     std::shared_ptr<Variant> variant_value;
         *     if (this->GetVariant(key, variant_value)) {
         *       return variant_value->GetInteger(value);
         *     } else {
         *       return false;
         *     }
         *
         * @returns true iff the key was present and was convertible to an `int32_t`
         */
        bool GetInteger(const std::string& key, int32_t& value) const;

        /**
         * @brief Assigns `value` to the `int64_t` value associated with `key`.
         *
         * Equivalent to:
         *
         *     std::shared_ptr<Variant> variant_value;
         *     if (this->GetVariant(key, variant_value)) {
         *       return variant_value->GetLong(value);
         *     } else {
         *       return false;
         *     }
         *
         * @returns true iff the key was present and was convertible to an `int64_t`
         */
        bool GetLong(const std::string& key, int64_t& value) const;

        /**
         * @brief Assigns `value` to the double value associated with `key`.
         *
         * Equivalent to:
         *
         *     std::shared_ptr<Variant> variant_value;
         *     if (this->GetVariant(key, variant_value)) {
         *       return variant_value->GetDouble(value);
         *     } else {
         *       return false;
         *     }
         *
         * @returns true iff the key was present and was convertible to a `double`
         */
        bool GetDouble(const std::string& key, double& value) const;

        /**
         * @brief Assigns `value` to the boolean value associated with `key`.
         *
         * Equivalent to:
         *
         *     std::shared_ptr<Variant> variant_value;
         *     if (this->GetVariant(key, variant_value)) {
         *       return variant_value->GetBoolean(value);
         *     } else {
         *       return false;
         *     }
         *
         * @returns true iff the key was present and was convertible to a `bool`
         */
        bool GetBoolean(const std::string& key, bool& value) const;

        /**
         * @brief Assigns `value` to the value associated with `key`.
         *
         * Equivalent to:
         *
         *     std::shared_ptr<Variant> variant_value;
         *     if (this->GetVariant(key, variant_value)) {
         *       return variant_value->GetBoolean(value);
         *     } else {
         *       return false;
         *     }
         *
         * @returns true iff the key was present
         */
        bool GetVariant(const std::string& key, std::shared_ptr<Variant>& value) const;

        /**
         * @brief Assigns `value` to the vector value associated with `key`.
         *
         * Equivalent to:
         *
         *     std::shared_ptr<Variant> variant_value;
         *     if (this->GetVariant(key, variant_value)) {
         *       return variant_value->GetVariantVector(value);
         *     } else {
         *       return false;
         *     }
         *
         * @returns true iff the key was present and was convertible to a `vector`
         */
        bool GetVariantVector(const std::string& key, std::vector<std::shared_ptr<Variant>>& value) const;

        /**
         * @brief Assigns `value` to the string map value associated with `key`.
         *
         * Equivalent to:
         *
         *     std::shared_ptr<Variant> variant_value;
         *     if (this->GetVariant(key, variant_value)) {
         *       return variant_value->GetStringMap(value);
         *     } else {
         *       return false;
         *     }
         *
         * @returns true iff the key was present and was convertible to a `vector`
         */
        bool GetStringMap(const std::string& key, std::map<std::string, std::string>& value) const;

        /**
         * @brief Assigns `value` to a copy of the variant map associated with `key`.
         *
         * Equivalent to:
         *
         *     std::shared_ptr<Variant> variant_value;
         *     if (this->GetVariant(key, variant_value)) {
         *       return variant_value->GetVariantMap(value);
         *     } else {
         *       return false;
         *     }
         *
         * @returns true iff the key was present and was convertible to a variant map
         */
        bool GetVariantMap(const std::string& key, std::map<std::string, std::shared_ptr<Variant>>& value) const;

        /**
         * @brief Assigns `value` to an object deserialization of the variant associated with key,
         *
         * Equivalent to:
         *
         *     std::shared_ptr<Variant> variant_value;
         *     if (this->GetVariant(key, variant_value)) {
         *       return variant_value->GetTypedObject<TObject>();
         *     } else {
         *       return { EVENT_DATA_NO_SUCH_KEY };
         *     }
         *
         * @returns the value as a TObject or EVENT_DATA_NO_SUCH_KEY if the key was not present
         */
        template<class TObject>
        Expected<std::shared_ptr<TObject>> GetTypedObject(const std::string& key) const;

        /**
         * @brief Assigns `value` to an object deserialization of the variant associated with key,
         *
         * Equivalent to:
         *
         *     std::shared_ptr<Variant> variant_value;
         *     if (this->GetVariant(key, variant_value)) {
         *       return variant_value->GetTypedObject<TObject>(s);
         *     } else {
         *       return { EVENT_DATA_NO_SUCH_KEY };
         *     }
         *
         * @returns the value as a TObject or EVENT_DATA_NO_SUCH_KEY if the key was not present
         */
        template<class TObject>
        Expected<std::shared_ptr<TObject>> GetTypedObject(const std::string& key,
                                        const std::shared_ptr<VariantSerializerInterface<TObject>>& s) const;

        /**
         * @brief Assigns `value` to an object vector deserialization of the value associated with key,
         *
         * Equivalent to:
         *
         *     std::shared_ptr<Variant> variant_value;
         *     if (this->GetVariant(key, variant_value)) {
         *       return variant_value->GetTypedVector<TObject>();
         *     } else {
         *       return { EVENT_DATA_NO_SUCH_KEY };
         *     }
         *
         * @returns the value as a TObject or EVENT_DATA_NO_SUCH_KEY if the key was not present
         */
        template<class TObject>
        Expected<std::vector<std::shared_ptr<TObject>>> GetTypedVector(const std::string& key) const;


        /**
         * @brief Assigns `value` to an object vector deserialization of the value associated with key,
         *
         * Equivalent to:
         *
         *     std::shared_ptr<Variant> variant_value;
         *     if (this->GetVariant(key, variant_value)) {
         *       return variant_value->GetTypedVector<TObject>(s);
         *     } else {
         *       return { EVENT_DATA_NO_SUCH_KEY };
         *     }
         *
         * @returns the value as a TObject or EVENT_DATA_NO_SUCH_KEY if the key was not present
         */
        template<class TObject>
        Expected<std::vector<std::shared_ptr<TObject>>> GetTypedVector(const std::string& key,
                const std::shared_ptr<VariantSerializerInterface<TObject>>& s) const;

        /**
         * @brief Assigns `value` to an object map deserialization of the value associated with key,
         *
         * Equivalent to:
         *
         *     std::shared_ptr<Variant> variant_value;
         *     if (this->GetVariant(key, variant_value)) {
         *       return variant_value->GetTypedMap<TObject>();
         *     } else {
         *       return { EVENT_DATA_NO_SUCH_KEY };
         *     }
         *
         * @returns the value as a TObject or EVENT_DATA_NO_SUCH_KEY if the key was not present
         */
        template<class TObject>
        Expected<std::map<std::string, std::shared_ptr<TObject>>> GetTypedMap(const std::string& key) const;

        /**
         * @brief Assigns `value` to an object map deserialization of the value associated with key,
         *
         * Equivalent to:
         *
         *     std::shared_ptr<Variant> variant_value;
         *     if (this->GetVariant(key, variant_value)) {
         *       return variant_value->GetTypedMap<TObject>(s);
         *     } else {
         *       return { EVENT_DATA_NO_SUCH_KEY };
         *     }
         *
         * @returns the value as a TObject or EVENT_DATA_NO_SUCH_KEY if the key was not present
         */
        template<class TObject>
        Expected<std::map<std::string, std::shared_ptr<TObject>>> GetTypedMap(const std::string& key,
                const std::shared_ptr<VariantSerializerInterface<TObject>>& s) const;

        /**
         * @brief Gets the string value associated with the given key, or a default
         *
         * Equivalent to:
         *
         *     std::string v;
         *     if (this->GetString(key, v)) {
         *       return v;
         *     } else {
         *       return fallback;
         *     }
         *
         * @returns the value as a string if the key was present and convertible to a string, otherwise `fallback`
         */
        std::string OptString(const std::string& key, const std::string& fallback);

        /**
         * @brief Gets the `int32_t` value associated with the given key, or a default
         *
         * Equivalent to:
         *
         *     int32_t v;
         *     if (this->GetInteger(key, v)) {
         *       return v;
         *     } else {
         *       return fallback;
         *     }
         *
         * @returns the value as an `int32_t` if the key was present and convertible to an `int32_t`, otherwise `fallback`
         */
        int32_t OptInteger(const std::string& key, int32_t fallback);

        /**
         * @brief Gets the `int64_t` value associated with the given key, or a default
         *
         * Equivalent to:
         *
         *     int64_t v;
         *     if (this->GetLong(key, v)) {
         *       return v;
         *     } else {
         *       return fallback;
         *     }
         *
         * @returns the value as an `int64_t` if the key was present and convertible to an `int64_t`, otherwise `fallback`
         */
        int64_t OptLong(const std::string& key, int64_t fallback);

        /**
         * @brief Gets the `double` value associated with the given key, or a default
         *
         * Equivalent to:
         *
         *     double v;
         *     if (this->GetDouble(key, v)) {
         *       return v;
         *     } else {
         *       return fallback;
         *     }
         *
         * @returns the value as a `double` if the key was present and convertible to a `double`, otherwise `fallback`
         */
        double OptDouble(const std::string& key, double fallback);

        /**
         * @brief Gets the `bool` value associated with the given key, or a default
         *
         * Equivalent to:
         *
         *     bool v;
         *     if (this->GetBoolean(key, v)) {
         *       return v;
         *     } else {
         *       return fallback;
         *     }
         *
         * @returns the value as a `bool` if the key was present and convertible to a `bool`, otherwise `fallback`
         */
        bool OptBoolean(const std::string& key, bool fallback);

        /**
         * @see ObjectInterface::ToStringImpl()
         */
        std::string ToStringImpl(const ToStringOptions& options) const override;

    private:
        std::map<std::string, std::shared_ptr<Variant>> internal_map_; ///< @private the internal map representation
    };

    namespace ErrorCodes {
        constexpr static const char* EVENT_DATA_NO_SUCH_KEY = "event_data.no_such_key"; ///< no such key exists in the EventData
    }

    template<class TObject>
    EventData& EventData::PutTypedObject(const std::string& key, const TObject* value) {
        return PutVariant(key, Variant::FromTypedObject<TObject>(value));
    }

    template<class TObject>
    EventData& EventData::PutTypedObject(const std::string& key, const TObject* value,
                                         const std::shared_ptr<VariantSerializerInterface<TObject>>& s) {
        return PutVariant(key, Variant::FromTypedObject<TObject>(value, s));
    }

    template<class TObject>
    EventData& EventData::PutTypedVector(const std::string& key, std::vector<std::shared_ptr<TObject>> value) {
        return PutVariant(key, Variant::FromTypedVector<TObject>(value));
    }
}

/////////////////////////////////
// template/inline definitions //
/////////////////////////////////

namespace AdobeMarketingMobile {

    template<class TObject>
    EventData& EventData::PutTypedVector(const std::string& key, std::vector<std::shared_ptr<TObject>> value,
                                         const std::shared_ptr<VariantSerializerInterface<TObject>>& s) {
        return PutVariant(key, Variant::FromTypedVector<TObject>(value, s));
    }

    template<class TObject>
    EventData& EventData::PutTypedMap(const std::string& key, std::map<std::string, std::shared_ptr<TObject>> value) {
        return PutVariant(key, Variant::FromTypedMap<TObject>(value));
    }

    template<class TObject>
    EventData& EventData::PutTypedMap(const std::string& key, std::map<std::string, std::shared_ptr<TObject>> value,
                                      const std::shared_ptr<VariantSerializerInterface<TObject>>& s) {
        return PutVariant(key, Variant::FromTypedMap<TObject>(value, s));
    }

    template<class TObject>
    Expected<std::shared_ptr<TObject>> EventData::GetTypedObject(const std::string& key) const {
        std::shared_ptr<Variant> variant_value;
        if (GetVariant(key, variant_value)) {
            return variant_value->GetTypedObject<TObject>();
        }
        return { SdkError(ErrorCodes::EVENT_DATA_NO_SUCH_KEY, "key error") };
    }

    template<class TObject>
    Expected<std::shared_ptr<TObject>> EventData::GetTypedObject(const std::string& key,
    const std::shared_ptr<VariantSerializerInterface<TObject>>& s) const {
        std::shared_ptr<Variant> variant_value;
        if (GetVariant(key, variant_value)) {
            return variant_value->GetTypedObject<TObject>(s);
        }
        return { SdkError(ErrorCodes::EVENT_DATA_NO_SUCH_KEY, "key error") };
    }

    template<class TObject>
    Expected<std::vector<std::shared_ptr<TObject>>> EventData::GetTypedVector(const std::string& key) const {
        std::shared_ptr<Variant> variant_value;
        if (GetVariant(key, variant_value)) {
            return variant_value->GetTypedVector<TObject>();
        }
        return { SdkError(ErrorCodes::EVENT_DATA_NO_SUCH_KEY, "key error") };
    }

    template<class TObject>
    Expected<std::vector<std::shared_ptr<TObject>>> EventData::GetTypedVector(const std::string& key,
            const std::shared_ptr<VariantSerializerInterface<TObject>>& s) const {
        std::shared_ptr<Variant> variant_value;
        if (GetVariant(key, variant_value)) {
            return variant_value->GetTypedVector<TObject>(s);
        }
        return { SdkError(ErrorCodes::EVENT_DATA_NO_SUCH_KEY, "key error") };
    }

    template<class TObject>
    Expected<std::map<std::string, std::shared_ptr<TObject>>> EventData::GetTypedMap(const std::string& key) const {
        std::shared_ptr<Variant> variant_value;
        if (GetVariant(key, variant_value)) {
            return variant_value->GetTypedMap<TObject>();
        }
        return { SdkError(ErrorCodes::EVENT_DATA_NO_SUCH_KEY, "key error") };
    }

    template<class TObject>
    Expected<std::map<std::string, std::shared_ptr<TObject>>> EventData::GetTypedMap(const std::string& key,
            const std::shared_ptr<VariantSerializerInterface<TObject>>& s) const {
        std::shared_ptr<Variant> variant_value;
        if (GetVariant(key, variant_value)) {
            return variant_value->GetTypedMap<TObject>(s);
        }
        return { SdkError(ErrorCodes::EVENT_DATA_NO_SUCH_KEY, "key error") };
    }
}

#endif //ADOBEMOBILE_CORE_EVENTDATA_H
