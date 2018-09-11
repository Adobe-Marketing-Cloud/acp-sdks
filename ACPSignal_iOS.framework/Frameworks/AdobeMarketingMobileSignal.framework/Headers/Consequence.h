/* **************************************************************************
 *
 * ADOBE CONFIDENTIAL
 * ___________________
 *
 * Copyright 2018 Adobe Systems Incorporated
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

#ifndef ADOBEMOBILE_CONSEQUENCE_H
#define ADOBEMOBILE_CONSEQUENCE_H

#include <AdobeMarketingMobileCore/Object.h>
#include <map>
#include <string>
#include <AdobeMarketingMobileCore/Variant.h>

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

#endif /* ADOBEMOBILE_CONSEQUENCE_H */
