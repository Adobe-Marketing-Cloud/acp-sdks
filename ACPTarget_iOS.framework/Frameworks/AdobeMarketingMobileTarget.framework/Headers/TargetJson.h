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

#ifndef ADOBEMOBILE_TARGET_TARGETJSON_H
#define ADOBEMOBILE_TARGET_TARGETJSON_H

#include <string>
#include <vector>

namespace AdobeMarketingMobile {

    class TargetJson {
    public:
        static const std::string CLIENT;
        static const std::string ID;
        static const std::string ID_TNT_ID;
        static const std::string ID_THIRD_PARTY_ID;
        static const std::string ID_MARKETING_CLOUD_VISITOR_ID;
        static const std::string ID_CUSTOMER_IDS;
        static const std::string AAM_PARAMETERS;
        static const std::string ENVIRONMENT_ID;
        static const std::string CONTENT_AS_JSON;
        static const std::string PREFETCH_MBOXES;
        static const std::string PREFETCH_MBOX_RESPONSES;
        static const std::string MBOX_RESPONSES;
        static const std::string PROFILE_PARAMETERS;
        static const std::string VISITED_MBOXES;
        static const std::string MBOXES;
        static const std::string EDGE_HOST;
        static const std::string ERROR_TYPE;
        static const std::string NOTIFICATION_ERRORS;
        static const std::string ERROR_CODE;
        static const std::string ERROR_CODE_TIME_OUT;
        static const std::string NOTIFICATION;
        static const std::vector<std::string> PREFETCH_NOTIFICATION_KEYS;

        class CustomerIds {
        public:
            static const std::string ID;
            static const std::string INTEGRATION_CODE;
            static const std::string AUTHENTICATION_STATE;

        private:
            CustomerIds() = delete;
        };

        class AAMParameters {
        public:
            static const std::string BLOB;
            static const std::string UUID;
            static const std::string LOCATION_HINT;
            static const std::string DPID;
            static const std::string DP_USER_ID;
        private:
            AAMParameters() = delete;
        };

        class Mbox {
        public:
            static const std::string TIMESTAMP;
            static const std::string MBOX;
            static const std::string PARAMETERS;
            static const std::string INDEX_ID;
            static const std::string PRODUCT;
            static const std::string ORDER;
            static const std::string EVENT_TOKENS;
            static const std::string CONTENT;
            static const std::string ERROR_TYPE;
            static const std::string A4T;
            static const std::string PROFILE_SCRIPT_TOKEN;

            class Product {
            public:
                static const std::string ID;
                static const std::string CATEGORY_ID;
            private:
                Product() = delete;
            };

            class Order {
            public:
                static const std::string ID ;
                static const std::string TOTAL;
                static const std::string PURCHASED_PRODUCT_IDS;
            private:
                Order() = delete;
            };

        private:
            Mbox() = delete;
        };

    private:
        TargetJson() = delete;
    };
}

#endif /* ADOBEMOBILE_TARGET_TARGETJSON_H */
