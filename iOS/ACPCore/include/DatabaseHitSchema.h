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
