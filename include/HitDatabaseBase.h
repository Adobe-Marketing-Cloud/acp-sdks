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

#ifndef ADOBEMOBILE_SHARED_HITDATABASEBASE_H
#define ADOBEMOBILE_SHARED_HITDATABASEBASE_H

#include <mutex>

#include "Object.h"
#include "DatabaseHitBase.h"
#include "DatabaseHitSchema.h"
#include "DatabaseServiceInterface.h"

namespace AdobeMarketingMobile {

    enum class DatabaseStatus : int32_t {
        OK = 0,
        FATALERROR
    };

    /*
     * @class HitDatabaseBase
     * Base class for hit data base management
     */
    class HitDatabaseBase : public Object {
        friend class HitQueueBaseMethods;  ///< for testing

    public:
        HitDatabaseBase() {}                ///< makes mocking easier

        /**
         * Opens the database with \p database_name_, if that exists or creates a new one if doesn't exist.
         * Logs an error if create/open operation failed.
         *
         * @return true if operation succeeds, false otherwise
         */
        virtual bool OpenOrCreateDatabase();

        /**
         * Create a table in the database with \p table_name_.
         * Logs an error if create/open operation failed.
         *
         * @return true if operation succeeds, false otherwise
         */
        virtual bool InitializeDatabase() = 0;

        virtual void PostReset();

        /**
         * Delete all items in the database table.
         * Logs an error if create/open operation failed.
         *
         * @return true if operation succeeds, false otherwise
         */
        virtual bool DeleteAllHits();

        /**
         * Delete the database table.
         * Logs an error if create/open operation failed.
         *
         * @return true if operation succeeds, false otherwise
         */
        virtual bool DeleteTable();

        /**
         * Attempts to remove the hit with given identifier from database. It resets the database and returns false if the
         * deleteAllHits operation fails, true otherwise.
         *
         * @param identifier the ID of the hit that we want to remove
         * @return true if operation succeeds, false otherwise
         */
        virtual bool DeleteHitWithIdentifier(const std::string& identifier);

        /**
         * Returns the count of current hits in database. It logs an error message when query fails
         *
         * @return number of rows if table exists, 0 if no entries or query has failed
         */
        virtual int32_t GetSize();

        /**
         * Returns the number of hits in the database that match the query.
         *
         * If the database query fails, this method logs an error message and returns 0.
         *
         * @param query the Query object used to query the database
         * @return number of rows match the query in the table
         */
        virtual int32_t GetSize(const std::shared_ptr<Query>& query);

        /**
         * Resets database (usually as a result of an unrecoverable exception) - it will remove the existing database and create
         * a new one with the same filename and structure
         */
        virtual void Reset();

        /**
         * Determines if we need to migrate database schemas, if so will migrate to new schema
         *
         * @return true if no migration is needed or if migration was successful, false otherwise
         */
        bool MigrateDatabaseIfNeeded(const std::shared_ptr<DatabaseHitSchemaBase> database_hit_schema);

    protected:
        std::string table_name_;        ///<  hit database table name

        std::shared_ptr<DatabaseInterface> database_;       ///< DatabaseInterface

        DatabaseStatus database_status_ = DatabaseStatus::OK;   ///< DatabaseStatus for database processing after throwing

        /**
         * @protected
         * @brief Constucts a HitDatabaseBase with database_service and database_hit_schema
         */
        explicit HitDatabaseBase(const std::shared_ptr<DatabaseServiceInterface>& database_service,
                                 const std::shared_ptr<DatabaseHitSchemaBase>& database_hit_schema);


    private:
        static const std::string LOG_PREFIX;    ///< Logging prefix

        std::shared_ptr<DatabaseServiceInterface> database_service_;    ///< DatabaseServiceInterface

        std::string database_name_;     ///< hit database name

        /**
         * @private
         * @brief Close the database
         */
        void CloseDatabase();


        /**
         * Attempts to migrate the old database schema to the current schema while preserving hits
         *
         * @return true if successful, false otherwise
         */
        bool MigrateDatabase(const std::shared_ptr<DatabaseHitSchemaBase> hit_schema);

        /**
         * Retruns true if the current hit schema is the same as the schema present in the SQL table
         *
         * @return True if the schemas match, false otherwise
         */
        bool HitSchemaMatchesExistingTableSchema(const std::shared_ptr<DatabaseHitSchemaBase> hit_schema);
    };
}

#endif /* ADOBEMOBILE_SHARED_HITDATABASEBASE_H */
