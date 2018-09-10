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

#ifndef ADOBEMOBILE_SHARED_DATABASEHITSCHEMA_H
#define ADOBEMOBILE_SHARED_DATABASEHITSCHEMA_H

#include <memory>
#include "DatabaseHitSchemaBase.h"
#include "DatabaseHitBase.h"
#include "Variant.h"

namespace AdobeMarketingMobile {

    /**
     * DatabaseHitSchema
     *
     * Abstract Base class that should be implemented by any class that will create a new database table
     */
    template<class TDatabaseHit>
    class DatabaseHitSchema : public DatabaseHitSchemaBase {
        // If you get an error on the following line, you need to make sure that TDatabaseHit is a type derived from DatabaseHitBase.
        static_assert(std::is_base_of<DatabaseHitBase, TDatabaseHit>::value,
                      "Type of TDatabaseHit must be derived from DatabaseHitBase.");

    public:
        /**
         * GenerateHit must be implemented by classes that implement DatabaseHitSchema.
         *
         * @return a DatabaseHitBase object generated off the provided QueryResult parameter.
         */
        virtual std::shared_ptr<TDatabaseHit> GenerateHit(const std::shared_ptr<QueryResultInterface>& query_result) = 0;

        /**
         * Overrides DatabaseHitSchemaBase::GenerateHitBase to call GenerateHit and return the proper data type
         */
        std::shared_ptr<DatabaseHitBase> GenerateHitBase(const std::shared_ptr<QueryResultInterface>& query_result) override;

        /**
         * GenerateDataMap must be implemented by classes that implement DatabaseHitSchema.
         *
         * @return a DatabaseHitBase object generated off the provided QueryResult parameter.
         */
        virtual std::map<std::string, std::shared_ptr<Variant>> GenerateDataMap(const std::shared_ptr<TDatabaseHit>& hit) = 0;

        /**
         * Overrides DatabaseHitSchemaBase::GenerateDataMapBase to call GenerateDataMap and accept the proper data type parameter
         */
        std::map<std::string, std::shared_ptr<Variant>> GenerateDataMapBase(const std::shared_ptr<DatabaseHitBase>& hit)
                override;

    protected:
        /**
         * Constructor.
         * For use by subclasses.
         */
        DatabaseHitSchema();
    };
}

/////////////////////////////////
// template/inline definitions //
/////////////////////////////////
namespace AdobeMarketingMobile {
    template<class TDatabaseHit>
    DatabaseHitSchema<TDatabaseHit>::DatabaseHitSchema() {}

    template<class TDatabaseHit>
    std::shared_ptr<DatabaseHitBase>
    DatabaseHitSchema<TDatabaseHit>::GenerateHitBase(const std::shared_ptr<QueryResultInterface>& query_result) {
        return GenerateHit(query_result);
    }

    template<class TDatabaseHit>
    std::map<std::string, std::shared_ptr<Variant>>
    DatabaseHitSchema<TDatabaseHit>::GenerateDataMapBase(const std::shared_ptr<DatabaseHitBase>& hit) {
        return GenerateDataMap(std::dynamic_pointer_cast<TDatabaseHit>(hit));
    }
}

#endif /* ADOBEMOBILE_SHARED_DATABASEHITSCHEMA_H */
