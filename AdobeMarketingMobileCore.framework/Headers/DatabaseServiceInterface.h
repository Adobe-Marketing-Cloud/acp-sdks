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

#ifndef ADOBEMOBILE_PLATFORMSHIM_DATABASESERVICEINTERFACE_H
#define ADOBEMOBILE_PLATFORMSHIM_DATABASESERVICEINTERFACE_H

#include <map>
#include <memory>
#include <vector>
#include <string>
#include "ObjectInterface.h"
#include "Variant.h"

namespace AdobeMarketingMobile {

    namespace ErrorCodes {
        // Platform shim errors
        constexpr static const char* DATABASE_OPEN_ERROR = "database.open_error"; ///< Database open error occurred.
        constexpr static const char* DATABASE_QUERY_EXEC_ERROR =
                    "database.query_exec_error"; ///< A database query execution error occurred.
        constexpr static const char* DATABASE_QUERYRESULT_INDEX_ERROR =
                    "database.queryresult_index_error"; ///< Error occurred in the index of the query result.
        constexpr static const char* DATABASE_QUERYRESULT_ALREADY_CLOSED =
                    "database.queryresult_already_closed"; ///< Query result is already closed.
    }

    /**
     * Interface defining methods for reading query results from a database
     */
    class QueryResultInterface : public virtual ObjectInterface {
    public:
        /**
         * Get total number of rows in the result
         *
         * @return int32_t number of rows in the QueryResult
         */
        virtual int32_t GetCount() const = 0;

        /**
         * Get the value of the requested column as an integer
         *
         * @param column_index zero-based index of the target column
         * @return int32_t the value of the column as an int32_t
         * @throws DATABASE_QUERYRESULT_ALREADY_CLOSED if the QueryResult is already closed, or DATABASE_QUERYRESULT_INDEX_ERROR if index is not available
         */
        virtual int32_t GetInt(uint32_t column_index) const = 0;

        /**
         * Get the value of the requested column as a double
         *
         * @param column_index zero-based index of the target column
         * @return double the value of the column as a double
         * @throws DATABASE_QUERYRESULT_ALREADY_CLOSED if the QueryResult is already closed, or DATABASE_QUERYRESULT_INDEX_ERROR if index is not available
         */
        virtual double GetDouble(uint32_t column_index) const = 0;

        /**
         * Get the value of the requested column as a float
         *
         * @param column_index zero-based index of the target column
         * @return float the value of the column as a float
         * @throws DATABASE_QUERYRESULT_ALREADY_CLOSED if the QueryResult is already closed, or DATABASE_QUERYRESULT_INDEX_ERROR if index is not available
         */
        virtual float GetFloat(uint32_t column_index) const = 0;

        /**
         * Get the value of the requested column as a long
         *
         * @param column_index zero-based index of the target column
         * @return the value of the column as int64_t
         * @throws DATABASE_QUERYRESULT_ALREADY_CLOSED if the QueryResult is already closed, or DATABASE_QUERYRESULT_INDEX_ERROR if index is not available
         */
        virtual int64_t GetLong(uint32_t column_index) const = 0;

        /**
         * Get the value of the requested column as a string
         *
         * @param column_index zero-based index of the target column
         * @return std::string the value of the column as a string
         * @throws DATABASE_QUERYRESULT_ALREADY_CLOSED if the QueryResult is already closed, or DATABASE_QUERYRESULT_INDEX_ERROR if index is not available
         */
        virtual std::string GetString(uint32_t column_index) const = 0;

        /**
         * Check if the value of the requested column is null
         *
         * @param column_index zero-based index of the target column
         * @return bool indicating whether the column value is null
         * @throws DATABASE_QUERYRESULT_ALREADY_CLOSED if the QueryResult is already closed, or DATABASE_QUERYRESULT_INDEX_ERROR if index is not available
         */
        virtual bool IsNull(uint32_t column_index) const = 0;

        /**
         * Move to the first row in the QueryResult
         *
         * @return bool indicating whether the move was successful
         * @throws DATABASE_QUERYRESULT_ALREADY_CLOSED if the QueryResult is already closed, or DATABASE_QUERYRESULT_INDEX_ERROR if index is not available
         */
        virtual bool MoveToFirst() = 0;

        /**
         * Move to the last row in the QueryResult
         *
         * @return bool indicating whether the move was successful
         * @throws DATABASE_QUERYRESULT_ALREADY_CLOSED if the QueryResult is already closed, or DATABASE_QUERYRESULT_INDEX_ERROR if index is not available
         */
        virtual bool MoveToLast() = 0;

        /**
         * Move to the next row in the QueryResult
         *
         * @return bool indicating whether the move was successful
         * @throws DATABASE_QUERYRESULT_ALREADY_CLOSED if the QueryResult is already closed, or DATABASE_QUERYRESULT_INDEX_ERROR if index is not available
         */
        virtual bool MoveToNext() = 0;

        /**
         * Close this QueryResult
         */
        virtual void Close() = 0;

    };
    /**
     * Interface defining relational database operations
     */

    class Query;
    class DatabaseInterface : public virtual ObjectInterface {
    public:
        /**
         * Allowed data types for database columns
         */
        enum class ColumnDataType : int32_t {
            INTEGER = 0,
            REAL,
            TEXT
        };

        /**
         * Allowed constraints for database columns
         */
        enum class ColumnConstraint : int32_t {
            NOT_NULL = 0,
            UNIQUE,
            PRIMARY_KEY,
            AUTOINCREMENT
        };

        /**
         * Create a table if it doesn't exist
         *
         * @param name the table name
         * @param column_names list of column names
         * @param column_data_types list of column data types
         * @param column_constraints a list of lists containing column constraints for each table column
         * @return bool indicating whether the create table operation was successful
         * @throw ErrorCodes::DATABASE_OPEN_ERROR if database cannot open, or ErrorCodes::DATABASE_QUERY_EXEC_ERROR if query is not executable.
         */
        virtual bool CreateTable(const std::string& name, const std::vector<std::string>& column_names,
                                 const std::vector<ColumnDataType>& column_data_types,
                                 const std::vector<std::vector<ColumnConstraint>>& column_constraints) = 0;

        /**
         * Insert a row into a table in the database
         *
         * @param table name of the table to insert the row into
         * @param values map containing the initial column values for the row. The keys should be the column names and the values the column values.
         * @return bool indicating whether the insert operation was successful
         * @throw ErrorCodes::DATABASE_OPEN_ERROR if database cannot open, or ErrorCodes::DATABASE_QUERY_EXEC_ERROR if query is not executable.
         */
        virtual bool Insert(const std::string& table, const std::map<std::string, std::shared_ptr<Variant>>& values) = 0;

        /**
         * Query a table in the database
         *
         * @param query the query to execute
         * @return QueryResult the result of this query, positioned at the first row
         */
        virtual std::shared_ptr<QueryResultInterface> RunQuery(const std::shared_ptr<Query>& query) = 0;

        /**
         * Update rows for a table in the database
         *
         * @param table name of the table to update
         * @param values a map from column names to new column values. Empty string is a valid value.
         * @param where_clause the optional WHERE clause to apply when updating. Passing empty string will update all rows
         * @param where_args A list of arguments for where clause. You may include ?s in the where clause, which will be replaced by the values from where_args. The values will be bound as strings
         * @return bool indicating whether the update operation was successful
         * @throw ErrorCodes::DATABASE_OPEN_ERROR if database cannot open, or ErrorCodes::DATABASE_QUERY_EXEC_ERROR if query is not executable.
         */
        virtual bool Update(const std::string& table,
                            const std::map<std::string, std::shared_ptr<Variant>>& values,
                            const std::string& where_clause,
                            const std::vector<std::string>& where_args) = 0;

        /**
         * Delete rows from a table in the Database
         *
         * @param table name of the table to delete rows from
         * @param where_clause the optional WHERE clause to apply when deleting. Passing empty string will delete all rows
         * @param where_args A list of arguments for where clause. You may include ?s in the where clause, which will be replaced by the values from where_args. The values will be bound as strings
         * @return bool indicating whether the delete operation was successful
         * @throw ErrorCodes::DATABASE_OPEN_ERROR if database cannot open, or ErrorCodes::DATABASE_QUERY_EXEC_ERROR if query is not executable.
         */
        virtual bool Delete (const std::string& table,
                             const std::string& where_clause,
                             const std::vector<std::string>& where_args) = 0;

        /**
         * Delete a table in the Database
         *
         * @param table name of the table to delete
         * @return bool indicating whether the delete operation was successful
         * @throw ErrorCodes::DATABASE_OPEN_ERROR if database cannot open, or ErrorCodes::DATABASE_QUERY_EXEC_ERROR if query is not executable.
         */
        virtual bool DeleteTable (const std::string& table) = 0;

        /**
         * Close this database
         */
        virtual void Close() = 0;

    };

    class DatabaseServiceInterface : public virtual ObjectInterface {
    public:
        /**
         * Opens a database if it exists, otherwise creates a new one with the specified name.
         *
         * @param db_name the database name
         * @return a Database instance, or null if error occurs
         */
        virtual std::shared_ptr<DatabaseInterface> OpenDatabase(const std::string& db_name) = 0;

        /**
         * Delete database if it exists
         *
         * @param db_name the database name
         * @return bool indicating whether the database file delete operation was successful
         */
        virtual bool DeleteDatabase(const std::string& db_name) = 0;
    };

} //namespace
#endif /* ADOBEMOBILE_PLATFORMSHIM_DATABASESERVICEINTERFACE_H */

