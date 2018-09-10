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

#ifndef ADOBEMOBILE_TARGET_TARGETOBJECT_H
#define ADOBEMOBILE_TARGET_TARGETOBJECT_H

#include <AdobeMarketingMobileCore/AdobeMarketingMobileCore.h>
#include <map>
#include <string>

namespace AdobeMarketingMobile {

    class TargetObjectSerializer;
    class TargetObject : public Object {
    public:
        using Serializer = TargetObjectSerializer;
        TargetObject(const std::string& name,
                     const std::map<std::string, std::shared_ptr<Variant>>& mbox_params,
                     const std::map<std::string, std::shared_ptr<Variant>>& product_params,
                     const std::map<std::string, std::shared_ptr<Variant>>& order_params);

        /**
         * @return the mbox name
         */
        const std::string& GetName() const;

        /**
         * @return the mbox parameters collection
         */
        const std::map<std::string, std::shared_ptr<Variant>>& GetMboxParameters() const;

        /**
         * @return the product parameters collection
         */
        const std::map<std::string, std::shared_ptr<Variant>>& GetProductParameters() const;

        /**
         * @return the order parameters collection
         */
        const std::map<std::string, std::shared_ptr<Variant>>& GetOrderParameters() const;

    private:
        std::string mbox_name_;
        std::map<std::string, std::shared_ptr<Variant>> mbox_parameters_;
        std::map<std::string, std::shared_ptr<Variant>> product_parameters_;
        std::map<std::string, std::shared_ptr<Variant>> order_parameters_;
    };

    /**
     * @brief Serializer for TargetObject objects
     */
    class TargetObjectSerializer : public Object, public virtual VariantSerializerInterface<TargetObject> {
    public:
        Expected<std::shared_ptr<TargetObject>> Deserialize(const Variant& value) const override;
        std::shared_ptr<Variant> Serialize(const TargetObject& o) const override;
    };

}

#endif /* ADOBEMOBILE_TARGET_TARGETOBJECT_H */
