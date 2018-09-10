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

#ifndef ADOBEMOBILE_TARGET_TARGETREQUEST_H
#define ADOBEMOBILE_TARGET_TARGETREQUEST_H

#include <AdobeMarketingMobileCore/AdobeMarketingMobileCore.h>
#include "TargetObject.h"
#include <string>
#include <functional>

namespace AdobeMarketingMobile {

    class TargetRequestSerializer;
    class TargetRequest : public TargetObject {
    public:
        using Serializer = TargetRequestSerializer;
        TargetRequest(const std::string& name,
                      const std::string& default_content,
                      const std::map<std::string, std::shared_ptr<Variant>>& mbox_params,
                      const std::map<std::string, std::shared_ptr<Variant>>& product_params,
                      const std::map<std::string, std::shared_ptr<Variant>>& order_params,
                      const std::function<void(const std::string&)>& content_callback);

        /**
         * @return the default content that was configure for current request
         */
        const std::string& GetDefaultContent() const;

        /**
         * @return the callback function that was set for the content
         */
        const std::function<void(const std::string&)>& GetContentCallback() const;

        /**
         * @return the event pair id that was set for current target request for returning the content
         */
        const std::string GetResponsePairId() const;

        /**
         * Sets the response pair id for current target request which will be used to return the content
         */
        void SetResponsePairId(const std::string& response_pair_id);

    private:
        std::string default_content_;
        std::function<void(const std::string&)> content_callback_;
        std::string response_pair_id_;
    };

    /**
     * @brief Serializer for TargetRequest objects
     */
    class TargetRequestSerializer : public Object, public virtual VariantSerializerInterface<TargetRequest> {
    public:
        Expected<std::shared_ptr<TargetRequest>> Deserialize(const Variant& value) const override;
        std::shared_ptr<Variant> Serialize(const TargetRequest& o) const override;
    };

}

#endif /* ADOBEMOBILE_TARGET_TARGETREQUEST_H */
