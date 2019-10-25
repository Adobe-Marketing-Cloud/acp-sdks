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

        /**
         * Builds a query string to create table with the given column names, data types and constraints.
         *
         * @param name table name
         * @param column_names list of column names in the table
         * @param column_data_types list of column data types for the table columns
         * @param column_constraints list of column contrainsts for the table columns
         * @param set_columns_default if true, will provide default values for columns
         * @return create table query string
         */
        static std::string PrepareCreateTableQueryString(const std::string& name,
                const std::vector<std::string>& column_names,
                const std::vector<DatabaseInterface::ColumnDataType>& column_data_types,
                const std::vector<std::vector<DatabaseInterface::ColumnConstraint>>& column_constraints,
                const bool set_columns_default);

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
        static const std::map<DatabaseInterface::ColumnDataType, std::string> COLUMN_DATA_TYPE_DEFAULT_MAP;

    };
}
#endif /* ADOBEMOBILE_PLATFORMSHIM_QUERYSTRINGBUILDER_H */
