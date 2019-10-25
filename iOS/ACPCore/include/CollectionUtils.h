/*
Copyright 2019 Adobe. All rights reserved.
This file is licensed to you under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License. You may obtain a copy
of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS
OF ANY KIND, either express or implied. See the License for the specific language
governing permissions and limitations under the License.
*/

#ifndef ADOBEMOBILE_UTIL_COLLECTIONUTILS_H
#define ADOBEMOBILE_UTIL_COLLECTIONUTILS_H

#include <map>
#include <vector>

namespace AdobeMarketingMobile {
    class Variant;

    class CollectionUtils {
    public:

        /**
         * @brief Merges the contents of from_map into to_map
         *
         * @discussion While merging from_map into to_map, this method will prioritize to_map for conflicting
         * values. If the value type being processed is a VariantMapVariant type, this method will recurse.
         * If from_map is empty, this method will return to_map.
         *
         * @param to_map a map<std::string, std::shared_ptr<Variant>> containing the higher priority data
         * @param from_map a map<std::string, std::shared_ptr<Variant>> containing the lower priority data
         * @return a map<std::string, std::shared_ptr<Variant>> with the combined contents of to_map and from_map
         */
        static std::map<std::string, std::shared_ptr<Variant>> AddDataToMap(
                            const std::map<std::string, std::shared_ptr<Variant>>& to_map,
                            const std::map<std::string, std::shared_ptr<Variant>>& from_map);

        /**
         * @brief Merges the contents of from_vector into to_vector
         *
         * @discussion If the value type being processed is a VariantVectorVariant type, this method will recurse.
         * If from_vector is empty, this method will return to_vector. For non-collection value types, this
         * method will prevent duplicate entries in the resulting vector.
         *
         * @param to_vector a vector<std::shared_ptr<Variant>> containing the higher priority data
         * @param from_vector a vector<std::shared_ptr<Variant>> containing the lower priority data
         * @return a vector<std::shared_ptr<Variant>> with the combined contents of to_vector and from_vector
         */
        static std::vector<std::shared_ptr<Variant>> AddDataToVector(
                            const std::vector<std::shared_ptr<Variant>>& to_vector,
                            const std::vector<std::shared_ptr<Variant>>& from_vector);

        /**
         * @brief Gets a json-formatted string representation of the provided map
         *
         * @discussion This method will provide a human-readable string output of the given map. If the value
         * being processed is std::map<std::string, std::shared_ptr<Variant>>, this method will recurse.
         * Unless it's being called from either GetPrettyString method, this method should be called with
         * an indent_depth of 1.
         *
         * @param map a map<std::string, std::shared_ptr<Variant>> containing the source data for generated string
         * @param indent_depth represents the number of indentations needed for whitespace alignment in the string
         * @return a json-formatted std::string representing the provided map - pretty to the eyes
         */
        static std::string GetPrettyString(const std::map<std::string, std::shared_ptr<Variant>>& map,
                                           int32_t indent_depth);

        /**
         * @brief Gets a json-formatted string representation of the provided vector
         *
         * @discussion This method will provide a human-readable string output of the given vector. If the value
         * being processed is std::vector<std::shared_ptr<Variant>>, this method will recurse. Unless it's being
         * called from either GetPrettyString method, this method should be called with an indent_depth of 1.
         *
         * @param vector a vector<std::shared_ptr<Variant>> containing the source data for generated string
         * @param indent_depth represents the number of indentations needed for whitespace alignment in the string
         * @return a json-formatted std::string representing the provided vector - calming to the nerves
         */
        static std::string GetPrettyString(const std::vector<std::shared_ptr<Variant>>& vector,
                                           int32_t indent_depth);

        /**
         * @brief Returns whitespace equal to the provided num_spaces
         *
         * @param num_spaces number of spaces you want returned
         * @return an std::string with num_spaces of whitespace characters
         */
        static std::string GetWhitespace(const int32_t num_spaces);
    };
}

#endif /* ADOBEMOBILE_UTIL_COLLECTIONUTILS_H */
