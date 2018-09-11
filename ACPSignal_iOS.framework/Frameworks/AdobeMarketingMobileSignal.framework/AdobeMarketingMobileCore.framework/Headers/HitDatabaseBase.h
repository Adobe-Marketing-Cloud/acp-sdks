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
         * Resets database (usually as a result of an unrecoverable exception) - it will remove the existing database and create
         * a new one with the same filename and structure
         */
        virtual void Reset();

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
    };
}

#endif /* ADOBEMOBILE_SHARED_HITDATABASEBASE_H */
