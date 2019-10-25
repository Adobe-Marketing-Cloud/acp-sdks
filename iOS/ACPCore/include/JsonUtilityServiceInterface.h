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

#ifndef ADOBEMOBILE_PLATFORMSHIM_JSONUTILITYSERVICEINTERFACE_H
#define ADOBEMOBILE_PLATFORMSHIM_JSONUTILITYSERVICEINTERFACE_H

#include <memory>
#include <string>
#include <vector>
#include "EventData.h"
#include "Variant.h"

namespace AdobeMarketingMobile {
    namespace ErrorCodes {
        // Platform shim errors
        /**
         * A json error occurred. Key is not found;
         */
        constexpr static const char* JSON_KEY_NOT_FOUND = "json.key_not_found";
        /**
         * A json error occurred. Index is not found.
         */
        constexpr static const char* JSON_INDEX_NOT_FOUND = "json.index_not_found";
        /**
         * A json error occurred. JsonObject is null.
         */
        constexpr static const char* JSON_JSONOBJECT_IS_NULL = "json.jsonobject_is_null";
        /**
         * A json error occurred. JsonArray is null.
         */
        constexpr static const char* JSON_JSONARRAY_IS_NULL = "json.jsonarray_is_null";
        /**
         * A json error occurred. Value is not of string type.
         */
        constexpr static const char* JSON_VALUE_NOT_STRING_TYPE = "json.value_not_string_type";
        /**
         * A json error occurred. Value is not of numeric type.
         */
        constexpr static const char* JSON_VALUE_NOT_NUMERIC_TYPE = "json.value_not_numeric_type";
        /**
         * A json error occurred. Value is not of boolean type.
         */
        constexpr static const char* JSON_VALUE_NOT_BOOLEAN_TYPE = "json.value_not_boolean_type";
        /**
         * A json error occurred. Value is not of array type.
         */
        constexpr static const char* JSON_VALUE_NOT_ARRAY_TYPE = "json.value_not_array_type";
        /**
         * A json error occurred. Value is not of dictionary type.
         */
        constexpr static const char* JSON_VALUE_NOT_OBJECT_TYPE = "json.value_not_object_type";
        /**
         * A json error occurred. Value is not of dictionary, array, numeric, boolean, string type.
         */
        constexpr static const char* JSON_OBJECT_UNKNOWN = "json.object_unknown";
        /**
         * A json serialization error occurred.
         */
        constexpr static const char* JSON_SERIALIZATION_ERROR = "json.serialization_error";
    }

    enum class JsonType : int32_t {
        NUMERIC = 0,
        BOOLEAN,
        STRING,
        ARRAY,
        OBJECT,
        UNKNOWN
    };

    /**
     * JSON objects are surrounded by curly braces {}.
     * JSON objects are written in key/value pairs.
     * Keys must be strings, and values must be a valid JSON data type (string, number, object, array, boolean or null).
     * Keys and values are separated by a colon.
     * Each key/value pair is separated by a comma.
     */
    class JsonArray;
    class JsonObject : public virtual ObjectInterface {
    public:
        /**
         * Returns a TYPE for the key specified
         *
         * @param name the key name
         * @return the JsonType
         * @throws ErrorCodes::JSON_OBJECT_UNKNOWN if JsonObject is not valid, ErrorCodes::JSON_KEY_NOT_FOUND if key is not present.
         */
        virtual JsonType GetType(const std::string& name) const = 0;

        /**
         * Returns a JsonObject value for the key specified
         *
         * @param name the key name
         * @return the JsonObject
         * @throws ErrorCodes::JSON_JSONOBJECT_IS_NULL if JsonObject value is null, or ErrorCodes::JSON_KEY_NOT_FOUND if key is not present, or
         * ErrorCodes::JSON_VALUE_NOT_OBJECT_TYPE if the value for the key \p name is not a JsonObject
         */
        virtual std::shared_ptr<JsonObject> GetJsonObject(const std::string& name) const = 0;

        /**
         * Returns a JsonArray value for the key specified
         *
         * @param name the key name
         * @return the JsonArray
         * @throws ErrorCodes::JSON_JSONARRAY_IS_NULL if JsonArray value is not null, or ErrorCodes::JSON_KEY_NOT_FOUND if key is not present, or
         * ErrorCodes::JSON_VALUE_NOT_ARRAY_TYPE if the alue for the key \p name is not a JsonArray
         */
        virtual std::shared_ptr<JsonArray> GetJsonArray(const std::string& name) const = 0;

        /**
         * Returns a int32_t value for the key specified
         *
         * @param name the key name
         * @return the int32_t value
         * @throws ErrorCodes::JSON_VALUE_NOT_NUMERIC_TYPE If the value is not numeric, or ErrorCodes::JSON_KEY_NOT_FOUND if key is not present.
         */
        virtual int32_t GetInt(const std::string& name) const = 0;

        /**
         * Returns a int64_t value for the key specified
         *
         * @param name the key name
         * @return the int64_t value
         * @throws ErrorCodes::JSON_VALUE_NOT_NUMERIC_TYPE If the value is not numeric, or ErrorCodes::JSON_KEY_NOT_FOUND if key is not present.
         */
        virtual int64_t GetLong(const std::string& name) const = 0;

        /**
         * Returns a double value for the key specified
         *
         * @param name the key name
         * @return the double value
         * @throws ErrorCodes::JSON_VALUE_NOT_NUMERIC_TYPE If the value is not numeric, or ErrorCodes::JSON_KEY_NOT_FOUND if key is not present.
         */
        virtual double GetDouble(const std::string& name) const = 0;

        /**
         * Returns a std::string value for the key specified
         *
         * @param name the key name
         * @return the std::string value
         * @throws ErrorCodes::JSON_VALUE_NOT_STRING_TYPE If the value is not a std::string, or ErrorCodes::JSON_KEY_NOT_FOUND if key is not present.
         */
        virtual std::string GetString(const std::string& name) const = 0;

        /**
         * Returns a boolean value for the key specified
         *
         * @param name the key name
         * @return the bool value
         * @throws ErrorCodes::JSON_VALUE_NOT_BOOLEAN_TYPE If the value is not a boolean, or ErrorCodes::JSON_KEY_NOT_FOUND if key is not present.
         */
        virtual bool GetBoolean(const std::string& name) const = 0;

        /**
         * Insert a JsonObject value
         *
         * @param name       std::string the key name
         * @param value      value the JsonObject
         * @return JsonObject this object
         */
        virtual std::shared_ptr<JsonObject> PutJsonObject(const std::string& name,
                const std::shared_ptr<JsonObject>& value) = 0;

        /**
         * Insert a JsonArray value
         *
         * @param name      std::string the key name
         * @param value     value the JsonArray value
         * @return JsonObject this object
         */
        virtual std::shared_ptr<JsonObject> PutJsonArray(const std::string& name, const std::shared_ptr<JsonArray>& value) = 0;

        /**
         * Insert an int32_t value
         *
         * @param name  std::string the key name
         * @param value int32_t the value
         * @return JsonObject this object
         */
        virtual std::shared_ptr<JsonObject> PutInt(const std::string& name, int32_t value) = 0;

        /**
         * Insert a int64_t value
         *
         * @param name  std::string the key name
         * @param value int64_t the value
         * @return JsonObject this object
         */
        virtual std::shared_ptr<JsonObject> PutLong(const std::string& name, int64_t value) = 0;

        /**
         * Insert a double value
         *
         * @param name  std::string the key name
         * @param value double the value
         * @return JsonObject this object
         */
        virtual std::shared_ptr<JsonObject> PutDouble(const std::string& name, double value) = 0;

        /**
         * Insert a std::string value
         *
         * @param name  std::string the key name
         * @param value std::string the value
         * @return JsonObject this object
         */
        virtual std::shared_ptr<JsonObject> PutString(const std::string& name, const std::string& value) = 0;

        /**
         * Insert a boolean value
         *
         * @param name  std::string the key name
         * @param value boolean the value
         * @return JsonObject this object
         */
        virtual std::shared_ptr<JsonObject> PutBoolean(const std::string& name, bool value) = 0;

        /**
         * Returns a JsonObject if a mapping exists, null otherwise.
         *
         * @param name the key name
         * @return JsonObject, if mapping exists, null otherwise
         */
        virtual std::shared_ptr<JsonObject> OptJsonObject(const std::string& name) const = 0;


        /**
         * Returns a JsonArray if a mapping exists, null otherwise.
         *
         * @param name Key name
         * @return JsonArray, if mapping exists, null otherwise
         */
        virtual std::shared_ptr<JsonArray> OptJsonArray(const std::string& name) const = 0;

        /**
         * Returns the int32_t value, if a valid mapping exists.
         *
         * @param name         Key name
         * @param default_value Value to be returned if a valid mapping does not exist.
         * @return int32_t value if a valid mapping exists, default_value otherwise.
         */
        virtual int32_t OptInt(const std::string& name, int32_t default_value) const = 0;

        /**
         * Returns the int64_t value, if a valid mapping exists.
         *
         * @param name         Key name
         * @param default_value Value to be returned if a valid mapping does not exist.
         * @return int64_t value if a valid mapping exists, default_value otherwise.
         */
        virtual int64_t OptLong(const std::string& name, int64_t default_value) const = 0;

        /**
         * Returns the double value, if a valid mapping exists.
         *
         * @param name         Key name
         * @param default_value Value to be returned if a valid mapping does not exist.
         * @return double value if a valid mapping exists, default_value otherwise.
         */
        virtual double OptDouble(const std::string& name, double default_value) const = 0;

        /**
         * Returns the String value, if a valid mapping exists.
         *
         * @param name         Key name
         * @param default_value Value to be returned if a valid mapping does not exist.
         * @return String value if a valid mapping exists, default_value otherwise.
         */
        virtual std::string OptString(const std::string& name, const std::string& default_value) const = 0;

        /**
         * Returns the boolean value, if a valid mapping exists.
         *
         * @param name         Key name
         * @param default_value Value to be returned if a valid mapping does not exist.
         * @return boolean value if a valid mapping exists, default_value otherwise.
         */
        virtual bool OptBoolean(const std::string& name, bool default_value) const = 0;


        /**
         * Returns an iterator of the String keys in this object.
         *
         * @param keys list of the std::string keys
         */
        virtual void Keys(std::vector<std::string>& keys) const = 0;


        /**
         * Returns the number of mappings in this object
         *
         * @return The number of mappings
         */
        virtual size_t Length() const = 0;

        /**
         * Removes the specifed key and its value from the JSONObject
         *
         * @param name key that will be removed from the JSONObject
         */
        virtual void Remove(const std::string& name) = 0;

        /**
         * Convert this JsonObject to std::string
         *
         * @return std::string the string
         * @throws ErrorCodes::JSON_SERIALIZATION_ERROR if there is error
         */
        virtual std::string ToString() const = 0;

    };

    class JsonArray : public virtual ObjectInterface {
    public:
        /**
         * Returns a TYPE for the key specified
         *
         * @param index the uint32_t index
         * @return the TYPE
         * @throws ErrorCodes::JSON_JSONARRAY_IS_NULL or ErrorCodes::JSON_INDEX_NOT_FOUND if the index is invalid.
         */
        virtual JsonType GetType(uint32_t index) const = 0;

        /**
         * Append a JsonObject value to the end of this array
         *
         * @param json_object JsonObject the value
         * @return JsonArray this array
         */
        virtual std::shared_ptr<JsonArray> PutJsonObject(const std::shared_ptr<JsonObject>& json_object) = 0;

        /**
         * Sets the value at index to json_object, null padding this array to the required length if necessary.
         * If a value already exists at index, it will be replaced
         *
         * @param index the uint32_t index
         * @param json_object JsonObject the value
         * @return JsonArray this array
         */
        virtual std::shared_ptr<JsonArray> PutJsonObject(uint32_t index, const std::shared_ptr<JsonObject>& json_object) = 0;

        /**
         * Append a JsonArray to the end of this array
         *
         * @param json_array JsonArray the value
         * @return JsonArray this array
         */
        virtual std::shared_ptr<JsonArray> PutJsonArray(const std::shared_ptr<JsonArray>& json_array) = 0;

        /**
         * Sets the value at index to value, null padding this array to the required length if necessary.
         * If a value already exists at index, it will be replaced
         *
         * @param index the uint32_t index
         * @param json_array JsonArray the value
         * @return JsonArray this array
         */
        virtual std::shared_ptr<JsonArray> PutJsonArray(uint32_t index, const std::shared_ptr<JsonArray>& json_array) = 0;

        /**
         * Append an int32_t value to the end of this array
         *
         * @param value int32_t the value
         * @return JsonArray this array
         */
        virtual std::shared_ptr<JsonArray> PutInt(int32_t value) = 0;

        /**
         * Sets the value at index to value, null padding this array to the required length if necessary.
         * If a value already exists at index, it will be replaced
         *
         * @param index the uint32_t index
         * @param value int32_t the value
         * @return JsonArray this array
         */
        virtual std::shared_ptr<JsonArray> PutInt(uint32_t index, int32_t value) = 0;

        /**
         * Append an int64_t value to the end of this array
         *
         * @param value int64_t the value
         * @return JsonArray this array
         */
        virtual std::shared_ptr<JsonArray> PutLong(int64_t value) = 0;

        /**
         * Sets the value at index to value, null padding this array to the required length if necessary.
         * If a value already exists at index, it will be replaced
         *
         * @param index the uint32_t index
         * @param value int64_t the value
         * @return JsonArray this array
         */
        virtual std::shared_ptr<JsonArray> PutLong(uint32_t index, int64_t value) = 0;

        /**
         * Append a double value to the end of this array
         *
         * @param value double the value
         * @return JsonArray this array
         */
        virtual std::shared_ptr<JsonArray> PutDouble(double value) = 0;

        /**
         * Sets the value at index to value, null padding this array to the required length if necessary.
         * If a value already exists at index, it will be replaced
         *
         * @param index the uint32_t index
         * @param value double the value
         * @return JsonArray this array
         */
        virtual std::shared_ptr<JsonArray> PutDouble(uint32_t index, double value) = 0;

        /**
         * Append a std::string value to the end of this array
         *
         * @param value std::string the value
         * @return JsonArray this array
         */
        virtual std::shared_ptr<JsonArray> PutString(const std::string& value) = 0;

        /**
         * Sets the value at index to value, null padding this array to the required length if necessary.
         * If a value already exists at index, it will be replaced.
         *
         * @param index the uint32_t index
         * @param value std::string the value
         * @return JsonArray this array
         */
        virtual std::shared_ptr<JsonArray> PutString(uint32_t index, const std::string& value) = 0;

        /**
         * Append a boolean value to the end of this array
         *
         * @param value bool the value
         * @return JsonArray this array
         */
        virtual std::shared_ptr<JsonArray> PutBoolean(bool value) = 0;

        /**
         * Sets the value at index to value, null padding this array to the required length if necessary.
         * If a value already exists at index, it will be replaced
         *
         * @param index the uint32_t index
         * @param value bool the value
         * @return JsonArray this array
         */
        virtual std::shared_ptr<JsonArray> PutBoolean(uint32_t index, bool value) = 0;

        /**
         * Returns the JsonObject value if a valid value is present at the index specified.
         *
         * @param index The index into the JsonArray
         * @return JsonObject
         * @throws ErrorCodes::JSON_INDEX_NOT_FOUND if the index is invalid
         */
        virtual std::shared_ptr<JsonObject> GetJsonObject(uint32_t index) const = 0;

        /**
         * Returns the JsonArray value if a valid value is present at the index specified.
         *
         * @param index The index into the JsonArray
         * @return JsonArray
         * @throws ErrorCodes::JSON_INDEX_NOT_FOUND if the index is invalid,
            ErrorCodes::JSON_VALUE_NOT_ARRAY_TYPE the value at index is not an array.
         */
        virtual std::shared_ptr<JsonArray> GetJsonArray(uint32_t index) const = 0;

        /**
         * Returns the int32_t value if a valid value is present at the index specified.
         *
         * @param index The index into the JsonArray
         * @return int32_t value
         * @throws ErrorCodes::JSON_INDEX_NOT_FOUND if the index is invalid, ErrorCodes::JSON_VALUE_NOT_NUMERIC_TYPE the value at index is not a number.
         */
        virtual int32_t GetInt(uint32_t index) const = 0;

        /**
         * Returns the int64_t value if a valid value is present at the index specified.
         *
         * @param index The index into the JsonArray
         * @return int64_t
         * @throws ErrorCodes::JSON_INDEX_NOT_FOUND if the index is invalid, ErrorCodes::JSON_VALUE_NOT_NUMERIC_TYPE the value at index is not a number.
         */
        virtual int64_t GetLong(uint32_t index) const = 0;

        /**
         * Returns the double value if a valid value is present at the index specified.
         *
         * @param index The index into the JsonArray
         * @return double
         * @throws ErrorCodes::JSON_INDEX_NOT_FOUND if the index is invalid, ErrorCodes::JSON_VALUE_NOT_NUMERIC_TYPE the value at index is not a number.
         */
        virtual double GetDouble(uint32_t index) const = 0;

        /**
         * Returns the std::string value if a valid value is present at the index specified.
         *
         * @param index The index into the JsonArray
         * @return String
         * @throws ErrorCodes::JSON_INDEX_NOT_FOUND if the index is invalid, ErrorCodes::JSON_VALUE_NOT_NUMERIC_TYPE the value at index is not a std::string.
         */
        virtual std::string GetString(uint32_t index) const = 0;

        /**
         * Returns the boolean value if a valid value is present at the index specified.
         *
         * @param index The index into the JsonArray
         * @return boolean
         * @throws ErrorCodes::JSON_INDEX_NOT_FOUND if the index is invalid, ErrorCodes::JSON_VALUE_NOT_BOOLEAN_TYPE the value at index is not a boolean.
         */
        virtual bool GetBoolean(uint32_t index) const = 0;

        /**
         * Returns the JsonObject value if a valid value is present at the index specified.
         *
         * @param index The index into the JsonArray
         * @return JsonObject value at the index if exists and valid, null otherwise.
         */
        virtual std::shared_ptr<JsonObject> OptJsonObject(uint32_t index) const = 0;

        /**
         * Returns the JsonArray value if a valid value is present at the index specified.
         *
         * @param index The index into the JsonArray
         * @return JsonArray value at the index, if exists and valid, null otherwise.
         */
        virtual std::shared_ptr<JsonArray> OptJsonArray(uint32_t index) const = 0;

        /**
         * Returns the int32_t value if a valid value is present at the index specified.
         *
         * @param index        The index into the JsonArray
         * @param default_value Value to be returned if a valid value does not exist at index.
         * @return int32_t value at the index if exists and valid, default_value otherwise.
         */
        virtual int32_t OptInt(uint32_t index, int32_t default_value) const = 0;

        /**
         * Returns the int64_t value if a valid value is present at the index specified.
         *
         * @param index        The index into the JsonArray
         * @param default_value Value to be returned if a valid value does not exist at index.
         * @return int64_t value at the index if exists and valid, default_value otherwise.
         */
        virtual int64_t OptLong(uint32_t index, int64_t default_value) const = 0;

        /**
         * Returns the double value if a valid value is present at the index specified.
         *
         * @param index        The index into the JsonArray
         * @param default_value Value to be returned if a valid value does not exist at index.
         * @return double value at the index if exists and valid, default_value otherwise.
         */

        virtual double OptDouble(uint32_t index, double default_value) const = 0;

        /**
         * Returns the std::string value if a valid value is present at the index specified.
         *
         * @param index        The index into the JsonArray
         * @param default_value Value to be returned if a valid value does not exist at index.
         * @return String value at the index if exists and valid, default_value otherwise.
         */
        virtual std::string OptString(uint32_t index, const std::string& default_value) const = 0;

        /**
         * Returns the boolean value if a valid value is present at the index specified.
         *
         * @param index        The index into the JsonArray
         * @param default_value Value to be returned if a valid value does not exist at index.
         * @return boolean value at the index if exists and valid, default_value otherwise.
         */
        virtual bool OptBoolean(uint32_t index, bool default_value) const = 0;

        /**
         * Returns the number of values in the array
         *
         * @return Number of values in the array.
         */
        virtual size_t Length() const = 0;

        /**
         * Convert this JsonArray to std::string
         *
         * @return std::string the string
         * @throws ErrorCodes::JSON_SERIALIZATION_ERROR if there is error
         */
        virtual std::string ToString() const = 0;
    };

    class JsonUtilityServiceInterface : public virtual ObjectInterface {
    public:
        /**
         * Parse a Json string provided as input into a JsonObject instance, if the JSON string has the JSON object as
         * the root element.
         *
         * @param json The json string to parse.
         * @return A valid JsonObject if parse was successful
         * @throws ErrorCodes::JSON_SERIALIZATION_ERROR if there is error
         */
        virtual std::shared_ptr<JsonObject> CreateJsonObject(const std::string& json) = 0;
        /**
         * Create a JsonObject from a Map
         *
         * @param map Map to create a JsonObject from
         * @return A valid JsonObject if parse was successful, null otherwise
         */
        virtual std::shared_ptr<JsonObject> CreateJsonObject(const std::map<std::string, std::shared_ptr<Variant>>& map) = 0;

        /**
         * Create a JsonObject from a String StringMap
         *
         * @param map Map to create a JsonObject from
         * @return A valid JsonObject if parse was successful, null otherwise
         */
        virtual std::shared_ptr<JsonObject> CreateJsonObject(const std::map<std::string, std::string>& map) = 0;

        /**
        * Creates a valid empty JsonObject.
        *
        * @return An empty JsonObject.
        */
        virtual std::shared_ptr<JsonObject> CreateEmptyJsonObject() = 0;

        /**
         * Parse a Json string provided as input into a JsonArray instance, if the JSON string has the JSON array as
         * the root element.
         *
         * @param json The json string to parse
         * @return A valid JsonArray if parse was successful
         * @throws ErrorCodes::JSON_SERIALIZATION_ERROR if there is error
         */
        virtual std::shared_ptr<JsonArray> CreateJsonArray(const std::string& json) = 0;

        /**
         * Creates a JsonArray from a variant vector
         *
         * @param vector variant vector to create the JsonArray from
         * @return A valid JsonArray if parse was successful, nullptr otherwise
         */
        virtual std::shared_ptr<JsonArray> CreateJsonArray(const std::vector<std::shared_ptr<Variant>>& vector) = 0;

        /**
         * Creates a valid empty JsonArray.
         *
         * @return An empty JsonArray.
         */
        virtual std::shared_ptr<JsonArray> CreateEmptyJsonArray() = 0;

        /**
         * Parse a JsonObject and return the converted std::map of that object
         *
         * @param json_data The JsonObject to parse
         * @return A valid string map if parse was successful, empty string map otherwise
         */
        virtual std::map<std::string, std::string> MapFromJsonObject(const std::shared_ptr<JsonObject>& json_data) = 0;

        /**
         * Parse EventData and deserialize the underlying variant map to JsonObject.
         *
         * @param data The EventData to parse
         * @return Valid JsonObject if successful, nullptr otherwise
         */
        virtual Expected<std::shared_ptr<JsonObject>> EventDataToJsonObject(const std::shared_ptr<EventData>& data);
        /**
         * Parse a JsonObject and convert it to EventData by serializing to a variant map
         *
         * @param json_data The JsonObject to parse
         * @return Valid EventData if successful, nullptr otherwise
         */
        virtual Expected<std::shared_ptr<EventData>> JsonObjectToEventData(const std::shared_ptr<JsonObject>& json_data);
    };

}   //namespace

#endif /* ADOBEMOBILE_PLATFORMSHIM_JSONUTILITYSERVICEINTERFACE_H */

