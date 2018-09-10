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

#ifndef ADOBEMOBILE_TARGET_TARGETPREFETCH_H
#define ADOBEMOBILE_TARGET_TARGETPREFETCH_H

#include <AdobeMarketingMobileCore/AdobeMarketingMobileCore.h>
#include "TargetObject.h"
#include <string>

namespace AdobeMarketingMobile {

    class TargetPrefetchSerializer;
    class TargetPrefetch : public TargetObject {
    public:
        using Serializer = TargetPrefetchSerializer;
        TargetPrefetch(const std::string& name,
                       const std::map<std::string, std::shared_ptr<Variant>>& mbox_params,
                       const std::map<std::string, std::shared_ptr<Variant>>& product_params,
                       const std::map<std::string, std::shared_ptr<Variant>>& order_params): TargetObject(name, mbox_params, product_params,
                                   order_params) {};
    };

    /**
     * @brief Serializer for TargetPrefetch objects
     */
    class TargetPrefetchSerializer : public Object, public virtual VariantSerializerInterface<TargetPrefetch> {
    public:
        Expected<std::shared_ptr<TargetPrefetch>> Deserialize(const Variant& value) const {
            if (value.GetKind() == VariantKind::VARIANT_NULL) {
                return { std::shared_ptr<TargetPrefetch>() };
            }

            auto base_class = value.Variant::GetTypedObject<TargetObject>();
            if (!base_class) {
                return { SdkError(ErrorCodes::VARIANT_NOT_TYPE, "type error") };
            }
            auto target_prefetch = std::make_shared<TargetPrefetch>(base_class.Value()->GetName(),
                                   base_class.Value()->GetMboxParameters(),
                                   base_class.Value()->GetProductParameters(),
                                   base_class.Value()->GetOrderParameters());
            return { target_prefetch };
        }

        std::shared_ptr<Variant> Serialize(const TargetPrefetch& o) const {
            return Variant::FromTypedObject<TargetObject>(&o);
        }
    };

}

#endif /* ADOBEMOBILE_TARGET_TARGETPREFETCH_H */
