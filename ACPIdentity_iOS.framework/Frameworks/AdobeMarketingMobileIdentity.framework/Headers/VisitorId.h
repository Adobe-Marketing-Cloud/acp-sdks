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
 ****************************************************************************/

#ifndef ADOBEMOBILE_SHARED_VISITORID_H
#define ADOBEMOBILE_SHARED_VISITORID_H

#include <AdobeMarketingMobileCore/AdobeMarketingMobileCore.h>
#include <string>
#include "VisitorIdAuthenticationState.h"

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
