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

#ifndef ADOBEMOBILE_PLATFORMSHIM_QUERYSTRINGBUILDER_H
#define ADOBEMOBILE_PLATFORMSHIM_QUERYSTRINGBUILDER_H

#include <vector>
#include "Object.h"
#include "DatabaseServiceInterface.h"

namespace AdobeMarketingMobile {

    class QueryStringBuilder : public Object {
    public:
        /**
         * Builds a query string to create table with the given column names, data types and constraints.
         *
         * @param name table name
         * @param column_names list of column names in the table
         * @param column_data_types list of column data types for the table columns
         * @param column_constraints list of column contrainsts for the table columns
         * @return create table query string
         */
        static std::string PrepareCreateTableQueryString(const std::string& name,
                const std::vector<std::string>& column_names,
                const std::vector<DatabaseInterface::ColumnDataType>& column_data_types,
                const std::vector<std::vector<DatabaseInterface::ColumnConstraint>>& column_constraints);

    private:
        QueryStringBuilder(); ///< Private Constructor

        /**
         * @private
         * Fetches the list of column data types.
         *
         * @param column_data_types list of column data types
         * @return column data types list with data types expressed as string
         */
        static std::vector<std::string> GetColumnDataTypes(const std::vector<DatabaseInterface::ColumnDataType>&
                column_data_types);

        /**
         * @private
         * Fetches the list of column constraints.
         *
         * @param column_constraints list of column constraints
         * @return column constraints list with constraints expressed as string
         */
        static std::vector<std::string> GetColumnConstraints(const std::vector<std::vector<DatabaseInterface::ColumnConstraint>>&
                column_constraints);

        static const std::map<DatabaseInterface::ColumnDataType, std::string> COLUMN_DATA_TYPE_MAP;
        static const std::map<DatabaseInterface::ColumnConstraint, std::string> COLUMN_CONSTRAINT_MAP;

    };
}
#endif /* ADOBEMOBILE_PLATFORMSHIM_QUERYSTRINGBUILDER_H */
