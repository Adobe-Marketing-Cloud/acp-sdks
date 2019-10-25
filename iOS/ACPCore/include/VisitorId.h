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

#ifndef ADOBEMOBILE_SHARED_VISITORID_H
#define ADOBEMOBILE_SHARED_VISITORID_H

#include <string>
#include "VisitorIdAuthenticationState.h"
#include "Object.h"
#include "Variant.h"

namespace AdobeMarketingMobile {

    class VisitorIdSerializer;
    /**
     * This class encapsulates the visitor identity information
     */
    class VisitorId : public Object {
    public:
        using Serializer = VisitorIdSerializer;
        std::string id_origin;
        std::string id_type;
        std::string id;
        VisitorIdAuthenticationState authentication_state;

        VisitorId() {};

        VisitorId(const std::string& id_origin,
                  const std::string& id_type,
                  const std::string& id,
                  const VisitorIdAuthenticationState authentication_state) ;

        bool Equals(std::shared_ptr<VisitorId>& right) const;
    };

    /**
     * @brief Serializer for VisitorId objects
     */
    class VisitorIdSerializer : public Object, public virtual VariantSerializerInterface<VisitorId> {
    public:
        Expected<std::shared_ptr<VisitorId>> Deserialize(const Variant& value) const override;
        std::shared_ptr<Variant> Serialize(const VisitorId& o) const override;
    };

}

#endif /* ADOBEMOBILE_SHARED_VISITORID_H */
