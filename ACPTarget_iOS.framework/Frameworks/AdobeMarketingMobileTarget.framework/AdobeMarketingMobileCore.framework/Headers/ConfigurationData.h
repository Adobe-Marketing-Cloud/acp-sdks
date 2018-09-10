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

#ifndef ADOBEMOBILE_CONFIGURATION_CONFIGURATIONDATA_H
#define ADOBEMOBILE_CONFIGURATION_CONFIGURATIONDATA_H

#include <map>
#include <string>
#include "JsonUtilityServiceInterface.h"
#include "EventData.h"
#include "Object.h"
#include "Variant.h"

namespace AdobeMarketingMobile {

    /**
     * @class ConfigurationData
     *
     */
    class ConfigurationData : public Object {
    public:

        /**
         * Construct new ConfigurationData object with the provided JSON parser.
         *
         * @param json_utilty_service JSON utility serviced used to parse JSON formatted strings into
         *                              internal JsonObjects and vice versa
         */
        explicit ConfigurationData(const std::shared_ptr<JsonUtilityServiceInterface>& json_utilty_service);

        /**
         * Add configuration data from a JSON formatted string into this object. The formatted string
         * must only contain flattened key/value pairs and no nested objects or array structures.
         * Any matching keys will overwrite existing values in this ConfigurationData object.
         *
         * @param json_string A JSON formatted string
         * @return a reference to this ConfigurationData object
         */
        ConfigurationData& Put(const std::string& json_string);

        /**
         * Add configuration data from a map into this object. The map must only contain
         * flattended configuration key/value pairs and no nested object, array, or map structures.
         * Any matching keys will overwrite existing values in this ConfigurationData object.
         *
         * @param map Key/value pairs to add to this object
         * @return a reference to this ConfigurationData object
         */
        ConfigurationData& Put(const std::map<std::string, std::shared_ptr<Variant>>& map);

        /**
         * Copy configuration data from another ConfigurationData object to this object.
         * Any matching keys will overwrite existing values in this ConfigurationData object.
         *
         * @param configuration_data ConfigurationData to copy into this object
         * @return a reference to this ConfigurationData object
         */
        ConfigurationData& Put(const std::shared_ptr<ConfigurationData>& configuration_data);

        /**
         * Add configuration data from a JsonObject to this configuration object. The JsonObject must
         * only contain flattened key/value paris and no nested JSON objects or JSON array structures.
         * Any matching keys in the given object will overwrite existing values in this ConfigurationData object
         *
         * @param json_object A JsonObject whose elements to add to this object
         * @return a reference to this ConfigurationData object
         */
        ConfigurationData& Put(const std::shared_ptr<JsonObject>& json_object);

        /**
         * Get a pointer to a new EventData object containing this configuration data.
         *
         * @return A pointer to a new EventData object containting this configuration data.
         */
        std::shared_ptr<EventData> GetEventData() const;

        /**
         * Get a JSON formatted string representation of this configuration data.
         *
         * @return a JSON formatted string
         */
        std::string GetJsonString() const;

        /**
         * Determine if there are any configuration elements.
         *
         * @return true if there are no configuration elements, false otherwise
         */
        bool IsEmpty() const;

        /**
         * @see ObjectInterface::ToStringImpl()
         */
        std::string ToStringImpl(const ToStringOptions& options) const override;

    private:

        /**
         * @private
         * Internal storage of configuration data.
         */
        std::map<std::string, std::shared_ptr<Variant>> internal_map_;

        /**
         * @private
         * Json Utility Service from Platform Services, passed into constructor.
         * Allowed to be nullptr. Must check for nullptr before using!
         */
        std::shared_ptr<JsonUtilityServiceInterface> json_utility_service_;
    };


} // end namespace AdobeMarketingMobile


#endif //ADOBEMOBILE_CONFIGURATION_CONFIGURATIONDATA_H
