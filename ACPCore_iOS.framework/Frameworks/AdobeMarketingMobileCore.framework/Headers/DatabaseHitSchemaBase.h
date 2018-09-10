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

#ifndef ADOBEMOBILE_SHARED_DATABASEHITSCHEMABASE_H
#define ADOBEMOBILE_SHARED_DATABASEHITSCHEMABASE_H

#include <chrono>
#include <string>
#include <vector>
#include "DatabaseServiceInterface.h"
#include "Variant.h"

namespace AdobeMarketingMobile {
    class DatabaseHitBase;

    /**
     * DatabaseHitSchemaBase
     *
     * Abstract Base class that should be implemented by any class that will create a new database table
     */
    class DatabaseHitSchemaBase : public Object {

    public:
        /**
         * @returns table_name_
         */
        ADOBE_VIRTUAL_FOR_TESTS std::string GetTableName();

        /**
         * @returns database_name_
         */
        ADOBE_VIRTUAL_FOR_TESTS std::string GetDatabaseName();

        /**
         * @returns column_names_
         */
        ADOBE_VIRTUAL_FOR_TESTS std::vector<std::string> GetColumnNames();

        /**
         * @returns column_data_types_
         */
        ADOBE_VIRTUAL_FOR_TESTS std::vector<DatabaseInterface::ColumnDataType> GetColumnDataTypes();

        /**
         * @returns column_constraints_
         */
        ADOBE_VIRTUAL_FOR_TESTS std::vector<std::vector<DatabaseInterface::ColumnConstraint>> GetColumnConstraints();

        /**
         * GenerateHit must be implemented by classes that implement DatabaseHitSchemaInterface.
         * This method returns a DatabaseHit object generated off the provided QueryResult parameter.
         */
        virtual std::shared_ptr<DatabaseHitBase> GenerateHitBase(const std::shared_ptr<QueryResultInterface>& query_result) = 0;

        /**
         * GenerateDataMap must be implemented by classes that implement DatabaseHitSchemaInterface.
         * This method returns a map of string-variants generated off the provided DatabaseHit parameter.
         */
        virtual std::map<std::string, std::shared_ptr<Variant>> GenerateDataMapBase(const std::shared_ptr<DatabaseHitBase>& hit)
                = 0;

    protected:
        /**
         * Constructor.
         * For use by subclasses.
         */
        DatabaseHitSchemaBase();

        /**
         * table_name_ name of the database table represented by this class
         */
        std::string table_name_;

        /**
         * database_name_ name of the database file to be created
         */
        std::string database_name_;

        /**
         * column_names_ is a vector of strings defining the names for the database columns
         * represented by this class
         */
        std::vector<std::string> column_names_;

        /**
         * column_data_types_ is a vector of data types, in order, for the database columns
         * represented by this class
         */
        std::vector<DatabaseInterface::ColumnDataType> column_data_types_;

        /**
         * column_constraints_ is a vector of vectors, representing column contraints for each column
         * represented by this class
         */
        std::vector<std::vector<DatabaseInterface::ColumnConstraint>> column_constraints_;
    };
}

#endif /* ADOBEMOBILE_SHARED_DATABASEHITSCHEMABASE_H */

