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
