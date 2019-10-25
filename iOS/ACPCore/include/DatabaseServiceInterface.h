/*
Copyright 2018 Adobe. All rights reserved.
This file is licensed to you under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License. You may obtain a copy
of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under
the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR REPRESENTATIONS
OF ANY KIND, either express or implied. See the License for the specific language
governing permissions and limitations under the License.
*/

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
         * Create a table if it doesn't exist, does not initalize columns with default values
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
        virtual bool Delete(const std::string& table,
                            const std::string& where_clause,
                            const std::vector<std::string>& where_args) = 0;

        /**
         * Delete a table in the Database
         *
         * @param table name of the table to delete
         * @return bool indicating whether the delete operation was successful
         * @throw ErrorCodes::DATABASE_OPEN_ERROR if database cannot open, or ErrorCodes::DATABASE_QUERY_EXEC_ERROR if query is not executable.
         */
        virtual bool DeleteTable(const std::string& table) = 0;

        /**
         * Close this database
         */
        virtual void Close() = 0;

        /**
         * Allowed database locks
         */
        enum class TransactionType : int32_t {
            DEFERRED = 0,
            IMMEDIATE,
            EXCLUSIVE
        };

        const std::map<TransactionType, std::string> TRANSACTION_TYPE_STRING_MAP = {{TransactionType::DEFERRED, "DEFERRED"}, {TransactionType::IMMEDIATE, "IMMEDIATE"}, {TransactionType::EXCLUSIVE, "EXCLUSIVE"}};

        /**
         * If the database is in an unrecoverable state, attempt to preserve the data by migrating to the new schema
         *
         * @param table_name name of the table to be preserved
         * @param column_names column names of the new schema
         * @param column_data_types column data types of the new schema
         * @param column_constraints the column constraints of the new schema
         */
        virtual bool AttemptDatabaseMigration(const std::string& table_name,
                                              const std::vector<std::string>& column_names,
                                              const std::vector<ColumnDataType>& column_data_types,
                                              const std::vector<std::vector<ColumnConstraint>>& column_constraints) = 0;


        /**
         * Returns true if the table contains the column
         *
         * @param table_name the name of the table
         * @param column_name name of the column to check against
         * @return true if column_name is contained in the table
         */
        virtual bool TableContainsColumn(const std::string table_name, const std::string column_name) = 0;

        /**
         * Returns a vector containing all the column names for the table
         *
         * @param table_name the name of the table
         * @return a vector containing all the columns in the table
         */
        virtual std::vector<std::string> GetColumnNamesForTable(const std::string table_name) = 0;

        /**
         * Returns a vector containing the name of columns present in column_names and other_table_name
         *
         * @param column_names the column names of a table
         * @param other_table_name the other table to be compared against
         * @return a vector containing a list of column names contained in both column_names and other_table_name
         */
        virtual std::vector<std::string> UnionColumns(const std::vector<std::string>& column_names,
                const std::string other_table_name) = 0;


        /**
         * Renames the given table with the new table name
         *
         * @param table_name the name of the table to be renamed
         * @param new_table_name new name for the table
         * @return true if successful, false otherwise
         */
        virtual bool RenameTable(const std::string table_name, const std::string new_table_name) = 0;


        /**
         * Copys columns from one table and inserts them into another
         *
         * @param from_table_name the table to copy from
         * @param to_table_name table to copy into
         * @param column_names the columns in which to copy
         * @return true if successful, false otherwise
         */
        virtual bool CopyColumnsFromTableToTable(const std::string from_table_name, const std::string to_table_name,
                const std::vector<std::string> column_names) = 0;


        /**
         * Begins a transaction on the database
         *
         * @param transaction_type The type of lock to be used for the transaction
         * @return true if sucessful, false otherwise
         */
        virtual bool BeginTransaction(const TransactionType transaction_type) = 0;


        /**
         * Ends the current transaction
         *
         * @return true if sucessful, false otherwise
         */
        virtual bool EndTransaction() = 0;

        /**
         * Create a table if it doesn't exist
         *
         * @param name the table name
         * @param column_names list of column names
         * @param column_data_types list of column data types
         * @param column_constraints a list of lists containing column constraints for each table column
         * @param set_columns_default if true, sets columns to a default value
         * @return bool indicating whether the create table operation was successful
         * @throw ErrorCodes::DATABASE_OPEN_ERROR if database cannot open, or ErrorCodes::DATABASE_QUERY_EXEC_ERROR if query is not executable.
         */
        virtual bool CreateTable(const std::string& name, const std::vector<std::string>& column_names,
                                 const std::vector<ColumnDataType>& column_data_types,
                                 const std::vector<std::vector<ColumnConstraint>>& column_constraints,
                                 const bool set_columns_default) = 0;

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

