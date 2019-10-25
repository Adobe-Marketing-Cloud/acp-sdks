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

#ifndef ADOBEMOBILE_SHARED_CONSEQUENCE_H
#define ADOBEMOBILE_SHARED_CONSEQUENCE_H

#include <map>
#include <string>
#include "Object.h"
#include "Variant.h"

namespace AdobeMarketingMobile {
    class ConsequenceSerializer;
    class Consequence : public Object {
    public:
        using Serializer = ConsequenceSerializer;
        Consequence(const std::string& id,
                    const std::string& type,
                    const std::string& assets_path,
                    const std::map<std::string, std::shared_ptr<Variant>>& detail);

        /**
         * @return the consequence id
         */
        const std::string& GetId() const;

        /**
         * @return the consequence type
         */
        const std::string& GetType() const;

        /**
         * @return the assets path for the consequence
         */
        const std::string& GetAssetsPath() const;

        /**
         * @return the consequence details
         */
        const std::map<std::string, std::shared_ptr<Variant>>& GetDetail() const;

    private:
        std::string id_;
        std::string type_;
        std::string assets_path_;
        std::map<std::string, std::shared_ptr<Variant>> detail_;
    };

    /**
     * @brief Serializer for Consequence objects
     */
    class ConsequenceSerializer : public Object, public virtual VariantSerializerInterface<Consequence> {
    public:
        Expected<std::shared_ptr<Consequence>> Deserialize(const Variant& value) const override;
        std::shared_ptr<Variant> Serialize(const Consequence& o) const override;
    };
}

#endif /* ADOBEMOBILE_SHARED_CONSEQUENCE_H */
