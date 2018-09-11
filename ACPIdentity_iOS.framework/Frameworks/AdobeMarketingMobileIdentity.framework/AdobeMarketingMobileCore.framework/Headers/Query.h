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

#ifndef ADOBEMOBILE_PLATFORMSHIM_QUERY_H
#define ADOBEMOBILE_PLATFORMSHIM_QUERY_H

#include <memory>
#include <string>
#include <vector>
#include "Object.h"

namespace AdobeMarketingMobile {

    class Query;

    /**
     * QueryBuilder class is POD type and is used to build a Query object.
     */
    class QueryBuilder {
    public:
        /**
         * Create a QueryBuilder object with required Query parameters
         *
         * @param table The table name to compile the query against
         * @param columns A list of columns to return. Passing empty vector will return all columns
         */
        explicit QueryBuilder(const std::string& table, const std::vector<std::string>& columns);

        QueryBuilder(const QueryBuilder&) = delete;                 ///< delete default copy constructor
        QueryBuilder& operator=(const QueryBuilder&) = delete;      ///< delete assignment operator
        QueryBuilder(QueryBuilder&&) = delete;                      ///< delete move constructor
        QueryBuilder&& operator=(QueryBuilder&&) = delete;          ///< delete move assignment operator

        /**
         * Query selection
         *
         * @param selection A filter declaring which rows to return, formatted as an SQL WHERE clause (excluding the WHERE itself). Passing empty string will return all rows for the given table
         * @param selection_args A list of selection args. You may include ?s in selection, which will be replaced by the values from selection_args, in order that they appear in the selection. The values will be bound as std::string
         * @return QueryBuilder this QueryBuilder object
         */
        QueryBuilder& Selection(const std::string& selection, const std::vector<std::string>& selection_args);

        /**
         * Group query result
         *
         * @param group_by A filter declaring how to group rows, formatted as an SQL GROUP BY clause (excluding the GROUP BY itself). Passing empty string will cause the rows to not be grouped
         * @return QueryBuilder this QueryBuilder object
         */
        QueryBuilder& GroupBy(const std::string& group_by);

        /**
         * Having clause for this query
         *
         * @param having A filter declaring which row groups to include in the cursor, if row grouping is being used, formatted as an SQL HAVING clause (excluding the HAVING itself). Passing empty string will cause all row groups to be included, and is required when row grouping is not being used
         * @return QueryBuilder this QueryBuilder object
         */
        QueryBuilder& Having(const std::string& having);

        /**
         * Order result rows for this query's result
         *
         * @param order_by Indicates how to order the rows, formatted as an SQL ORDER BY clause (excluding the ORDER BY itself). Passing empty string will use the default sort order, which may be unordered
         * @return QueryBuilder this QueryBuilder object
         */
        QueryBuilder& OrderBy(const std::string& order_by);

        /**
         * Limit the number of rows in the query result
         *
         * @param limit Limits the number of rows returned by the query, formatted as LIMIT clause. Passing empty string denotes no LIMIT clause
         * @return QueryBuilder this QueryBuilder object
         */
        QueryBuilder& Limit(const std::string& limit);

        /**
         * Build the Query object
         *
         * @return the Query object
         */
        std::shared_ptr<Query> Build();

    private:
        void ThrowIfAlreadyBuilt();

        std::shared_ptr<Query> query_;
        bool did_build_;

    };

    class Query : public Object {
        friend class QueryBuilder;
    public:
        /**
         * @return table name in this query
         */
        std::string GetTable() const;

        /**
         * @return table column names in this query
         */
        std::vector<std::string> GetColumns() const;

        /**
         * @return SELECT clause in this query
         */
        std::string GetSelection() const;

        /**
         * @return SELECT clause arguments in this query
         */
        std::vector<std::string> GetSelectionArgs() const;

        /**
         * @return GROUP BY clause in this query
         */
        std::string GetGroupBy() const;

        /**
         * @return HAVING clause in this query
         */
        std::string GetHaving() const;

        /**
         * @return ORDER BY clause in this query
         */
        std::string GetOrderBy() const;

        /**
         * @return LIMIT clause in this query. It can be used to constrain the number of rows returned.
         */
        std::string GetLimit() const;

    private:
        /**
         * @private
         * Constructor. Intended for use by QueryBuilder.
         */
        Query() {}

        std::string table_;
        std::vector<std::string> columns_;
        std::string selection_;
        std::vector<std::string> selection_args_;
        std::string group_by_;
        std::string having_;
        std::string order_by_;
        std::string limit_;

    };

} // namespace
#endif /* ADOBEMOBILE_PLATFORMSHIM_QUERY_H */
