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
 **************************************************************************/


#ifndef ADOBEMOBILE_IDENTITY_DATABASE_HIT_SCHEMA_H
#define ADOBEMOBILE_IDENTITY_DATABASE_HIT_SCHEMA_H

#include "Identity.h"

namespace AdobeMarketingMobile {
    class IdentityDatabaseHit;

    class IdentityDatabaseHitSchema: public DatabaseHitSchema<IdentityDatabaseHit> {
    public:
        IdentityDatabaseHitSchema();
        std::shared_ptr<IdentityDatabaseHit> GenerateHit(const std::shared_ptr<QueryResultInterface>& query_result) override;
        std::map<std::string, std::shared_ptr<Variant>> GenerateDataMap(const std::shared_ptr<IdentityDatabaseHit>& hit)
                override;
        std::map<std::string, std::shared_ptr<Variant>> GenerateUpdateValuesForResetEventNumberAndPairId();

        static const std::string LOG_TAG;
        static const std::string TABLE_NAME;
        static const std::string DATABASE_FILE_NAME;

        static const int32_t COL_INDEX_REQUESTS_ID;
        static const int32_t COL_INDEX_REQUESTS_URL;
        static const int32_t COL_INDEX_REQUESTS_TIMESTAMP;
        static const int32_t COL_INDEX_REQUESTS_PAIR_ID;
        static const int32_t COL_INDEX_REQUESTS_EVENT_NUMBER;
        static const int32_t COL_INDEX_REQUESTS_SSL;

        static const std::string COL_REQUESTS_ID;
        static const std::string COL_REQUESTS_URL;
        static const std::string COL_REQUESTS_CONFIG_SSL;
        static const std::string COL_REQUESTS_PAIR_ID;
        static const std::string COL_REQUESTS_EVENT_NUMBER;
        static const std::string COL_REQUESTS_TIMESTAMP;
    };


}

#endif /* ADOBEMOBILE_IDENTITY_DATABASE_HIT_SCHEMA_H */
