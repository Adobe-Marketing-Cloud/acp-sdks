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

#ifndef ADOBEMOBILE_RULESENGINE_EVENTDATAFLATTENER_H
#define ADOBEMOBILE_RULESENGINE_EVENTDATAFLATTENER_H

#include <list>
#include <map>
#include <string>
#include "Object.h"

namespace AdobeMarketingMobile {
    class FlatDictionaryInterface;
    class EventData;
    class Variant;

    class EventDataFlattener : public Object {

    public:

        /**
         * Construct an instance of EventDataFlattener
         *
         * @param event_data The EventData to flatten
         */
        EventDataFlattener(const std::shared_ptr<EventData>& event_data);

        /**
         * Returns a `Map<String, Variant>` which has been flattened in the following way:
         *
         * The Keys are of the format "eventdataKey"."nestedMapKeyOrFlatDictionaryKey"....
         * So For example, an event data in the following format:
         *
         *     [mapKey][key1]=value1
         *     [mapKey][key2]=value2
         *
         * will be flattened to
         *
         *     [mapKey.key1]=value1
         *     [mapKey.key1]=value2
         *
         * @return flattened values as `std::map<std::string, std::shared_ptr<Variant>>`
         */
        std::map<std::string, std::shared_ptr<Variant>> GetFlattenedDataMap() const;

    private:

        /**
         * @private
         * Inserts the value into a Map by flattening the value if needed.
         *
         * If the value is a Map it will be flattened (the namespaced key will be prefixed to the nested keys).
         * If the value is a {@link FlatDictionary}, the result of {@link FlatDictionary::GetFlatDictionary()}
         * will be inserted (the namespaced key will be prefixed to the keys).
         * Else, the value will be inserted as is with the key being the {@code namespaced key}
         *
         * @param nameSpacedKey The key (which has been appropriately namespaced) that will be used as the key for the
         *                         value inserted.
         *                      If the value is further flattened for inserting into the returned map, then the key will
         *                      be used as the
         *                      prefix for the keys in the flattened representation.
         * @param value         The Object that will be inserted into the map after flattening (if needed)
         * @param out           The flattened map result.
         */
        void Flatten(const std::string& namespaced_key, const std::shared_ptr<Variant>& value,
                     std::map<std::string, std::shared_ptr<Variant>>& out) const;

        /**
         * @private
         * Returns a map after flattening the map_value. It is done by recursively calling
         * {@link ::Flatten(std::string, std::shared_ptr<Variant>)}
         *
         * @param key_prefix The string that will be prefixed to the map keys.
         * @param map_value  The map that will be flattened.
         * @param out The flattened map result.
         */
        void Flatten(const std::string& key_prefix, const std::map<std::string, std::shared_ptr<Variant>>& map_value,
                     std::map<std::string, std::shared_ptr<Variant>>& out) const;

        /**
         * @private
         * Returns a map after flattening the map_value.
         *
         * @param key_prefix The string that will be prefixed to the map keys.
         * @param map_value The map to be flattened.
         * @param out the flattended map result.
         */
        void Flatten(const std::string& key_prefix, const std::map<std::string, std::string>& map_value,
                     std::map<std::string, std::shared_ptr<Variant>>& out) const;

        /**
         * @private
         * Returns a map after flattening the flat_dictionary.
         *
         * @param key_prefix      The string that will be prefixed to the {@code flat_dictionary} keys.
         * @param flat_dictionary The {@link FlatDictionary} instance, that will be inserted (after prefixing the {@code
         * key_prefix})
         * @out The flattened map result.
         */
        void Flatten(const std::string& key_prefix, const std::shared_ptr<FlatDictionaryInterface>& flat_dictionary,
                     std::map<std::string, std::shared_ptr<Variant>>& out) const;

        std::map<std::string, std::shared_ptr<Variant>> data_; // the data to flatten
    };
}

#endif /* ADOBEMOBILE_RULESENGINE_EVENTDATAFLATTENER_H */
